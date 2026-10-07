//
// Created by 86188 on 2026/9/28.
//

#ifndef MOTOR_USART_SELF_H
#define MOTOR_USART_SELF_H

#include "main.h"
#include "stdbool.h"

#define USART_TX_BUF_SIZE 128
#define USART_RX_BUF_SIZE 128
#define USART_DMA_BUF_SIZE 128

typedef  struct {
    UART_HandleTypeDef *huart;
    //发送
    uint8_t tx_buf[USART_TX_BUF_SIZE];  //发送缓冲区

    //接收
    uint8_t rx_buf[USART_RX_BUF_SIZE];  //读取缓冲区
    volatile uint16_t rx_head;          //写
    volatile uint16_t rx_tail;          //读
    uint8_t rx_tmp;                     //单字节寄存处
    volatile uint32_t rx_overflow;      //记录溢出

    //接收缓冲区
    uint8_t rx_DMA_buf[USART_DMA_BUF_SIZE];
}USART_T;


void USART_Init(USART_T *u,UART_HandleTypeDef *huart);
bool USART_Send(USART_T *u,const uint8_t *data,uint16_t len);

int USART_ReadByte(USART_T *u);                            //读
void USART_RxCpltHandler(UART_HandleTypeDef *huart);       //中断分发处理 把中断产生的数据搬到对应结构体（多接口时方便使用）

void SendVOFA(USART_T *u,const float *data,uint8_t cnt);

void USART_IdleHandler(USART_TypeDef *huart);


#endif //MOTOR_USART_SELF_H
