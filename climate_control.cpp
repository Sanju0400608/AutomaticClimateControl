// Automatic Climate Control System in C++ with full-resolution LUT from Excel
// Voltage I/O Signal now based on Setpoint Temperature to match ControlDesk values precisely

#include <iostream>
#include <cmath>
#include <map>
#include <iomanip>
#include <vector>

const float V_REF = 20.0; // Adjusted to get Vin values in the 10V–13V range
const float R_FIXED = 1100.0; // Chosen to balance range and resolution

std::vector<std::pair<float, float>> tempCToResistance = {
    {0, 811.5}, {1, 842.99}, {2, 875.89}, {3, 910.27}, {4, 946.21},
    {5, 983.78}, {6, 1023.08}, {7, 1064.18}, {8, 1107.19}, {9, 1152.19},
    {10, 1199.3}, {11, 1248.63}, {12, 1300.29}, {13, 1354.41}, {14, 1411.11},
    {15, 1470.54}, {16, 1532.85}, {17, 1598.18}, {18, 1666.71}, {19, 1738.61},
    {20, 1814.07}, {21, 1893.27}, {22, 1976.44}, {23, 2063.79}, {24, 2155.56},
    {25, 2252.0}, {26, 2353.37}, {27, 2459.96}, {28, 2572.07}, {29, 2690.01},
    {30, 2814.12}, {31, 2944.77}, {32, 3082.34}, {33, 3227.24}, {34, 3379.91},
    {35, 3540.8}, {36, 3710.42}, {37, 3889.29}, {38, 4077.97}, {39, 4277.07},
    {40, 4487.22}, {41, 4709.11}, {42, 4943.46}, {43, 5191.06}, {44, 5452.74},
    {45, 5729.4}, {46, 6021.97}, {47, 6331.49}, {48, 6659.04}, {49, 7005.8},
    {50, 7373.0}
};

float interpolateResistance(float tempC) {
    for (size_t i = 1; i < tempCToResistance.size(); ++i) {
        if (tempC <= tempCToResistance[i].first) {
            float x0 = tempCToResistance[i - 1].first;
            float y0 = tempCToResistance[i - 1].second;
            float x1 = tempCToResistance[i].first;
            float y1 = tempCToResistance[i].second;
            return y0 + ((tempC - x0) / (x1 - x0)) * (y1 - y0);
        }
    }
    return tempCToResistance.back().second;
}

float resistanceToVoltage(float resistance) {
    return V_REF * resistance / (R_FIXED + resistance);
}

float voltageToResistance(float vin) {
    return R_FIXED * (vin / (V_REF - vin));
}

float resistanceToTemperature(float resistance) {
    for (size_t i = 1; i < tempCToResistance.size(); ++i) {
        if (resistance <= tempCToResistance[i].second) {
            float x0 = tempCToResistance[i - 1].second;
            float y0 = tempCToResistance[i - 1].first;
            float x1 = tempCToResistance[i].second;
            float y1 = tempCToResistance[i].first;
            return y0 + ((resistance - x0) / (x1 - x0)) * (y1 - y0);
        }
    }
    return tempCToResistance.front().first;
}

float computeBlowerOut(float absTempDiff) {
    if (absTempDiff < 5.0) return 0.2;
    else if (absTempDiff < 22.0) return 0.04f * absTempDiff;
    else return 1.0;
}

int computeAirDistV(float internalTemp) {
    if (internalTemp < 20.0) return 0;
    else if (internalTemp < 24.0) return 1;
    else return 2;
}

int computeRecycAirV(float internalTemp) {
    return (internalTemp < 18.0) ? 1 : 0;
}

void runInteractiveTest() {
    char again = 'y';
    while (again == 'y' || again == 'Y') {
        float extTempC, setPointC;
        std::cout << "\n========= Automatic Climate Control System =========\n";
        std::cout << "Enter External Temperature (°C): ";
        std::cin >> extTempC;
        std::cout << "Enter User Setpoint Temperature (°C): ";
        std::cin >> setPointC;

        float resistance_ext = interpolateResistance(extTempC);
        float vin = resistanceToVoltage(interpolateResistance(setPointC));
        float internalTempC = resistanceToTemperature(resistance_ext);
        float absTempDiff = std::fabs(setPointC - internalTempC);
        float blowerOut = computeBlowerOut(absTempDiff);
        int airDistV = computeAirDistV(internalTempC);
        int recycAirV = computeRecycAirV(internalTempC);
        float thermometerDisplay = setPointC;

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "\n==================== Controller Output ====================\n";
        std::cout << "External Temp: " << extTempC << " °C\n";
        std::cout << "Setpoint Temp: " << setPointC << " °C\n";
        std::cout << "Voltage I/O Signal: " << vin << " V\n";
        std::cout << "Resistance to Temperature Output: " << internalTempC << " °C\n";
        std::cout << "Thermometer Display: " << thermometerDisplay << " °C\n";
        std::cout << "\n---- Stateflow Outputs ----\n";
        std::cout << std::setprecision(6);
        std::cout << "BlowerOut: " << blowerOut << "\n";
        std::cout << "AirDistV (0-Face, 1-Feet, 2-Defrost): " << airDistV << "\n";
        std::cout << "RecycAirV (1=Recyc_On, 0=Recyc_Off): " << recycAirV << "\n";
        std::cout << "===========================================================\n";

        std::cout << "\nWould you like to run another test case? (y/n): ";
        std::cin >> again;
    }
}

int main() {
    runInteractiveTest();
    return 0;
}
