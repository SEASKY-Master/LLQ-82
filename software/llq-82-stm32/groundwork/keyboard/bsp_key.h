/***
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime                    : 2022-01-18 15:25:01
 * @LastEditors                     : Seasky.Liu
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v7\groundwork\keyboard\bsp_key.h
 * @symbol_custom_string_obkoro1    :
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */

#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "struct_typedef.h"
#include "keyboard_cfg.h"

#define MAX_SEG 6
#define MAX_POS 14
#define MAX_KEY 80

#define PRESS_LEVEL 1 //���尴������ʱ�ĵ�ƽ

#define TIME_ALL_CYCLE 1.2f //ɨ��һ�����а�������ʱ��  ��λms

// 6ms	������λ3ms
#define TIME_RESTER_COUNT 	5 //���尴����λʱ�䣬һ����˵����������ñȰ������¿�
// 12ms	�̰�����12ms
#define TIME_PRESS_COUNT 	10 //ʵ��ʱ�� TIME_ALL_CYCLE*TIME_PRESS_COUNT 		(��λms)ȷ��Ϊ�̰�ʱ��
// 0.75s
#define TIME_PRESS_L_COUNT  625 	 //ʵ��ʱ�� TIME_ALL_CYCLE*TIME_PRESS_L_COUNT 	(��λms)ȷ��Ϊ����ʱ��
#define TIME_MAX_COUNT 		2500     //���尴�������ʱ��

//����HID�������ڣ�����HID��Ҫ���ڵ���10��USB������Ϊ2���˴������˼��ݣ�����Ϊ10
#define TIME_HID_DELAY 10

//����״̬HID����ʱ��,��СΪ2
#define TIME_PRESS_L_HID_COUNT 2 // HID��������Ϊ10ms,����״̬20ms����һ���ַ�


#define KEY_NO_USER 255
#define KEY_USER 1

