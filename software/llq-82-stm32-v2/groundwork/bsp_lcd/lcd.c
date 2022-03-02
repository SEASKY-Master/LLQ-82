/*
 * @FilePath                        : \keyboard_v6\groundwork\bsp_lcd\lcd.c
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-24 09:25
 * @LastEditors                     : your name
 * @Description                     : https://github.com/SEASKY-Master
 * @symbol_custom_string_obkoro1    : 
 * ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */
#include "lcd.h"
#include "lcd_init.h"
#include "stm32f4xx_hal.h"
#include "spi.h"

/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{
    u16 i,j;
    LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ
    for(i=ysta; i<yend; i++)
        {
            for(j=xsta; j<xend; j++)
                {
                    LCD_WR_DATA(color);
                }
        }
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/

void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
    LCD_Address_Set(x,y,x,y);//���ù��λ��
    LCD_WR_DATA(color);
}


void LCD_DrawPoint_DMA(u16 x,u16 y,u16 color)
{
    LCD_WR_REG(0x2a);//�е�ַ����
    LCD_WR_DATA(x+40);
    LCD_WR_DATA(x+40);
    LCD_WR_REG(0x2b);//�е�ַ����
    LCD_WR_DATA(y+53);
    LCD_WR_DATA(y+53);
    LCD_WR_REG(0x2c);//������д
    LCD_WR_DATA(color);
}

void LCD_Fill_DMA(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,const uint8_t *pic)
{
    uint16_t length;
    uint16_t width;
    length = x2 - x1 + 1 ;
    width  = y2 - y1 + 1;
	//��DMA SPI����ˢ������
	LCD_Address_Set(x1,y1,x2,y2);
	//DMA SPI��ʽˢ��
	HAL_SPI_Transmit_DMA(&hspi1,&pic[0],length*width*2);
	while(hspi1.State == HAL_SPI_STATE_BUSY_TX);
}

///******************************************************************************
//      ����˵������ʾͼƬ
//      ������ݣ�x,y�������
//                length ͼƬ����
//                width  ͼƬ���
//                pic[]  ͼƬ����
//      ����ֵ��  ��
//******************************************************************************/
void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[])
{
    u16 i,j;
    u32 k=0;
    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=0; i<length; i++)
        {
            for(j=0; j<width; j++)
                {
                    LCD_WR_DATA8(pic[k*2]);
                    LCD_WR_DATA8(pic[k*2+1]);
                    k++;
                }
        }
}


