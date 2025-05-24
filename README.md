# 🚗 Automatic Climate Control System (C++ Simulation)

This project simulates an **Automatic Climate Control** system in C++, modeled after a dSPACE/Simulink control model using thermistor-based temperature sensing and state machine logic.

---

## 🔧 Features

* Thermistor-based lookup table for temperature-resistance conversion
* Voltage I/O Signal computed using voltage divider formula
* Control logic:

  * `BlowerOut` depends on absolute temperature difference
  * `AirDistV`: Face (0), Feet (1), Defrost (2)
  * `RecycAirV`: Recirculation ON/OFF
* Interactive command-line input for test conditions

---

## 📊 Controller Results Summary

Here’s an overview of controller behavior across three validated test cases, showcasing ControlDesk-style response:

| Test Case | External Temp | Setpoint | Vin (V) | BlowerOut |
| --------- | ------------- | -------- | ------- | --------- |
| Case 1    | 25°C          | 13°C     | 13.34   | 0.48      |
| Case 2    | 26°C          | 9°C      | 9.25    | 0.68      |
| Case 3    | 10°C          | 28°C     | 14.00   | 0.72      |

### 🔍 Detailed Case Analysis

**Case 1**: External Temp = 25°C, Setpoint = 13°C

* Result: Vin = 13.34V, BlowerOut = 0.48
* Air distribution mode: Defrost (AirDistV = 2), Recirculation Off (RecycAirV = 0)
* ➤ The system reacts to a moderate cooling need, increasing airflow moderately.

**Case 2**: External Temp = 26°C, Setpoint = 9°C

* Result: Vin = 9.25V, BlowerOut = 0.68
* Air distribution mode: Defrost (AirDistV = 2), Recirculation Off (RecycAirV = 0)
* ➤ A high cooling demand results in a stronger blower response.

**Case 3**: External Temp = 10°C, Setpoint = 28°C

* Result: Vin = 14.00V, BlowerOut = 0.72
* Air distribution mode: Face (AirDistV = 0), Recirculation On (RecycAirV = 1)
* ➤ Heating requirement triggers recirculation and high airflow toward passengers.

  

---

## 📁 Folder Structure

```
AutomaticClimateControl/
├── climate_control.cpp       # Main simulation code
├── lookup_table.xlsx         # Thermistor resistance vs. temperature
├── graphs/                   # Output graphs for each test case
│   ├── TEST01Results.png
│   ├── TEST02Results.png
│   └── TEST03Results.png
└── README.md
```

---

## ▶️ How to Run

1. Open `climate_control.cpp` in an online compiler like [OnlineGDB](https://www.onlinegdb.com/online_c++_compiler)
2. Compile and run the code
3. Enter values for:

   * External temperature
   * Setpoint temperature
4. View live output of voltage, blower logic, and temperature readings

---

## 🖥️ Console Output Example (Case 1)

```
External Temp: 25.0000 °C
Setpoint Temp: 13.0000 °C
Voltage I/O Signal: 13.3400 V
Resistance to Temperature Output: 25.0000 °C
Thermometer Display: 13.0000 °C

---- Stateflow Outputs ----
BlowerOut: 0.480000
AirDistV (0-Face, 1-Feet, 2-Defrost): 2
RecycAirV (1=Recyc_On, 0=Recyc_Off): 0
```

---

