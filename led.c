#include <avr/io.h>

#include "config.h"
#include "led.h"
#include "blink_kit.h"

#define PORT_(p) PORT##p
#define PORT(p) PORT_(p)
#define PIN_(p) PIN##p
#define PIN(p) PIN_(p)
#define DDR_(p) DDR##p
#define DDR(p) DDR_(p)

/*! \addtogroup led
 *  @{
 */

/*! \brief File internal lookup table from led index to PORT register
 *         address.
 *
 *  If led i is connected to I/O port x, then port_table[i] contains
 *  &PORTx.
 */
volatile uint8_t *port_table[NUM_LEDS] =
{
    &PORT(LED0_PORT),
    &PORT(LED1_PORT),
    &PORT(LED2_PORT),
    &PORT(LED3_PORT),
    &PORT(LED4_PORT),
    &PORT(LED5_PORT),
    &PORT(LED6_PORT),
    &PORT(LED7_PORT),
    &PORT(LED8_PORT),
    &PORT(LED9_PORT),
    &PORT(LED10_PORT),
    &PORT(LED11_PORT),
    &PORT(LED12_PORT),
    &PORT(LED13_PORT),
    &PORT(LED14_PORT),
    &PORT(LED15_PORT),
    &PORT(LED16_PORT),
    &PORT(LED17_PORT)
};

/*! \brief File internal lookup table from led index to PIN register
 *         address.
 *
 *  If led i is connected to I/O port x, then pin_table[i] contains &PINx.
 */
volatile uint8_t *pin_table[NUM_LEDS] =
{
    &PIN(LED0_PORT),
    &PIN(LED1_PORT),
    &PIN(LED2_PORT),
    &PIN(LED3_PORT),
    &PIN(LED4_PORT),
    &PIN(LED5_PORT),
    &PIN(LED6_PORT),
    &PIN(LED7_PORT),
    &PIN(LED8_PORT),
    &PIN(LED9_PORT),
    &PIN(LED10_PORT),
    &PIN(LED11_PORT),
    &PIN(LED12_PORT),
    &PIN(LED13_PORT),
    &PIN(LED14_PORT),
    &PIN(LED15_PORT),
    &PIN(LED16_PORT),
    &PIN(LED17_PORT)
};

/*! \brief File internal lookup table from led index to DDR register
 *         address.
 *
 *  If led i is connected to I/O port x, then ddr_table[i] contains
 *  &DDRx.
 */
volatile uint8_t *ddr_table[NUM_LEDS] =
{
    &DDR(LED0_PORT),
    &DDR(LED1_PORT),
    &DDR(LED2_PORT),
    &DDR(LED3_PORT),
    &DDR(LED4_PORT),
    &DDR(LED5_PORT),
    &DDR(LED6_PORT),
    &DDR(LED7_PORT),
    &DDR(LED8_PORT),
    &DDR(LED9_PORT),
    &DDR(LED10_PORT),
    &DDR(LED11_PORT),
    &DDR(LED12_PORT),
    &DDR(LED13_PORT),
    &DDR(LED14_PORT),
    &DDR(LED15_PORT),
    &DDR(LED16_PORT),
    &DDR(LED17_PORT)
};

/*! \brief File internal lookup table from led index to the bitmask of
 *         the led pin relative its port.
 *
 *  If led i is connected to bit j on its I/O port, then bitmask_table[i]
 *  contains 1<<j.
 */
uint8_t bitmask_table[NUM_LEDS] =
{
    1<<LED0_BIT,
    1<<LED1_BIT,
    1<<LED2_BIT,
    1<<LED3_BIT,
    1<<LED4_BIT,
    1<<LED5_BIT,
    1<<LED6_BIT,
    1<<LED7_BIT,
    1<<LED8_BIT,
    1<<LED9_BIT,
    1<<LED10_BIT,
    1<<LED11_BIT,
    1<<LED12_BIT,
    1<<LED13_BIT,
    1<<LED14_BIT,
    1<<LED15_BIT,
    1<<LED16_BIT,
    1<<LED17_BIT
};

/*! \brief File internal lookup table from LED intensity level to PWM
 *         duty cycle.
 *
 *  This table is needed since the intensity of a PWM'ed LED when
 *  perceived by a human is not proportional to the PWM duty
 *  cycle. These values follow a quadratic curve.
 */
uint8_t intensity_table[NUM_INTENSITIES] =
{
    0,
    1,
    4,
    8,
    14,
    22,
    32,
    43,
    56,
    71,
    88,
    107,
    127,
    149,
    173,
    199,
    226,
    255
};

/*! \brief Initialize led I/O port.
 *
 *  #port_table and #ddr_table are used to configure all #NUM_LEDS leds as
 *  outputs initalized to 0.
 */
void led_init(void)
{
    uint8_t i;

    // Initialize each led port into a known state
    for (i = 0; i < NUM_LEDS; i++) {
        // Set output value to 0
        *port_table[i] &= ~bitmask_table[i];
        // Config the I/O pin as output
        *ddr_table[i] |= bitmask_table[i];
    }
}

/*! \brief Turn on a LED.
 *
 *  \warning The AVR cannot supply enough current for all LEDs at the
 *           same time. Use #led_display to safely light a LED.
 *
 *  \param led The index of the LED to turn on (range from 0 to
 *             #NUM_LEDS - 1).
 */
void led_off(uint8_t led)
{
    *port_table[led] &= ~bitmask_table[led];
}

/*! \brief Turn on a LED.
 *
 *  \param led The index of the LED to turn off (range from 0 to
 *             #NUM_LEDS - 1).
 */
void led_on(uint8_t led)
{
    *port_table[led] |= bitmask_table[led];
}

/*! \brief Light the LEDs for the given times with intensities from
 *         the #values variable.
 *
 *  An array of NUM_LEDS number of bytes determines the intensity of
 *  each LED. This array is passed implicitly with the global variable
 *  #values. The LEDs are only lit during the function call; when
 *  #led_display returns all leds are turned off.
 *
 *  \param ticks The number of time "ticks" to keep the LEDs lit.
 */
void display_for(uint8_t ticks)
{
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint8_t x0, x1, x2;

    for (k = 0; k < ticks; k++) {
        for (i = 0; i < NUM_LEDS; i+=3) {
            x0 = intensity_table[values[i]];
            x1 = intensity_table[values[i+1]];
            x2 = intensity_table[values[i+2]];
            if (x0 > 0)
                led_on(i);
            if (x1 > 0)
                led_on(i+1);
            if (x2 > 0)
                led_on(i+2);
            j = 0;
            do {
                j++;
                if (j == x0) {
                    led_off(i);
                }
                if (j == x1) {
                    led_off(i+1);
                }
                if (j == x2) {
                    led_off(i+2);
                }
            } while (j < 255);
        }
    }
}

/*! @} */

