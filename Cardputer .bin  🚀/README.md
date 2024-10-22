# Cardputer .bin file with SD Card Configuration Loader

The .bin initialize an SD card and load configuration values for WiFi credentials, time zone, API key, and location from a `config.txt` file stored on the SD card.

## Cardputer .bin Setup

1. Update `config.txt` with you data and copy to the root directory of your SD card (i.e., not inside any folder).
```
WIFI_SSID=SSID
WIFI_PASSWORD=Passwrod
TIME_ZONE=Time Zone
API_KEY=weatherapi.com API key
LOCATION=Location
```

2. Use the [ESP Web Flasher](https://espressif.github.io/esptool-js/) to flash the .bin to Cardputer. Set the flash address to `0x0` / (`0`) when flashing.