/*�궨�����ⰴ��*/
#define KEY_LEFT_SHIFT 55
#define KEY_RIGHT_SHIFT 66
#define KEY_LEFT_CONTROL 68
#define KEY_LEFT_WIN 69
#define KEY_LEFT_ALT 70
#define KEY_RIGHT_ALT 72
#define KEY_RIGHT_WIN 73
#define KEY_RIGHT_CONTROL 75

    typedef enum
    {
        KEY_UPSPRING,     //��������
        KEY_PRESS,        //��������
        KEY_PRESS_L_TIME, //��������
    } key_states;
    typedef struct
    {
        key_states states;          //����״̬
        uint16_t time_count;        //��������ʱ��
        uint16_t rester_time_count; //������λʱ��
    } key_time_info;
    typedef struct
    {
        GPIO_TypeDef *gpio;
        uint16_t gpio_pin;
    } key_gpio;
    typedef struct
    {
        keypad_page_t key_char;
        key_time_info press_it;
    } key_press;
    typedef struct
    {
        uint8_t num_lock : 1;
        uint8_t caps_lock : 1;
        uint8_t scroll_lock : 1;
        uint8_t compose : 1;
        uint8_t kana : 1;
    } llq_82_lock;
    typedef enum
    {
        LLQ_NULL_HID,
        LLQ_USB_HID,
        LLQ_BLE_HID,
    } llq_82_mode_enum;
    typedef enum
    {
        LLQ_WORK_KEYBOARD = 0, //���̿���
        LLQ_WORK_MOUSE,        //������
        LLQ_WORK_KEYBOARD_STR, //�����������(lvgl)
        LLQ_WORK_MEDIA,        //ý�����
        LLQ_WORK_STRING,       //�ַ���תHID���
    } llq_82_work_mode;
    typedef enum
    {
        LLQ_INPUT_BUFFER1 = 0,
        LLQ_INPUT_BUFFER2,
    } llq_82_input_str;
    typedef struct
    {
        llq_82_mode_enum keyboard_hid_mode; //����ģʽ,���߻�������
        llq_82_work_mode keyboard_work; //���̹���״̬
        uint8_t usb_connect_status;
        uint8_t ble_connect_status;
    } key_hid_mode;
    typedef struct
    {
        key_gpio key_seg[MAX_SEG];
        key_gpio key_pos[MAX_POS];
        uint8_t key_is_press_seg[MAX_SEG][MAX_POS]; //�������У��ж��Ƿ���
        key_press key_is_press[MAX_KEY];            //���µ�ID
        llq_82_lock keyboard_lock;                  //
        keyboard_cfg keyboard;
        llq_82_input_str keyboard_user;
        key_hid_mode keyboard_mode;
    } key_info_t;
    /***
     * @Author: Seasky.Liu
     * @Description: ����Ĭ������
     * @param {key_info_t} *key_cfg
     * @return {*}
     */
    void key_set_default(key_info_t *key_cfg);

    /***
     * @Author: Seasky.Liu
     * @Description: ���þ��󰴼��е�ƽ
     * @param {key_info_t} *key_cfg
     * @param {uint8_t} seg
     * @return {*}
     */
    void key_scan_gpio_set(key_info_t *key_cfg, uint8_t seg);

    /***
     * @Author: Seasky.Liu
     * @Description: ��ȡ���󰴼��е�ƽ
     * @param {key_info_t} *key_cfg
     * @param {uint8_t} seg
     * @return {*}
     */
    void key_scan_gpio_read(key_info_t *key_cfg, uint8_t seg);

    /***
     * @Author: Seasky.Liu
     * @Description: ���¼���״̬
     * @param {key_info_t} *key_cfg
     * @param {uint8_t} *rx_buff
     * @return {*}
     */
    void keyboard_led_get(key_info_t *key_cfg, uint8_t *rx_buff);

    /***
     * @Author: Seasky.Liu
     * @Description: ���°���ɨ����
     * @param {key_info_t} *key_cfg
     * @return {*}
     */
    void key_scan_updata(key_info_t *key_cfg);

    /***
     * @Author: Seasky.Liu
     * @Description: ��������ϱ�����
     * @param {uint8_t} *pTxbuf
     * @param {key_info_t} *key_cfg
     * @return {*}
     */
    void key_update(uint8_t *pTxbuf, key_info_t *key_cfg);

    /**
     * @Author          : Seasky.Liu
     * @Description     : �����Ƿ���Ҫ�Զ�����ģʽ������Ҫ���øú���
     * @param            {key_info_t} *key_cfg
     * @param            {uint8_t} usb_connect
     * @param            {uint8_t} ble_connect
     * @return           {*}
     */
    void keyboard_mode_check(key_info_t *key_cfg, uint8_t usb_connect, uint8_t ble_connect);

    /**
     * @Author          : Seasky.Liu
     * @Description     : �ֶ�����ģʽ��ʹ��ǰ��Ҫ���Զ��������
     * @param            {key_info_t} *key_cfg
     * @param            {llq_82_mode_enum} mode_t
     * @return           {*}
     */
    void keyboard_mode_set(key_info_t *key_cfg, llq_82_mode_enum mode_t);

    /**
     * @Author          : Seasky.Liu
     * @Description     : ��ȡ����ģʽ
     * @param            {key_info_t} *key_cfg
     * @return           {*}
     */
    llq_82_mode_enum keyboard_mode_get(key_info_t *key_cfg);

    /**
     * @Author          : Seasky.Liu
     * @Description     : ��ȡ����ģʽ
     * @param            {key_info_t} *key_cfg
     * @return           {*}
     */
    llq_82_work_mode keyboard_work_get(key_info_t *key_cfg);

    /**
     * @Author          : Seasky.Liu
     * @Description     : ���ü��̹������ݣ���ɹ�������Ҫ��λ������ģʽ�����ڼ���ģʽ�����л�����ģʽ
     * @param            {key_info_t} *key_cfg
     * @param            {llq_82_work_mode} work_mode_t
     * @return           {*}
     */
    void keyboard_work_set(key_info_t *key_cfg, llq_82_work_mode work_mode_t);

    /**
     * @Author          : Seasky.Liu
     * @Description     : Ĭ�ϼ��̣������л�Ϊ����ģʽ����Ҫ��λ
     * @param            {key_info_t} *key_cfg
     * @return           {*}
     */
    void keyboard_work_reset(key_info_t *key_cfg);

    void keyboard_work_input_exit(key_info_t *key_cfg);
    
    uint8_t media_updata(key_info_t *key_cfg);

#ifdef __cplusplus
}
#endif

#endif
