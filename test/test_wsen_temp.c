#include "wsen_temp.h"

static wsen_temp_t temp_sensor;

/* Print temperature */
void temp_print(void)
{
    float temp;
    wsen_temp_get_celsius(&temp_sensor, &temp);
    printf("Temperature in Celsius: %f\n", temp);
}

/* Initialize temperature sensor */
void temp_init(void)
{
    wsen_temp_cfg_t cfg;
    wsen_temp_set_default_cfg(&cfg);
    wsen_temp_init(&temp_sensor, &cfg);
    wsen_temp_sw_rst(&temp_sensor);
    /* Configure continuous mode */
    wsen_temp_ctrl_t ctrl_reg;
    wsen_temp_get_ctrl(&temp_sensor, &ctrl_reg);
    ctrl_reg.free_run = WSEN_TEMP_CTRL_FREE_RUN_EN;
    ctrl_reg.block_data_upd = WSEN_TEMP_CTRL_BLOCK_DATA_UPD_EN;
    ctrl_reg.out_rate = WSEN_TEMP_CTRL_ODR_50HZ;
    wsen_temp_set_ctrl(&temp_sensor, &ctrl_reg);
}

int main() {
    // Enable print status output
    stdio_init_all();
    // Init and test temperature sensor
    temp_init();
    // Test tasks
    while (1) {
        temp_print();
        platform_sleep_ms(1000);
    }
    return 0;
}
