#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "led.h"
#include "blink_kit.h"
#include "effect.h"

/*! \mainpage Åvvekit
 *
 *  How to add a new effect is explained in \ref effect. A small
 *  library is available to build effects with: \ref blink_kit.
 */

int main(void)
{
    cli();

    led_init();
    button_init();
    blink_kit_init();
    effect_init();

    sei();

    for (;;) {
        run_next_effect();
    }

    return 0;
}

