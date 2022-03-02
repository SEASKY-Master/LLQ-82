/*** 
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime: 2022-02-06 14:43:57
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v6\groundwork\bsp_touch\bsp_bm2166.h
 * @symbol_custom_string_obkoro1    : 
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef __AS608_H
#define __AS608_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "struct_typedef.h"

#define PS_Sta   PAin(6)//��ָ��ģ��״̬����
#define CharBuffer1 	0x01
#define CharBuffer2 	0x02

#define BMC_ADDR 		0XFFFFFFFF

#define FRAME_HEAD   	0XEF01

#define BM_GET_IMAGE 		0X01
#define BM_GENCHAE			0X02
#define BM_MATCH			0X03	//��ȷ�Ա�ָ��
#define BM_REG_MODE			0X05	//�ϲ�ָ������
#define BM_STORECHAR		0X06 	//��������
#define BM_EMPTY			0X0D	
#define BM_HIGH_SEARCH		0X1B
#define ValidTempleteNum	0X1D
#define BM_GETENROLLIMAGE	0X29
#define BM_HAND_SHAKE		0X35	//����ָ��
#define BM_LED_CFG          0X3C

#define BM2166_PACK     	0X01
//Ӧ��
#define BM2166_ACK			0X07

#define BM_ACK_NO  			 0
#define BM_ACK_WAIT 	     1
#define BM_ACK_OK   		 2
#define BM_ACK_MAX_WAIT_TIME 300


#define TOUCH_MAX_RUN_COUNT 	10 
#define TOUCH_MAX_FINGER_COUNT 	300
#define TOUCH_INPUT_COUNT		2	//ָ��¼�����
#define TOUCH_ADD_OK      		0
#define TOUCH_ADD_ERR			1
typedef enum
{
	ACK_DONE_OK 		= 	0X00,//��ʾָ��ִ����ϻ�OK��
	ACK_RX_ERROR 		=	0X01,//��ʾ���ݰ����մ���
	ACK_NO_TOUCH		=	0X02,//��ʾ��������û����ָ��
	ACK_FINGER_ENTER_ERR =  0X03,//��ʾ¼��ָ��ͼ��ʧ�ܣ�
	ACK_IMAGE_DRY_LIGHT	=	0X04,//��ʾָ��ͼ��̫�ɡ�̫����������������
	ACK_IMAGE_WET_MUDDY	=	0X05,//��ʾָ��ͼ��̫ʪ��̫����������������
	ACK_IMAGE_MESSY		=	0X06,//��ʾָ��ͼ��̫�Ҷ�������������
	ACK_IMAGE_SMALL		=	0X07,//��ʾָ��ͼ����������������̫�٣������̫С����������������
	ACK_IMAGE_NOT_MATCH	=	0X08,//��ʾָ�Ʋ�ƥ�䣻
	ACK_NO_FINGER_F		=	0X09,//��ʾû������ָ�ƣ�
	ACK_MERGE_FAILED	=	0X0A,//��ʾ�����ϲ�ʧ�ܣ�
	ACK_OUT_RANGE		=	0X0B,//��ʾ����ָ�ƿ�ʱ��ַ��ų���ָ�ƿⷶΧ��
	ACK_WRONG_INVALID	=	0X0C,//��ʾ��ָ�ƿ��ģ��������Ч��
	ACK_UPLOAD_FAILED	=	0X0D,//��ʾ�ϴ�����ʧ�ܣ�
	ACK_RECEIVE_NOT		=	0X0e,//��ʾģ�鲻�ܽ��պ������ݰ���
	ACK_IMG_UP_FAILED	=	0X0f,//��ʾ�ϴ�ͼ��ʧ�ܣ�
	ACK_FAILED_DEL_TEMP	=	0X10,//��ʾɾ��ģ��ʧ�ܣ�
	ACK_CLEAR_FAILED	=	0X11,//��ʾ���ָ�ƿ�ʧ�ܣ�
	ACK_LOW_POWER_NO_E	=	0X12,//��ʾ���ܽ���͹���״̬��
	ACK_PASS_INCORRECT	=	0X13,//��ʾ�����ȷ��
	ACK_RES_FAILED		=	0X14,//��ʾϵͳ��λʧ�ܣ�
	ACK_NO_VALID		=	0X15,//��ʾ��������û����Чԭʼͼ��������ͼ��
	ACK_UPGRADE_FAILED	=	0X16,//��ʾ��������ʧ�ܣ�
	ACK_NOT_MOVE		=	0X17,//��ʾ����ָ�ƻ����βɼ�֮����ָû���ƶ�����
	ACK_FLASH_WR_ERR	=	0X18,//��ʾ��д FLASH ����
	ACK_AFTER_REC		=	0Xf0,//�к������ݰ���ָ���ȷ���պ��� 0xf0 Ӧ�� f1,//�к������ݰ���ָ�������� 0xf1 Ӧ��
	ACK_FLASH_SUM_ERR	=	0Xf2,//��ʾ��д�ڲ� FLASH ʱ��У��ʹ���
	ACK_FLASH_PACK_ERR	=	0Xf3,//��ʾ��д�ڲ� FLASH ʱ������ʶ����
	ACK_FLASH_LEN_ERR	=	0Xf4,//��ʾ��д�ڲ� FLASH ʱ�������ȴ���
	ACK_FLASH_CODE_ERR	=	0Xf5,//��ʾ��д�ڲ� FLASH ʱ�����볤��̫����
	ACK_FLASH_PRO_ERR	=	0Xf6,//��ʾ��д�ڲ� FLASH ʱ����д FLASH ʧ�ܣ�
	ACK_RANDOW_FAILED	=	0X19,//���������ʧ�ܣ�
	ACK_INVALID_REG		=	0X1a,//��Ч�Ĵ����ţ�
	ACK_ERR_NUMBER		=	0X1b,//�Ĵ����趨���ݴ���ţ�
	ACK_NOTE_ERR		=	0X1c,//���±�ҳ��ָ������
	ACK_PORT_FAILED		=	0X1d,//�˿ڲ���ʧ�ܣ�
	ACK_ENROLL_FAILED	=	0X1e,//�Զ�ע�ᣨenroll��ʧ�ܣ�
	ACK_LIB_FULL		=	0X1f,//ָ�ƿ�����
	ACK_DEV_ADDR_ERR	=	0X20,//�豸��ַ����
	ACK_PASS_WRONG		=	0X21,//��������
	ACK_TEMP_NOT_ENPTY	=	0X22 ,//ָ��ģ��ǿգ�
	ACK_TEMP_EMPTY		=	0X23 ,//ָ��ģ��Ϊ�գ�
	ACK_LIB_EMPTY	=	0X24 ,//ָ�ƿ�Ϊ�գ�
	ACK_ENTRIES_ERR	=	0X25 ,//¼��������ô���
	ACK_TIMEOUT		=	0X26 ,//��ʱ��
	ACK_ALREADY_EXISTS	=	0X27 ,//ָ���Ѵ��ڣ�
	ACK_TEMP_RELATED	=	0X28 ,//ָ��ģ���й�����
	ACK_INIT_ERR	=	0X29 ,//��������ʼ��ʧ�ܣ�

	//��������Ĭ��ֵ������Ƿ����ص�
	ACK_NORMAL      =   0XFF,
	//Reserved
	//0X2AH��ef,
}ack_enum;

//����״̬��
typedef enum
{
	STATE_PRESS_NO = 0, //Ĭ��ָ��δ����
	STATE_PRESS_READY,	//ָ�ư��£�׼����ʼ����
	STATE_PRESS_RUN,	//�Ѿ���ʼ����
	STATE_SEARCH,
	STATE_MATCH,		//��ȷ�Ա�ָ��
	STATE_REG_MODEL,	//�ϲ�����
	STATE_STORECHAR,	//���������ļ�
	STATE_PRESS_END,	//ָ�ƴ������
}state_machine;
typedef struct
{
	uint16_t frame_header;
	uint32_t frame_addr;
	uint16_t frame_logo;
	uint16_t frame_len;
	uint16_t frame_ins;
	uint16_t checksum;
	uint16_t all_len;
	uint8_t  rec_is_ok;
	/*����ָ�������Ϣ*/
	uint8_t  ack_ctr_cmd;
	uint8_t  ack_rec_ok;//�����һ֡δ�յ�������ʱ��������ָ��
}bm2166_calc;

