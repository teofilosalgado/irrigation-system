# Irrigation System

A simple 8051-based irrigation system for my garden.

## Installation

### System requirements

- sdcc
- make
- avrdude

### Hardware specific settings

The `src/lib/global.h` file contains constants defined according to the
suggested circuit, more specifically:

- Countdown timer register values

- Pins used for the LCD display and buttons

Feel free to edit them according to your circuit.

### Compilation

```sh
make
```

### Flashing

```sh
make PORT=/dev/ttyUSB0 flash
```

### Suggested Circuit

## Usage

![State machine](state-machine.png)
