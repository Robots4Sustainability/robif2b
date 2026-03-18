// SPDX-License-Identifier: LGPL-3.0
#include <robif2b/functions/robotiq_ft_sensor.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    float wrench[6];
    enum robif2b_robotiq_ft_state state;
    bool success, new_data;

    struct robif2b_robotiq_ft_nbx sensor = {
        .conf = { .device = "/dev/ttyUSB0", .baudrate = 19200 },
        .wrench = wrench,
        .state = &state,
        .success = &success,
        .new_data = &new_data,
    };

    robif2b_robotiq_ft_configure(&sensor);
    if (!success) {
        printf("Failed to configure sensor\n");
        return 1;
    }
    printf("Sensor: %s, FW: %s\n", sensor.serial_number, sensor.firmware_version);

    robif2b_robotiq_ft_start(&sensor);

    // robif2b_robotiq_ft_zero(&sensor);

    // for (int i = 0; i < 1000; i++) {
    while (true) {
        robif2b_robotiq_ft_update(&sensor);
        if (new_data) {
            printf("F: [%6.2f, %6.2f, %6.2f] N  T: [%6.3f, %6.3f, %6.3f] Nm\n",
                   wrench[0], wrench[1], wrench[2], wrench[3], wrench[4], wrench[5]);
        }
        usleep(4000);
    }

    robif2b_robotiq_ft_stop(&sensor);
    robif2b_robotiq_ft_shutdown(&sensor);

    return 0;
}