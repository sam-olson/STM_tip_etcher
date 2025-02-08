# STM Tip Etcher

## Preliminary
This repository contains design files for building a microcontroller-based etcher for creating scanning tunneling microscopy (STM) tips from tungsten wire. The system works by applying a voltage between two tungsten electrodes immersed in an etchant (in this case, 1 M NaOH). The resistance between the two electrodes is monitored through a voltage divider formed between the electrodes and a 100 Ω reference resistor. The output voltage of the divider is read by an analog input pin on the microcontroller. When a spike in resistance between the etching electrodes is detected, a transistor switch shuts off power to the tip, preventing over-etching and rounding of the tip. Using tips etched via this system, high resolution STM images of highly-oriented pyrolytic graphite (HOPG) have been obtained.

The following items are required to assemble this system:

*Equipment*

- Soldering iron
- 3D-printer

*Parts (see the included Bill of Materials for sourcing)*

- Arduino Nano (x1)
- 300 Ω resistor (x1)
- 100 Ω resistor (x2)
- Green LED (x1)
- 2N3904 NPN transistor (x1)
- M4x6.4mm heat set insert (x2)
- M4x8mm set screw (x2)
- 5x7 cm perfboard (x1)
- M3x14mm socket head screw (x4)
- M3x11mm spacer (x4)
- M3x3.8mm heat set insert (x4)

## Build Instructions
### Assembling the Circuit

![fig1](/figures/Figure1.jpg)

Figure 1: a) Electrical schematic for the tip etching set up, b) assembled circuit board with header pins labeled

1. Solder electrical components onto a 5x7 cm perfboard following the schematic shown in Fig. 1
2. Power can be supplied to the electrodes from the Arduino’s 5V pin, or an external benchtop power supply
can be used if the current required is ≥ 500 mA or a different voltage is required. If an external power supply is used, it can also power the Arduino through the VIN pin (as long as the voltage is ≤ 12 V)
3. Header pins and alligator clip cables can be used for interfacing with the tungsten tip and counter electrodes

### 3D-Printing Components
3D-print the STEP files for the electrode holding fixture and the circuit board base in PLA (see Fig. 2).

![fig2](/figures/Figure2.jpg)

Figure 2: Renders of 3D-printed components: a) electrode holding fixture (ElectrodeHoldingFixture.step), b) circuit board base (CircuitBoardBase.step)

### Preparing the Electrode Holding Fixture for Use

![fig3](/figures/Figure3.jpg)

Figure 3: a) Installing the M4x6.4mm threaded inserts into the electrode holding fixture using a soldering iron tip, b) installation of set screws, c) tip electrode added to electrode holding fixture, d) counter electrode added to electrode holding fixture

1. Using a soldering iron set to 250 °C, heat set two M4x6.4mm threaded inserts into the 6.2 mm holes on the front of the fixture (Fig. 3a)
2. Insert a M4x8mm set screw into each threaded insert, these will be used to press against the tungsten wires to hold them in place during etching (Fig. 3b)
3. Cut a 100 mm length of 0.25 mm diameter tungsten wire and form a 6 mm diameter loop at one end, this will serve as the counter electrode
4. Cut a 75 mm straight length of 0.25 mm diameter tungsten wire, this will serve as the tip electrode
5. Push the tip electrode through the rectangular hole on the left side of the bottom of the electrode holding fixture, leaving roughly 10 mm exposed at the bottom, and fasten it in place by tightening the set screw (Fig. 3c)
6. Push the straight end of the counter electrode through the rectangular hole on the right side of the bottom of the electrode holding fixture
7. Place a straight piece of 0.25 mm tungsten wire into the hole on the lefthand side of the top of the fixture and push it through until 14 mm of wire is exposed between the bottom of the fixture and the top of the loop
8. Create a 90° bend 7 mm from the top of the loop in the counter electrode and situate the loop so that the tip electrode sits in the middle (Fig. 3d)
9. The electrode holding fixture includes two M4-size holes for optional attachment to a stand, however the fixture can also easily be held in place via a lab stand clamp

### Attaching the Circuit Board to the Circuit Board Base

![fig4](/figures/Figure4.jpg)

Figure 4: a) Circuit board base with heat set inserts installed, b) circuit board base with circuit board and standoffs attached

1. Install four M3x3.8mm heat set inserts using a soldering iron set to 250 °C into the 5.5 mm diameter circular recesses on the top of the circuit board stand (Fig. 4a)
2. Place the M3x10mm unthreaded standoffs on the threaded inserts
3. Place the circuit board on top of the unthreaded standoffs and secure it in place with four M3x14mm socket screws (Fig. 4b)
4. Load the firmware (`STM_tip_etcher.ino`) onto the Arduino Nano via the Arduino IDE

## Using the Tip Etcher

### Running an Etch Recipe

1. Prepare an etchant solution of 1 M NaOH in a small dish
2. Attach the electrode holding fixture to a stand with two M4 screws, or place it into a lab stand clamp and lower it until both the tip electrode and the loop of the counter electrode are submerged just below the surface of the etchant
3. Using alligator clips, connect the tip electrode to the 5V pin of the Arduino (or an external power supply), and connect the counter electrode to the counter electrode header (the junction with the 100 Ω resistor and pin A3 on the Arduino)
4. If using an external power supply, ensure that the voltage is kept below 12V and that the ground is tied to the ground pin of the Arduino
5. Turn on the power supply/Arduino, this will begin the tip etching process
6. For a voltage of 5V, a counter electrode loop of 6 mm, and a 1 M NaOH etchant, the etch time is typically around 20 minutes
7. Once the bottom of the tip electrode drops off into the etchant, the resistance between the tip and counter electrode will increase drastically and the microcontroller will automatically stop the power to the electrodes to prevent overetching. The LED will illuminate at this point to indicate that the etching is complete

### Modifying the Firmware
The firmware for the system (`STM_tip_etcher.ino`) is designed to be easy to modify if necessary. There are two important variables for etch profile modification: the voltage threshold below which the etching halts (variable `v_threshold`), and the minimum etching time before cut off can occur (variable `t_threshold`). Variation in one of several experimental parameters can result in the need to modify the voltage and time thresholds. For example, a larger counter electrode diameter may result in a higher final resistance (and so a lower voltage threshold), while an increase in etchant molarity can result in a lower final resistance (and so higher voltage threshold) and/or a shorter etch time. The firmware prints the voltage reading to the serial port during etching, so it is advised to monitor this during several etches once the physical arrangement of your set up is finalized to determine where to set your thresholds.

## Results
![fig5](/figures/Figure5.jpg)

Figure 5: An STM tip etched from 0.25 mm tungsten wire using this system

![fig6](/figures/Figure6.jpg)

Figure 6: STM micrograph of highly oriented pyrolytic graphite (HOPG) taken using a tip etched with this system
