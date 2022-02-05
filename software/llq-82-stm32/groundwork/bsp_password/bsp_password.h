/*** 
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime: 2022-02-05 14:50:51
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v6\groundwork\bsp_password\bsp_password.h
 * @symbol_custom_string_obkoro1    : 
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef _BSP_PASSWORD_H
#define	_BSP_PASSWORD_H

 #ifdef __cplusplus
extern "C" {
#endif


#include "struct_typedef.h"

#define STR_PROCESS			4				//Ԥ����С
#define MAX_USER_NAME_LEN 32+STR_PROCESS	//�������Ƴ���
#define MAX_PASS_WORD_LEN 32+STR_PROCESS	//���볤��
#define MAX_PASS_NUM	   24				//����������

typedef struct
{
	char user_name[MAX_USER_NAME_LEN];
	char pass_word[MAX_PASS_WORD_LEN];
}pass_word_info;
typedef  enum
{
	KEY_BOARD_NO_CAP,
	KEY_BOARD_IS_CAP
}iscapital;
typedef struct
{
	pass_word_info   pass_word_t[MAX_PASS_NUM];
	uint8_t 		 pass_word_num;
	uint8_t 		 pass_word_default_point;
	uint8_t			 pass_word_point;
	iscapital 		 iscapital_t;		//��Сд��Ҫ����,����״̬�޷���ȡ��Сд
}password_ctr;


void set_pass_word_def(password_ctr *password_ctr_t);


void set_username(password_ctr *password_ctr_t,char *pass_t,uint8_t num);


void set_password(password_ctr *password_ctr_t,char *pass_t,uint8_t num);

void write_user_info(password_ctr *password_ctr_t, char *username, char *password, uint8_t num);

void read_user_info(password_ctr *password_ctr_t,char *username,char *password,uint8_t num);

void read_user_name(password_ctr *password_ctr_t,char *username,uint8_t num);


void read_pass_word(password_ctr *password_ctr_t,char *password,uint8_t num);


void read_current_name(password_ctr *password_ctr_t, char *username);
void read_current_word(password_ctr *password_ctr_t, char *password);
void read_default_name(password_ctr *password_ctr_t, char *username);
void read_default_word(password_ctr *password_ctr_t, char *password);


#ifdef __cplusplus
}
#endif

#endif

