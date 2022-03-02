/*
 * @author                          : Seasky.Liu
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \llq-82\applications\key_task.c
 * @symbol_custom_string_obkoro1    :
 * ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */

#include "key_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "tim.h"
#include "bsp_interface.h"
#include "lvgl_task.h"
#include "bsp_gui.h"
#include "lvgl_app.h"
#include "flash_task.h"

static void key_scan_task(void const *pvParameters);

enc_key key_enc_info; //������������Ϣ

static uint8_t key_count, key[2];
static osThreadId key_sacn_TaskHandle;

uint8_t key_task_scan(mx_key_task_info key_scan_t)
{
    if (HAL_GPIO_ReadPin(key_scan_t.key_gpio, key_scan_t.key_gpio_pin) == KEY_TASK_PRESS_LEVEL)
    {
        return KEY_TASK_PRESS_S;
    }
    return KEY_TASK_UPSPRING_S;
}

/**
 * @Author                         : Seasky.Liu
 * @Date                           : Do not edit
 * @description                    : ʹ��֮�����״̬
 * @param                           {*}
 * @return                          {*}
 * @param {mx_key_task_info} *click_state_t
 */
uint8_t get_click_state_num_clark(mx_key_task_info *click_state_t)
{
    uint8_t state = 0;
    state = click_state_t->key_info.click_state_num;
    click_state_t->key_info.click_state_num = 0;
    return state;
}

void key_task_creat(void)
{
    osThreadDef(key_task, key_scan_task, osPriorityRealtime, 0, 128);
    key_sacn_TaskHandle = osThreadCreate(osThread(key_task), NULL);
}

