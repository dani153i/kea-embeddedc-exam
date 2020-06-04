#ifndef BANDITGUI_H_INCLUDED
#define BANDITGUI_H_INCLUDED

#include "bandit.h"
#include "banditutil.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * Prints bandit to to screen.
 * 
 * @param banditPtr Pointer to a Bandit.
 * @param rows How many wheel wheel rows to display.
 * @param row_offset Offset of current wheel row. If you have 5 rows and want the
 *                   current row to be displayed in the middle, then row_offset
 *                   would be -2.
 *******************************************************************************/
void banditgui_print_bandit(Bandit *banditPtr, const int rows, const int row_offset);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // BANDITGUI_H_INCLUDED
