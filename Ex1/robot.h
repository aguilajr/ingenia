#include "robotAPI.h"

/**
* Initializes the timer and the SPI module.
*/
void initialization (void);

/**
*  Disable the optical sensor SPI communication and gets the actual EEPROM value.
*/
uint8_t getEepromValue (void);

/**
*  Disable the SPI communication with EEPROM and gets the value returned by the sensor.
*/
uint8_t getSensorValue (void);
