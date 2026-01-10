// SPDX-License-Identifier: LGPL-3.0
#ifndef ROBIF2B_FUNCTIONS_ROBOTIQ_FT_SENSOR_H
#define ROBIF2B_FUNCTIONS_ROBOTIQ_FT_SENSOR_H

#include <robif2b/types/robotiq_ft_sensor.h>


#ifdef __cplusplus
extern "C" {
#endif

void robif2b_robotiq_ft_configure(struct robif2b_robotiq_ft_nbx *b);

void robif2b_robotiq_ft_shutdown(struct robif2b_robotiq_ft_nbx *b);

void robif2b_robotiq_ft_start(struct robif2b_robotiq_ft_nbx *b);

void robif2b_robotiq_ft_stop(struct robif2b_robotiq_ft_nbx *b);

void robif2b_robotiq_ft_update(struct robif2b_robotiq_ft_nbx *b);

void robif2b_robotiq_ft_zero(struct robif2b_robotiq_ft_nbx *b);

#ifdef __cplusplus
}
#endif

#endif