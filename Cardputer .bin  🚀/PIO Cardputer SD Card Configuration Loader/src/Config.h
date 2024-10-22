#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials will be loaded dynamically
extern String WIFI_SSID;
extern String WIFI_PASSWORD;

// Time zone setting
extern String TIME_ZONE;  // Will be loaded dynamically

// weatherapi.com API key
extern String API_KEY;    // Will be loaded dynamically
// Location for weather query
extern String LOCATION;   // Will be loaded dynamically

#endif // CONFIG_H
