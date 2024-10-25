/**
 ****************************************************************************************************
 * @file        gt9xxx.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-25
 * @brief       4.3����ݴ�����-GT9xxx ��������
 *   @note      GTϵ�е��ݴ�����ICͨ������,������֧��: GT9147/GT917S/GT968/GT1151/GT9271 �ȶ���
 *              ����IC, ��Щ����IC��ID��һ��, ��������������Ҫ���κ��޸ļ���ͨ��������ֱ������
 *
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200425
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __GT9XXX_H
#define __GT9XXX_H

#include "stm32h7xx.h"


typedef struct touch_coordinates{

uint8_t touch_switch;
uint16_t touch_x;
uint16_t	touch_y;
}Touch_coordinates,*pTouch_coordinates;


/******************************************************************************************/
/* GT9XXX INT �� RST ���� ���� */

#define GT9XXX_RST_GPIO_PORT            GPIOD
#define GT9XXX_RST_GPIO_PIN             GPIO_PIN_3
#define GT9XXX_RST_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PD3��ʱ��ʹ�� */

#define GT9XXX_INT_GPIO_PORT            GPIOG
#define GT9XXX_INT_GPIO_PIN             GPIO_PIN_12
#define GT9XXX_INT_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOG_CLK_ENABLE(); }while(0)   /* PG12��ʱ��ʹ�� */

/******************************************************************************************/

/* ����ݴ��������ӵ�оƬ����(δ����IIC����) 
 * IO�������� 
 */
#define GT9XXX_RST(x)     do{ x ? \
                              HAL_GPIO_WritePin(GT9XXX_RST_GPIO_PORT, GT9XXX_RST_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(GT9XXX_RST_GPIO_PORT, GT9XXX_RST_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)       /* ��λ���� */

#define GT9XXX_INT        HAL_GPIO_ReadPin(GT9XXX_INT_GPIO_PORT, GT9XXX_INT_GPIO_PIN)     /* ��ȡ�������� */

/* IIC��д���� */
#define GT9XXX_CMD_WR       0X28        /* д���� */
#define GT9XXX_CMD_RD       0X29        /* ������ */
													
													
													
////GT1151 ���ּĴ������� 
//#define GT_CTRL_REG 	0X8040   	//GT1151���ƼĴ���
//#define GT_CFGS_REG 	0X8050   	//GT1151������ʼ��ַ�Ĵ���
//#define GT_CHECK_REG 	0X813C   	//GT1151У��ͼĴ���
//#define GT_PID_REG 		0X8140   	//GT1151��ƷID�Ĵ���
//#define GT_FW_REG 		0X8145   	//GT1151 IC FW�Ĵ���
													
													
													

/* GT9XXX ���ּĴ�������  */
#define GT9XXX_CTRL_REG     0X8040      /* GT9XXX���ƼĴ��� */

//#define GT9XXX_CFGS_REG     0X8047      /* GT9XXX������ʼ��ַ�Ĵ��� */
#define GT9XXX_CFGS_REG     0X8050      /* GT9XXX������ʼ��ַ�Ĵ��� */	

//#define GT9XXX_CHECK_REG    0X80FF      /* GT9XXXУ��ͼĴ��� */
#define GT9XXX_CHECK_REG    0X813C      /* GT9XXXУ��ͼĴ��� */

#define GT9XXX_PID_REG      0X8140      /* GT9XXX��ƷID�Ĵ��� */



#define GT9XXX_GSTID_REG    0X814E      /* GT9XXX��ǰ��⵽�Ĵ������ */
#define GT9XXX_TP1_REG      0X8150      /* ��һ�����������ݵ�ַ */
#define GT9XXX_TP2_REG      0X8158      /* �ڶ������������ݵ�ַ */
#define GT9XXX_TP3_REG      0X8160      /* ���������������ݵ�ַ */
#define GT9XXX_TP4_REG      0X8168      /* ���ĸ����������ݵ�ַ */
#define GT9XXX_TP5_REG      0X8170      /* ��������������ݵ�ַ */
#define GT9XXX_TP6_REG      0X8178      /* ���������������ݵ�ַ */
#define GT9XXX_TP7_REG      0X8180      /* ���߸����������ݵ�ַ */
#define GT9XXX_TP8_REG      0X8188      /* �ڰ˸����������ݵ�ַ */
#define GT9XXX_TP9_REG      0X8190      /* �ھŸ����������ݵ�ַ */
#define GT9XXX_TP10_REG     0X8198      /* ��ʮ�����������ݵ�ַ */
 

uint8_t gt9xxx_wr_reg(uint16_t reg,uint8_t *buf,uint8_t len);
void gt9xxx_rd_reg(uint16_t reg,uint8_t *buf,uint8_t len); 
uint8_t gt9xxx_init(void);
uint8_t gt9xxx_scan(uint8_t mode); 
#endif













