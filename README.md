# In-situ powder-flow sensor for metal DED additive manufacturing

> Research internship — **Joanneum Research (Austria), 2019–2020**.
> Developing an **in-situ sensor** to measure, and ultimately close the loop on, the **metal powder mass-flow** that feeds a **laser Directed Energy Deposition (DED / LMD)** process.

> ℹ️ **Note.** This repository is my own account of the engineering, with my own design artifacts (system concept, sensor PCB, prototype). The formal project deliverable was co-authored with the host institute and produced under an EU-funded project — it is **the consortium's document and is not reproduced here**, nor are partner/colleague names, the grant identifier, measured project data or any third-party reference material. The confidentiality term covering the work (a 5-year NDA signed in 2020) has expired.

## The problem

In **Directed Energy Deposition (DED)** — also called **Laser Metal Deposition (LMD)** — metal powder is carried by an Argon stream through a ~4 mm tube to the laser head, where it melts into the moving melt pool and builds the part up layer by layer on a multi-axis robot.

The **powder mass-flow rate** (typically **2.5–50 g/min**, i.e. 0.08–0.83 g/s) sets the energy delivered *per unit mass* and so directly drives deposition quality — geometry, density, dilution. But it is hard to measure **in situ**:

- the "fluid" is a **heterogeneous solid–gas mix** (Argon-to-powder volume ratio ≈ **99:1**) — a tiny mass of powder in a lot of gas;
- the powder feeder emits **irregularly**, with **no fast feedback** near the head — flow can drift by **up to 30 %**.

Closed-loop control therefore needs a **high-sensitivity, high-speed** flow sensor placed close to the nozzle. That sensor was the goal of my internship.

## System concept

<p align="center">
  <img src="docs/images/concept-system.svg" width="620"><br>
  <em>Proposed powder-flow control concept: buffered hopper with an adjustable "loose-angle" outlet, an electromagnetically-actuated gate, and an <strong>inductance sensor</strong> (sensing coil around the delivery tube) feeding the flow signal back to the controller.</em>
</p>

## Sensing approaches I tested

I started from a systematic survey of flow-measurement physics, then narrowed by **sensitivity** and **speed**:

| Family | Examples | Verdict for powder-in-Argon |
|---|---|---|
| Mechanical | orifice, Venturi, turbine, Coriolis | too slow / intrusive for a fast micro-flow |
| Electrical | hot-wire, magnetic meters | promising frequency response |
| **Magnetic** | **inductance / RF frequency shift** | **pursued** — coil permeability changes with powder |
| Acoustic | ultrasonic transit-time, Doppler, magneto-acoustic | tested as an alternative |
| Optical | laser scattering + photodiode | tested — fastest, but optics foul |

The **magnetic / RF path**, in four iterations:

1. **Inductance measurement** — a small sensing coil (`L = µN²S/l`); the powder inside it changes the permeability. *Result: the change was far too small for a cheap LCR meter to resolve.*
2. **Frequency-shift** — put the coil in an oscillator (`f₀ = 1/2π√(LC)`), so a tiny ΔL becomes a measurable Δf. *Result: ~2 kHz of signal, but unstable — 200–300 Hz jitter from the intermittent particle stream.*
3. **Super-heterodyne + Faraday cage** — borrow the radio-receiver principle (local oscillator → fixed IF) to pull out the small shift, the circuit shielded in a metal box. *Result: clean on/off detection, but flow-rate changes still hard to resolve.*
4. **PLL-stabilized sensor** — lock the base frequency with a **PLL** and feed a professional SMD super-heterodyne mixer (**MC1496**) directly, removing over-air transmission and spurious fields. *Result: **valid** — sensitive enough to detect powder-flow variations.*

<p align="center">
  <img src="docs/images/pwd-sensor-pcb.png" width="620"><br>
  <em>My PWD-sensor board — the sensing element is the on-board <strong>inductor</strong>, read out by a stabilized RF oscillator (signed "Alex83 PWD sensor 1.0").</em>
</p>

In parallel I also tested a **magneto-acoustic** method (spectral analysis of the sound vs. flow rate) and an **optical** setup — a 3 mW laser diode (driven at constant current with an `LM317` / `REF25Z` reference) and an **avalanche photodiode** receiver.

## Prototype

When COVID-19 closed access to the production DED cell, I **built a benchtop powder feeder** to keep experimenting off-site: a vibrating-sheet feeder (no carrier gas) dropping powder through the PWD sensor, driven by an **Arduino MKR WiFi 1010** controller running:

- a **PID** loop regulating flow via a **PWM-driven micro-vibrator**,
- **sampling** of the sensor signal and **SD-card logging**,
- multi-channel I/O (Bluetooth / WiFi / USB / Ethernet) with **Modbus TCP** over the MKR ETH shield.

<table>
  <tr>
    <td width="50%" align="center"><img src="docs/images/prototype-feeder.jpg" height="320"></td>
    <td width="50%" align="center"><img src="docs/images/prototype-demo.gif" height="320"></td>
  </tr>
  <tr>
    <td align="center"><em>Benchtop prototype: reservoir, vibrating feeder, sensor board and LCD — Arduino-controlled.</em></td>
    <td align="center"><em>Powder metered through the sensor, PID setpoint on the LCD.<br>▶ <a href="docs/video/prototype-demo.mp4">Full demo video</a></em></td>
  </tr>
</table>

## Results (honestly)

| Approach | Outcome |
|---|---|
| Inductance (LCR) | change too small to resolve |
| Frequency-shift | ~2 kHz signal, unstable |
| Super-heterodyne | reliable on/off, weak rate discrimination |
| **PLL-stabilized RF** | **valid — sensitive to flow variation** ✓ |
| Optical (laser + APD) | good signal, but powder fouls the tube |

Two failure modes were pinned down and given a path forward: **Argon's diamagnetism** (µ < 1) tends to mask the powder's contribution → a **dual-oscillator differential** scheme to cancel the gas term; and **environmental magnetic / vibration noise** → shielding. For the optical fouling, a **self-cleaning square tempered-glass tube** was proposed.

## Skills demonstrated

**Embedded** (PIC, Arduino MKR) · **RF & analog** (oscillators, PLL, super-heterodyne, MC1496 mixer, frequency/impedance measurement) · **sensor & signal conditioning** · **control systems** (PID, closed-loop) · **mechatronics** (PWM actuation, custom feeder) · **CAD** (Autodesk Inventor) and **PCB design** · **metal additive manufacturing** (DED/LMD & PBF on a 6-axis robot; certified *Additive Manufacturing Operator*, Bureau Veritas Italia 2020) · **research method** (method selection, prototyping, honest evaluation).

## Context

Research internship at **Joanneum Research** (Austria), **2019–2020**, in metal additive manufacturing — the start of my path into embedded & sensor engineering, which continued at Leonardo (radar integration & validation) and across the projects below.

## Author

**Alessandro Corgiolu** — System / Embedded Integration & Validation Engineer
GitHub [@corgiolu-labs](https://github.com/corgiolu-labs) · part of a hardware portfolio that includes [JONNY5](https://github.com/corgiolu-labs/jonny5) (VR-teleoperated 6-DoF arm), the [UAV LoRa transponder](https://github.com/corgiolu-labs/uav-lora-transponder), [ESP32 radar](https://github.com/corgiolu-labs/esp32-radar-tracking) and [RASPYNVERTER](https://github.com/corgiolu-labs/raspinverter).
