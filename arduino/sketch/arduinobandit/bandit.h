#ifndef BANDIT_H_INCLUDED
#define BANDIT_H_INCLUDED

#include "banditutil.h"
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <time.h>


/* BANDIT UI */
#define WHEEL_ROWS_DISPLAY 5
#define WHEEL_ROWS_DISPLAY_OFFSET -2

#define SYMBOL_MAX 6
#define SYMBOLS_MAX 8

#define WHEELS_MAX 3
#define WHEEL_SIZE 10

#define RULES_MAX 10

#define SPINRESULTS_MAX 20


/* Bandit Constants */

static const char *SYMBOLS[SYMBOLS_MAX] = \
{ "BAR", "Apple", "Bell", "Cherry", "Grape", "Lemon", "Orange", "Plum" };

static const int WHEEL_LAYOUT[WHEELS_MAX][WHEEL_SIZE] = \
{\
    { 0, 3, 2, 7, 1, 1, 4, 5, 6, 5 }, \
    { 0, 3, 3, 2, 2, 7, 1, 4, 6, 5 }, \
    { 0, 3, 3, 3, 2, 7, 1, 4, 6, 6 }, \
};

static const int RULES[RULES_MAX][WHEELS_MAX] = \
{\
    { -1, -1, 3 }, \
    { -1, 3, 3}, \
    { 3, 3, 3}, \
    { -1, 2, 2}, \
    { 2, 2, 2}, \
    { 6, 6, 6}, \
    { 1, 1, 1}, \
    { 7, 7, 7}, \
    { 4, 4, 4}, \
    { 0, 0, 0}, \
};

static const int RULE_REWARDS[RULES_MAX] =\
{ 2, 8, 12, 8, 16, 10, 18, 24, 24, 50 };

/* Definitions */

typedef struct BanditSpinResult_s
{
    int cursor_position[WHEELS_MAX];
} BanditSpinResult;



typedef struct BanditPlayer_s
{
    int spins_available;
    int spins_used;
    /* total winnings this game session*/
    int winnings;

} BanditPlayer;


typedef struct Bandit_s
{
    // contains information about the current player
    BanditPlayer *banditPlayer;
    /* wheel cursor position */
    int cursor_position[WHEELS_MAX];
    /* indicator of what wheels are spinning */
    int spinning_wheels[WHEELS_MAX];
    /* indicator of any wheels spinning */
    int spinning;
    
    /* saved for statistics (across all game sessions) */
    int spinResults_len;
    BanditSpinResult spinResults[SPINRESULTS_MAX];
} Bandit;


/**
 * Returns a new instance of bandit with
 * initialized data.
 */
Bandit bandit_new();

/**
 * Assign spin results to specified Bandit.
 */
void bandit_assign_spin_result(Bandit *bandit);

/**
 * Turn wheels of specified Bandit.
 */
void bandit_turn_wheels(Bandit *banditPtr);

/**
 * Return winnings (int) from a BanditSpinResult.
 */
int bandit_calculate_winnings(BanditSpinResult *spinResult);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // BANDIT_H_INCLUDED
