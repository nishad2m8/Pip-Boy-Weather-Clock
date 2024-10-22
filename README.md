# Pip Boy Weather Clock Using LVGL

---
<p align="center">
  <span style="color: yellow;">If you like this project, consider supporting it:</span>
</p>

<p align="center">
  <a href="https://www.buymeacoffee.com/nishad2m8" target="_blank">
    <img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me a Coffee" style="height: 35px;">
  </a>
  <a href="https://www.youtube.com/channel/UCV_35rUyf4N5mHZXaxaFKiQ" target="_blank">
    <img src="https://img.shields.io/badge/Subscribe%20on%20YouTube-FF0000?style=flat&logo=youtube" alt="Subscribe on YouTube" style="height: 35px;">
  </a>
</p>

---

![alt text](Elements/IMG_2923.JPG)

Check videos on 

Lilygo 1.64" : https://youtu.be/y4AK9kuxWG8

Cardputer : https://youtu.be/WOr_QTMYXRI

---
## PIO (PlatformIO) Setup
1. Update the `config.h` file with your own WiFi credentials, Time Zone, API key, and location data.

```c++
#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials (replace with your SSID and password)
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#define TIME_ZONE "AST-3"  // Adjust this to the desired time zone string

// weatherapi.com API key
#define API_KEY "PPI_KEY"
// Location for weather query
#define LOCATION "LOCATION"


#endif // CONFIG_H
```
2. Open the folder in PlatformIO and Flash it.

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

## Time Zone Configuration for NTP

This project uses NTP (Network Time Protocol) to synchronize time over the internet and adjusts the local time based on the configured time zone. The time zone is set using POSIX-style strings, allowing you to handle both standard and daylight saving time automatically.

### Example Time Zones:

*  PST8PDT  - Pacific Standard Time with Daylight Saving Time
*  EST5EDT  - Eastern Standard Time with Daylight Saving Time
*  UTC      - Coordinated Universal Time
*  GMT      - Greenwich Mean Time
*  CET-1CEST- Central European Time with Daylight Saving Time
*  IST-5:30 - Indian Standard Time (UTC+5:30)
*  JST-9    - Japan Standard Time (UTC+9)
*  CST6CDT  - Central Standard Time with Daylight Saving Time (US)
*  MST7MDT  - Mountain Standard Time with Daylight Saving Time (US)
*  PHT-8    - Philippine Time (UTC+8)
*  SGT-8    - Singapore Time (UTC+8)
*  MSK-3    - Moscow Time (UTC+3)
*  GMT+4    - UAE Time (UTC+4)
*  AST-3    - Arabian Standard Time (Bahrain, UTC+3)