# 🤖 Robotic Arm Simulation with Real-time Sensor Control

![Demo](https://via.placeholder.com/800x400.png?text=Robot+Arm+and+Stylus+Visualization) *Replace with actual GIF/video*

A dynamic project that bridges hardware sensors 🎚️ and MATLAB visualization 📊 to control a virtual Kinova Jaco robotic arm and 3D stylus in real-time. Powered by **Arduino (ESP32)** and **MATLAB Robotics Toolbox**.

## 🚀 Overview
- **Arduino**: Reads 3 potentiometers (joint angles) and a BNO055 gyroscope 🧭 using FreeRTOS tasks.
- **MATLAB**: Simulates a Kinova Jaco arm 🤖 and renders a stylus ✍️ reflecting sensor orientation.
- **Data Pipeline**: Serial communication 📟 streams sensor data to MATLAB for live updates.

---

## ✨ Features
- ✅ Real-time sensor data acquisition (10Hz pots / 2Hz gyro)
- ✅ Multi-threaded Arduino code using FreeRTOS 🧵
- ✅ 3D visualization of robotic arm kinematics 🤯
- ✅ Quaternion-based orientation tracking 🔄
- ✅ Custom piecewise linear calibration for pots 📐

---

## 🔧 Hardware Requirements
| Component          | Quantity | Emoji |
|--------------------|----------|-------|
| ESP32 Board        | 1        | 🎛️   |
| BNO055 IMU         | 1        | 🧭    |
| Linear Potentiometer (10kΩ) | 3 | 🎚️   |
| USB Cable          | 1        | 🔌    |

---

## 📦 Software Requirements
- **Arduino IDE** (with libraries):
  - `Adafruit BNO055` 📚
  - `Adafruit Unified Sensor` 📚
- **MATLAB 2021a+**:
  - Robotics System Toolbox 🤖
  - Instrument Control Toolbox 📡

---

## 🔩 Setup & Connections

### 🎛️ Arduino Wiring Table
| Component | ESP32 Pin | Emoji |
|-----------|-----------|-------|
| Pot 1     | GPIO 34   | 🔴    |
| Pot 2     | GPIO 35   | 🟢    |
| Pot 3     | GPIO 36   | 🔵    |
| BNO055 SDA| GPIO 21   | 🟡    |
| BNO055 SCL| GPIO 22   | 🟠    |

### 🧭 BNO055 Setup
- `VIN` → `3.3V` 🔋
- `GND` → `GND` ⚡
- Ensure I2C communication is stable (check with `Wire` library 🔍).

---

## 🛠️ Installation

1. **Arduino Setup**:
   ```bash
   # Install required libraries via Arduino Library Manager
   Adafruit BNO055
   Adafruit Unified Sensor
