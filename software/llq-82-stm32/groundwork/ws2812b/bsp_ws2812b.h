/***
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:39
 * @LastEditTime                    : 2021-11-27 11:11:10
 * @LastEditors                     : your name
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v5\groundwork\ws2812b\bsp_ws2812b.h
 * @symbol_custom_string_obkoro1    :
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef _BSP_WS2812B_H
#define _BSP_WS2812B_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "struct_typedef.h"

#define MAX_WS2812B_NUM 35
#define WS2812B_R_OFFSET 1
#define WS2812B_G_OFFSET 2
#define WS2812B_B_OFFSET 0

    typedef enum
    {
        L_DIN_1 = 1,
        L_DIN_2,
        L_DIN_3,
    } din_ch;
    typedef union
    {
        uint32_t WS2812B_RGB;
        uint8_t RGB_OFFSET[4];
    } ws2812b_led;
    typedef struct
    {
        uint8_t id;
        uint8_t name;
        din_ch id_ch;
        uint8_t id_ch_id;  // ch������id
        uint8_t id_column; //������
        uint8_t id_line;   //������
        ws2812b_led rgb_set;
    } keyboard_rgb;

    /***
     * @Author: Seasky.Liu
     * @Description: ��ʼ��
     * @param {keyboard_rgb} *board_rgb_led
     * @return {*}
     */
    void mx_ws2812b_init(keyboard_rgb *board_rgb_led);

    /***
     * @Author: Seasky.Liu
     * @Description:    ��ID����LED
     * @param {keyboard_rgb} *board_rgb_led
     * @return {*}
     */
    void ws2812b_id_cfg(keyboard_rgb *board_rgb_led);

    /***
     * @Author: Seasky.Liu
     * @Description: �����жϷ�����֮�У���֤�жϺ��������㹻���
     * @param {*}
     * @return {*}
     */
    void ws2812b_IRQ(void);

#ifdef __cplusplus
}
#endif
#endif
