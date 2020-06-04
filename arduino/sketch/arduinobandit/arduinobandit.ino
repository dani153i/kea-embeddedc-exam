#include "game.h"

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  game_setup();
  
  // Enable global interrupts
  sei();
}

/* main arduino loop*/
void loop()
{
  game_run();
}
