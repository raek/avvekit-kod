#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "config.h"
#define PORT_(p) PORT##p
#define PORT(p) PORT_(p)
#define PIN_(p) PIN##p
#define PIN(p) PIN_(p)
#define DDR_(p) DDR##p
#define DDR(p) DDR_(p)
#define PCIE_(p) PORT##p##_PCIE
#define PCIE(p) PCIE_(p)
#define PCMSK_(p) PORT##p##_PCMSK
#define PCMSK(p) PCMSK_(p)
#define PCINT_vect_(p) PORT##p##_PCINT_vect
#define PCINT_vect(p) PCINT_vect_(p)

#define PORTA_PCIE PCIE3
#define PORTB_PCIE PCIE0
#define PORTC_PCIE PCIE1
#define PORTD_PCIE PCIE2

#define PORTA_PCMSK PCMSK3
#define PORTB_PCMSK PCMSK0
#define PORTC_PCMSK PCMSK1
#define PORTD_PCMSK PCMSK2

#define PORTA_PCINT_vect PCINT3_vect
#define PORTB_PCINT_vect PCINT0_vect
#define PORTC_PCINT_vect PCINT1_vect
#define PORTD_PCINT_vect PCINT2_vect

/*! \addtogroup button
 *  @{
 */

/*! \brief Has the button been pressed?
 *
 *  This variable is set to 1 when the button is pressed. It is up to
 *  the application to reset it to 0.
 */
volatile uint8_t button_pressed;

/*! \brief Set up button interrupt service routine.
 */
void button_init(void)
{
    // Config the I/O pin as input
    DDR(BUTTON_PORT) &= ~(1<<BUTTON_BIT);
    // Activate pull-up resitor
    PORT(BUTTON_PORT) |= (1<<BUTTON_BIT);

    // Enable pin change interrupt for the port
    PCICR |= 1<<PCIE(BUTTON_PORT);
    // Enable pin change interrupt for the pin
    PCMSK(BUTTON_PORT) |= (1<<BUTTON_BIT);
}

/*! \brief Button interrupt service routine.
 *
 *  When the button is pressed, #button_pressed is set to 1.
 */
ISR(PCINT_vect(BUTTON_PORT))
{
    if (!(PIN(BUTTON_PORT) & (1<<BUTTON_BIT))) {
        button_pressed = 1;
    }
}

/*! @} */

