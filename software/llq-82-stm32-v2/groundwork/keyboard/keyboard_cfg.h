/***
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime: 2022-01-29 16:50:36
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v5\groundwork\keyboard\keyboard_cfg.h
 * @symbol_custom_string_obkoro1    :
 * @��Ȩ����:@Seasky.liu
 * @��ϵ��ʽ:liuwei_seasky@163.com
 * @��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * @************************************************************************
 * @           If you want a thing done well, do it yourself.
 * @************************************************************************
 */
#ifndef _KEYBOARD_CFG_H
#define _KEYBOARD_CFG_H

    /*
        ý�巢�͸�PC������ÿ��4���ֽ� :
        BYTE1 --
            |--bit7: UAGE - Stop
            |--bit6: UAGE - Pause
            |--bit5: UAGE - Mute
            |--bit4: UAGE - Volume Decrement
            |--bit3: UAGE - Volume Increment
            |--bit2: UAGE - Scan Previous Track
            |--bit1: UAGE - Scan Next Track
            |--bit0: UAGE - Play
    */
    /*
        ��귢�͸�PC������ÿ��4���ֽ� ��
            ����ֱ��ǣ�
            BYTE1 --
                |--bit7:   1   ��ʾ   Y   ����ı仯��������256   ~   255�ķ�Χ,0��ʾû�����  ��
                |--bit6:   1   ��ʾ   X   ����ı仯��������256   ~   255�ķ�Χ��0��ʾû�������
                |--bit5:   Y   ����仯�ķ���λ��1��ʾ����������������ƶ�  ��
                |--bit4:   X   ����仯�ķ���λ��1��ʾ����������������ƶ�  ��
                |--bit3:     ��Ϊ1  ��
                |--bit2:     1��ʾ�м�����  ��
                |--bit1:     1��ʾ�Ҽ�����  ��
                |--bit0:     1��ʾ�������  ��
            BYTE2 -- X����仯������byte��bit4���9λ������,������ʾ�����ƣ����������ơ��ò����ʾ�仯����
            BYTE3 -- Y����仯������byte��bit5���9λ��������������ʾ�����ƣ����������ơ��ò����ʾ�仯�� ��
            BYTE4 -- ���ֱ仯��
        BYTE1��4-7ȫΪ0��ʱ��BYTE2 BYTE3��������ʾ����ƶ����� ��
    */

    /*
    ���̷��͸�PC������ÿ��8���ֽ�
                    BYTE0 BYTE1 BYTE2 BYTE3 BYTE4 BYTE5 BYTE6 BYTE7
                    ����ֱ��ǣ�
                    BYTE0 --
                                 |--bit0:   Left Control�Ƿ��£�����Ϊ1
                                 |--bit1:   Left Shift  �Ƿ��£�����Ϊ1
                                 |--bit2:   Left Alt    �Ƿ��£�����Ϊ1
                                 |--bit3:   Left GUI    �Ƿ��£�����Ϊ1
                                 |--bit4:   Right Control�Ƿ��£�����Ϊ1
                                 |--bit5:   Right Shift �Ƿ��£�����Ϊ1
                                 |--bit6:   Right Alt   �Ƿ��£�����Ϊ1
                                 |--bit7:   Right GUI   �Ƿ��£�����Ϊ1
                    BYTE1 -- �ݲ�������еĵط�˵�Ǳ���λ
                    BYTE2--BYTE7 -- ������Ϊ��ͨ����
                    ���̾������ԡ�
    */

