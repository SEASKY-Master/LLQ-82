/*
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime: 2022-01-29 15:57:17
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \llq-82\groundwork\bsp_touch\bsp_bm2166.c
 * @symbol_custom_string_obkoro1    :
 * ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */
#include "bsp_bm2166.h"
#include "usart.h"
bm2166_touch bm2166_touch_info;

static void bm2166_transmit(uint8_t *pData, uint16_t len)
{
	HAL_UART_Transmit_DMA(&huart3, pData, len);
}
void bm2166_init(void)
{
	bm2166_touch_info.bm_transmit = bm2166_transmit;
}
static void bm2166_return(uint8_t err_check)
{
}
static void bm2166_tx_updata(uint8_t *pData, uint16_t bm_len)
{
	uint16_t i = 0;
	uint16_t check_sum = 0;
	pData[0] = 0XEF;
	pData[1] = 0x01;
	/*��ַ*/
	pData[2] = 0xFF;
	pData[3] = 0xFF;
	pData[4] = 0xFF;
	pData[5] = 0xFF;

	//	pData[6]=
	pData[7] = (bm_len >> 8) & 0XFF;
	pData[8] = bm_len & 0XFF;
	//	pData[9]=
	check_sum = 0;
	for (i = 6; i <= bm_len + 6; i++)
	{
		check_sum += pData[i];
	}
	pData[i] = (check_sum >> 8) & 0XFF;
	pData[i + 1] = (check_sum)&0XFF;
}

/**
 * @Author: Seasky.Liu
 * @Description: ������������
 * @param {*}
 * @return {*}
 */
void hand_shake_ask(void)
{
	static uint8_t hand_shake_ask_tx[12] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x35, 0x00, 0x39};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_HAND_SHAKE;
		bm2166_touch_info.bm_transmit(&hand_shake_ask_tx[0], 12);
	}
}
void hand_shake_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->hand_shake_s = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: ���õ�Ч
 * @param {uint8_t} ctr_t
 * @param {uint8_t} speed_t
 * @param {uint8_t} color_t
 * @param {uint8_t} count_t
 * @return {*}
 */
void config_led_ask(uint8_t ctr_t, uint8_t speed_t, uint8_t color_t, uint8_t count_t)
{
	static uint8_t config_led_ask_tx[16] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint16_t check_sum_t = 0, i = 0;
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{

		config_led_ask_tx[6] = BM2166_PACK;
		config_led_ask_tx[9] = BM_LED_CFG;
		config_led_ask_tx[10] = ctr_t;
		config_led_ask_tx[11] = speed_t;
		config_led_ask_tx[12] = color_t;
		config_led_ask_tx[13] = count_t;
		check_sum_t = 0;
		for (i = 6; i < 7 + 7; i++)
		{
			check_sum_t += config_led_ask_tx[i];
		}
		config_led_ask_tx[i] = (check_sum_t >> 8) & 0XFF;
		config_led_ask_tx[i + 1] = (check_sum_t)&0XFF;

		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_LED_CFG;
		bm2166_touch_info.bm_transmit(&config_led_ask_tx[0], 16);
	}
}
void config_led_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	// bm2166_touch_p->hand_shake_s = pData[0];
	if (pData[0] == 0)
	{
		//������ɫ�ɹ�
	}
}

/**
 * @Author: Seasky.Liu
 * @Description: ��ָ֤��ʱ��̽����ָ��̽�⵽��¼��ָ��ͼ�����ͼ�񻺳�����
 * @param {*}
 * @return {*}
 */
void get_iamge_ask(void)
{
	static uint8_t iamge_ask_tx[12] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_GET_IMAGE;
		bm2166_touch_info.bm_transmit(&iamge_ask_tx[0], 12);
	}
}
void get_image_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->get_image_t = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: ��ͼ�񻺳����е�ԭʼͼ������ָ�������ļ����������ļ���������
 * @param {uint8_t} buffer_id
 * @return {*}
 */
