/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "../samples/thread_sample.h"
#include "../../packages/SystemView-latest/SystemView_Src/SEGGER/SEGGER_SYSVIEW.h"
/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(C, 13)
#define serial_num(n)   "serial_num##n"

/*
 * 程序清单：这是一个串口设备 DMA 接收使用例程
 * 例程导出了 uart_dma_sample 命令到控制终端
 * 命令调用格式：uart_dma_sample uart3
 * 命令解释：命令第二个参数是要使用的串口设备名称，为空则使用默认的串口设备
 * 程序功能：通过串口输出字符串"hello RT-Thread!"，并通过串口输出接收到的数据，然后打印接收到的数据。
*/

#include <rtthread.h>

#define SAMPLE_UART_NAME       "uart1"      /* 串口设备名称 */

/* 串口接收消息结构*/
struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};
/* 串口设备句柄 */
static rt_device_t serial;
/* 消息队列控制块 */
static struct rt_messagequeue rx_mq;

/* 接收数据回调函数 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;

    result = rt_mq_send(&rx_mq, &msg, sizeof(msg));
    if ( result == -RT_EFULL)
    {
        /* 消息队列满 */
        rt_kprintf("message queue full！\n");
    }
    return result;
}

static void serial_thread_entry(void *parameter)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_length = 0;
    static char rx_buffer[RT_SERIAL_RB_BUFSZ + 1];
    char input;
    
    while(1)
    {
        result = rt_mq_recv(&rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if(result < 0)
        {
            rt_kprintf("mq recv err\n");
        }

        rt_device_read(msg.dev, 0, &input, 1);
        rx_buffer[rx_length++] = input;
        rt_kprintf("input: %c\n",input);

        /* 以回车为缓冲区输出标志 */
        if(input == '\r')
        {
            /* 通过串口设备 serial 输出读取到的消息 */
            rt_size_t size = rt_device_write(msg.dev, 0, rx_buffer, sizeof(rx_buffer));
            if(size != sizeof(rx_buffer))
            {
                rt_kprintf("write err\n");
            }
            /* 打印数据 */
            rt_kprintf("rx_buffer: %s\n", rx_buffer);
            /* 重置初始量 */
            rx_length = 0;
            rt_memset((void*)rx_buffer, 0, sizeof(rx_buffer));
        }  
    }
}

// void serial_recv(void* para)
// {
//     char input;
//     char rx_buffer[32] = {0};
//     int rx_length = 0;
//     while(1)
//     {
//         rt_sem_take(&serial_sem, RT_WAITING_FOREVER);
//         rt_device_read(msg1.dev, 0, &input, 1);
//         rx_buffer[rx_length++] = input;
//         rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
//         if(input == '\r')
//         {
//             rt_size_t size = rt_device_write(msg1.dev, 0, rx_buffer, sizeof(rx_buffer));
//             rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
//             if(size != sizeof(rx_buffer))
//             {
//                 rt_kprintf("write err\n");
//             }
            
//             rt_kprintf("rx_buffer: %s\n", rx_buffer);
//             rx_length = 0;
//             rt_memset((void*)rx_buffer, 0, sizeof(rx_buffer));
//         }  
//     }
// }

static int uart_dma_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    static char msg_pool[256];
    char str[] = "hello RT-Thread!\r\n";

    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }

    /* 查找串口设备 */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }

    /* 初始化消息队列 */
    rt_mq_init(&rx_mq, "rx_mq",
               msg_pool,                 /* 存放消息的缓冲区 */
               sizeof(struct rx_msg),    /* 一条消息的最大长度 */
               sizeof(msg_pool),         /* 存放消息的缓冲区大小 */
               RT_IPC_FLAG_FIFO);        /* 如果有多个线程等待，按照先来先得到的方法分配消息 */

    /* 以 DMA 接收及轮询发送方式打开串口设备 */
    rt_device_open(serial, RT_DEVICE_FLAG_DMA_RX);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(serial, uart_input);
    /* 发送字符串 */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart_dma_sample, uart device dma sample);

// struct msg{
//     rt_device_t dev;
//     rt_size_t size;
// };
// rt_device_t u1;
// struct rt_semaphore serial_sem;
// struct msg msg1;
// rt_err_t serial_rx_ind(rt_device_t dev, rt_size_t size)
// {
//     //bind设备
//     rt_kprintf("receive thread initing...\n");
    
//     msg1.dev = dev;
//     msg1.size = size;
//     rt_kprintf("%s,%d\n",__FUNCTION__, __LINE__);
//     rt_sem_release(&serial_sem);
//     return RT_EOK;
// }

// void serial_recv(void* para)
// {
//     char input;
//     char rx_buffer[32] = {0};
//     int rx_length = 0;
//     while(1)
//     {
//         rt_sem_take(&serial_sem, RT_WAITING_FOREVER);
//         rt_device_read(msg1.dev, 0, &input, 1);
//         rx_buffer[rx_length++] = input;
//         rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
//         if(input == '\r')
//         {
//             rt_size_t size = rt_device_write(msg1.dev, 0, rx_buffer, sizeof(rx_buffer));
//             rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
//             if(size != sizeof(rx_buffer))
//             {
//                 rt_kprintf("write err\n");
//             }
            
//             rt_kprintf("rx_buffer: %s\n", rx_buffer);
//             rx_length = 0;
//             rt_memset((void*)rx_buffer, 0, sizeof(rx_buffer));
//         }  
//     }
// }

// int serial_sample(void)
// {
//     rt_err_t errnum;
//     rt_sem_init(&serial_sem, "serial_order", 0, RT_IPC_FLAG_FIFO);
//     char str1[] = {"hello world\n"};
    
//     u1 = rt_device_find("uart1");
//     if(!u1)
//     {
//         rt_kprintf("don't find serial device\n");
//         return ERROR;
//     }
//     errnum = rt_device_open(u1, RT_DEVICE_FLAG_DMA_RX);
//     if(errnum != RT_EOK)
//     {
//         rt_kprintf("open errnum = %d\n",errnum);
//     }

//     errnum = rt_device_set_rx_indicate(u1, serial_rx_ind);
//     if(errnum != RT_EOK)
//     {
//         rt_kprintf("set_rx_indicate errnum = %d\n",errnum);
//     }
    
//     rt_size_t size = rt_device_write(u1, 0, str1, sizeof(str1)-1);
//     if(size == 0)
//     {
//         rt_kprintf("write err\n");
//     }

    
//     rt_thread_t serial_recv_thread = rt_thread_create("serial_recv", serial_recv, NULL, 1024, 10, 10);
//     if (serial_recv_thread != RT_NULL)
//     {
//         rt_thread_startup(serial_recv_thread);
//     }
//     else
//     {
//         return RT_ERROR;
//     }
    
    

//     return 0;
// }

// MSH_CMD_EXPORT(serial_sample, uart device sample);


int main(void)
{
	//SEGGER_SYSVIEW_Start();
    /* set LED0 pin mode to output */
    //rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    //demo_init();
    // rt_kprintf("hello world\n");
    // while (1)
    // {
    //     rt_thread_mdelay(1000);
    // }

    rt_thread_delay(10);
}
