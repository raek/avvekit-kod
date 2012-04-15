#ifndef BLINK_KIT_H
#define BLINK_KIT_H

#include <avr/io.h>
#include "led.h"

/*! \defgroup blink_kit Blink Kit
 *
 *  This module provides a toolkit for blink effects. Most function
 *  operate on an array of intensity values which is passed
 *  implicitly. This array can be accessed manually using
 *  #get_led_array and be replaced using #set_led_array. Initially, a
 *  statically allocated array is used.
 */

/*! \addtogroup blink_kit
 *  @{
 */

uint8_t* values;

void blink_kit_init(void);

uint8_t* get_led_array(void);

void set_led_array(uint8_t* a);

void run_next_effect(void);

uint8_t should_exit(void);

void clear(uint8_t value);

void ramp_right(void);

void ramp_left(void);

void triangle(void);

void rotate_right(void);

void rotate_left(void);

uint8_t peek_right(void);

uint8_t peek_left(void);

uint8_t shift_right(uint8_t left);

uint8_t shift_left(uint8_t right);

void flip(void);

typedef void (*effect_function)(void);

void add_effect (effect_function effect);

/*! @} */

#endif

