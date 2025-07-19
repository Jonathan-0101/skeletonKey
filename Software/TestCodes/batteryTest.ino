#define batteryPin 4

void setup() {
    Serial.begin(115200);
    delay(1000);
    int batteryADC = analogRead(batteryPin);
    float batteryVoltage = batteryADC * (11.0 / 6825.0);
    float batteryPercent = ((batteryVoltage - 3.0) / 1.2) * 100.0;
    Serial.printf("Battery Percentage: %.0f%%\n", batteryPercent);
}

void loop() {
    // Nothing to do here
}