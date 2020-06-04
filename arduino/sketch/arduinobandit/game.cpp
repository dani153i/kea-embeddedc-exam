#include "game.h"

void timer1_counter_reset_activate();
unsigned long interruptTimes[WHEELS_MAX];
volatile unsigned char firstInterrupt = 0x01;

void btn_click();
void game_play();

void (*bandit_print_ptr)(int, int, int);
Bandit *banditPtr = NULL;

void game_setup()
{
  banditPtr = malloc(sizeof(Bandit));
  *banditPtr = bandit_new();

  if (banditPtr == NULL) {
    exit(1);
  }
  
  banditPtr->banditPlayer->spins_available = 55;

  //bandit_print_ptr = &banditgui_print_bandit;
  bandit_print_ptr = &serial_bandit_display;

  pinMode(PIN_BTN_A, INPUT_PULLUP);

  // Reset Timer1 Control Reg A
  TCCR1A = 0;
  
  // Set prescaler of 256
  TCCR1B = 4; // (5th prescaler) -> 1 * 8 * 8 * 4 = 256 (4 steps)

  // Reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp_min;
}




void game_run()
{
  uint8_t input = 0;
  while(true) {
    input = input_serial_menu_display(MAINMENU, MAINMENU_MAX);
    switch(input)
    {
      case 1:
        banditPtr->banditPlayer->spins_available = input_serial_int_range(1, 100, "input tokens 1-100: ");
        game_play();
        input_serial_wait("Send anything through Serial to continue");
        break;
      case 2:
        for (int i=0; i < banditPtr->spinResults_len; i++) {
          for (int w=0; w < WHEELS_MAX; w++) {
            Serial.print(banditPtr->spinResults[i].cursor_position[w]);
            Serial.print(" ");
          }
          Serial.print("  - winnings - ");
          Serial.print(bandit_calculate_winnings(&(banditPtr->spinResults[i])));
          Serial.print("\n\r");
        }
        input_serial_wait("Send anything through Serial to continue");
        break;
    }
  }
  free(banditPtr->banditPlayer);
  free(banditPtr->cursor_position);
  free(banditPtr->spinning_wheels);
  free(banditPtr);
  free(banditPtr);
}


void game_play()
{
  int wheel;
  for (  wheel=0; wheel  < WHEELS_MAX; wheel++ ) {
    banditPtr->cursor_position[wheel] = 0;
  }

  // display bandit to serial
  (bandit_print_ptr)(banditPtr, 3, -1);
  //serial_bandit_display(banditPtr, 3, -1);
  
  while (banditPtr->banditPlayer->spins_available > 0)
  {
    /* set interrupt time for wheels and set them spinning */
    for (  wheel=0; wheel  < WHEELS_MAX; wheel++ ) {
      // set interrupt time for wheel
      interruptTimes[wheel] = get_random_long(62500, 187500);
      // set wheel spinning
      banditPtr->spinning_wheels[wheel] = 1;
    }
    
    // set bandit spinning
    banditPtr->spinning = 1;

    // wait for button click
    input_pin_wait(PIN_BTN_A, HIGH);
    
    // subtract the used spin
    banditPtr->banditPlayer->spins_available -= 1;

    // Enable Timer/Counter1 Output Compare Match A Interrupt
    TIMSK1 = (1 << OCIE1A);
    
    while (banditPtr->spinning == 1)
    {
      // turn bandit wheels
      bandit_turn_wheels(banditPtr);
      // display bandit to serial
      serial_bandit_display(banditPtr, 3, -1);
      delay(150);
    }

    int spins_available_tmp = banditPtr->banditPlayer->spins_available;

    // let bandit handle point assignment
    bandit_assign_spin_result(banditPtr);

    // if spins_available changed since assignment of spin esult
    if (spins_available_tmp != banditPtr->banditPlayer->spins_available) {
      // display bandit to serial
      (bandit_print_ptr)(banditPtr, 3, -1);
      //serial_bandit_display(banditPtr, 3, -1);
    }
  }
}


ISR(TIMER1_COMPA_vect)
{
  /* disable global interrupts to not stack */
  noInterrupts();
  cli();

  // first interrupt (runs as soon as activated) musts be avoided
  if (firstInterrupt == 0x01)
  {
    firstInterrupt = 0x00;
    OCR1A = interruptTimes[0];
    timer1_counter_reset_activate();
    return;
  }

  /* stop a spinning wheel */
  int wheelsStopped = 0;
  int wheel;
  for ( wheel=0; wheel  < WHEELS_MAX; wheel++ )
  {
    wheelsStopped++;
    if (banditPtr->spinning_wheels[wheel] == 1)
    {
      banditPtr->spinning_wheels[wheel] = 0;
      break;
    }
  }

  /* if all wheels have stopped spinning */
  if (wheelsStopped == WHEELS_MAX)
  {
    /* reset indicator of first interrupt */
    firstInterrupt = 0x01;
    /* set bandit not spinning */
    banditPtr->spinning = 0;
    /* Disable Timer/Counter1 Output Compare Match A Interrupt */
    TIMSK1 = 0;
  } else {
    /* set next interrupt compare value */
    OCR1A = interruptTimes[wheelsStopped];
  }

  timer1_counter_reset_activate();
}

void timer1_counter_reset_activate() {
  /* set timer/counter1 counter 0 */
  TCNT1 = 0;
  /* enable global interrupts */
  interrupts();
  sei();
}
