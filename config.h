#ifndef CONFIG_H
#define CONFIG_H

/*! \defgroup config Config
 *  \brief Port and bit definitions for all LEDs and the button.
 *
 *  The wiring of the LEDs and the button is highly configurable. The
 *  LEDs and the button can be connected to any I/O pin. The defines
 *  in this module specifies these connections.
 *
 *  The value of a LEDx_PORT define should be one of A, B, C, and
 *  D. The value of a LEDx_BIT should be an integer in the range 0 to
 *  7 (inclusive). The same rules apply for #BUTTON_PORT and
 *  #BUTTON_BIT.
 */

/*! \addtogroup config
 *  @{
 */

#define LED0_PORT C
#define LED0_BIT  3

#define LED1_PORT C
#define LED1_BIT  4

#define LED2_PORT C
#define LED2_BIT  5

#define LED3_PORT D
#define LED3_BIT  0

#define LED4_PORT D
#define LED4_BIT  1

#define LED5_PORT D
#define LED5_BIT  2

#define LED6_PORT D
#define LED6_BIT  3

#define LED7_PORT D
#define LED7_BIT  4

#define LED8_PORT A
#define LED8_BIT  2

#define LED9_PORT B
#define LED9_BIT  6

#define LED10_PORT B
#define LED10_BIT  7

#define LED11_PORT D
#define LED11_BIT  6

#define LED12_PORT D
#define LED12_BIT  7

#define LED13_PORT B
#define LED13_BIT  0

#define LED14_PORT B
#define LED14_BIT  1

#define LED15_PORT A
#define LED15_BIT  1

#define LED16_PORT C
#define LED16_BIT  0

#define LED17_PORT C
#define LED17_BIT  1

#define BUTTON_PORT D
#define BUTTON_BIT  5

/*! @} */

#endif

