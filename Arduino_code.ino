const int pwmPin = 9; // Output pin for the PWM-like signal (intensity)
const int amplitudePin = 10; // Output pin for amplitude control
char incomingCommand = 0;
int intensityValue = 0; // Variable to store intensity level (0 to 10)
int pulseAmplitude = 1; // Variable to store pulse amplitude (1 to 50 mA)
void setup() {
pinMode(pwmPin, OUTPUT); // Set the PWM pin as an output
pinMode(amplitudePin, OUTPUT); // Set the amplitude pin as an output
Serial.begin(9600); // Start Serial communication at 9600 baud
}
void loop() {
if (Serial.available() > 0) {
incomingCommand = Serial.read(); // Read the incoming command
Serial.print("Received Command: ");
Serial.println(incomingCommand);
switch (incomingCommand) {
case 'M': // Handle intensity decrease
if (intensityValue > 0) {
intensityValue--;
}
break;
case 'P': // Handle intensity increase
if (intensityValue < 10) {
intensityValue++;
}
break;
case 'I': // Handle pulse amplitude decrease
if (pulseAmplitude > 1) {
pulseAmplitude--;
}
break;
case 'A': // Handle pulse amplitude increase
if (pulseAmplitude < 50) {
pulseAmplitude++;
}
break;
default:
Serial.println("Unknown command");
}
// Calculate analog output for amplitude control
int analogAmplitude = map(pulseAmplitude, 1, 50, 0, 255); //
Map pulse amplitude range to 0-255
analogWrite(amplitudePin, analogAmplitude);
// Calculate analog output for intensity control (PWM)
int analogIntensity = map(intensityValue, 0, 10, 0, 255); //
Assuming 8-bit PWM
analogWrite(pwmPin, analogIntensity);
Serial.print("Intensity: ");
Serial.println(intensityValue);
Serial.print("Pulse Amplitude: ");
Serial.print(pulseAmplitude);
Serial.println(" mA");
}
}
