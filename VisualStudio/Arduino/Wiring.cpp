#include "Wiring.h"
#include "ModelicaUtilities.h"

extern "C" {

ArduinoUno ArduinoUno::instance;


void pinMode(uint8_t pin, uint8_t mode) {
	//ModelicaFormatMessage("pinMode(%d, %d)\n", pin, mode);
	ArduinoUno::instance.portMode[pin] = mode;
}

void digitalWrite(uint8_t pin, uint8_t val) {
	ArduinoUno::instance.pulseWidth[pin] = (val == HIGH) ? 100 : 0;
	ModelicaFormatMessage("digitalWrite(%d, %d) -> %f\n", pin, val, ArduinoUno::instance.pulseWidth[pin]);
}

int digitalRead(uint8_t pin) {
	// ModelicaFormatMessage("digitalRead(%d) -> %f\n", pin, instance.digital[pin]);
	return ArduinoUno::instance.digital[pin] > 2.5 ? HIGH : LOW;
}

int analogRead(uint8_t pin) {
	// TODO: clip [0, 1023]
	return (ArduinoUno::instance.analog[pin - 14] / 5) * 1024;
}

void analogReference(uint8_t mode) {

}

void analogWrite(uint8_t pin, int val) {
	//instance.error = "analogWrite() is not supported";
	ArduinoUno::instance.portMode[pin] = OUTPUT;
	ArduinoUno::instance.pulseWidth[pin] = 100. * (val / 255.); 
}

void delay(unsigned long ms) {
	//ModelicaFormatMessage("delay at %f\n", ArduinoUno::instance.time);
	double end_time = ArduinoUno::instance.time + ms * 1e-3;
	while (ArduinoUno::instance.time < end_time) {
		// idle
	}
}

unsigned long millis() {
	return ArduinoUno::instance.time * 1000;
}

}