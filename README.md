OCILLOPADDLE
============

Custom game controllers for use with XYNTH based games on the OSCILLOTRON. Build during #PegJam2018.

Hardware
--------

These game controllers were build with a 5V (16 MHz) Pro Micro board, a 20 detent (4 point per detent) rotary encoder with the detent mechanism removed, a low profile arcade button, and a plain plastic project box. Wiring is pretty simple and can likely be inferred from the code.

Software
--------

The paddles emulate generic gamepads. The arcade button is the primary button, the encoder button is secondary, and the encoders rotation is mapped as though the primary joystick is continuously being pushed fully in a direction relative to the encoders current orientation. In order to get the gamepads to display "OSCILLOTRON" as the controller name on the PC, the SparkFun boards file was modified to add an extra entry for the Pro Micro CPU variants. This modified file has been included here as reference.
