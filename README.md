# NebelmaschineArtNet_ESP8266

This project involves controlling a fog machine using an ESP8266 microcontroller via the Art-Net protocol. It includes both the firmware for the ESP8266 and the web interface for configuring and controlling the fog machine.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project allows you to control a fog machine using an ESP8266 microcontroller via Art-Net, a protocol for sending DMX512 data over an IP network. The system includes a web interface to configure and operate the fog machine.

## Features

- Control fog machine via Art-Net protocol
- Web-based configuration and control interface
- OTA (Over-The-Air) updates for firmware

## Requirements

- ESP8266 microcontroller
- Fog machine with a wire to start to power the pump
- Optional: Art-Net compatible lighting controller software or hardware

## Installation

### Hardware Setup

1. Connect the ESP8266 to the fog machine using, for example, a relay.
2. Ensure the ESP8266 is powered and connected to your local network.

### Software Setup

1. Clone or download the repository.
2. Open the Arduino IDE and install the required libraries:
    - ESP8266 board support
    - ArduinoOTA
    - ESPAsyncWebServer
    - DNSServer
    - [ArtNet](https://github.com/hideakitai/ArtNet)
3. Open the `main/main.ino` file in Arduino IDE.
4. Configure your Wi-Fi settings and other necessary configurations in `main/fog_config.h`.
5. Upload the code to your ESP8266.

## Usage

1. Once the ESP8266 is powered and connected to the network, access the web interface by entering the IP address assigned to the ESP8266 in your web browser.
2. Use the web interface or Art-Net to configure and control the fog machine.

## File Structure

- `main/`: Contains the main firmware files for the ESP8266.
- `web/`: Contains the files for the web interface.
- `TechnikFLGFogmachine.Fixture`: Configuration file for the fog machine.
- `convert.py`: Python script for converting the web fils into ".h" files.

## Contributing

Contributions are welcome! Please fork this repository and submit pull requests with your changes. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.