void key_app_fun(void)
{
    uint8_t key_count[2] = {0};
    uint8_t key_enc[2] = {0};
    uint8_t key_enc_dir[2] = {0};
    uint8_t key_status[2] = {0};
    static uint8_t last_key_enc[2] = {0};
    static uint8_t media_play_p = 0;
    key_count[(key_enc_info.click_switch != 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[0]);
    key_count[(key_enc_info.click_switch == 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[1]);

    key_enc[(key_enc_info.click_switch != 0)] = key_enc_info.encoder_t[0].enc_t;
    key_enc[(key_enc_info.click_switch == 0)] = key_enc_info.encoder_t[1].enc_t;

    key_enc_dir[(key_enc_info.click_switch != 0)] = key_enc_info.encoder_t[0].dir;
    key_enc_dir[(key_enc_info.click_switch == 0)] = key_enc_info.encoder_t[1].dir;

    key_status[(key_enc_info.click_switch != 0)] = key_enc_info.key_t[0].key_info.states;
    key_status[(key_enc_info.click_switch == 0)] = key_enc_info.key_t[1].key_info.states;

    //��������ιػ�
    if ((key_count[0] == 5))
    {
        flash_config_enter_standy();
    }
    else if ((key_count[0] == 10) ||
             (key_count[1] == 10))
    {
        key_enc_info.click_switch = !key_enc_info.click_switch;


        key_count[(key_enc_info.click_switch != 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[0]);
        key_count[(key_enc_info.click_switch == 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[1]);

        key_enc[(key_enc_info.click_switch != 0)] = key_enc_info.encoder_t[0].enc_t;
        key_enc[(key_enc_info.click_switch == 0)] = key_enc_info.encoder_t[1].enc_t;

        key_enc_dir[(key_enc_info.click_switch != 0)] = key_enc_info.encoder_t[0].dir;
        key_enc_dir[(key_enc_info.click_switch == 0)] = key_enc_info.encoder_t[1].dir;

        key_status[(key_enc_info.click_switch != 0)] = key_enc_info.key_t[0].key_info.states;
        key_status[(key_enc_info.click_switch == 0)] = key_enc_info.key_t[1].key_info.states;

        last_key_enc[0] = key_enc[0];
        last_key_enc[1] = key_enc[1];
    }
    /*key - 0  ������*/
    if ((0 == get_flash_lcd_touch_enable()))
    {
        if (key_count[0] == 1)
        {
            set_interface_button(mx_key_right);
        }
        else if (key_count[0] == 2)
        {
            set_interface_button(mx_key_left);
        }
        if (key_status[0] == KEY_TASK_PRESS_L_TIME)
        {
            set_interface_button(mx_key_left);
        }
    }
    else
    {
        if ((key_count[0] == 1))
        {
            lcd_wake_up();
        }
        else if ((key_count[0] == 2))
        {
            lcd_wake_up();
        }
        if ((key_status[0] == KEY_TASK_PRESS_L_TIME))
        {
            lcd_wake_up();
        }
    }
    set_interface_enc(key_enc[0]);
    /*key - 1  ������*/
    //ý�����
    switch (key_count[1])
    {
    case 1: //���ţ�ֹͣ
    {
        media_play_p = !media_play_p;
        if (media_play_p)
        {
            media_play();
        }
        else
        {
            media_paus();
        }
    }
    break;
    case 2: //��һ��
    {
        media_previous_track();
    }
    break;
    case 3: //��һ��
    {
        media_next_track();
    }
    case 4: //����
    {
        media_mute();
    }
    break;
    case 5: //ֹͣ
    {
        media_stop();
    }
    break;
    default:
        break;
    }
    if (key_enc[1] != last_key_enc[1])
    {
        if (!key_enc_dir[1])
        {
            media_volume_increment();
        }
        else
        {
            media_volume_decrement();
        }
    }
    last_key_enc[0] = key_enc[0];
    last_key_enc[1] = key_enc[1];
}

void key_scan_task(void const *pvParameters)
{
    TickType_t peroid = osKernelSysTick();
    //����������
    if (check_standby_normal())
    {
        HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
        HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
        //��ʼ����ɨ�趨ʱ��
        __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
        HAL_TIM_Base_Start(&htim1);
    }
    //��ʼ������������ɨ��
    key_enc_init();
    while (1)
    {
        key_enc_scanf();
        if (check_standby_normal())
        {
            //���±�����
            key_enc_info.encoder_t[0].enc_t = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim3)) / 2;
            key_enc_info.encoder_t[0].dir = (uint32_t)(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3));
            key_enc_info.encoder_t[1].enc_t = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2)) / 2;
            key_enc_info.encoder_t[1].dir = (uint32_t)(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2));
        }
        key_app_fun();
        osDelayUntil(&peroid, KEY_TASK_TIME_CYCLE); //������ʱ
    }
}


/**
 * @Author                         : Seasky.Liu
 * @Date                           : Do not edit
 * @description                    : ��������ʹ��
 * @param                           {*}
 * @return                          {*}
 */
