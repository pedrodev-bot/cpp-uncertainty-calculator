#include "types.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

bool validateAnswerYN(string usersInput){
    if(usersInput.length() != 1){
        return false;
    }

    char answer = toupper(usersInput[0]);
    if(answer == 'Y' || answer == 'N'){
        return true;
    } 

    return false;
}
optional<big_float> validateNumberInput(string usersInput){
    replace(usersInput.begin(), usersInput.end(), ',', '.');
    
    big_float value;

    size_t postProcessed = 0;

    try {
        value = stold(usersInput, &postProcessed);

        if(postProcessed < usersInput.length()){
            return nullopt;
        }
    } catch (const invalid_argument& e){
        return nullopt;
    } catch (const out_of_range& e){
        return nullopt;
    }

    return value;
}