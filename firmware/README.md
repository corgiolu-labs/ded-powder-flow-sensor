# Powder-flow controller (Arduino)

Benchtop firmware for the powder-flow prototype — an **LCD + numeric keypad** menu that lets you:

- select the **powder material** (steel, titanium, copper, aluminium, Inconel, vanadium);
- set the **flow setpoint** in g/min;
- drive the **vibrating feeder** via PWM (`VIBRO_PIN`);
- read the **photodiode** receiver (`PHOTODIODE_PIN`);
- run a **PID** loop to hold the setpoint.

`powder_flow_controller.ino` is the main sketch; `getgrams.h`, `lcd.h`, `lcdkeypad.h`, `numerickeypad.h`
are the helper modules (LCD driver, keypad handling, timed keypad entry of the g/min value).
