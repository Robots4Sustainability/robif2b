// SPDX-License-Identifier: LGPL-3.0
#include <robif2b/functions/robotiq_ft_sensor.h>
#include <stdlib.h>
#include <string.h>

// Include original Robotiq driver sources
#include "vendor/rq_sensor_com.h"
#include "vendor/rq_sensor_state.h"

struct robotiq_ft_internal
{
    bool is_streaming;
};

void robif2b_robotiq_ft_configure(struct robif2b_robotiq_ft_nbx *b)
{
    b->internal = calloc(1, sizeof(struct robotiq_ft_internal));
    
    // if (rq_sensor_state() != 0) {
    //     *b->success = false;
    //     return;
    // }
    while (rq_sensor_state() != 0) {
        usleep(100000);
    }
    
    rq_com_get_str_serial_number((INT_8*)b->serial_number);
    rq_com_get_str_firmware_version((INT_8*)b->firmware_version);
    rq_com_get_str_production_year((INT_8*)b->production_year);
    
    *b->state = ROBIF2B_ROBOTIQ_FT_STATE_READ_INFO;
    *b->success = true;
}

void robif2b_robotiq_ft_shutdown(struct robif2b_robotiq_ft_nbx *b)
{
    stop_connection();
    free(b->internal);
    b->internal = NULL;
}

void robif2b_robotiq_ft_start(struct robif2b_robotiq_ft_nbx *b)
{
    struct robotiq_ft_internal *s = (struct robotiq_ft_internal*)b->internal;
    
    if (rq_com_start_stream() == 0) {
        s->is_streaming = true;
        *b->state = ROBIF2B_ROBOTIQ_FT_STATE_RUN;
        *b->success = true;
    } else {
        *b->success = false;
    }
}

void robif2b_robotiq_ft_stop(struct robif2b_robotiq_ft_nbx *b)
{
    struct robotiq_ft_internal *s = (struct robotiq_ft_internal*)b->internal;
    s->is_streaming = false;
    *b->state = ROBIF2B_ROBOTIQ_FT_STATE_INIT;
}

void robif2b_robotiq_ft_update(struct robif2b_robotiq_ft_nbx *b)
{
    // Run state machine
    rq_sensor_state();
    
    if (rq_state_got_new_message()) {
        if (b->force_x)  *b->force_x  = rq_state_get_received_data(0);
        if (b->force_y)  *b->force_y  = rq_state_get_received_data(1);
        if (b->force_z)  *b->force_z  = rq_state_get_received_data(2);
        if (b->torque_x) *b->torque_x = rq_state_get_received_data(3);
        if (b->torque_y) *b->torque_y = rq_state_get_received_data(4);
        if (b->torque_z) *b->torque_z = rq_state_get_received_data(5);
        
        if (b->wrench) {
            for (int i = 0; i < 6; i++) {
                b->wrench[i] = rq_state_get_received_data(i);
            }
        }
        *b->new_data = true;
    } else {
        *b->new_data = false;
    }
    
    *b->success = rq_com_get_valid_stream();
}

void robif2b_robotiq_ft_zero(struct robif2b_robotiq_ft_nbx *b)
{
    rq_set_zero();
    *b->success = true;
}