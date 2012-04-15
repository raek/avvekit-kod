#ifndef EFFECT_H
#define EFFECT_H

/*! \defgroup effect Effects
 *  \brief Blink pattern definitions
 *
 *  A blink effect is represented as a function. The function should
 *  not take any arguments and should have return type void. In order
 *  to make the main program aware of an effect, a call to #add_effect
 *  for that effect must be added to the body of #effect_init.
 *
 *  When an effect function returns, the next effect function in
 *  sequence will be called. An effect may run for as long time as it
 *  likes as long it follows one rule: it must call #should_exit every
 *  now and then and if #should_exit returns true the effect must
 *  return.
 *
 *  A new effect can be created by writing a new function in \ref
 *  effect.c and adding a corresponding line in the body of the
 *  #effect_init function. See the source of \ref effect.c for example
 *  effects.
 */

void effect_init(void);

#endif

