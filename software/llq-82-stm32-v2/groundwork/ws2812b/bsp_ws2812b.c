/*
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:39
 * @LastEditTime: 2022-02-06 19:15:36
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \llq-82\groundwork\ws2812b\bsp_ws2812b.c
 * @symbol_custom_string_obkoro1    :
 * ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */
#include "bsp_ws2812b.h"
#include "tim.h"
/*
    PB6     ------> TIM4_CH1  1-27--------27
    PB7     ------> TIM4_CH2  1-27--------27
    PB8     ------> TIM4_CH3  28-54-------27
    PB9     ------> TIM4_CH4  55-87-------33
*/
static void mx_ws2812b_low(uint8_t ch);
static void mx_ws2812b_high(uint8_t ch);
static void mx_ws2812b_reset(void);
/*IRQ��ʹ���ݴ棬IRQ�в��ܰ���������룬�ʷ�װ��ʾ*/
ws2812b_led ws2812b_irq_cfg[3][MAX_WS2812B_NUM];

/**
 * @Author: Seasky.Liu
 * @Description: ��ʼ��ws2812
 * @param {keyboard_rgb} *board_rgb_led
 * @return {*}
 */
void mx_ws2812b_init(keyboard_rgb *board_rgb_led)
{
    uint8_t i;
    for (i = 0; i < 80; i++)
    {
        /*
            PB7     ------> TIM4_CH2 ------> L_DIN_1 ------> 1-27--------28
            PB8     ------> TIM4_CH3 ------> L_DIN_2 ------> 28-55-------27
            PB9     ------> TIM4_CH4 ------> L_DIN_3 ------> 56-80-------33
        */
        board_rgb_led[i].id = i + 1;
        /*ͨ������*/
        if (board_rgb_led[i].id <= 27)
        {
            board_rgb_led[i].id_ch = L_DIN_1;
            board_rgb_led[i].id_ch_id = i + 1;
        }
        else if (board_rgb_led[i].id <= 55)
        {
            board_rgb_led[i].id_ch = L_DIN_2;
            board_rgb_led[i].id_ch_id = i + 1 - 27;
        }
        else if (board_rgb_led[i].id <= 80)
        {
            board_rgb_led[i].id_ch = L_DIN_3;
            board_rgb_led[i].id_ch_id = i + 1 - 55;
        }

        /*  ��������
                1->13
                2->14
                3->14
                4->13
                5->12
                6->8
                7->4
                8->2
        */
        if (board_rgb_led[i].id <= 13)          //13
        {
            board_rgb_led[i].id_line = 1;       //������
            board_rgb_led[i].id_column = i + 1; //������
        }
        else if (board_rgb_led[i].id <= 27)     //14
        {
            board_rgb_led[i].id_line = 2;            //������
            board_rgb_led[i].id_column = i + 1 - 13; //������
        }
        else if (board_rgb_led[i].id <= 41)     //14
        {
            board_rgb_led[i].id_line = 3;        //������
            board_rgb_led[i].id_column = i - 26; //������
        }
        else if (board_rgb_led[i].id <= 54)     //13
        {
            board_rgb_led[i].id_line = 4;        //������
            board_rgb_led[i].id_column = i - 40; //������
        }
        else if (board_rgb_led[i].id == 55)     //2
        {
            //����
            board_rgb_led[i].id_line = 8; //������
            board_rgb_led[i].id_column = 1;
        }
        else if (board_rgb_led[i].id <= 67)     //12
        {
            board_rgb_led[i].id_line = 5;        //������
            board_rgb_led[i].id_column = i - 54; //������
        }
        else if (board_rgb_led[i].id == 68)     //2
        {
            //����
            board_rgb_led[i].id_line = 8; //������
            board_rgb_led[i].id_column = 2;
        }
        else if (board_rgb_led[i].id <= 76)     //8
        {
            board_rgb_led[i].id_line = 6;        //������
            board_rgb_led[i].id_column = i - 67; //������
        }
        else if (board_rgb_led[i].id <= 80)     //4
        {
            board_rgb_led[i].id_line = 7;        //������
            board_rgb_led[i].id_column = i - 75; //������
        }
    }
}

/*����id���䵽3����ʾͨ��*/
void mx_ws2812b_config(uint8_t ch, uint8_t set)
{
    TIM4->ARR = 95;
    switch (ch)
    {
    case 1:
        TIM4->CCR1 = set;
        break;
    case 2:
        TIM4->CCR2 = set;
        break;
    case 3:
        TIM4->CCR3 = set;
        break;
    case 4:
        break;
    }
}
/*��ID����*/
void ws2812b_id_cfg(keyboard_rgb *board_rgb_led)
{
    uint8_t i;
    for (i = 0; i < 80; i++)
    {
        /*
            PB7     ------> TIM4_CH2 ------> L_DIN_1 ------> 1-27--------28
            PB8     ------> TIM4_CH3 ------> L_DIN_2 ------> 28-55-------27
            PB9     ------> TIM4_CH4 ------> L_DIN_3 ------> 56-80-------33
        */
        switch (board_rgb_led[i].id_ch)
        {
        case L_DIN_1:
            ws2812b_irq_cfg[0][i].WS2812B_RGB = board_rgb_led[i].rgb_set.WS2812B_RGB;
            break;
        case L_DIN_2:
            ws2812b_irq_cfg[1][i - 27].WS2812B_RGB = board_rgb_led[i].rgb_set.WS2812B_RGB;
            break;
        case L_DIN_3:
            ws2812b_irq_cfg[2][i - 55].WS2812B_RGB = board_rgb_led[i].rgb_set.WS2812B_RGB;
            break;
        }
    }
}
/*���˺������붨ʱ���ж��У���ʱ���ж������б�Ҫ���ж��Լ��ж����������
������ֱ��ʹ���жϻص�����*/
void ws2812b_IRQ(void)
{
    static uint16_t ws2812b_num = 0;
    static uint8_t ws2812b_size = 0;
    if (ws2812b_num == MAX_WS2812B_NUM)
    {
        ws2812b_num = 0;
        mx_ws2812b_reset();
    }
    else
    {
        if ((ws2812b_irq_cfg[0][ws2812b_num].WS2812B_RGB >> (23 - ws2812b_size) & 0x01) == 1)
        {
            mx_ws2812b_high(1);
        }
        else
        {
            mx_ws2812b_low(1);
        }
        if ((ws2812b_irq_cfg[1][ws2812b_num].WS2812B_RGB >> (23 - ws2812b_size) & 0x01) == 1)
        {
            mx_ws2812b_high(2);
        }
        else
        {
            mx_ws2812b_low(2);
        }
        if ((ws2812b_irq_cfg[2][ws2812b_num].WS2812B_RGB >> (23 - ws2812b_size) & 0x01) == 1)
        {
            mx_ws2812b_high(3);
        }
        else
        {
            mx_ws2812b_low(3);
        }
        ws2812b_size++;
        if (ws2812b_size == 24)
        {
            ws2812b_num++;
            ws2812b_size = 0;
        }
    }
}

/*pwm��� 0��*/
static void mx_ws2812b_low(uint8_t ch)
{
    mx_ws2812b_config(ch, 4);
}
/*pwm��� 1��*/
static void mx_ws2812b_high(uint8_t ch)
{
    mx_ws2812b_config(ch, 9);
}
/*�����������ֽں����PWM��λ��*/
static void mx_ws2812b_reset(void)
{
    TIM4->ARR = 1199;
    TIM4->CCR1 = 0;
    TIM4->CCR2 = 0;
    TIM4->CCR3 = 0;
    TIM4->CCR4 = 0;
}