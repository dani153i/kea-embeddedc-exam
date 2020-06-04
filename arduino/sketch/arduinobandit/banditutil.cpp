#include "banditutil.h"

/*************************************************
 * Adds val2 to val1 until val1 is positive.
 *
 * @param val1 The value wanted positive
 * @param val2 The value added to val1
 * @return Positive version of val1
 ************************************************/
unsigned int abs_max(int val1, int val2)
{
    while (val1 < 0) {
        val1 += val2;
    }
    return val1;
}


/* indicates if random was seeded */
unsigned char seeded = 0x00;

/********************************************************************
 * Returns an unsigned long value between two given values. [min;max]
 * 
 * @param min Minimum value.
 * @param max Maximum value.
 * @return A value between min & max.
 *******************************************************************/
unsigned long get_random_long(unsigned long min, unsigned long max)
{
  /* if random isn't seeded */
  if (seeded == 0x00)
  {   
      /* seed random with random analog reading */
      randomSeed(analogRead(0));
      
      /* indicate random seeded */
      seeded = 0x01;
  }
  
  // return random [min;max]
  return random(min, max);
}
