/*** 
 * @Author                         : Seasky.Liu
 * @Date                           : Do not edit
 * @LastEditTime: 2022-02-27 17:32:07
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
#ifndef _BSP_BLE_H_
#define _BSP_BLE_H_

#include "struct_typedef.h"

#define FRAME_HEAD (0XA5)
#define FRAME_LEN  (30)
#define FRAME_END  (0XFE)
#define KEYBOARD_INFO_LEN    27

/*ǰ12�ֽڹ�������������ʹ��,��16�ֽڹ�esp-nowʹ��*/
#define UART_REPORT_ID_MOUSE 0X01
#define UART_REPORT_ID_KEY   0X02
#define UART_REPORT_ID_MEDIA 0X03
#define UART_REPORT_ID_INFO  0X04   
#define UART_REPORT_ID_MAC   0X05

#define HID_CONSUMER_PLAY           176 // Play			
#define HID_CONSUMER_SCAN_NEXT_TRK  181 // Scan Next Track
#define HID_CONSUMER_SCAN_PREV_TRK  182 // Scan Previous Track			
#define HID_CONSUMER_VOLUME_UP      233 // Volume Increment
#define HID_CONSUMER_VOLUME_DOWN    234 // Volume Decrement
#define HID_CONSUMER_MUTE           226 // Mute
#define HID_CONSUMER_PAUSE          177 // Pause
#define HID_CONSUMER_STOP           183 // Stop

#define HID_CONSUMER_POWER          48  // Power
#define HID_CONSUMER_RECALL_LAST    131 // Recall Last
#define HID_CONSUMER_ASSIGN_SEL     129 // Assign Selection
#define HID_CONSUMER_RECORD         178 // Record
#define HID_CONSUMER_FAST_FORWARD   179 // Fast Forward
#define HID_CONSUMER_REWIND         180 // Rewind
#define HID_CONSUMER_CHANNEL_UP     156 // Channel Increment
#define HID_CONSUMER_CHANNEL_DOWN   157 // Channel Decrement

typedef enum
{
    LLQ_RESET = 0 ,
    LLQ_DISCONNECT,
    LLQ_CONNECT,
    LLQ_ERR,
}LLQ_STATE;

typedef struct
{
	uint8_t num_lock:1;
	uint8_t caps_lock:1;
	uint8_t scroll_lock:1;
	uint8_t compose:1;
	uint8_t kana:1;
}ble_lock_key;

typedef enum
{
    ENUM_NUM_LOCK = 0,
    ENUM_CAPS_LOCK,
    ENUM_SCROLL_LOCK,
    ENUM_COMPOSE,
    ENUM_KANA,
}ble_enum_lock;
typedef struct
{
    /*18 �ֽ� ��������*/
    uint8_t key_press[10];//��������״̬
    uint8_t enc_press;    //��������������״̬
    uint8_t enc_value[2]; //������ֵ
    uint8_t touch_id;     //ָ��ʶ����
    uint8_t customize[4]; //�Զ��幦��
} llq_now_info;
typedef struct 
{
    uint8_t         tx_battery_cap;
    uint8_t         rx_battery_cap;
    LLQ_STATE       ble_connect;
    ble_lock_key    ble_lock;
	uint8_t			llq_mac[6];
	uint8_t			now_mac[6];
    uint8_t         set_esp_now;
	llq_now_info	esp_now_p;
}bsp_ble_info;

void ble_tx_buff_updata(uint8_t *tx_p,uint8_t len);
void ble_rx_buff_updata(uint8_t *rx_p, uint8_t len);
void ble_set_battery(uint8_t cap_t);
void ble_clear_connect(void);
uint8_t ble_check_connect(void);

#endif