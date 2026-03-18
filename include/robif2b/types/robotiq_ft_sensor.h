// SPDX-License-Identifier: LGPL-3.0
#ifndef ROBIF2B_TYPES_ROBOTIQ_FT_SENSOR_H
#define ROBIF2B_TYPES_ROBOTIQ_FT_SENSOR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum robif2b_robotiq_ft_state
{
    ROBIF2B_ROBOTIQ_FT_STATE_INIT,
    ROBIF2B_ROBOTIQ_FT_STATE_READ_INFO,
    ROBIF2B_ROBOTIQ_FT_STATE_START_STREAM,
    ROBIF2B_ROBOTIQ_FT_STATE_RUN
};

struct robif2b_robotiq_ft_config
{
    const char *device;             // Serial device path, e.g. "/dev/ttyUSB0"
    int baudrate;                   // Baud rate
};

struct robif2b_robotiq_ft_nbx
{
    // Configuration
    struct robif2b_robotiq_ft_config conf;

    // Ports
    float *wrench;                  // [Fx, Fy, Fz, Tx, Ty, Tz]

    // Status
    enum robif2b_robotiq_ft_state *state;
    bool *success;
    bool *new_data;

    // Sensor info
    char serial_number[20];
    char firmware_version[20];
    char production_year[20];

    // Internal state
    void *internal;
};

#ifdef __cplusplus
}
#endif

#endif