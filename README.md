# stm32g0-bare-metal

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Contents](#contents)
- [How to Use](#how-to-use)

## Introduction

Bare metal STM32G0 examples to serve as starting points for projects. Contains necessary libraries for interfacing with peripherals and sensors. CMSIS library is added for a general support.

## Project Structure

Describe the overall structure of the project repository, including directories, files, and their purposes.

## How to Use

* First, clone the project using `git clone https://github.com/erhangk/stm32g0-bare-metal.git `.
* Download and install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html). Select workspace on the root folder, then import existing projects to workspace. (File -> Import -> General -> Existing Projects into Workspace)
* You do not need any additional tools. It comes with the compiler and debugger pre-installed.
* Repository has a static library that all the projects use commonly. Static library includes all the header and project files.

## Projects

- `ASM_001_Single_Led`: Contains code for controlling a single LED.
- `ASM_002_Multiple_Leds`: Controlling 8 LED.
- `ASM_003_Led_Toggle`: Toggling a single LED.
- `ASM_004_Multiple_Leds_Toggle`: Toggling multiple LEDs.
- `ASM_005_Button_Polling`: Button reading with polling.
- `ASM_006_Led_Shift`: Controlling LED with shifting pattern.
- `ASM_007_Knight_Rider`: Implementing a Knight Rider effect with LEDs.
- `ASM_008_Led_Button_Counter`: Counting button presses and controlling LEDs accordingly.
- `Libraries`: This static library contains libraries and external dependencies used in the project.
- `REGC_001_SysTick_Timer`: Implementation of a delay function using the SysTick timer.
- `REGC_002_Timer_Interrupt`: Toggling the on-board led using timer interrupts.
- `REGC_003_Seven_Segment_Display`: Contains code examples for driving a seven-segment display.
- `REGC_004_IWDG`: Implementation of Independent Watchdog  timer (IWDG).
- `REGC_005_IWDG_Seven_Segment`: Contains code examples combining the IWDG with a seven-segment display.
- `REGC_006_UART_Receive_Transmit`: Contains code examples for UART receive and transmit operations.
- `REGC_007_PWM`: Pulse Width Modulation (PWM) control.
- `REGC_008_Keypad`: Contains code examples for interfacing with a keypad and combining with PWM and UART.
- `REGC_009_ADC_POT_PWM_Led_Control`: Contains code examples for using ADC to read potentiometer and control LEDs with PWM.
- `REGC_010_Sound_Sensor_SSD`: Implementation of a knock counter using a sound sensor with a seven-segment display.
- `REGC_011_MPU6050`: Contains code examples for interfacing with the MPU6050 sensor.
