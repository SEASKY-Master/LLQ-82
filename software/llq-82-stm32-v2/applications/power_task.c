/*
 * @Author                         : Seasky.Liu
 * @Date                           : Do not edit
 * @LastEditTime: 2022-02-04 18:19:45
 * @LastEditors: Please set LastEditors
 * @Description                    : https://github.com/SEASKY-Master
 * @FilePath                       : Do not edit
 * @symbol_custom_string_obkoro1          : ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "power_task.h"
#include "i2c.h"
#include "bsp_sw6208.h"

static osThreadId Ws2812b_TaskHandle;
static void power_info_task(void const *pvParameters);

void power_task_creat(void)
{
    osThreadDef(power_task, power_info_task, osPriorityNormal, 0, 256);
    Ws2812b_TaskHandle = osThreadCreate(osThread(power_task), NULL);
}

static void power_info_task(void const *pvParameters)
{
    bsp_sw6208_info *p_Power;
    p_Power = get_sw6208_point();
    while (1)
    {
        bsp_sw6208_get_info();
        lv_bat_set_value(p_Power->battery_elec,p_Power->ischarger);
        ble_set_battery(p_Power->battery_elec);
        osDelay(100);
    }
}