/*
 *                                                        ____  _____
 *                            ________  _________  ____  / __ \/ ___/
 *                           / ___/ _ \/ ___/ __ \/ __ \/ / / /\__ \
 *                          / /  /  __/ /__/ /_/ / / / / /_/ /___/ /
 *                         /_/   \___/\___/\____/_/ /_/\____//____/
 *
 * ======================================================================
 *
 *   title:        Architecture specific code
 *
 *   project:      ReconOS
 *   author:       Christoph Rüthing, University of Paderborn
 *   description:  Functions needed for ReconOS which are architecure
 *                 specific and are implemented here.
 *
 * ======================================================================
 */

#ifndef RECONOSTIMER_H
#define RECONOSTIMER_H

/* == Timer functions ================================================== */

/*
 * Initializes the timer. Must be called before any other function can
 * be used.
 *
 *   no parameters
 */
void reconostimer_init();

/*
 * Resets the timer to zero.
 *
 *   no parameters
 */
void reconostimer_reset();

/*
 * Sets the step of the counter, i.e. the number of clock cycles to wait
 * between incrementing the counter. Therefore 0 means to count every clock cycle.
 */
void reconostimer_setstep(unsigned int step);

/*
 * Gets the current timestamp.
 *
 *   no parameters
 */
unsigned int reconostimer_get();

/*
 * Cleans up the driver.
 *
 *   no parameters
 */
void reconostimer_cleanup();

/*
 * Converts the timer value to millisecongs.
 *
 *   t - timer value or difference
 */
float reconostimer_toms(unsigned int t);

/*
 * Converts millisecongs to timer value  .
 *
 *   t - milliseconds
 */
unsigned int reconostimer_msto(float t);

#endif /* TIMER_H */