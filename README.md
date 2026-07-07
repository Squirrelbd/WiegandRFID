# WiegandRFID

A simple, efficient Arduino library for ESP32 to read Wiegand 26-bit RFID cards.

## Overview

WiegandRFID is a lightweight library designed specifically for ESP32 microcontrollers to interface with Wiegand 26-bit RFID readers. It provides an easy-to-use API for detecting and reading RFID cards, with built-in duplicate detection and automatic noise handling.

### Key Features

- **26-bit Wiegand Protocol Support**: Reads standard 26-bit RFID cards with facility code and card number extraction
- **ESP32 Optimized**: Uses IRAM_ATTR interrupt handlers for reliable performance
- **Duplicate Card Detection**: Configurable time window to prevent duplicate reads
- **Noise Handling**: Automatically clears invalid data and recovers from transmission errors
- **Simple API**: Easy to integrate with just a few function calls

### Use Cases

- Access control systems
- Attendance tracking
- Inventory management
- IoT projects requiring RFID authentication
- Security systems

## Prerequisites

- **Hardware**:
  - ESP32 development board
  - Wiegand 26-bit RFID reader
  - RFID cards/tags compatible with your reader
  - Jumper wires

- **Software**:
  - Arduino IDE (v1.8.x or later) or PlatformIO
  - ESP32 board support package installed

## Installation

### Method 1: Arduino Library Manager (Recommended)

1. Open the Arduino IDE
2. Go to **Sketch > Include Library > Manage Libraries**
3. Search for "WiegandRFID"
4. Click **Install**

### Method 2: Manual Installation

1. Download the latest release from GitHub
2. Extract the ZIP file
3. Rename the folder to `WiegandRFID`
4. Move it to your Arduino libraries directory:
   - **Windows**: `Documents\Arduino\libraries\`
   - **macOS**: `Documents/Arduino/libraries/`
   - **Linux**: `Arduino/libraries/`
5. Restart the Arduino IDE

### Method 3: Git Clone

```bash
cd ~/Arduino/libraries
git clone https://github.com/yourusername/WiegandRFID.git
```

## Configuration

### Wiring Diagram

Connect your Wiegand RFID reader to the ESP32 as follows:

| RFID Reader | ESP32 Pin | Description |
|-------------|-----------|-------------|
| D0 (Data 0) | GPIO 18   | Wiegand data line 0 |
| D1 (Data 1) | GPIO 19   | Wiegand data line 1 |
| GND         | GND       | Ground connection |
| VCC         | 5V/3.3V   | Power supply (check your reader's requirements) |

*Note: You can use any GPIO pins that support external interrupts.*

## Usage

### Basic Example

```cpp
#include <WiegandRFID.h>

WiegandRFID rfid;

void setup() {
  Serial.begin(115200);
  rfid.begin(18, 19);  // D0 on pin 18, D1 on pin 19
}

void loop() {
  rfid.loop();
  
  if (rfid.available()) {
    RFIDCard card = rfid.read();
    Serial.println("Card detected!");
    Serial.print("Card ID: ");
    Serial.println(card.idString);
    Serial.print("Facility Code: ");
    Serial.println(card.facilityCode);
    Serial.print("Card Number: ");
    Serial.println(card.cardNumber);
    Serial.print("Bit Length: ");
    Serial.println(card.bitLength);
    Serial.println("------------------------");
  }
}
```

### Advanced Configuration

#### Set Duplicate Read Timeout

```cpp
// Set duplicate detection to 2 seconds (default is 1 second)
rfid.setDuplicateTime(2000);
```

#### Set Read Timeout

```cpp
// Set read timeout to 50ms (default is 25ms)
rfid.setReadTimeout(50);
```

### RFIDCard Structure

The `RFIDCard` struct contains the following fields:

| Field | Type | Description |
|-------|------|-------------|
| `bitLength` | uint8_t | Number of bits read (26 for standard cards) |
| `facilityCode` | uint8_t | 8-bit facility code |
| `cardNumber` | uint16_t | 16-bit card number |
| `cardID` | uint32_t | Combined 24-bit card ID (facility + card number) |
| `rawData` | uint32_t | Raw 26-bit data received |
| `idString` | char[11] | 10-digit formatted string of cardID |

## Examples

The library includes a basic example in the `examples/BasicReader` folder. To open it:

1. Arduino IDE: **File > Examples > WiegandRFID > BasicReader**
2. PlatformIO: Navigate to `examples/BasicReader` in the library folder

## API Reference

### `WiegandRFID` Class

#### `begin(uint8_t d0, uint8_t d1)`
Initializes the library with specified D0 and D1 pins.

- **Parameters**:
  - `d0`: GPIO pin connected to Wiegand D0
  - `d1`: GPIO pin connected to Wiegand D1

#### `loop()`
Processes incoming Wiegand data. **Must be called repeatedly in your main loop.**

#### `available()`
Checks if a new card has been read.

- **Returns**: `true` if a card is available to read, `false` otherwise

#### `read()`
Reads the latest card data.

- **Returns**: `RFIDCard` struct with card information

#### `setDuplicateTime(uint32_t ms)`
Sets the duplicate detection window (default: 1000ms).

- **Parameters**:
  - `ms`: Time in milliseconds to ignore duplicate reads

#### `setReadTimeout(uint32_t ms)`
Sets the read timeout (default: 25ms).

- **Parameters**:
  - `ms`: Time in milliseconds to wait for complete card data

## Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
5. Push to the branch (`git push origin feature/AmazingFeature`)
6. Open a Pull Request

Please ensure your code follows the existing style and includes appropriate documentation.

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

## Contact

- Maintainer: MD Amirul Islam
- Project Link: [https://github.com/yourusername/WiegandRFID](https://github.com/yourusername/WiegandRFID)

## Visit ProgrammingBoss.com

We invite all users to visit **[www.programmingboss.com](https://www.programmingboss.com)** to explore a wealth of additional resources including:

- Embedded systems projects and tutorials
- IoT project ideas and implementations
- Technical articles and guides
- Code examples and best practices
- Community forums and discussions

Whether you're a beginner or an experienced developer, ProgrammingBoss.com has something for everyone interested in embedded systems and IoT development!
