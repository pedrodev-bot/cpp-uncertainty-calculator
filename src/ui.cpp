#include "calculator.hpp"
#include "types.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include <iostream>
#include <map>

using namespace std;

big_float computeMeasurements(int i){
    while(true){
        string usersInput;
        cout << i << "º > Measurement: ";
        cin >> usersInput;
        auto result = validateNumberInput(usersInput);
        if(!result.has_value()){
            cout << "Your input isn't a number, try again.\n";
        } else {
            return result.value();
        }
    }

    return 0;
}
void getAverage(){
    string usersInput;
    vector<big_float> measurements(0);
    cout << "\n───────────────────────";
    cout << "\nCalculate Average\n";
    cout << " → Formula: x₁+...+xₙ/n, xₙ being the n-th measurement value.\n";
    while(true){
        cout << "\n ▪ How many measurements do you have: ";
        cin >> usersInput;
        auto result = validateNumberInput(usersInput);
        if(!result.has_value()){
            cout << "Your input isn't a integer, try again.\n";
        } else {
            measurements.resize(int(result.value()));
            break;
        }
    }
    cout << "\n";

    for(size_t i = 0; i < measurements.size(); i++){
        measurements[i] = computeMeasurements(i+1);
    }

    big_float average = calculateAverage(measurements);

    cout << "\nAverage: " << average << endl;
    return;
}
void getFunction(){
    map<int, function<void()>> commandList;

    commandList[1] = getAverage;
    //commandList[2] = calculateAverageVelocity;
    commandList[3] = getLinearMomentum;
    //commandList[4] = calculateKineticEnergy;
    //commandList[5] = calculateMeasurementUncertainty;
    //commandList[6] = calculateVelocityUncertainty;
    //commandList[7] = calculateLinearMomentumUncertainty;
    //commandList[8] = calculateKineticEnergyUncertainty;

    int usersChoice = 0;
    while(true){
        // Menu that asks user his functions choice.
        cout << "\nExperiment Calculator\n";
        cout << " → Choose an option:\n";
        cout << " ▪ 0. Leave\n";
        cout << " ▪ 1. Calculate Average\n";
        cout << " ▪ 2. Calculate Average Velocity (Unavailable)\n";
        cout << " ▪ 3. Calculate Linear Momentum\n";
        cout << " ▪ 4. Calculate Kinetic Energy (Unavailable)\n";
        cout << " ▪ 5. Calculate Measurement Uncertainty (Distance and Time only) (Unavailable)\n";
        cout << " ▪ 6. Calculate Velocity Uncertainty (Unavailable)\n";
        cout << " ▪ 7. Calculate Linear Momentum Uncertainty (Unavailable)\n";
        cout << " ▪ 8. Calculate Kinetic Energy Uncertainty (Unavailable)\n";
        cout << " ▪ 9. Calculate all data that came from Distance and Time (Unavailable)\n";
        cout << "        They are: Average Time and Distance with their Uncertainty,\n";
        cout << "        Average Velocity, Linear Momentum, Kinetic Energy and their\n";
        cout << "        respective Uncertainty.\n";
        cout << "\n▪ Your choice: ";
        cin >> usersChoice;

        if (usersChoice == 0){
            break;
        }

        auto it = commandList.find(usersChoice);

        if (it != commandList.end()){
            it->second();
            break;
        } else {
            cout << "\nInvalid option. Try again.\n";
        }
    }

    return;
}
void getLinearMomentum(){
    string usersInput;
    char answer;
    // 0 for elastic collision and 1 for inelastic collision;
    bool collisionType;
    cout << "\n───────────────────────";
    cout << "\nCalculate Linear Momentum\n";
    cout << " → Formula: pₙ=mₙ.v, n being the n-th particle measurement we are calculating,\n";
    cout << "p being the linear momentum, m being the particles mass and v being the average\n";
    cout << "velocity. Made for two particles at most.\n";

    while(true){
        cout << "\n ▪ Do we have multiple particles (Y/N)? ";
        cin >> usersInput;
        bool answerValidate = validateAnswerYN(usersInput);
        if(answerValidate){
            answer = toupper(usersInput[0]);
            break;
        } else {
            cout << "Your input should be 'Y' or 'N'.";
        }
    }

    while(true){
        cout << "\n → Choose an option:\n";
        cout << " ▪ 0. Elastic Collision\n";
        cout << " ▪ 1. Inelastic Collision\n";
        cout << "\n▪ Your choice: ";
        cin >> usersInput;

        auto result = validateNumberInput(usersInput);
        if(!result.has_value()){
            cout << "Your input isn't a integer, try again.\n";
        } else if(result.value() != 1 && result.value() != 0){
            cout << "You are choosing an unavailable option, try again.\n";
        } else {
            collisionType = int(result.value());
            break;
        }
    }

    int measurementCount;
    if(answer == 'Y'){
        measurementCount = 2;
    } else if (answer == 'N'){
        measurementCount = 1;
    }

    Measurement data_for_linear_momentum;
    for(int i = 0; i < measurementCount; i++){
        cout << "\nData from particle #" << i+1 << "\n";
        cout << "For average distance value (cm):\n";
        data_for_linear_momentum.distance.push_back(computeMeasurements(i+1));
        
        cout << "\nFor average time value (s):\n";
        data_for_linear_momentum.time.push_back(computeMeasurements(i+1));

        cout << "\nFor mass value (g):\n";
        data_for_linear_momentum.mass.push_back(computeMeasurements(i+1));
    }

    calculateLinearMomentum(data_for_linear_momentum);
    
    cout << "\nList of calculated data\n";
    for(int i = 0; i < measurementCount; i++){
        cout << "\nData from particle #" << i+1 << "\n";
        cout << i+1 << "º > Average Distance: " << data_for_linear_momentum.distance[i] << " cm\n";
        cout << i+1 << "º > Average Time: " << data_for_linear_momentum.time[i]<< " s\n";
        cout << i+1 << "º > Average Velocity: " << data_for_linear_momentum.averageVelocity[i]<< " m/s\n";
        cout << i+1 << "º > Linear Momentum: " << data_for_linear_momentum.linearMomentum[i]<< " kg.m/s\n";
    }
    if(collisionType) {
        cout << "\nList of calculated data - Inelastic Collision";
        cout << "\nTotal | Linear Momentum: " << data_for_linear_momentum.linearMomentum[data_for_linear_momentum.linearMomentum.size()-1] << " kg.m/s";
    }

}