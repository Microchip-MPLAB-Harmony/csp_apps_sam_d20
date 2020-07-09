[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Systick periodic interrupt

This example shows how to use the SysTick to generate periodic interrupts.

## Description

This example application configures the SysTick Peripheral Library to generate periodic ticks. The application registers a periodic timeout callback. It toggles an LED every time the callback is triggered.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/csp_apps_sam_d20) and click

![clone](../../../docs/images/clone.png)

Path of the application within the repository is **apps/systick/systick_periodic_timeout/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_d20_xpro.X | MPLABX project for [SAM D20 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAMD20-XPRO) |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_d20_xpro.X | [SAM D20 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAMD20-XPRO)
|||

### Setting up [SAM D20 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAMD20-XPRO)

- Connect the Debug USB port on the board to the computer using a micro USB cable

## Running the Application

1. Build and Program the application using its IDE
2. The LED blinks continuously

Following table provides the LED name:

| Board      | LED Name |
| ---------- | ---------------- |--------- |
| [SAM D20 Xplained Pro Evaluation Kit](https://www.microchip.com/developmenttools/ProductDetails/ATSAMD20-XPRO) |SW0 |
|||