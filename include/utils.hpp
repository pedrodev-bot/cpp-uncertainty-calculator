#pragma once
#include "types.hpp"
#include <string>
#include <optional>

/** Ensures that the users input is indeed "Y" or "N". */
bool validateAnswerYN(std::string usersInput);
/** Ensures that the users input is indeed a number. */
std::optional<big_float> validateNumberInput(std::string usersInput);