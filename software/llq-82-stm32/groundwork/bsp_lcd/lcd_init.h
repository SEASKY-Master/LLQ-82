/*** 
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-24 09:25:08
 * @LastEditTime                    : 2022-01-04 15:23
 * @LastEditors                     : your name
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v6\groundwork\bsp_lcd\lcd_init.h
 * @symbol_custom_string_obkoro1    : 
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "struct_typedef.h"

#define USE_HORIZONTAL 2  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 135
#define LCD_H 240

#else
#define LCD_W 240
#define LCD_H 135
#endif


#define LCD_RES_Clr()  HAL_GPIO_WritePin(LDC_RES_GPIO_Port,LDC_RES_Pin,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(LDC_RES_GPIO_Port,LDC_RES_Pin,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_SET)
 		     
#define LCD_BLK_Clr()  HAL_GPIO_WritePin(LCD_BLK_GPIO_Port,LCD_BLK_Pin,GPIO_PIN_SET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LCD_BLK_GPIO_Port,LCD_BLK_Pin,GPIO_PIN_RESET)




void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(u8 dat);//ģ��SPIʱ��
void LCD_WR_DATA8(u8 dat);//д��һ���ֽ�
void LCD_WR_DATA(u16 dat);//д�������ֽ�
void LCD_WR_REG(u8 dat);//д��һ��ָ��
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//�������꺯��
void bsp_lcd_init(void);//LCD��ʼ��

#ifdef __cplusplus
}
#endif

#endif




