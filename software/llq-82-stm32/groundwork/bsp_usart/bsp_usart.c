/*
 * @author                          : Seasky.Liu
 * @Date                            : 2021-11-22 14:56:38
 * @LastEditTime: 2022-02-04 18:16:07
 * @LastEditors: Please set LastEditors
 * @Description                     : https://github.com/SEASKY-Master
 * @FilePath                        : \keyboard_v7\groundwork\bsp_usart\bsp_usart.c
 * @symbol_custom_string_obkoro1    : 
 * ��Ȩ����:@Seasky.liu
 * ��ϵ��ʽ:liuwei_seasky@163.com
 * ��ԴЭ��:����ӿ�ԴЭ�飨��Ŀ�ֿ�����˵������δ�����������Ͻ�������ҵ��;
 * ************************************************************************
 *            If you want a thing done well, do it yourself.
 * ************************************************************************
 */
#include "bsp_usart.h"
#include "bsp_bm2166.h"

uint8_t 	usart3_rx_buf[2][USART_RX_LEN];
uint16_t 	usart3_rx_pos;
uint8_t 	usart1_rx_buf[2][USART_RX_LEN];
uint16_t 	usart1_rx_pos;
extern  UART_HandleTypeDef huart1;
extern  UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;


void bsp_usart1_init(void)
{
   //ʹ��DMA���ڽ���
   SET_BIT(huart1.Instance->CR3, USART_CR3_DMAR);
   __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);     //�����ж�ʹ��
//	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE); 	//�����ж�ʹ��
   __HAL_UART_CLEAR_IDLEFLAG(&huart1);       		//������ڿ����жϱ�־λ
   //ʧЧDMA
   __HAL_DMA_DISABLE(&hdma_usart1_rx);

   while(hdma_usart1_rx.Instance->CR & DMA_SxCR_EN)
       {
           __HAL_DMA_DISABLE(&hdma_usart1_rx);
       }
   hdma_usart1_rx.Instance->PAR = (uint32_t) & (USART1->DR);
   //�ڴ滺����1
   hdma_usart1_rx.Instance->M0AR = (uint32_t)(usart1_rx_buf[0]);
   //�ڴ滺����2
   hdma_usart1_rx.Instance->M1AR = (uint32_t)(usart1_rx_buf[1]);
   //���ݳ���
   hdma_usart1_rx.Instance->NDTR = USART_RX_LEN;
   //ʹ��˫������
   SET_BIT(hdma_usart1_rx.Instance->CR,DMA_SxCR_DBM);
   //ʹ��DMA
   __HAL_DMA_ENABLE(&hdma_usart1_rx);
}

void bsp_usart3_init(void)
{
    //ʹ��DMA���ڽ���
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);
    __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);     //�����ж�ʹ��
