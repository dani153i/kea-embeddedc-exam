#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "bandit.h"
#include "banditutil.h"
#include "banditgui.h"
#include "serialutil.h"
#include <Arduino.h>

const uint8_t PIN_BTN_A = 0x2;

#ifdef __cplusplus
extern "C" {
#endif

#define MAINMENU_MAX 2
static const MenuItem MAINMENU[MAINMENU_MAX] = {
  { "PLAY", 1 },
  { "SEE STATISTICS", 2 },
};



// Timer1 load value
const uint16_t t1_load = 0;

// Timer1 compare value = 
// ((100.000ns x 16mhz) / 256)
// <=> ((2s * 16mhz) / (4th prescaler))
// and (4th prescaler) = (1 * 8 * 8 * 4) = 256
// Timer1 min compare value
const uint16_t t1_comp_min = 62500; // 1 second
// Timer1 max compare value
const uint16_t t1_comp_max = 187500; // 3 seconds

/*************
 * Setup game.
 ************/
void game_setup();

/***********
 * Run game.
 **********/
void game_run();


#ifdef __cplusplus
} // extern "C"
#endif

#endif // GAME_H_INCLUDED
