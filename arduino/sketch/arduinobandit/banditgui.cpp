#include "banditgui.h"


void banditgui_print_wheels(Bandit *bandit, const int rows, const int row_offset);


void banditgui_print_bandit(Bandit *banditPtr, const int rows, const int row_offset)
{
  Serial.print("Spins: ");
  Serial.print(banditPtr->banditPlayer->spins_available);
  Serial.println("\n\r");
  banditgui_print_wheels(banditPtr, rows, row_offset);
}


void banditgui_print_wheels(Bandit *bandit, const int rows, const int row_offset)
{
    char symbolTmp[SYMBOL_MAX + 1];
    char symbol_output[sizeof(SYMBOLS[0]) / sizeof(char) + 1];

    int symbol_id;

    /* foreach row to be displayed */
    int row, wheel;
    for ( row=0; row < rows; row++ )
    {
        /* find and print symbol for each wheel  */
        for ( wheel=0; wheel < WHEELS_MAX; wheel++ )
        {
            /* next symbol id = cursor_position-- = [0;WHEEL_SIZE] */
            symbol_id = abs_max(row + bandit->cursor_position[wheel] + row_offset, WHEEL_SIZE) % WHEEL_SIZE;
            /* next symbol id is found within WHEEL_LAYOUT
             * relative to wheel and previous found symbol id (cursor_position) */
            symbol_id = WHEEL_LAYOUT[wheel][symbol_id];

            /* save symbol to output buffer */
            if ( SYMBOLS[symbol_id] != SYMBOLS[0] )
            {
                /* clear all chars in buffer and replace middle char */
                symbol_output[0] = ' ';
                symbol_output[1] = SYMBOLS[symbol_id][0];
                symbol_output[2] = ' ';
                symbol_output[3] = '\0';
            } else {
                /* copy complete symbol to output buffer */
                strcpy(symbol_output, SYMBOLS[symbol_id]);
            }
            /* print symbol to serial */
            Serial.print(symbol_output);
        }
        /* after line of symbols, print linebreak to serial  */
        Serial.print("\n\r");
    }

}
