#include "user_config.h" 
#include "c_types.h" 
#include "pwm.h"
#include "FreeRTOS.h"
#include "task.h"
uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void)
{
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
            rf_cal_sec = 512 - 5;
            break;
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;
        case FLASH_SIZE_32M_MAP_512_512:
            rf_cal_sec = 1024 - 5;
            break;
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
static os_timer_t LEDTimer;
uint32_t ledDuty = 0;
uint8 ledDuty_1 = 0;
uint32_t maxDuty = 111111;
uint8 dir = 1;
void ICACHE_FLASH_ATTR TIMER(void){
if (1==dir){
    ledDuty_1++;
    if (ledDuty_1 >=100){
        dir = 0;
    }
}
else
{
   ledDuty_1--;
   if (ledDuty_1<=0){
    dir=1;
   }
}
  ledDuty = (uint32_t)((ledDuty_1/100.0) * maxDuty);
  pwm_set_duty(ledDuty, 0);
  pwm_start();
  vTaskDelay(1000/portTICK_RATE_MS);
}
void ICACHE_FLASH_ATTR user_init(void) {
gpio_init();
static const uint32_t period = 5000;
uint32 io_info[1][3] = {{PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2, 2}};
pwm_init(period, &ledDuty , 1, io_info);
xTaskCreate(&TIMER, "PWM_PWM", 2048, NULL, 2, NULL);
}         