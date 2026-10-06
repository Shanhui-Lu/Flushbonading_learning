#ifndef __I2C_BUS_H
#define __I2C_BUS_H

#include "cmsis_os2.h"

osStatus_t I2C_Bus_Lock(void);
osStatus_t I2C_Bus_Unlock(void);

#endif
