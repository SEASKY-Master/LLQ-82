/***
 * @Author                          : Seasky.Liu
 * @LastEditors                     : Seasky.Liu
 * @FilePath                        : \keyboard_v7\applications\flash_task.h
 * @Description                     : https://github.com/SEASKY-Master
 * @symbol_custom_string_obkoro1    :
 * @��Ȩ����: @Seasky.Liu
 * @��ϵ��ʽ: liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;,ΥȨ�ؾ�
 * @************************************************************************
 * @				If you want a thing done well, do it yourself.
 * @************************************************************************
 */

#ifndef _FLASH_TASK_H
#define _FLASH_TASK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_flash.h"
#include "bsp_password.h"
#include "lvgl_app.h"

#define USER_FALSH_PAGE ADDR_FLASH_SECTOR_11

#define FLASH_DELAY_TIME 500
#define FLASH_MAX_TRY_COUNT 5
#define NORMAL_LCD_SHOW_TIME 40
#define MIN_LCD_SHOW_TIME 20
//��flash������
#define cali_flash_read(address, buf, len) flash_read((address), (buf), (len))
//��һҳflashд����
#define cali_flash_write(address, buf, len) flash_write_single_address((address), (buf), (len))
//����flash
#define cali_flash_erase(address, page_num) flash_erase_address((address), (page_num))

	typedef enum
	{
		MCU_NORMAL_MODE = 0,
		MCU_STOP_MODE,
		MCU_SLEEP_MODE,
		MCU_STANDBY_MAX,
	} mcu_standby;
	typedef struct
	{
		uint8_t mcu_sleep_ctr; // mcu_standby
		uint8_t left_dir;
		uint8_t right_dir;
		uint8_t lcd_touch_power;
		uint8_t rgb_power;
		uint8_t sleep_time;
	} mcu_ctr;
	//�ò��ֽ��ᱻ�洢��flash��,llq_store��������128k
	typedef struct
	{
		password_ctr bsp_password; //�û���Ϣ
		llq_lvgl_style_code lvgl_style;
		mcu_ctr llq_mcu_ctr;
		uint16_t crc_check;
	} llq_store;

	typedef enum
	{
		FLASH_NO_INIT = 0, // flash��δ���г�ʼ��
		FLASH_READY = 1,   // flash׼������
		FLASH_READ = 2,	   // flash���ڽ��ж�����
		FLASH_WRITE = 3,   // flash���ڽ���д����
		FLASH_ERR = 4,
	} llq_flash_status;
	typedef enum
	{
		FLASH_CMD_NO = 0,
		FLASH_CMD_READ,
		FLASH_CMD_READ_OK,
		FLASH_CMD_READ_ERR,
		FLASH_CMD_WRITE,
		FLASH_CMD_WRITE_OK,
		FLASH_CMD_WRITE_ERR,
	} llq_flash_cmd;
	//�ṩflash������صĽӿ�
	typedef struct
	{
		llq_store llq_store_p;		  //��Ҫ�洢������
		pass_word_info password_edit; //��ǰ���ڱ༭�����ƺ����룬׼������FLASH
		uint16_t password_index;	  //׼��д�뵽��һ�����ƺ�����
		uint8_t read_count;
		uint8_t write_count;

		uint8_t lcd_timer_count;
		uint8_t lcd_timer_enable;
		uint8_t lcd_power;
		llq_flash_status flash_status; // flash״̬
		llq_flash_cmd flash_cmd;
	} llq_store_ctr;

	/**
	 * @Author          : Seasky.Liu
	 * @Date            : 2022-01-18 14:18:28
	 * @Description     : ��ʼ��flash
	 * @param            {*}
	 * @return           {*}
	 */
	void flash_info_init(void);

	void flash_task_creat(void);
	/***
	 * @Author: Seasky.Liu
	 * @Description: ��������
	 * @param {char} *name
	 * @param {char} *word
	 * @param {uint8_t} num
	 * @return {*}
	 */

	void updata_password_edit(char *name, char *word, uint8_t num);

	/***
	 * @Author: Seasky.Liu
	 * @Description: ��ȡ������Ϣ
	 * @param {char} *name
	 * @param {char} *word
	 * @param {uint8_t} num
	 * @return {*}
	 */
	void get_password_info(char *name, char *word, uint8_t num);

	void set_user_info(char *username, char *password, uint8_t num);

	void get_user_info(char *username, char *password, uint8_t num);

	void get_user_name(char *username, uint8_t num);

	void get_pass_word(char *password, uint8_t num);

	void flash_info_lvgl_style(llq_lvgl_style_code *pstyle_code);

	void flash_save_setting(void);

	uint8_t check_standby_normal(void);

	void set_standy_mode(mcu_standby standby_p);

	void flash_config_exit_standy(void);

	void flash_config_enter_standy(void);

	void flash_config_save_standy(void);

	void key_setting_show_info(uint8_t level, uint8_t enc_t, uint8_t enable);

	uint8_t get_flash_ble_enable(void);

	uint8_t get_flash_lcd_touch_enable(void);

	uint8_t get_flash_rgb_enable(void);

	void lcd_wake_up(void);

	void get_current_name(char *username);
	void get_current_word(char *password);
	void get_default_name(char *username);
	void get_default_word(char *password);
	void set_tx_current(uint8_t curr_num);
	void set_tx_default(uint8_t def_num);
	password_ctr *password_show(void);
#ifdef __cplusplus
}
#endif

#endif