typedef struct
{
	state_machine press_t;
	uint8_t       run_count;
	bm2166_calc   frame_calc_t;
	uint8_t 	  hand_shake_s;	//����״̬,1������ʧ�ܣ�0�����ֳɹ���ʹ��ǰӦ�ñ��Ϊ1
	ack_enum 	  get_image_t; 	//��ָ֤��ʱָ��״̬
	ack_enum	  genchar_t;	//����ָ������״̬
	ack_enum	  regmode_t;	//�ϲ�����״̬
	ack_enum	  storechar_t;
	struct
	{
		ack_enum high_search_s;
		uint16_t page_id;	//ָ�Ƶ�ID
		uint16_t mathscore; //ͨ����
	}high_search_t;
	ack_enum	get_enroll_t;//ע��ָ��ʱָ��״̬
	struct
	{
		ack_enum match_ack_t;
		uint16_t score;
	}match_t;
	uint16_t valid_num;//ע�����Чģ�����
	uint8_t  empty_is_ok;
	void (*bm_transmit)(uint8_t *pData,uint16_t len);
}bm2166_touch;

void bm2166_init(void);


/*** 
 * @Author: Seasky.Liu
 * @Description: ���������ź�
 * @param {*}
 * @return {*}
 */
void hand_shake_ask(void);

