#include <iostream>
#include <iomanip>
#include "core/Engine/VortecV6.h"
#include "core/TestStand/TestStandOverheat.h"
#include "core/TestStand/TestStandMaxPower.h"


void initConfig(EngineSimulationConfig& config, double ambientTemp) {
    config.ambientTemp = ambientTemp;
    config.inertia = 10.0;
    config.overheatTemp = 110.0;
    config.hm = 0.01;
    config.hv = 0.0001;
    config.c = 0.1;
    config.torqueMap = {
        {0.0, 20.0},
        {75.0, 75.0},
        {150.0, 100.0},
        {200.0, 105.0},
        {250.0, 75.0},
        {300.0, 0.0},
    };
}


int main(){
    setlocale(LC_ALL, "Russian");
    std::cout << std::fixed << std::setprecision(6);
    double ambientTemp = 0.0;
    const double stepSec = 0.1;
    std::cout << "Введите температуру окружающей среды: " << '\n';
    std::cin >> ambientTemp;
    
    EngineSimulationConfig config;
    initConfig(config, ambientTemp);

    VortecV6 vortecV6(config);
    TestStandOverheat testStandOverheat;
    TestStandMaxPower testStandMaxPower;

    testStandOverheat.Run(vortecV6, stepSec);
    const auto& resultOverHeat = testStandOverheat.GetResult();

    testStandMaxPower.Run(vortecV6, stepSec);
	const auto& resultMaxPower = testStandMaxPower.GetResult();

    std::cout << "Время до перегрева: " << resultOverHeat.timeToOverheatSec << " сек\n";
    std::cout << "Макс мощность двигателя: " << resultMaxPower.maxPowerKW << " кВт, при скорости вращения коленвала: " << resultMaxPower.speedAtMaxPowerRadSec << " рад/сек \n";
    
    return 0;
}

