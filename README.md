# IDSO1070 Protocol Library (for Linux)

This is a reverse engineered implementation of the protocol used to communicate with the 2 channel digital storage oscilloscope IDSO1070 from Hantek.
It's possible to communicate with the device over WiFi (TCP) as well as USB.

USB ID: ```0483:5740 [STMicroelectronics STM32F407]```

## Current state of development

**Attention:**  This is not a production ready version, there's still a lot of stuff to do. If you're interested to support this library, just contact me.

### Features

* Connection to device with WiFi (TCP) or USB
* Send command packets ([Packet Format](lib/README.md#request-command-packet))
* Receive and parse command response and sample data packets ([Packet Format](lib/README.md#response-packet))

### Next steps

#### Library

* Handling for interrupted connections
* Better overall exception handling

#### GUI

* Implement sample streaming and visualization
* Add controls for device settings
* Add controls to display device infos

## Dependencies

* GCC
* CMake: >= 3.5
* Boost: >= 1.58.0
* gtkmm: >= 3.18.0
* [liquid-dsp: >= 1.3.0](https://github.com/jgaeddert/liquid-dsp/tree/v1.3.0)

On Ubuntu/Mint you can run ```apt install libboost-all-dev libgtkmm-3.0-dev cmake gcc``` to install the dependencies.
You have to compile and install liquid-dsp manually, for instructions follow the link above.

## Build instructions

Just run the ```build.sh``` or execute following commands in your shell:

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

To run the GUI without installing, you can execute the ```run.sh```

There is also a pre configured task for building (CTRL-SHIFT-B) in vscode and a launch.json to debug(F5).

## Directories

* gui: Simple Gtk GUI
* lib: Implementation of the protocol itself
* include: Library headers
* cmake: Helper scripts for cmake

## Links

* Product page: http://www.hantek.com/en/ProductDetail_2_10165.html
* [sigrok: Hardware photos & information only, not supported by the library](https://sigrok.org/wiki/Hantek_iDSO1070)