/*** 
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime                    : 2022-01-04 15:00
 * @LastEditors                     : your name
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v6\groundwork\bsp_delay\bsp_delay.h
 * @symbol_custom_string_obkoro1    : 
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */

#ifndef _BSP_DELAY_H
#define _BSP_DELAY_H


#ifdef __cplusplus
extern "C" {
#endif

#include "struct_typedef.h"

void delay_init(void);
void delay_us(uint16_t nus);
void delay_ms(uint16_t nms);


#ifdef __cplusplus
}
#endif


#endif