void genchar_ask(uint8_t buffer_id)
{
	static uint8_t genchar_ask_tx[13] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00};
	uint8_t i = 0;
	uint16_t check_sum_t = 0;
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		genchar_ask_tx[6] = BM2166_PACK;
		genchar_ask_tx[9] = BM_GENCHAE;
		genchar_ask_tx[10] = buffer_id;
		check_sum_t = 0;
		for (i = 6; i < 4 + 7; i++)
		{
			check_sum_t += genchar_ask_tx[i];
		}
		genchar_ask_tx[i] = (check_sum_t >> 8) & 0XFF;
		genchar_ask_tx[i + 1] = (check_sum_t)&0XFF;
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_GENCHAE;
		bm2166_touch_info.bm_transmit(&genchar_ask_tx[0], 13);
	}
}
/**
 * @Author: Seasky.Liu
 * @Description: ��ͼ�񻺳����е�ԭʼͼ������ָ�������ļ����������ļ������������
 * @param {bm2166_touch} *bm2166_touch_p
 * @param {uint8_t} *pData
 * @return {*}
 */
void genchar_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->genchar_t = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: ��ȷ�ȶ������ļ��������е������ļ�(BufferID1��BufferID2)�� ? ��������� none
 * @param {*}
 * @return {*}
 */
void match_ask(void)
{
	uint8_t match_ask_tx[12] = {0XEF, 0X01, 0XFF, 0XFF, 0XFF, 0XFF, 0X01, 0X00, 0X03, 0X03, 0X00, 0X07};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_MATCH;
		bm2166_touch_info.bm_transmit(&match_ask_tx[0], 12);
	}
}
void match_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->match_t.match_ack_t = pData[0];
	bm2166_touch_p->match_t.score = (pData[1] << 8) | pData[2];
}
/**
 * @Author: Seasky.Liu
 * @Description: �ϲ�ָ����������
 * @param {*}
 * @return {*}
 */
void reg_mode_ask(void)
{
	static uint8_t reg_mode_askt[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_REG_MODE;
		bm2166_touch_info.bm_transmit(&reg_mode_askt[0], 12);
	}
}
/**
 * @Author: Seasky.Liu
 * @Description: �ϲ�ָ���������
 * @param {bm2166_touch} *bm2166_touch_p
 * @param {uint8_t} *pData
 * @return {*}
 */
void reg_mode_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->regmode_t = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: ��������
 * @param {uint8_t} buffer_id
 * @param {uint16_t} start_page
 * @return {*}
 */
void store_char_ask(uint8_t buffer_id, uint16_t start_page)
{

	static uint8_t store_char_ask_tx[15] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t i = 0;
	uint16_t check_sum_t = 0;
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		store_char_ask_tx[6] = BM2166_PACK;
		store_char_ask_tx[9] = BM_STORECHAR;
		store_char_ask_tx[10] = buffer_id;
		store_char_ask_tx[11] = (start_page >> 8) & 0XFF;
		store_char_ask_tx[12] = (start_page)&0XFF;
		check_sum_t = 0;
		for (i = 6; i < 6 + 7; i++)
		{
			check_sum_t += store_char_ask_tx[i];
		}
		store_char_ask_tx[i] = (check_sum_t >> 8) & 0XFF;
		store_char_ask_tx[i + 1] = (check_sum_t)&0XFF;
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_STORECHAR;
		bm2166_touch_info.bm_transmit(&store_char_ask_tx[0], 15);
	}
}
void store_char_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->storechar_t = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: �ȶ�ָ��
 * @param {uint8_t} buffer_id
 * @param {uint16_t} start_page
 * @param {uint16_t} pagenum
 * @return {*}
 */
void high_speed_search_ask(uint8_t buffer_id, uint16_t start_page, uint16_t pagenum)
{
	static uint8_t high_speed_search_ask_tx[17] =
		{0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t i = 0;
	uint16_t check_sum_t = 0;
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		high_speed_search_ask_tx[6] = BM2166_PACK;
		high_speed_search_ask_tx[9] = BM_HIGH_SEARCH;
		high_speed_search_ask_tx[10] = buffer_id;
		high_speed_search_ask_tx[11] = (start_page >> 8) & 0XFF;
		high_speed_search_ask_tx[12] = (start_page)&0XFF;
		high_speed_search_ask_tx[13] = (pagenum >> 8) & 0XFF;
		high_speed_search_ask_tx[14] = (pagenum)&0XFF;
		check_sum_t = 0;
		for (i = 6; i < 8 + 7; i++)
		{
			check_sum_t += high_speed_search_ask_tx[i];
		}
		high_speed_search_ask_tx[i] = (check_sum_t >> 8) & 0XFF;
		high_speed_search_ask_tx[i + 1] = (check_sum_t)&0XFF;

		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_HIGH_SEARCH;
		bm2166_touch_info.bm_transmit(&high_speed_search_ask_tx[0], 17);
	}
}
void high_speed_search_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->high_search_t.high_search_s = pData[0];
	bm2166_touch_p->high_search_t.page_id = (pData[1] << 8) | pData[2];
	bm2166_touch_p->high_search_t.mathscore = (pData[3] << 8) | pData[4];
	touch_delect_callback(bm2166_touch_p->high_search_t.high_search_s,
						  bm2166_touch_p->high_search_t.page_id,
						  bm2166_touch_p->high_search_t.mathscore);
}
/*
����˵����
	ע��ָ��ʱ��̽����ָ��̽�⵽��¼��ָ��ͼ�����ͼ�񻺳�����
*/
void get_enrollImage_ask(void)
{
	static uint8_t enroll_tx[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x29, 0x00, 0x2D};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_GETENROLLIMAGE;
		bm2166_touch_info.bm_transmit(&enroll_tx[0], 12);
	}
}
void get_enrollImage_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	bm2166_touch_p->get_enroll_t = pData[0];
}

