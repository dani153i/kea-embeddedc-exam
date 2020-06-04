#ifndef SERIALUTIL_H_INCLUDED
#define SERIALUTIL_H_INCLUDED

#include <Arduino.h>
#include "banditgui.h"

typedef struct MenuItem_s
{
  const char *text;
  const int value;
}  MenuItem;

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************
 * Clear serial monitor. (print linebreaks).
 * 
 ******************************************/
void serial_clear();

/****************************************************
 * Wait for specified input value on a specified pin.
 * 
 * @param pin
 * @param value
 ***************************************************/
void input_pin_wait(uint8_t pin, uint8_t value);

/********************************************************
 * Display a message to Serial and Wait for Serial input.
 * 
 * @param message A message to be displayed.
 *******************************************************/
void input_serial_wait(const char *message);

/***************************************************************
 * Display menu items to Serial and return value of chosen item.
 * 
 * @param menuItems An array of MenuItem.
 * @param itemCount Length of menuItems.
 * 
 * @return value of chosen MenuItem.
 **************************************************************/
int input_serial_menu_display(const MenuItem menuItems[], uint8_t itemCount);

/****************************************************************
 * Display a message to Serial and return chosen value. [min;max]
 * 
 * @param min Minimum value.
 * @param max Maximum value.
 * @param message A message to be displayed.
 * 
 * @return Value between min & max included. [min;max]
 ***************************************************************/
int input_serial_int_range(const int min, const int max, const char *message);

/********************************************************************************
 * Display bandit to to Serial.
 * 
 * @param banditPtr Pointer to a Bandit.
 * @param rows How many wheel wheel rows to display.
 * @param row_offset Offset of current wheel row. If you have 5 rows and want the
 *                   current row to be displayed in the middle, then row_offset
 *                   would be -2.
 *******************************************************************************/
void serial_bandit_display(Bandit *banditPtr, const int rows, const int offset);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // SERIALUTIL_H_INCLUDED
