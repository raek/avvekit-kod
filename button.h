#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

/*! \defgroup button Button
 *  \brief Button input
 *
 *  This module prodived a boolean flag and an interrupt service
 *  routine. The flag is set to 1 by the ISR when the button is
 *  pressed. It is up to the application to reset the flag to 0.
 *
 *  The #button_init function has to be called for the ISR to work.
 */

extern volatile uint8_t button_pressed;

void button_init(void);

#endif

