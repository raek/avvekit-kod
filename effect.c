#include <stdint.h>
#include "led.h"
#include "blink_kit.h"

/*! \addtogroup effect
 *  @{
 */

/*! \brief Rotate a triangle shaped instensity distribution in
 *         increasing and decreasing speed.
 */
void smooth_roll(void)
{
    int8_t i, j;

    triangle();
    for (;;) {
        for (i = 2; i < 20; i++) {
            for (j = i; j < 20; j++) {
                display_for(i);
                rotate_right();
            }
            if (should_exit()) {
                return;
            }
        }
        for (i = 19; i > 2; i--) {
            for (j = i; j < 20; j++) {
                display_for(i);
                rotate_right();
            }
            if (should_exit()) {
                return;
            }
        }
    }
}

/*! \brief Light all LEDs left to right and then darken them left to
 *          right.
 *
 *  Start with all LEDs off. Then shift in lit LEDs on the left end
 *  until all leds are on. Then shift in unlit LEDs on the left until
 *  all leds are off again and repeat.
 */
void fill_drain(void)
{
    uint8_t x;

    clear(0);
    shift_right(MAX_INTENSITY);
    while (!should_exit()) {
        display_for(10);
        x = MAX_INTENSITY - peek_right();
        shift_right(x);
    }
}


/*! \brief Step the intensity of all LEDs simuntaneously up and down
 *         rapidly and repeatedly.
 */
void flash(void)
{
    int8_t i;

    while(1) {
        for (i = 0; i <= MAX_INTENSITY; i++) {
            clear(i);
            display_for(3);
            if (should_exit()) {
                return;
            }
        }
        for (i = MAX_INTENSITY; i >= 0; i--) {
            clear(i);
            display_for(3);
            if (should_exit()) {
                return;
            }
        }
    }
}

/*! \brief Register all available effects.
 *
 *  To make the blink kit aware of a new effect, modify this function
 *  and add a call to #add_effect with the effect function as the only
 *  argument.
 */
void effect_init(void)
{
    add_effect(smooth_roll);
    add_effect(fill_drain);
    add_effect(flash);
}

/*! @} */

