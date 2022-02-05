/*** 
 * @Author                          : Seasky.Liu
 * @LastEditors: Please set LastEditors
 * @FilePath                        : \llq-82\groundwork\bsp_gui\bsp_gui.h
 * @Description                     : https://github.com/SEASKY-Master
 * @symbol_custom_string_obkoro1    : 
 * @��Ȩ����: @Seasky.Liu
 * @��ϵ��ʽ: liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;,ΥȨ�ؾ�
 * @************************************************************************
 * @				If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef _BSP_GUI_H
#define _BSP_GUI_H


#include "struct_typedef.h"

#define MAX_GUI 		7

#define MAX_DIRECTORY   3 	//���Ŀ¼����
#define MAX_SIZE_LENGTH 24

//gui ������ʾ���ַ�������
#define MAX_GUI_SHOW_NUM 5

//һ��Ŀ¼����
#define MAX_GUI_LEVEL1  7

//����Ŀ¼����
#define MAX_TASK1_NUM	24
#define MAX_TASK2_NUM	7
#define MAX_TASK3_NUM	7
#define MAX_TASK4_NUM	5
#define MAX_TASK5_NUM	7
#define MAX_TASK6_NUM	7
#define MAX_TASK7_NUM	7

typedef enum
{
	oled_interface_task1 = 0,
	oled_interface_task2  = 1,
	oled_interface_task3 = 2,
	oled_interface_task4 = 3,
	oled_interface_task5 =4,
	oled_interface_task6 = 5,
	oled_interface_task7 = 6,
}oled_gui_task;
typedef enum
{
	mx_key_null = 0,
	mx_key_on  = 1,
	mx_key_left = 2,
	mx_key_right = 3,
	mx_key_top =4,
	mx_key_bottom = 5,
}oled_key_button;

typedef struct
{
	uint8_t oled_gui_lock:2;	 				  //��ֵΪ0,gui�ɸ��ģ���ֵΪ1��gui����
	uint8_t oled_level1_options;				  //һ��Ŀ¼��С
	uint8_t oled_level2_options[MAX_GUI_LEVEL1];  //����Ŀ¼��С
	uint8_t oled_options_all;					  //
	uint8_t oled_directory;      				  //����Ŀ¼��ǩ Ĭ��0��Ŀ¼
	oled_gui_task   oled_gui_tsak_s;
	oled_key_button oled_key_button_s;
}oled_gui;

const oled_gui* get_oled_info_data(void);
void gui_interface_reset(void);;
void bsp_gui_init(void);
void interface_main(void);
void gui_lock(void);	 //gui��������
void gui_unlock_s(void); //gui��������������ʵ������޸Ĵ�������
void set_interface_button(oled_key_button button_p);
void set_interface_enc(uint8_t enc_t);

#endif
