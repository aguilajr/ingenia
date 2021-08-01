#include <stdint.h>
#include <stdbool.h>
#include "robotAPI.h"
#include "robot.h"

//Addresses for High and Low data registers
#define REG_ACCEL_XOUT_H 0x3B
#define REG_ACCEL_XOUT_L 0x3C
#define REG_ACCEL_YOUT_H 0x3D
#define REG_ACCEL_YOUT_L 0x3E
#define REG_ACCEL_ZOUT_H 0x3F
#define REG_ACCEL_ZOUT_L 0x40
#define REG_GYRO_XOUT_H 0x43
#define REG_GYRO_XOUT_L 0x44
#define REG_GYRO_YOUT_H 0x45
#define REG_GYRO_YOUT_L 0x46
#define REG_GYRO_ZOUT_H 0x47
#define REG_GYRO_ZOUT_L 0x48

#define ICM20602_ADDRESS 0x0068

typedef struct{
volatile uint16_t axisX;
volatile uint16_t axisY;
volatile uint16_t axisZ;
}axisAccel;

typedef struct{
volatile uint16_t axisX;
volatile uint16_t axisY;
volatile uint16_t axisZ;
}axisGyro;

void getAccelerometerValues(axisAccel *accel) {
    uint8_t accelDataLow[3] = {0};
    uint8_t accelDataHigh[3] = {0};
    
    I2CRead(REG_ACCEL_XOUT_H, accelDataHigh, sizeof(uint8_t));
    I2CRead(REG_ACCEL_YOUT_H, (accelDataHigh + 1), sizeof(uint8_t));
    I2CRead(REG_ACCEL_ZOUT_H, (accelDataHigh + 2), sizeof(uint8_t));
    
    I2CRead(REG_ACCEL_XOUT_L, accelDataLow, sizeof(uint8_t));
    I2CRead(REG_ACCEL_YOUT_L, (accelDataLow + 1), sizeof(uint8_t));
    I2CRead(REG_ACCEL_ZOUT_L, (accelDataLow + 2), sizeof(uint8_t));
    
    accel->axisX = concatenateHighLowRegisters(accelDataHigh[0], accelDataLow[0]);
    accel->axisY = concatenateHighLowRegisters(accelDataHigh[1], accelDataLow[1]);
    accel->axisZ = concatenateHighLowRegisters(accelDataHigh[2], accelDataLow[2]);
}

void getGyroscopeValues(axisGyro *gyroscope) {
    uint8_t gyroDataLow[3] = {0};
    uint8_t gyroDataHigh[3] = {0};
    
    I2CRead(REG_GYRO_XOUT_H, gyroDataHigh, sizeof(uint8_t));
    I2CRead(REG_GYRO_YOUT_H, (gyroDataHigh + 1), sizeof(uint8_t));
    I2CRead(REG_GYRO_ZOUT_H, (gyroDataHigh + 2), sizeof(uint8_t));
    
    I2CRead(REG_GYRO_XOUT_L, gyroDataLow, sizeof(uint8_t));
    I2CRead(REG_GYRO_YOUT_L, (gyroDataLow + 1), sizeof(uint8_t));
    I2CRead(REG_GYRO_ZOUT_L, (gyroDataLow + 2), sizeof(uint8_t));
    
    accel->axisX = concatenateHighLowRegisters(gyroDataHigh[0], gyroDataLow[0]);
    accel->axisY = concatenateHighLowRegisters(gyroDataHigh[1], gyroDataLow[1]);
    accel->axisZ = concatenateHighLowRegisters(gyroDataHigh[2], gyroDataLow[2]);
}

void initialization() {
    I2CInit();
    configAccelerometer();
    configGyroscope();
    ExtIntInit();
}

uint16_t concatenateHighLowRegisters (uint8_t highRegister, uint8_t lowRegister) {
    uint16_t completeRegister = (highRegister << 8) | lowRegister;

    return completeRegister;
}

