#ifndef BANDITUTIL_H_INCLUDED
#define BANDITUTIL_H_INCLUDED

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************
 * Adds val2 to val1 until val1 is positive.
 *
 * @param val1 The value wanted positive.
 * @param val2 The value added to val1.
 * @return Positive version of val1.
 ************************************************/
unsigned int abs_max(int val1, int val2);

/********************************************************************
 * Returns an unsigned long value between two given values. [min;max]
 * 
 * @param min Minimum value.
 * @param max Maximum value.
 * @return A value between min & max.
 *******************************************************************/
unsigned long get_random_long(unsigned long min, unsigned long max);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // BANDITUTIL_H_INCLUDED
