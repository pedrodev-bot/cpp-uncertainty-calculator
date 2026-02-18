#pragma once
#include "types.hpp"
#include <optional>
#include <string>
#include <vector>

/** --- PUBLIC CONSTANT DECLARATION --- */

/** The constant value used to describe the uncertainty of the time measurement. */
inline const big_float TIME_INSTRUMENTAL_UNCERTAINTY = 0.001;
/** The constant value used to describe the uncertainty of the distance measurement. */
inline const big_float DISTANCE_INSTRUMENTAL_UNCERTAINTY = 0.05;

//** --- FUNCTIONS DECLARATIONS --- */

/** Calculate the average of measurements.
 *- Formula: x₁+...+xₙ/n, xₙ being the n-th measurement value.
 *- Formula description: The sum of all measurements (x) divided by the measurement count.
 */
big_float calculateAverage(std::vector<big_float>& measurements);
/** Calculate the average velocity.
 *- Formula: average distance/average time.
 */
big_float calculateAverageVelocity(big_float distance, big_float time);
/** Calculate the linear momentum.
 *- Formula: pₙ=mₙ.v, n being the n-th particle measurement we are calculating, p being the
 *- linear momentum, m being the particles mass and v being the average velocity. Made for two
 *- particles at most.
 */
void calculateLinearMomentum(Measurement& data);