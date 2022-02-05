/*** 
 * @Author                         : Seasky.Liu
 * @Date                           : Do not edit
 * @LastEditTime: 2022-02-05 16:33:20
 * @LastEditors: Please set LastEditors
 * @Description                    : https://github.com/SEASKY-Master
 * @FilePath                       : Do not edit
 * @symbol_custom_string_obkoro1          : ��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
/***
 * @Author                          : Seasky.Liu
 * @LastEditors                     : Seasky.Liu
 * @FilePath                        : \keyboard_v7\applications\key_task.h
 * @Description                     : https://github.com/SEASKY-Master
 * @symbol_custom_string_obkoro1    :
 * @��Ȩ����: @Seasky.Liu
 * @��ϵ��ʽ: liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;,ΥȨ�ؾ�
 * @************************************************************************
 * @				If you want a thing done well, do it yourself.
 * @************************************************************************
 */

#ifndef _KEY_TSAK_H
#define _KEY_TSAK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "struct_typedef.h"

#define MAX_KEY_NUM 2 //��������
#define KEY_TASK_TIME_CYCLE 2     //��λms
#define KEY_TASK_TIME_P_COUNT 10  // TIME_P_TIME/TIME_CYCLE	20ms
#define KEY_TASK_TIME_L_COUNT 750 // TIME_L_TIME/TIME_CYCLE	1500ms

#define KEY_PRESS_MAX_COUNT 2000 //�������ʱ	4s
#define KEY_RES_MAX_COUNT 2000   //��λ���ʱ	4s
#define KEY_RES_COUNT 6          //������λ�������ʱ��		12ms
#define KEY_RES_NUM_COUNT 250    //��������ֹͣ����ʱ��		500ms
#define KEY_MAX_NUM 100

#define KEY_TASK_PRESS_S 1    //�������·����ź�
#define KEY_TASK_UPSPRING_S 0 //�������𷵻��ź�

#define KEY_TASK_PRESS_LEVEL 0 //���尴������ʱ�ĵ�ƽ

    typedef enum
    {
        KEY_TASK_UPSPRING = 0,     //��������
        KEY_TASK_PRESS,        //��������
        KEY_TASK_PRESS_L_TIME, //��������
    } key_task_states;
    typedef struct
    {
        key_task_states states;  //����״̬
        uint8_t click_state_num; //�����̰�����
        uint16_t time_count;     //��������ʱ�����
        uint16_t res_count;      //��������ʱ�����
        uint8_t click_num;       //����״̬Ϊ�̰�����
    } key_task_time_info;
    typedef struct
    {
        GPIO_TypeDef *key_gpio;      //����İ���GPIO
        uint16_t key_gpio_pin;       //����İ���GPIO
        key_task_time_info key_info; //�����㷨��Ϣ
    } mx_key_task_info;
    typedef struct
    {
        mx_key_task_info key_t[2];
        struct
        {
            uint16_t enc_t;
            uint8_t  dir;
        } encoder_t[2];
        uint8_t  click_switch;
        uint8_t (*get_click_state_num)(mx_key_task_info *click_state_t);
    } enc_key;

    void key_task_creat(void);
    void key_scanf_for_standby(void);
    void key_enc_init(void);
    void key_enc_scanf(void);
    uint8_t key_get_press_count(uint8_t enc_t);


#ifdef __cplusplus
}
#endif

#endif
