# Betmobil 2d graphics Project

## Overview

The Betmobil project implements a car dashboard instrument panel that simulates various functionalities of a car's dashboard. This project is designed to provide a graphical interface that includes a tachometer, odometer progress bar, warning indicators, gear indicator, and a customizable mouse cursor representation.

## Features

1. **Tachometer**:
   - Displays the current RPM (revolutions per minute) of the engine.
   - The needle's color changes over time.
   - The needle is represented as a thick line (greater than 1 pixel).
   - Current RPM is obtained using `car.getTachometer()`.

2. **Odometer Progress Bar**:
   - A progress bar that indicates the distance traveled in kilometers.
   - The bar has 10 increments; it resets after exceeding 10 kilometers.
   - Distance traveled is retrieved using `car.getOdometer()`.
   - For every additional 10 kilometers, a new segment is added to the progress bar.

3. **Warning Indicators**:
   - "Check Engine" light and Battery Problem light indicators.
   - Indicators activate when `car.getCheckEngineLight()` or `car.getBatteryProblemLight()` return true.
   - Pressing `C` activates the "Check Engine" indicator with `car.setCheckEngine(true)`.
   - Pressing `B` activates the Battery Problem indicator with `car.setBatteryLight(true)`.

4. **Gear Indicator**:
   - Displays the current gear level as a circular light that blinks from black to a random color.
   - The speed of blinking increases with higher gear levels, creating noticeable differences between adjacent gears.
   - Gear level is obtained using `car.getGear()`.

5. **Custom Mouse Cursor**:
   - A simplified representation of a mouse cursor that can be controlled with the **WASD** keys:
     - **W**: Move up.
     - **A**: Move left.
     - **S**: Move down.
     - **D**: Move right.
   - The cursor remains within the display boundaries.
   - The display adapts based on the current gear:
     - **Gear 1**: Only the vertices of the triangles are shown.
     - **Gear 2**: Only the edges of the triangles are shown.
     - **Gears 3-5**: The interior of the triangles is displayed.
   - Pressing `P` makes the cursor semi-transparent, allowing the background color to show through.
   - Pressing `X` restores the cursor's opacity.

6. **Student Information**:
   - The display includes the name, surname, and my student ID

7. **Screenshot**
![display](<Screenshot 2024-09-20 191201.png>)