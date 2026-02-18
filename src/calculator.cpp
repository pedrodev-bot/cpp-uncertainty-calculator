#include "calculator.hpp"
#include "ui.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

big_float calculateAverage(vector<big_float>& measurements){
    if (measurements.empty()){
        return 0;
    }
    big_float averageSum = 0;

    for(const auto& a : measurements) averageSum+=a;

    return averageSum/static_cast<big_float>(measurements.size());
}
big_float calculateAverageVelocity(big_float distance, big_float time){
    return distance/time;
}
void calculateLinearMomentum(Measurement& data){
    big_float massSum = 0;
    for(size_t i = 0; i < data.distance.size(); i++){
        big_float currentVelocity = calculateAverageVelocity(data.distance[i]/100, data.time[i]);
        big_float currentLinearMomentum = (data.mass[i]/1000)*currentVelocity;
        data.averageVelocity.push_back(currentVelocity);
        data.linearMomentum.push_back(currentLinearMomentum);
        massSum += data.mass[i];
    }

    data.linearMomentum.push_back((massSum/1000)*data.averageVelocity[data.averageVelocity.size()-1]);

    return;
}