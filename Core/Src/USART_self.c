//
// Created by 86188 on 2026/9/28.
//
#include "main.h"
#include "USART_self.h"
#include "string.h"

static USART_T *g_instance[4];   //开启的串口数量
static uint8_t g_cnt=0;          //计算有几个结构体

//对指定USART进行初始化
void USART_Init(USART_T *u,UART_HandleTypeDef *huart) {
    //清空指定结构体
    memset(u,0,sizeof(*u));
    //包装结构体
    u->huart=huart;

    if (g_cnt<4) {
        g_instance[g_cnt]=u;
        g_cnt++;
    }

    //HAL_UART_Receive_IT(huart,&u->rx_tmp,1);  //接收中断函数

    //启动DMA接收
    HAL_UART_Receive_DMA(huart,u->rx_DMA_buf,USART_DMA_BUF_SIZE);
    //启动IDLE中断
    
}

//把数据拷贝进缓冲区
bool USART_Send(USART_T *u,const uint8_t *data,uint16_t len) {

    //判断数据长度
    if (len==0||len>USART_TX_BUF_SIZE) {
        return false;
    }

    //把数据正式拷贝进缓冲区
    memcpy(u->tx_buf,data,len);

    //发送
    HAL_UART_Transmit(u->huart,u->tx_buf,len,HAL_MAX_DELAY);

    //
    //判断是否发送成功（后期要进行修改）  有点懒就先不判断了  默认发送成功
    //有没有猫娘学长 OvO
    return true;
}

//中断接收处理
void USART_RxCpltHandler(UART_HandleTypeDef *huart) {
    for (int i=0;i<g_cnt;i++) {
        if (g_instance[i]->huart==huart) {
            USART_T *u=g_instance[i];

                uint16_t next_head=(u->rx_head+1)%USART_RX_BUF_SIZE;

                if (next_head!=u->rx_tail) {
                    u->rx_buf[u->rx_head]=u->rx_tmp;
                    u->rx_head=next_head;
                }else {
                    u->rx_overflow++;
                }

                HAL_UART_Receive_IT(huart,&u->rx_tmp,1);
                return;
        }
    }
}



//接收数据
int USART_ReadByte(USART_T *u) {

    if (u->rx_head==u->rx_tail) {
        return -1;
    }

    uint8_t b=u->rx_buf[u->rx_tail];
    u->rx_tail=(u->rx_tail+1)%USART_RX_BUF_SIZE;

    return b;
}


//发送float类型的方法
//
//发送的函数
void SendVOFA(USART_T *u,const float *data,uint8_t cnt) {

    uint8_t frame[10*4+4];
    uint8_t len=cnt*4;

    memcpy(frame,data,len);

    frame[len+0]=0x00;
    frame[len+1]=0x00;
    frame[len+2]=0x80;
    frame[len+3]=0x7f;

    USART_Send(u,frame,len+4);
}
//main里这么写
/*
    float data[x];                      x自定义

    data[0]=        ;
    .......

    SendVOFA(&uart ,data, x );

*/


//DMA的重任交给明天的自己了