#ifdef __cplusplus
extern "C"
{
#endif

#include "struct_typedef.h"
#define MAX_KEYPAD_PAGE 104
#define STACK_POINT_LENGTH 6

    typedef enum
    {
        MEDIA_PLAY = 0,
        MEDIA_NEXT_TRACK ,
        MEDIA_PREVIOUS_TRACK,
        MEDIA_VOLUME_INCREMENT,
        MEDIA_VOLUME_DECREMENT,
        MEDIA_MUTE,
        MEDIA_PAUSE,
        MEDIA_STOP,
    }keypad_media;
    /*���̰���ö��*/
    typedef enum
    {
        Key_board_Null = 0,
        Keyboard_a = 4,               // Keyboard a and A	YES
        Keyboard_b = 5,               // Keyboard b and B	YES
        Keyboard_c = 6,               // Keyboard c and C	YES
        Keyboard_d = 7,               // Keyboard d and D	YES
        Keyboard_e = 8,               // Keyboard e and E	YES
        Keyboard_f = 9,               // Keyboard f and F	YES
        Keyboard_g = 10,              // Keyboard g and G	YES
        Keyboard_h = 11,              // Keyboard h and H	YES
        Keyboard_i = 12,              // Keyboard i and I	YES
        Keyboard_j = 13,              // Keyboard j and J	YES
        Keyboard_k = 14,              // Keyboard k and K	YES
        Keyboard_l = 15,              // Keyboard l and L	YES
        Keyboard_m = 16,              // Keyboard m and M	YES
        Keyboard_n = 17,              // Keyboard n and N	YES
        Keyboard_o = 18,              // Keyboard o and O	YES
        Keyboard_p = 19,              // Keyboard p and P	YES
        Keyboard_q = 20,              // Keyboard q and Q	YES
        Keyboard_r = 21,              // Keyboard r and R	YES
        Keyboard_s = 22,              // Keyboard s and S	YES
        Keyboard_t = 23,              // Keyboard t and T	YES
        Keyboard_u = 24,              // Keyboard u and U	YES
        Keyboard_v = 25,              // Keyboard v and V	YES
        Keyboard_w = 26,              // Keyboard w and W	YES
        Keyboard_x = 27,              // Keyboard x and X	YES
        Keyboard_y = 28,              // Keyboard y and Y	YES
        Keyboard_z = 29,              // Keyboard z and Z	YES
        Keyboard_1 = 30,              // Keyboard 1 and !	YES
        Keyboard_2 = 31,              // Keyboard 2 and @	YES
        Keyboard_3 = 32,              // Keyboard 3 and #	YES
        Keyboard_4 = 33,              // Keyboard 4 and $	YES
        Keyboard_5 = 34,              // Keyboard 5 and %	YES
        Keyboard_6 = 35,              // Keyboard 6 and ^	YES
        Keyboard_7 = 36,              // Keyboard 7 and &	YES
        Keyboard_8 = 37,              // Keyboard 8 and *	YES
        Keyboard_9 = 38,              // Keyboard 9 and (	YES
        Keyboard_0 = 39,              // Keyboard 0 and )	YES
        Keyboard_ENTER = 40,          // Keyboard ENTER 	YES
        Keyboard_ESCAPE = 41,         // Keyboard ESCAPE	YES
        Keyboard_Backspace = 42,      // Keyboard Backspace	YES
        Keyboard_Tab = 43,            // Keyboard Tab	YES
        Keyboard_KongGe = 44,         // Keyboard Spacebar	YES
        Keyboard_JianHao = 45,        // Keyboard - and _(underscore)	YES
        Keyboard_DengHao = 46,        // Keyboard = and +	YES
        Keyboard_ZuoZhongKuoHao = 47, // Keyboard [ and {	YES
        Keyboard_YouZhongKuoHao = 48, // Keyboard ] and }	YES
        Keyboard_FanXieGang = 49,     // Keyboard \ and |	YES
        Keyboard_FenHao = 51,         // Keyboard ; and :	YES
        Keyboard_DanYinHao = 52,      // Keyboard �� and ��	YES
        Keyboard_BoLangXian = 53,     // Keyboard `(Grave Accent) and ~(Tilde)	YES
        Keyboard_Douhao = 54,         // Keyboard, and <	YES
        Keyboard_JuHao = 55,          // Keyboard . and >	YES
        Keyboard_XieGang_WenHao = 56, // Keyboard / and ?	YES
        Keyboard_CapsLock = 57,       // Keyboard Caps Lock	YES
        Keyboard_F1 = 58,             // Keyboard F1	YES
        Keyboard_F2 = 59,             // Keyboard F2	YES
        Keyboard_F3 = 60,             // Keyboard F3	YES
        Keyboard_F4 = 61,             // Keyboard F4	YES
        Keyboard_F5 = 62,             // Keyboard F5	YES
        Keyboard_F6 = 63,             // Keyboard F6	YES
        Keyboard_F7 = 64,             // Keyboard F7	YES
        Keyboard_F8 = 65,             // Keyboard F8	YES
        Keyboard_F9 = 66,             // Keyboard F9	YES
        Keyboard_F10 = 67,            // Keyboard F10	YES
        Keyboard_F11 = 68,            // Keyboard F11	YES
        Keyboard_F12 = 69,            // Keyboard F12	YES
        Keyboard_PrintScreen = 70,    // Keyboard PrintScreen	YES
        Keyboard_ScrollLock = 71,     // Keyboard Scroll Lock YES
        Keyboard_Pause = 72,          // Keyboard Pause		YES
        Keyboard_Insert = 73,         // Keyboard Insert	YES
        Keyboard_Home = 74,           // Keyboard Home		YES
        Keyboard_PageUp = 75,         // Keyboard PageUp	YES
        Keyboard_Delete = 76,         // Keyboard Delete	YES
        Keyboard_End = 77,            // Keyboard End
        Keyboard_PageDown = 78,       // Keyboard PageDown		YES
        Keyboard_RightArrow = 79,     // Keyboard RightArrow	YES
        Keyboard_LeftArrow = 80,      // Keyboard LeftArrow		YES
        Keyboard_DownArrow = 81,      // Keyboard DownArrow	YES
        Keyboard_UpArrow = 82,        // Keyboard UpArrow			YES
        Keypad_NumLock = 83,          // Keypad Num Lock and Clear
        Keypad_ChuHao = 84,           // Keypad /
        Keypad_ChengHao = 85,         // Keypad *
        Keypad_JianHao = 86,          // Keypad -
        Keypad_JiaHao = 87,           // Keypad +
        Keypad_ENTER = 88,            // Keypad ENTER
        Keypad_1_and_End = 89,        // Keypad 1 and End
        Keypad_2_and_DownArrow = 90,  // Keypad 2 and Down Arrow
        Keypad_3_and_PageDn = 91,     // Keypad 3 and PageDn
        Keypad_4_and_LeftArrow = 92,  // Keypad 4 and Left Arrow
        Keypad_5 = 93,                // Keypad 5
        Keypad_6_and_RightArrow = 94, // Keypad 6 and Right Arrow
        Keypad_7_and_Home = 95,       // Keypad 7 and Home
        Keypad_8_and_UpArrow = 96,    // Keypad 8 and Up Arrow
        Keypad_9_and_PageUp = 97,     // Keypad 9 and PageUp
        Keypad_0_and_Insert = 98,     // Keypad 0 and Insert
        Keypad_Dian_and_Delete = 99,  // Keypad . and Delete
        Keyboard_Application = 101,   // Keyboard Application
        Keyboard_Menu = 118,

        Keyboard_Mute = 127,        //����ʹ�ã�
        Keyboard_Volume_Up = 128,   //����ʹ�ã�
        Keyboard_Volume_Down = 129, //����ʹ�ã�

        Keyboard_LeftControl = 224,
        Keyboard_LeftShift = 225,
        Keyboard_LeftAlt = 226,
        Keyboard_LeftWindows = 227,
        Keyboard_RightControl = 228,
        Keyboard_RightShift = 229,
        Keyboard_RightAlt = 230,
        Keyboard_RightWindows = 231
    } keypad_page_t;
    typedef enum
    {
        Left_Control = 0,
        Left_Shift,
        Left_Alt,
        Left_GUI,
        Right_Control,
        Right_Shift,
        Right_Alt,
        Right_GUI,
    } Byte0_Offset;

    typedef enum
    {
        KEYBOARD_UPSPRING,     //��������
        KEYBOARD_PRESS,        //��������
        KEYBOARD_PRESS_L_TIME, //��������
    } keyboard_states;


    typedef struct
    {
        struct
        {
            uint8_t Left_Control : 1;
            uint8_t Left_Control_used_it : 1;
            uint8_t Left_Shift : 1;
            uint8_t Left_Shift_used_it : 1;
            uint8_t Left_Alt : 1;
            uint8_t Left_Alt_used_it : 1;
            uint8_t Left_GUI : 1;
            uint8_t Left_GUI_used_it : 1;
            uint8_t Right_Control : 1;
            uint8_t Right_Control_used_it : 1;
            uint8_t Right_Shift : 1;
            uint8_t Right_Shift_used_it : 1;
            uint8_t Right_Alt : 1;
            uint8_t Right_Alt_used_it : 1;
            uint8_t Right_GUI : 1;
            uint8_t Right_GUI_used_it : 1;
            keyboard_states Left_Control_Status;
            keyboard_states Left_Shift_Status;
            keyboard_states Left_Alt_Status;
            keyboard_states Left_GUI_Status;
            keyboard_states Right_Control_Status;
            keyboard_states Right_Shift_Status;
            keyboard_states Right_Alt_Status;
            keyboard_states Right_GUI_Status;
        } byte0_off;
        struct
        {
            uint8_t key_play : 1;
            uint8_t key_next_track : 1;
            uint8_t key_previous_track : 1;
            uint8_t key_volume_increment : 1;
            uint8_t key_volume_decrement : 1;
            uint8_t key_mute : 1;
            uint8_t key_pause : 1;
            uint8_t key_stop : 1;
            uint8_t media_msg;
        }media_off;
        //�����޳建����
        uint8_t stack_pointer;
        keypad_page_t keypad[6];
        keyboard_states keypad_status[6];
        uint8_t used_it[6];
    } keyboard_cfg;

#ifdef __cplusplus
}
#endif

#endif