/*** 
 * @Author: Seasky.Liu
 * @Description: ���Ͷ�ȡָ��״ָ̬��
 * @param {*}
 * @return {*}
 */
void get_iamge_ask(void);

/*** 
 * @Author: Seasky.Liu
 * @Description: ���ͻ�ȡָ��ͼ��ָ��
 * @param {*}
 * @return {*}
 */
void get_enrollImage_ask(void);

/*** 
 * @Author: Seasky.Liu
 * @Description: ���ͻ�ȡ��Чָ������ָ��
 * @param {*}
 * @return {*}
 */
void validtemp_num_ask(void);

/*** 
 * @Author: Seasky.Liu
 * @Description: ����ָ�Ƽ��ָ��
 * @param {uint8_t} buffer_id
 * @return {*}
 */
void genchar_ask(uint8_t buffer_id);

/*** 
 * @Author: Seasky.Liu
 * @Description: ����ָ�ƿ�������ָ��
 * @param {uint8_t} buffer_id
 * @param {uint16_t} start_page
 * @param {uint16_t} pagenum
 * @return {*}
 */
void high_speed_search_ask(uint8_t buffer_id,uint16_t start_page,uint16_t pagenum);


/*** 
 * @Author: Seasky.Liu
 * @Description: �������ݴ���ص�����
 * @param {uint8_t} *pData
 * @param {uint16_t} rec_len
 * @return {*}
 */
void bsp_bm2166_receive(uint8_t *pData,uint16_t rec_len);



/*** 
 * @Author: Seasky.Liu
 * @Description: �Զ�ʶ��ָ��
 * @param {*}
 * @return {*}
 */
void auto_finger_detect(void);


/**
 * @Author: Seasky.Liu
 * @Description: ���ָ�ƣ���������ָ��
 * @param {uint16_t} page_id
 * @return {*}
 */
uint8_t add_finger(uint16_t page_id);


/**
 * @Author: Seasky.Liu
 * @Description: ���ָ��
 * @param {*}
 * @return {*}
 */
void finger_empty(void);


/**
 * @Author: Seasky.Liu
 * @Description: ���õ�Ч
 * @param {uint8_t} ctr_t
 * @param {uint8_t} speed_t
 * @param {uint8_t} color_t
 * @param {uint8_t} count_t
 * @return {*}
 */
void config_led_ask(uint8_t ctr_t,uint8_t speed_t,uint8_t color_t,uint8_t count_t);


void bm2166_check_err_time(void);

#ifdef __cplusplus
}
#endif

#endif

