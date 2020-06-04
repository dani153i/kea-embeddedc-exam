#include "serialutil.h"


void serial_clear() {

  Serial.println("\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r");
}

void input_pin_wait(uint8_t pin, uint8_t value)
{
  while (digitalRead(pin) != value) {
    delay(2);
  }
}

/*void serial_print(const char * message) {
  Serial.println(message);
}*/

void input_serial_wait(const char *message) {
  Serial.println(message);
  // while 0 bits in buffer
  while (!Serial.available()) {  }
  Serial.readString();
}

int input_serial_int()
{
  // while 0 bits in buffer
  while (!Serial.available()) { delay(2); }
  return Serial.parseInt();
}

String input_serial_string() {
  // while 0 bits in buffer
  while (!Serial.available()) { delay(2); }
  return Serial.readString();
}


int input_serial_int_range(const int min, const int max, const char *message)
{
  serial_clear();
  Serial.print(message);
  
  int input = 0;
  while (true) {
    input = input_serial_int();
    if(input >= min && max >= input) {
      break;
    }
    
    Serial.print("\n\renter a number in range [");
    Serial.print(min);
    Serial.print(", ");
    Serial.print(max);
    Serial.print("]\n\r");

    Serial.print(message);
  }

  return input;
}

int input_serial_menu_display(const MenuItem menuItems[], uint8_t itemCount)
{
  serial_clear();
  
  for (uint8_t i = 0; i < itemCount; i++) {
    Serial.print(menuItems[i].value);
    Serial.print(". ");
    Serial.print(menuItems[i].text);
    Serial.print("\n\r");
  }
  uint8_t input;
  while (true)
  {
    input = input_serial_int();
    for (uint8_t i = 0; i < itemCount; i++) {
      if(input == menuItems[i].value) { return input; }
    }
    
    Serial.println("input not recognized");
    delay(2);
  }
}


void serial_bandit_display(Bandit *banditPtr, const int rows, const int offset) {
  serial_clear();
  banditgui_print_bandit(banditPtr, rows, offset);
}
