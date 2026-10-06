#include "i2c_bus.h"
#include "freertos.h"

extern osMutexId_t I2C_MutexHandle;

osStatus_t I2C_Bus_Lock(void)
{
    return osMutexAcquire(I2C_MutexHandle, osWaitForever);
}

osStatus_t I2C_Bus_Unlock(void)
{
    return osMutexRelease(I2C_MutexHandle);
}
