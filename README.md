# ESP8266 Arduino Core Deploy the Fleet Library

This library simplifies integration with the [Deploy the Fleet](https://deploythefleet.io) update service enabling secure OTA updates. It is meant for projects that currently use the [ESP8266 Arduino Core](https://arduino-esp8266.readthedocs.io/) library.

![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/sidwarkd/c1275ec2d5e358d56f268223abeb3660/raw/DTF_ESP8266Update_v1.0.6.json)
![Static Badge](https://img.shields.io/badge/not%20connecting-test?label=versions%20%3C%3D%201.0.5&color=hsl(0%2C%20100%25%2C%2040%25))





## Requirements

  * Project built using [ESP8266 Arduino Core](https://arduino-esp8266.readthedocs.io/) library
  * A [Deploy the Fleet](https://deploythefleet.io/docs/create-account/) account
  * Product Update URL from Deploy the Fleet dashboard

## Usage

The library's main class implements a static `getFirmwareUpdate` function that checks for a firmware update from Deploy the Fleet and automatically loads it if available. It then resets the device to run the new firmware if an update occurs. You can call this function from a button press handler or other location in your project where it makes sense to trigger an update.

```cpp
# define DTF_UPDATE_URL "[YOUR PRODUCT UPDATE URL]"

DTF_ESP8266Update::getFirmwareUpdate(DTF_UPDATE_URL, "[CURRENT VERSION OF YOUR FIRMWARE]");
```

## Options

The main call to `DTF_ESP8266Update::getFirmwareUpdate` has several default arguments defined. These additional arguments 
can be passed to modify some behaviors of the library. The full signature of the call is:

```cpp
static DTF_UpdateResponse getFirmwareUpdate(
    const char* updateUrl, 
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

Copyright © 2024 MakerCrew, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.