//	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE); 	//�����ж�ʹ��
    __HAL_UART_CLEAR_IDLEFLAG(&huart3);       		//������ڿ����жϱ�־λ
    //ʧЧDMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);

    while(hdma_usart3_rx.Instance->CR & DMA_SxCR_EN)
        {
            __HAL_DMA_DISABLE(&hdma_usart3_rx);
        }
    hdma_usart3_rx.Instance->PAR = (uint32_t) & (USART3->DR);
    //�ڴ滺����1
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(usart3_rx_buf[0]);
    //�ڴ滺����2
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(usart3_rx_buf[1]);
    //���ݳ���
    hdma_usart3_rx.Instance->NDTR = USART_RX_LEN;
    //ʹ��˫������
    SET_BIT(hdma_usart3_rx.Instance->CR,DMA_SxCR_DBM);
    //ʹ��DMA
    __HAL_DMA_ENABLE(&hdma_usart3_rx);
}
void USER_UART_DMA_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint16_t rx_flag;
    static uint16_t this_time_rx_len = 0;
    if(huart->Instance == huart3.Instance)
        {
            //�ж��Ƿ��ǿ����ж�
            if(huart3.Instance->SR & UART_FLAG_RXNE)//���յ�����
                {
                    __HAL_UART_CLEAR_PEFLAG(&huart3);
                }
            else if(RESET != __HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE))
                {
                    __HAL_UART_CLEAR_IDLEFLAG(&huart3);//��������жϱ�־�������һֱ���Ͻ����жϣ�
                    if ((hdma_usart3_rx.Instance->CR & DMA_SxCR_CT) == RESET)
                        {
                            //ʧЧDMA
                            __HAL_DMA_DISABLE(&hdma_usart3_rx);
                            //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
                            this_time_rx_len = USART_RX_LEN - hdma_usart3_rx.Instance->NDTR;
                            //�����趨���ݳ���
                            hdma_usart3_rx.Instance->NDTR = USART_RX_LEN;
                            //�趨������1
                            hdma_usart3_rx.Instance->CR |= (uint32_t)(DMA_SxCR_CT);
                            //ʹ��DMA
                            __HAL_DMA_ENABLE(&hdma_usart3_rx);
                            /*���㻺����0*/
                            bsp_bm2166_receive(usart3_rx_buf[0],this_time_rx_len);
                        }
                    else
                        {
                            //ʧЧDMA
                            __HAL_DMA_DISABLE(&hdma_usart3_rx);
                            //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
                            this_time_rx_len = USART_RX_LEN - hdma_usart3_rx.Instance->NDTR;
                            //�����趨���ݳ���
                            hdma_usart3_rx.Instance->NDTR = USART_RX_LEN;
                            //�趨������0
                            hdma_usart3_rx.Instance->CR &= ~(uint32_t)(DMA_SxCR_CT);
                            //ʹ��DMA
                            __HAL_DMA_ENABLE(&hdma_usart3_rx);
                            /*���㻺����1*/
                            bsp_bm2166_receive(usart3_rx_buf[1],this_time_rx_len);
                        }
                }
        }
		else if(huart->Instance == huart1.Instance)
		{
		            //�ж��Ƿ��ǿ����ж�
           if(huart1.Instance->SR & UART_FLAG_RXNE)//���յ�����
               {
                   __HAL_UART_CLEAR_PEFLAG(&huart1);
               }
           else if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))
               {
                   __HAL_UART_CLEAR_IDLEFLAG(&huart1);//��������жϱ�־�������һֱ���Ͻ����жϣ�
                   if ((hdma_usart3_rx.Instance->CR & DMA_SxCR_CT) == RESET)
                       {
                           //ʧЧDMA
                           __HAL_DMA_DISABLE(&hdma_usart1_rx);
                           //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
                           this_time_rx_len = USART_RX_LEN - hdma_usart1_rx.Instance->NDTR;
                           //�����趨���ݳ���
                           hdma_usart1_rx.Instance->NDTR = USART_RX_LEN;
                           //�趨������1
                           hdma_usart1_rx.Instance->CR |= (uint32_t)(DMA_SxCR_CT);
                           
                           //ʹ��DMA
                           __HAL_DMA_ENABLE(&hdma_usart1_rx);
                           /*���㻺����0*/
                           ble_rx_buff_updata(usart1_rx_buf[0],this_time_rx_len);
                           
                       }
                   else
                       {
                           //ʧЧDMA
                           __HAL_DMA_DISABLE(&hdma_usart1_rx);
                           //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
                           this_time_rx_len = USART_RX_LEN - hdma_usart1_rx.Instance->NDTR;
                           //�����趨���ݳ���
                           hdma_usart1_rx.Instance->NDTR = USART_RX_LEN;
                           //�趨������0
                           hdma_usart1_rx.Instance->CR &= ~(uint32_t)(DMA_SxCR_CT);
                           
                           //ʹ��DMA
                           __HAL_DMA_ENABLE(&hdma_usart1_rx);
                           /*���㻺����1*/
                           ble_rx_buff_updata(usart1_rx_buf[1],this_time_rx_len);
                       }
               }
		}
}