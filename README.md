### Distributed home temperature measurement system
## Bartłomiej Gordon INF sem. V
`⭐ Do not forget to give a star on GitHub!`

A device used for distributed temperature measurement at home with the possibility of adding more boards to the system.

View of the page you use when reading the temperature:
![example](https://user-images.githubusercontent.com/69083596/218278069-8b4bd2b4-d66f-49a7-a6b0-ddc5db8df6ed.png)

## Code Highlights

### WiFi Channel Discovery Without Association

```cpp
int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}
```

`Software/scr/sender.cpp`, lines 38–47

ESP-NOW requires both peers to operate on the same WiFi channel, but sender nodes must not associate with the router (they only need peer-to-peer radio). This function scans for the target SSID to resolve its channel, then the result is used with `esp_wifi_set_promiscuous` to force the radio to that channel without joining the network — a non-obvious but necessary workaround for a real ESP32 platform constraint.

### ESP-NOW to Server-Sent Events Bridge

```cpp
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) 
{ 
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  board["id"] = incomingReadings.id;
  board["temperature"] = incomingReadings.temp;
  board["readingId"] = String(incomingReadings.readingId);
  String jsonString = JSON.stringify(board);
  events.send(jsonString.c_str(), "new_readings", millis());
}
```

`Software/scr/server.cpp`, lines 33–41

This callback forms the core of the real-time pipeline: it receives a raw binary struct over ESP-NOW, deserializes it via `memcpy`, serializes to JSON, and immediately pushes a Server-Sent Event to all connected browsers. The entire bridge between the embedded radio protocol and the browser's `EventSource` API is handled in a single, seven-line callback with no intermediate buffering or polling.
