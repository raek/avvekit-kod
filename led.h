#ifndef LED_H
#define LED_H

#include <stdint.h>

/*! \defgroup led LED
 *  \brief Functions and definitions for controlling the LEDs
 *
 *  This module is used to control the LEDs of the board. Each of the
 *  #NUM_LEDS LEDs can be controlled individually in #NUM_INTENSITIES
 *  number of intensity levels. Intensities are represented as
 *  integers from 0 to #MAX_INTENSITY (inclusive).
 *
 *  The AVR cannot handle the current from all LEDs if they are on at
 *  the same time, and #led_display takes this into account. The low
 *  level #led_off and #led_off functions however do not.
 *
 *  Before any other function of this module is called, the #led_init
 *  function must first be called to correctly configure and
 *  initialize the LED pins. (Initial state is off.)
 *
 *  The #display_for function lights the LEDs for a given time. An
 *  array of NUM_LEDS number of bytes determines the intensity of each
 *  LED. This array is passed implicitly with the global variable
 *  #values. The LEDs are only lit during the function call; when
 *  #led_display returns all leds are turned off.
 */

/*! \addtogroup led
 *  @{
 */

/*! \brief The number of LEDs connected to the board
 *
 *  An integer that identifies a LED should be in the range from 0 to
 *  #NUM_LEDS - 1 (inclusive).
 */
#define NUM_LEDS 18

/*! \brief The number of LED intensity levels
 *
 *  An integer value that represents a LED intensity should be in the
 *  range from 0 to #NUM_INTENSITIES - 1 (inclusive).
 *
 *  This value is the same as #MAX_INTENSITY + 1.
 */
#define NUM_INTENSITIES NUM_LEDS

/*! \brief The most bright led intensity level
 *
 *  An integer value that represents a LED intensity should be in the
 *  range from 0 to #MAX_INTENSITY (inclusive).
 *
 *  This value is the same as #NUM_INTENSITIES - 1.
 */
#define MAX_INTENSITY (NUM_INTENSITIES - 1)

void led_init(void);
void led_off(uint8_t led);
void led_on(uint8_t led);
void display_for(uint8_t ticks);

/*! @} */

#endif

