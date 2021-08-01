#include "API.h"

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

/**
 * @brief  Get X, Y, and Z axis values from the accelerometer
 * @param[in] accel    Struct accelerometer axis value
 */
void getAccelerometerValues(axisAccel *accel);
/**
 * @brief  Get X, Y, and Z axis values from the gyroscope
 * @param[in] gyroscope    Struct gyroscope axis value
 */
void getGyroscopeValues(axisGyro *gyroscope);

/**
 * @brief Initializes the I2C module and the configuration of gyroscope and accelerometer
 */
void initialization();

/**
 * @brief  Concatenates the high and low values from two registers
 * @param[in] highRegister    High position register value
 * @param[in] lowRegister    Low position register value
 * @param[out] completeRegister    2-byte whole register
 */

uint16_t concatenateHighLowRegisters (uint8_t highRegister, uint8_t lowRegister);