/**
 * @Author: Seasky.Liu
 * @Description: ���ָ��
 * @param {*}
 * @return {*}
 */
void empty_ask(void)
{
	static uint8_t tx_temp_num_t[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0d, 0x00, 0x11};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = BM_EMPTY;
		bm2166_touch_info.bm_transmit(&tx_temp_num_t[0], 12);
	}
}
void empty_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	//���ָ���� pData[0]
	if (pData[0] != 0)
	{
		//���ʧ��
		bm2166_touch_p->empty_is_ok = 1;
	}
	else
	{
		bm2166_touch_p->empty_is_ok = 0;
	}
}

/*��ȡָ�Ƹ���*/
void validtemp_num_ask(void)
{
	static uint8_t tx_temp_num_t[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x1d, 0x00, 0x21};
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_NO)
	{
		//����Ϊ��Ӧ����Ҫ�ȴ�Ӧ��
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_WAIT;
		//�����·�ָ�����Ӧ�����
		bm2166_touch_info.frame_calc_t.ack_ctr_cmd = ValidTempleteNum;
		bm2166_touch_info.bm_transmit(&tx_temp_num_t[0], 12);
	}
}
void validtemp_num_ack(bm2166_touch *bm2166_touch_p, uint8_t *pData)
{
	if (pData[0] == ACK_DONE_OK)
	{
		bm2166_touch_p->valid_num = (pData[1] << 8) | pData[2];
		touch_num_callback(bm2166_touch_p->valid_num);
	}
}

/*����ָ��*/
void normal_speed_search()
{
}
void Ps_Rec_Calc(uint8_t frame_logo_t, uint8_t *pData, uint8_t data_len)
{
	//���ȷʵ�ڵȴ�Ӧ��
	if (bm2166_touch_info.frame_calc_t.ack_rec_ok == BM_ACK_WAIT)
	{
		//�ȴ���Ӧ���źţ�����δ����
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_OK;
		//����ָ��,����Ӧ���ź�
		switch (bm2166_touch_info.frame_calc_t.ack_ctr_cmd)
		{
		case BM_GET_IMAGE:
			get_image_ack(&bm2166_touch_info, pData);
			break;
		case BM_GENCHAE:
			genchar_ack(&bm2166_touch_info, pData);
			break;
		case BM_MATCH:
			match_ack(&bm2166_touch_info, pData);
			break;
		case BM_REG_MODE:
			reg_mode_ack(&bm2166_touch_info, pData);
			break;
		case BM_STORECHAR:
			store_char_ack(&bm2166_touch_info, pData);
			break;
		case BM_EMPTY:
			empty_ack(&bm2166_touch_info, pData);
			break;
		case ValidTempleteNum:
			validtemp_num_ack(&bm2166_touch_info, pData);
			break;
		case BM_GETENROLLIMAGE:
			get_enrollImage_ack(&bm2166_touch_info, pData);
			break;
		case BM_HAND_SHAKE:
			hand_shake_ack(&bm2166_touch_info, pData);
			break;
		case BM_HIGH_SEARCH:
			high_speed_search_ack(&bm2166_touch_info, pData);
			break;
		case BM_LED_CFG:
			config_led_ack(&bm2166_touch_info, pData);
			break;
		default:
			break;
		}
		//�������
		bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_NO;
	}
}

