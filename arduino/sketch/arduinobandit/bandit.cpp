#include "bandit.h"

/* def */
BanditPlayer bandit_player_new();


/**
 * Returns a new instance of Bandit.
 */
Bandit bandit_new()
{
    Bandit bandit;
    
    bandit.banditPlayer = malloc(sizeof(BanditPlayer));

    
    *(bandit.banditPlayer) = bandit_player_new();

    int i;
    for ( i=0; i < WHEELS_MAX; i++) {
        bandit.cursor_position[i] = 0;
        bandit.spinning_wheels[i] = 0;
        bandit.spinning = 0;
    }

    bandit.spinResults_len = 0;
    
    int w;
    for ( i=0; i < SPINRESULTS_MAX; i++) {
      for ( w=0; i < WHEELS_MAX; i++) {
        bandit.spinResults[i].cursor_position[w] = 0;
      }
    }

    return bandit;
}

/**
 * Returns a new instance of BanditPlayer.
 */
BanditPlayer bandit_player_new()
{
    BanditPlayer player;

    player.spins_available = 0;
    player.spins_used = 0;
    player.winnings = 0;

    return player;
}

BanditSpinResult spinResult;
void bandit_assign_spin_result(Bandit *bandit)
{
  ++bandit->banditPlayer->spins_used;
  
  /* iterate backwards through rules (high->low reward) to find winnings */
  int rulesCount;
  for ( rulesCount = RULES_MAX - 1; rulesCount >= 0; rulesCount-- )
  {
    /* check how many criteria are fulfilled */
      int wheel, criteriaFound;
      for ( criteriaFound=0, wheel=(WHEELS_MAX - 1); wheel >= 0; wheel-- )
      {
          if ( RULES[rulesCount][wheel] == -1 ||
              RULES[rulesCount][wheel] == WHEEL_LAYOUT[wheel][bandit->cursor_position[wheel]] )
          {
              criteriaFound++;
          }
      }

      /* if all criteria are fulfilled */
      if ( criteriaFound == WHEELS_MAX )
      {
          /* award player with spins (reward) */
          bandit->banditPlayer->spins_available += RULE_REWARDS[rulesCount];
          /* add to player total winnings */
          bandit->banditPlayer->winnings += RULE_REWARDS[rulesCount];
          break;
      }
  }


  /* add BanditSpinResult to bandit statistics */
  // initialize spinResult
  for (int wheel=0; wheel < WHEELS_MAX; wheel++)
  {
    spinResult.cursor_position[wheel] = WHEEL_LAYOUT[wheel][bandit->cursor_position[wheel]];
  }
  
  // push spinResult to bandit statistics
  // if array is full
  if (bandit->spinResults_len < SPINRESULTS_MAX)
  {
      bandit->spinResults_len++;
  } else{
    // shift spinResults array by 1
    for (int x = 0; x < bandit->spinResults_len-1; x++)
    {
      // copy values
      for (int w=0; w < WHEELS_MAX; w ++)
      {
        bandit->spinResults[x].cursor_position[w] = bandit->spinResults[x+1].cursor_position[w];
      }
    }
  }

  // push SpinResult to statistics array
  for (int w=0; w < WHEELS_MAX; w++)
  {
    bandit->spinResults[bandit->spinResults_len - 1].cursor_position[w] = spinResult.cursor_position[w];
  }
  

  
}


void bandit_turn_wheels(Bandit *banditPtr)
{
  /* only turn wheels if bandit is spinning */
  if (banditPtr->spinning == 0) {
    return;
  }

  /* iterate through wheels */
  int wheel;
  for ( wheel=0; wheel  < WHEELS_MAX; wheel++ )
  {
    /* skip if wheel is not spinning */
    if (banditPtr->spinning_wheels[wheel] == 0) {
      continue;
    }
    /* point to next symbol within range [0;WHEEL_SIZE] */
    banditPtr->cursor_position[wheel] = abs_max(banditPtr->cursor_position[wheel] + 1, WHEEL_SIZE) % WHEEL_SIZE;
  }
}


int bandit_calculate_winnings(BanditSpinResult *spinResult)
{
  /* iterate backwards through rules (high->low reward) to find winnings */
  int rulesCount;
  for ( rulesCount = RULES_MAX - 1; rulesCount >= 0; rulesCount-- )
  {
      /* check how many criteria are fulfilled */
      int wheel, criteriaFound;
      for ( criteriaFound=0, wheel=(WHEELS_MAX - 1); wheel >= 0; wheel-- )
      {
          if ( RULES[rulesCount][wheel] == -1 ||
              RULES[rulesCount][wheel] == spinResult->cursor_position[wheel] )
          {
              criteriaFound++;
          }
      }

      /* if all criteria are fulfilled */
      if ( criteriaFound == WHEELS_MAX )
      {
          /* return reward (winnings) */
          return RULE_REWARDS[rulesCount];
      }
  }
  
  /* no rule matched BanditSpinResult */
  return 0;
}
