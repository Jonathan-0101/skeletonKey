#include "WiFiTools.h"

WiFiTools wifiTools;

void setup() {
    Serial.begin(115200);

    // Call the begin function
    wifiTools.begin();
    delay(1000);

    // Call the rickRollBeaconSpam function
    wifiTools.rickRollBeaconSpam();
}

void loop() {
    // Nothing to do here
}