//bm2166_touch bm2166_touch_info;
void bsp_bm2166_receive(uint8_t *pData, uint16_t rec_len)
{
	/*
    	��ͷ		->	2-byte 	0xEF 	0x01
    	оƬ��ַ	->	4-byte
    	����ʶ		->	1-byte
    	������		->	2-byte
    	ָ��		->	1-byte
    	����		->	n-byte
    	У���		->	2-byte
    	������		=	��������У��ͣ�ָ����������ݣ������ֽ���������У��ͣ��������������ȱ�����ֽ�����
    				=	n+3
    	У����ǴӰ���ʶ��У���֮�������ֽ�֮�ͣ����� 2 �ֽڵĽ�λ���ԡ�
    */
	bm2166_touch_info.frame_calc_t.rec_is_ok = 0;
	bm2166_touch_info.frame_calc_t.frame_header = (pData[0] << 8) | pData[1];
	if (bm2166_touch_info.frame_calc_t.frame_header == FRAME_HEAD)
	{
		//		bm2166_touch_info.frame_calc_t.frame_addr =
		bm2166_touch_info.frame_calc_t.frame_logo = pData[6];
		bm2166_touch_info.frame_calc_t.frame_len = (pData[7] << 8) | pData[8];
		bm2166_touch_info.frame_calc_t.frame_ins = pData[9];
		bm2166_touch_info.frame_calc_t.checksum = (pData[10] << 8) | pData[11];
		bm2166_touch_info.frame_calc_t.all_len = bm2166_touch_info.frame_calc_t.frame_len + 9;
		if (bm2166_touch_info.frame_calc_t.all_len == rec_len)
		{
			/*����֡����*/
			bm2166_touch_info.frame_calc_t.rec_is_ok = 1;
			Ps_Rec_Calc(bm2166_touch_info.frame_calc_t.frame_logo,
						&pData[9],
						bm2166_touch_info.frame_calc_t.frame_len - 2);
		}
	}
}


void bm2166_check_err_time(void)
{
	static uint8_t check_count = 0 ;

	if(bm2166_touch_info.frame_calc_t.ack_rec_ok != BM_ACK_NO)
	{
		check_count++;
		if(check_count>=BM_ACK_MAX_WAIT_TIME)
		{
			bm2166_touch_info.frame_calc_t.ack_rec_ok = BM_ACK_NO;
			check_count = 0;
		}
	}
	else
	{
		check_count = 0;
	}
}
/**
 * @Author: Seasky.Liu
 * @Description: �Զ����ټ��ָ��
 * @param {*}
 * @return {*}
 */
