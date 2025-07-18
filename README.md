# ESP8266 Arduino Core Deploy the Fleet Library

This library simplifies integration with the [Deploy the Fleet](https://deploythefleet.com) update service enabling secure OTA updates. It is meant for projects that currently use the [ESP8266 Arduino Core](https://arduino-esp8266.readthedocs.io/) library.


## Requirements

  * Project built using [ESP8266 Arduino Core](https://arduino-esp8266.readthedocs.io/) library
  * A [Deploy the Fleet](https://deploythefleet.com/docs/create-account/) account
  * Product ID from Deploy the Fleet dashboard

## Usage

The library's main class implements a static `getFirmwareUpdate` function that checks for a firmware update from Deploy the Fleet and automatically loads it if available. It then resets the device to run the new firmware if an update occurs. You can call this function from a button press handler or other location in your project where it makes sense to trigger an update.

```cpp
# define DTF_PRODUCT_ID "[YOUR PRODUCT ID]"

DTF_ESP8266Update::getFirmwareUpdate(DTF_PRODUCT_ID, "[CURRENT VERSION OF YOUR FIRMWARE]");
```

## Options

The main call to `DTF_ESP8266Update::getFirmwareUpdate` has several default arguments defined. These additional arguments 
can be passed to modify some behaviors of the library. The full signature of the call is:

```cpp
static DTF_UpdateResponse getFirmwareUpdate(
    const char* productId, 
    const char* currentVersion, 
    DTF_RebootOption rebootOption = DTF_RebootOption::REBOOT, 
    DTF_SetTimeOption setTimeOption = DTF_SetTimeOption::DO_NOT_SET_TIME
);   
```

You can change any of these options but they must be passed in the same order as defined in the signature.

### Reboot Option
**Default:** Reboot on successful update

```cpp
enum class DTF_RebootOption
{
    NO_REBOOT = 0,
    REBOOT = 1,
};
```

### Set Time Via NTP
**Default:** Do not set time via NTP

```cpp
enum class DTF_SetTimeOption
{
    DO_NOT_SET_TIME = 0,
    SET_TIME = 1,
};
```

## License
MIT License

Copyright © 2025 MakerCrew, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.