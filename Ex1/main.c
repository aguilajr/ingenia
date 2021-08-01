#include <stdint.h>
#include <stdbool.h>
#include "robotAPI.h"
#include "robot.h"

#define SENSOR_THRESHOLD 128

bool objectDetected = false;

int main(void) {
    uint8_t command = 0;

    inicialization();

    while(!objectDetected)
    {
        command = getEepromValue();
        RobotTask(command);
    }

    RobotStop();

    return 0;
}

void initialization() {
    SPIInit();
    TimerInit();
}

uint8_t getEepromValue() {
    uint8_t command = 0;

    SPISensorDisable(); //Assure there are no conflicts because of ISR
    SPIEepromEnable();

    uint8_t command = SPIRead();

    return command;
}

uint8_t getSensorValue() {
    uint8_t sensorValue = 0;

    SPIEepromDisable(); //Assure there are no conflicts because of ISR
    SPISensorEnable();

    sensorValue = SPIRead();

    return sensorValue;
}

void TimerISR(void) {
    uint8_t sensorValue = getSensorValue();

    if(sensorValue > SENSOR_THRESHOLD)
    {
        RobotStop();
        objectDetected = true;
    }

}