void key_scanf_for_standby(void)
{
    static uint16_t standby_timer = 0;
    uint8_t key_count[2] = {0};
    uint8_t key_status[2] = {0};
    //��ʼ������������ɨ��
    key_enc_init();
    standby_timer = 0;
    key_enc_info.get_click_state_num(&key_enc_info.key_t[0]);
    key_enc_info.get_click_state_num(&key_enc_info.key_t[1]);
    while (1)
    {
        key_enc_scanf();
        key_count[(key_enc_info.click_switch != 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[0]);
        key_count[(key_enc_info.click_switch == 0)] = key_enc_info.get_click_state_num(&key_enc_info.key_t[1]);
        //��������ιػ�
        if ((key_count[0] == 5) ||
            (key_count[1] == 5))
        {
            flash_config_exit_standy();
        }
        else if (check_standby_normal())
        {
            break;
        }
        else if((key_count[0]!=0)||(key_count[0]!=0))
        {
            sys_enter_stop();
        }
        if (check_standby_normal())
        {
            break;
        }
        else if (standby_timer > 1000)
        {
            //����Ǵ���ģʽ������ʱ��δ���������������´���
            sys_enter_stop();
        }
        standby_timer++;
        HAL_Delay(KEY_TASK_TIME_CYCLE+1);
    }

    return;
}

void key_enc_init(void)
{
    //��ʼ������������ɨ��
    memset(&key_enc_info, 0, sizeof(key_enc_info));
    key_enc_info.key_t[0].key_gpio = LEFT_KEY_GPIO_Port;
    key_enc_info.key_t[0].key_gpio_pin = LEFT_KEY_Pin;
    key_enc_info.key_t[1].key_gpio = SW_KEY_NET2_GPIO_Port;
    key_enc_info.key_t[1].key_gpio_pin = SW_KEY_NET2_Pin;
    key_enc_info.get_click_state_num = get_click_state_num_clark;
}

void key_enc_scanf(void)
{
    for (key_count = 0; key_count < MAX_KEY_NUM; key_count++)
    {
        //��ȡ������ƽ
        key[key_count] = key_task_scan(key_enc_info.key_t[key_count]);
        if (key[key_count] == KEY_TASK_PRESS_S)
        {
            //�������¼���
            if (key_enc_info.key_t[key_count].key_info.time_count < KEY_PRESS_MAX_COUNT)
            {
                key_enc_info.key_t[key_count].key_info.time_count++;
            }
        }
        else
        {
            //�����������
            if (key_enc_info.key_t[key_count].key_info.res_count < KEY_RES_MAX_COUNT)
            {
                key_enc_info.key_t[key_count].key_info.res_count++;
            }
        }
        //���ﳤ��ʱ��
        if (key_enc_info.key_t[key_count].key_info.time_count >= KEY_TASK_TIME_L_COUNT)
        {
            if (key_enc_info.key_t[key_count].key_info.states == KEY_TASK_PRESS)
            {
                key_enc_info.key_t[key_count].key_info.states = KEY_TASK_PRESS_L_TIME;
                key_enc_info.key_t[key_count].key_info.click_num = 0;
                key_enc_info.key_t[key_count].key_info.click_state_num = 0;
                //������λ��������
                key_enc_info.key_t[key_count].key_info.res_count = 0;
            }
        }
        //�̰�ʱ��
        else if (key_enc_info.key_t[key_count].key_info.time_count >= KEY_TASK_TIME_P_COUNT)
        {
            //�״θ��°����¼�
            if (key_enc_info.key_t[key_count].key_info.states == KEY_TASK_UPSPRING)
            {
                key_enc_info.key_t[key_count].key_info.states = KEY_TASK_PRESS;
                //��¼�������´���
                if (key_enc_info.key_t[key_count].key_info.click_num < KEY_MAX_NUM)
                {
                    key_enc_info.key_t[key_count].key_info.click_num++;
                }
                //������λ��������
                key_enc_info.key_t[key_count].key_info.res_count = 0;
            }
        }
        //��������ʱ
        if (key_enc_info.key_t[key_count].key_info.res_count >= KEY_RES_NUM_COUNT)
        {
            if (key_enc_info.key_t[key_count].key_info.click_num != 0)
            {
                key_enc_info.key_t[key_count].key_info.click_state_num =
                    key_enc_info.key_t[key_count].key_info.click_num;
                key_enc_info.key_t[key_count].key_info.click_num = 0;
            }
        }
        //������λ����
        else if (key_enc_info.key_t[key_count].key_info.res_count >= KEY_RES_COUNT)
        {
            if (key_enc_info.key_t[key_count].key_info.states != KEY_TASK_UPSPRING)
            {
                key_enc_info.key_t[key_count].key_info.states = KEY_TASK_UPSPRING; //��������λ
                //�������¼�������
                key_enc_info.key_t[key_count].key_info.time_count = 0; //������������
            }
        }
    }
}

uint8_t key_get_press_count(uint8_t enc_t)
{
    if (enc_t < MAX_KEY_NUM)
    {
        return key_enc_info.get_click_state_num(&key_enc_info.key_t[enc_t]);
    }
    return 0;
}