void auto_finger_detect(void)
{
	/***************************�Զ�ʶ��ָ���߼�***************************/
	switch (bm2166_touch_info.press_t)
	{
	case STATE_PRESS_NO:
	{
		//�����ȡ��ָ��
		if (bm2166_touch_info.get_image_t == ACK_DONE_OK)
		{
			//���ͻ�ȡͼ������
			bm2166_touch_info.press_t = STATE_PRESS_READY;
			bm2166_touch_info.genchar_t = ACK_NORMAL;
			bm2166_touch_info.high_search_t.high_search_s = ACK_NORMAL;
		}
		else
		{
			//���ͻ�ȡͼ������
			get_iamge_ask();
			break;
		}
	}
	case STATE_PRESS_READY:
	{
		//��������ͼ����������
		genchar_ask(CharBuffer1);
		bm2166_touch_info.press_t = STATE_PRESS_RUN;
	}
	// break;
	case STATE_PRESS_RUN: //ָ�ư����¼�����
	{
		//�������ɳɹ�
		if (bm2166_touch_info.genchar_t == ACK_DONE_OK)
		{
			//���Ϳ�������ָ��
			high_speed_search_ask(CharBuffer1, 0, 300);
		}
		else if (bm2166_touch_info.genchar_t != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
	}
	case STATE_SEARCH:
	{
		//���������ָ��
		if (bm2166_touch_info.high_search_t.high_search_s == ACK_DONE_OK)
		{
			// bm2166_touch_info.high_search_t.high_search_s = 0;
			bm2166_touch_info.high_search_t.page_id = 0;
			bm2166_touch_info.high_search_t.mathscore = 0;
			//�ȶԳɹ�
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
		else if (bm2166_touch_info.high_search_t.high_search_s != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
	}
	break;
	case STATE_PRESS_END:
	{
		//���û�л�ȡ��ָ�ƣ���ʾ��ָ�뿪
		if (bm2166_touch_info.get_image_t != ACK_DONE_OK)
		{
			//���û�л�ȡ��ָ�ƣ����δ����
			bm2166_touch_info.press_t = STATE_PRESS_NO;
		}
		else
		{
			//���ͻ�ȡͼ������
			get_iamge_ask();
		}
	}
	default:
		break;
	}
}


/**
 * @Author: Seasky.Liu
 * @Description: ���ָ�ƣ���������ָ��
 * @param {uint16_t} page_id
 * @return {*}
 */
uint8_t add_finger(uint16_t page_id)
{
	static uint8_t get_iamge_ask_count = 0;
	if (page_id >= TOUCH_MAX_FINGER_COUNT)
	{
		//�����趨��Χ
		return TOUCH_ADD_ERR;
	}
	/***************************�Զ����ָ���߼�***************************/
	switch (bm2166_touch_info.press_t)
	{
	case STATE_PRESS_NO:
	{
		//�����ȡ��ָ��
		if (bm2166_touch_info.get_image_t == ACK_DONE_OK)
		{
			//���ͻ�ȡͼ������
			bm2166_touch_info.press_t = STATE_PRESS_READY;
			bm2166_touch_info.genchar_t = ACK_NORMAL;
			bm2166_touch_info.match_t.match_ack_t = ACK_NORMAL;
			bm2166_touch_info.regmode_t = ACK_NORMAL;
			bm2166_touch_info.storechar_t = ACK_NORMAL;
			break;
		}
		get_iamge_ask();
	}
	break;
	case STATE_PRESS_READY:
	{
		//����ͼ������
		genchar_ask(get_iamge_ask_count + 1);
		bm2166_touch_info.press_t = STATE_PRESS_RUN;
	}
	break;
	case STATE_PRESS_RUN: //ָ�ư����¼�����
	{
		//����ͼ�������ɹ�
		if (bm2166_touch_info.genchar_t == ACK_DONE_OK)
		{
			if (get_iamge_ask_count < TOUCH_INPUT_COUNT)
			{
				get_iamge_ask_count++;
				//�ȴ��ﵽ¼�����
				bm2166_touch_info.press_t = STATE_PRESS_END;
				break;
			}
			else
			{
				//�ﵽ¼�����
				//				match_ask();
				//				bm2166_touch_info.press_t = STATE_MATCH;
				//���ͺϲ���������
				reg_mode_ask();
				bm2166_touch_info.press_t = STATE_REG_MODEL;
			}
		}
		else if (bm2166_touch_info.genchar_t != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
	}
	break;
	case STATE_MATCH:
	{
		//��⾫ȷ�ȶԽ��
		if (bm2166_touch_info.match_t.match_ack_t == ACK_DONE_OK)
		{
			//���ͺϲ���������
			reg_mode_ask();
			bm2166_touch_info.press_t = STATE_REG_MODEL;
		}
		else if (bm2166_touch_info.match_t.match_ack_t != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
	}
	break;
	case STATE_REG_MODEL:
	{
		//���ϲ��������
		if (bm2166_touch_info.regmode_t == ACK_DONE_OK)
		{
			get_iamge_ask_count = 0;
			store_char_ask(CharBuffer1, page_id);
			bm2166_touch_info.press_t = STATE_STORECHAR;
		}
		else if (bm2166_touch_info.regmode_t != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
		}
	}
	break;
	case STATE_STORECHAR:
	{
		if (bm2166_touch_info.storechar_t != ACK_NORMAL)
		{
			bm2166_touch_info.press_t = STATE_PRESS_END;
			if (bm2166_touch_info.storechar_t == ACK_DONE_OK)
			{
				get_iamge_ask();
				return TOUCH_ADD_OK;
			}
		}
	}
	break;
	case STATE_PRESS_END:
	{
		//���û�л�ȡ��ָ�ƣ���ʾ��ָ�뿪
		if (bm2166_touch_info.get_image_t != ACK_DONE_OK)
		{
			//���û�л�ȡ��ָ�ƣ����δ����
			bm2166_touch_info.press_t = STATE_PRESS_NO;
		}
		else
		{
			//���ͻ�ȡͼ������
			get_iamge_ask();
		}
	}
	break;
	default:
		break;
	}
	return TOUCH_ADD_ERR;
}

/**
 * @Author: Seasky.Liu
 * @Description: ���ָ��
 * @param {*}
 * @return {*}
 */
void finger_empty(void)
{
	empty_ask();
}
