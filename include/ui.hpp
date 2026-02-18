#pragma once
#include "types.hpp"

/** --- FUNCTIONS DECLARATIONS --- 
 * These functions below receive data from user and call functions to calculate those values described in "calculator.hpp"
*/

/** Asks the user for the values to store it in a vector. */
big_float computeMeasurements(int i);

/** Asks the user which value he wants to calculate. */
void getFunction();

/** Asks the user the values for calculate the average. */
void getAverage();

/** Asks the user the values for calculate the linear momentum. */
void getLinearMomentum();