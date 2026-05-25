#include <stdio.h>
#include "ets_sys.h"
#include "user_interface.h"
#include "osapi.h"
#include "gpio.h"
#include "user_config.h"
#define LED 2


uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void) {
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }
    return rf_cal_sec;
}

LOCAL void ICACHE_FLASH_ATTR delay_ms(u32 x){
for(;x>0;x--){
os_delay_us(1000);
   }
}
void ICACHE_FLASH_ATTR user_init() {
gpio_init();
PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); 
gpio_output_set(0, 0, (1 << LED), 0);
while (1)
{
    delay_ms(500);
    gpio_output_set(0, (1 << LED), 0, 0);
    delay_ms(500);
    gpio_output_set((1 << LED), 0, 0, 0);
    delay_ms(500);

}
}
