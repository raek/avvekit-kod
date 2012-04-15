#include "blink_kit.h"
#include "button.h"
#include "effect.h"

/*! \addtogroup blink_kit
 *  @{
 *
 */

/*! \brief Limit on how many effects can be registered.
 */
#define MAX_EFFECTS 20

/*! \brief Default array for #values.
 */
uint8_t led_array[NUM_LEDS];

/*! \brief Array of / pointer to the LED intensities manipulated by
 *         the \ref blink_kit module.
 */
uint8_t* values;
effect_function effects[MAX_EFFECTS];
uint8_t effect_count;
uint8_t current_effect;

/*! \brief Initialize global variables.
 */
void blink_kit_init(void) {
    values = led_array;
    effect_count = 0;
    current_effect = -1;
}

/*! \brief Get the array that is currently used for the leds.
 */
uint8_t* get_led_array(void)
{
    return values;
}

/*! \brief Set the array that is currently used for the leds.
 */
void set_led_array(uint8_t* a)
{
    values = a;
}

/*! \brief Run the next effect.
 *
 *  This function cannot be called from within an effect. Return from
 *  the effect instead.
 */
void run_next_effect(void)
{
    current_effect++;
    if (current_effect >= effect_count) {
        current_effect = 0;
    }
    effects[current_effect]();
}

/*! \brief Should the currenlty running effect exit?
 *
 *  This function must be polled regularly from all effects. If it
 *  returns true, the effect function must return.
 */
uint8_t should_exit(void)
{
    if (button_pressed) {
        button_pressed = 0;
        return 1;
    } else {
        return 0;
    }
}

/*! \brief Reset the contents of each element of the led array to
 *         value.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  After: [0, 0, 0, 0, 0, 0]
 */
void clear(uint8_t value)
{
    uint8_t i;

    for (i = 0; i < NUM_LEDS; i++) {
        values[i] = value;
    }
}

/*! \brief Initialize the led array to a rising ramp-shaped intensity
 *         distribution.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  After: [0, 1, 2, 3, 4, 5]
 */
void ramp_right(void) {
    uint8_t i;
    uint16_t level;

    for (i = 0; i < NUM_LEDS; i++) {
        level = (i * MAX_INTENSITY) / NUM_LEDS;
        values[i] = level;
    }
}

/*! \brief Initialize the led array to a falling ramp-shaped intensity
 *         distribution.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  After: [5, 4, 3, 2, 1, 0]
 */
void ramp_left(void) {
    uint8_t i;
    uint16_t level;

    for (i = 0; i < NUM_LEDS; i++) {
        level = ((NUM_LEDS - i - 1) * MAX_INTENSITY) / NUM_LEDS;
        values[i] = level;
    }
}

/*! \brief Initialize the led array to two mirrored ramp-shaped
 *         intensity distributions.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  After: [0, 1, 3, 3, 1, 0]
 */
void triangle(void) {
    uint8_t i;
    uint16_t level;

    for (i = 0; i < NUM_LEDS/2; i++) {
        level = (i * MAX_INTENSITY * 2) / NUM_LEDS;
        values[i] = level;
    }
    for (i = NUM_LEDS/2; i < NUM_LEDS; i++) {
        level = ((NUM_LEDS - i - 1) * MAX_INTENSITY * 2) / NUM_LEDS;
        values[i] = level;
    }
}

/*! \brief Shift all intensities one step to the right, using the
 *         rightmost intensity as the new leftmost.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before: [0, 1, 2, 3, 4, 5]
 *  After:  [5, 0, 1, 2, 3, 4]
 */
void rotate_right(void)
{
    uint8_t i;
    uint8_t last;

    last = values[NUM_LEDS - 1];
    for (i = NUM_LEDS - 1; i > 0; i--) {
        values[i] = values[i - 1];
    }
    values[0] = last;
}

/*! \brief Shift all intensities one step to the left, using the
 *         leftmost intensitiy as the new rightmost.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before: [0, 1, 2, 3, 4, 5]
 *  After:  [1, 2, 3, 4, 5, 0]
 */
void rotate_left(void)
{
    uint8_t i;
    uint8_t left;

    left = values[0];
    for (i = 1; i < NUM_LEDS; i++) {
        values[i - 1] = values[i];
    }
    values[NUM_LEDS - 1] = left;
}

/*! \brief Get the current intensity of the rightmost LED.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before:   [0, 1, 2, 3, 4, 5]
 *  Returned: 5
 */
uint8_t peek_right(void) {
    return values[NUM_LEDS - 1];
}

/*! \brief Get the current intensity of the leftmost LED.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before:   [0, 1, 2, 3, 4, 5]
 *  Returned: 0
 */
uint8_t peek_left(void) {
    return values[0];
}

/*! \brief Shift all intensities one step to the right, using the the
 *         provided intensity as the new leftmost.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before:   [0, 1, 2, 3, 4, 5]
 *  New left: 3
 *  After:    [3, 0, 1, 2, 3, 4]
 */
uint8_t shift_right(uint8_t left)
{
    uint8_t i;
    uint8_t right;

    right = values[NUM_LEDS - 1];
    for (i = NUM_LEDS - 1; i > 0; i--) {
        values[i] = values[i - 1];
    }
    values[0] = left;
    return right;
}

/*! \brief Shift all intensities one step to the left, using the the
 *         provided intensity as the new rightmost.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before:    [0, 1, 2, 3, 4, 5]
 *  New right: 3
 *  After:     [1, 2, 3, 4, 5, 3]
 */
uint8_t shift_left(uint8_t right)
{
    uint8_t i;
    uint8_t left;

    left = values[0];
    for (i = 1; i < NUM_LEDS; i++) {
        values[i - 1] = values[i];
    }
    values[NUM_LEDS - 1] = right;
    return left;
}

/*! \brief Shift all intensities one step to the left, using the the
 *         provided intensity as the new rightmost.
 *
 *  Example with NUM_LEDS = NUM_INTENSITIES = 6:
 *
 *  Before: [0, 0, 1, 1, 3, 5]
 *  After:  [5, 3, 1, 1, 0, 0]
 */
void flip(void)
{
    uint8_t i, j;
    uint8_t temp;
    for (i = 0; i < NUM_LEDS/2; i++) {
        j = NUM_LEDS-i-1;
        temp = values[i];
        values[i] = values[j];
        values[j] = temp;
    }
}

/*! \brief Register a new effect.
 *
 *  This function should only be called once per effect and only at
 *  program initialization. When the button is pressed, the registered
 *  effects will cycled through in the order their #add_effect calls
 *  were executed during the initialization.
 */
void add_effect(effect_function effect)
{
    if (effect_count != MAX_EFFECTS) {
        effects[effect_count] = effect;
        effect_count++;
    }
}

/*! @} */

