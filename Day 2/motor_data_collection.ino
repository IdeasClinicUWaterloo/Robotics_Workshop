// Arduino Code to Batch Capture Motor Current Data for Stall Testing

const float R_SHUNT = 0.5; // Shunt Resistor Value in Ohms
const float V_REF = 5;    // ADC Reference Voltage in Volts
const int ADC_MAX = 4095;

const int BUFFER_SIZE = 500;

float buffer[BUFFER_SIZE];

void setup()
{
  Serial.begin(115200);
  analogReadResolution(12);
}

float readVoltage()
{
  int raw = analogRead(A0);
  return (raw * V_REF) / ADC_MAX;
}

void loop()
{
  // --- CAPTURE PHASE ---
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    float voltage = readVoltage();
    float current = voltage / R_SHUNT;

    buffer[i] = current;

    delayMicroseconds(500); // ~2 kHz sampling
  }

  // --- TRANSMIT PHASE ---
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    Serial.println(buffer[i], 6);
  }

}