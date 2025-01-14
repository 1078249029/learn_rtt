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
#include "D:/Programes/RT-Thread/rtt/rt-thread/bsp/stm32/stm32f103-blue-pill/packages/SystemView-latest/SystemView_Src/SEGGER/SEGGER_SYSVIEW.h"
/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(C, 13)
#define serial_num(n)   "serial_num##n"

/*
* �����嵥��systemview ��ʾ����
*
* ��������н�����һ����̬�ź���(��ʼֵΪ0)��������̬�̣߳������������̬�߳���
* �߳�2����ͼ������Զ�ȴ���ʽȥ�����ź��������гɹ�֮�������б�־��
* �߳�1���ȷ����������б�־��Ȼ���ͷ�һ���ź��������߳�2�����ȼ��ϸߣ��߳�2���е��ź������߳�1���ϡ�
* Ȼ���߳�2�������б�־֮�󣬻�ȡ�����ź������������߳�1��������
*/

// #define THREAD_PRIORITY         25
// #define THREAD_STACK_SIZE       512
// #define THREAD_TIMESLICE        5
// /* ָ���ź�����ָ�� */
// rt_sem_t sem_food;
// /* �߳�1��� */
// void thread1_entry(void* parameter)
// {
//     while (1)
//     {
//         /* �߳�1��һ������ */
//         rt_kprintf("thread1 is run!\n");
//         /* �ͷ�һ���ź��� */
//         rt_sem_release(sem_food);
//         /* �߳�1�ڶ������� */
//         rt_kprintf("thread1 run again!\n");
//         /* �߳�1��ʱ1�� */
//         rt_thread_delay(RT_TICK_PER_SECOND);
//     }
// }
// /* �߳�2��� */
// void thread2_entry(void* parameter)
// {
//     while (1)
//     {
//         /* ��ͼ�����ź���������Զ�ȴ�ֱ�����е��ź��� */
//         rt_sem_take(sem_food, RT_WAITING_FOREVER);
//         /* �߳�2�������� */
//         rt_kprintf("thread2 is run!\n");
//     }
// }
// /* DEMO��ʼ������ */
// void demo_init(void)
// {
//     /* ָ���߳̿��ƿ��ָ�� */
//     rt_thread_t thread1_id, thread2_id;
//     /* ����һ���ź�������ʼֵ��0 */
//     sem_food = rt_sem_create("sem_food", 0, RT_IPC_FLAG_PRIO);
//     if (sem_food == RT_NULL)
//     {
//         rt_kprintf("sem created fail!\n");
//         return ;
//     }
//     /* �����߳�1 */
//     thread1_id = rt_thread_create("thread1",
//                     thread1_entry, RT_NULL,/* �߳������thread1_entry, ����RT_NULL */
//                     THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
//     if (thread1_id != RT_NULL)
//         rt_thread_startup(thread1_id);
//     /* �����߳�2 */
//     thread2_id = rt_thread_create("thread2",
//                     thread2_entry, RT_NULL,/* �߳������thread2_entry, ����RT_NULL */
//                     THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
//     if (thread2_id != RT_NULL)
//         rt_thread_startup(thread2_id);
// }

// #include <rtthread.h>

// #define THREAD_PRIORITY      9
// #define THREAD_TIMESLICE     5

// #define EVENT_FLAG3 (1 << 3)
// #define EVENT_FLAG5 (1 << 5)

// /* 事件控制块 */
// static struct rt_event event;

// ALIGN(RT_ALIGN_SIZE)
// static char thread1_stack[1024];
// static struct rt_thread thread1;

// /* 线程 1 入口函数 */
// static void thread1_recv_event(void *param)
// {
//     rt_uint32_t e;

//     /* 第一次接收事件，事件 3 或事件 5 任意一个可以触发线程 1，接收完后清除事件标志 */
//     if (rt_event_recv(&event, (EVENT_FLAG3 | EVENT_FLAG5),
//                       RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
//                       RT_WAITING_FOREVER, &e) == RT_EOK)
//     {
//         rt_kprintf("thread1: OR recv event 0x%x\n", e);
//     }

//     rt_kprintf("thread1: delay 1s to prepare the second event\n");
//     rt_thread_mdelay(1000);

//     /* 第二次接收事件，事件 3 和事件 5 均发生时才可以触发线程 1，接收完后清除事件标志 */
//     if (rt_event_recv(&event, (EVENT_FLAG3 | EVENT_FLAG5),
//                       RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
//                       RT_WAITING_FOREVER, &e) == RT_EOK)
//     {
//         rt_kprintf("thread1: AND recv event 0x%x\n", e);
//     }
//     rt_kprintf("thread1 leave.\n");
// }


// ALIGN(RT_ALIGN_SIZE)
// static char thread2_stack[1024];
// static struct rt_thread thread2;

// /* 线程 2 入口 */
// static void thread2_send_event(void *param)
// {
//     rt_kprintf("thread2: send event3\n");
//     rt_event_send(&event, EVENT_FLAG3);
//     rt_thread_mdelay(200);

//     rt_kprintf("thread2: send event5\n");
//     rt_event_send(&event, EVENT_FLAG5);
//     rt_thread_mdelay(200);

//     rt_kprintf("thread2: send event3\n");
//     rt_event_send(&event, EVENT_FLAG3);
//     rt_kprintf("thread2 leave.\n");
// }

// int event_sample(void)
// {
//     rt_err_t result;

//     /* 初始化事件对象 */
//     result = rt_event_init(&event, "event", RT_IPC_FLAG_PRIO);
//     if (result != RT_EOK)
//     {
//         rt_kprintf("init event failed.\n");
//         return -1;
//     }

//     rt_thread_init(&thread1,
//                    "thread1",
//                    thread1_recv_event,
//                    RT_NULL,
//                    &thread1_stack[0],
//                    sizeof(thread1_stack),
//                    THREAD_PRIORITY - 1, THREAD_TIMESLICE);
//     rt_thread_startup(&thread1);

//     rt_thread_init(&thread2,
//                    "thread2",
//                    thread2_send_event,
//                    RT_NULL,
//                    &thread2_stack[0],
//                    sizeof(thread2_stack),
//                    THREAD_PRIORITY, THREAD_TIMESLICE);
//     rt_thread_startup(&thread2);

//     return 0;
// }

// /* 导出到 msh 命令列表中 */
// MSH_CMD_EXPORT(event_sample, event sample);

//------------------------------------------------------------------------------------------------------

struct msg{
    rt_device_t dev;
    rt_size_t size;
};
rt_device_t u1;
struct rt_semaphore serial_sem;
struct msg msg1;
rt_err_t serial_rx_ind(rt_device_t dev, rt_size_t size)
{
    //bind设备
    rt_kprintf("receive thread initing...\n");
    
    msg1.dev = dev;
    msg1.size = size;
    rt_kprintf("%s,%d\n",__FUNCTION__, __LINE__);
    rt_sem_release(&serial_sem);
    return RT_EOK;
}

void serial_recv(void* para)
{
    char input;
    char input_buffer[32] = {0};
    int count = 0;
    while(1)
    {
        rt_sem_take(&serial_sem, RT_WAITING_FOREVER);
        rt_device_read(msg1.dev, 0, &input, 1);
        input_buffer[count++] = input;
        rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
        if(input == '\r')
        {
            rt_size_t size = rt_device_write(msg1.dev, 0, input_buffer, sizeof(input_buffer));
            rt_kprintf("%s,%d,%c\n",__FUNCTION__, __LINE__,input);
            if(size != sizeof(input_buffer))
            {
                rt_kprintf("write err\n");
            }
            
            rt_kprintf("input_buffer: %s\n", input_buffer);
            count = 0;
            rt_memset((void*)input_buffer, 0, sizeof(input_buffer));
        }  
    }
}

int serial_sample(void)
{
    rt_err_t errnum;
    rt_sem_init(&serial_sem, "serial_order", 0, RT_IPC_FLAG_FIFO);
    char str1[] = {"hello world\n"};
    
    u1 = rt_device_find("uart1");
    if(!u1)
    {
        rt_kprintf("don't find serial device\n");
        return ERROR;
    }
    errnum = rt_device_open(u1, RT_DEVICE_FLAG_DMA_RX);
    if(errnum != RT_EOK)
    {
        rt_kprintf("open errnum = %d\n",errnum);
    }

    errnum = rt_device_set_rx_indicate(u1, serial_rx_ind);
    if(errnum != RT_EOK)
    {
        rt_kprintf("set_rx_indicate errnum = %d\n",errnum);
    }
    
    rt_size_t size = rt_device_write(u1, 0, str1, sizeof(str1)-1);
    if(size == 0)
    {
        rt_kprintf("write err\n");
    }

    
    rt_thread_t serial_recv_thread = rt_thread_create("serial_recv", serial_recv, NULL, 1024, 10, 10);
    if (serial_recv_thread != RT_NULL)
    {
        rt_thread_startup(serial_recv_thread);
    }
    else
    {
        return RT_ERROR;
    }
    
    

    return 0;
}

MSH_CMD_EXPORT(serial_sample, uart device sample);


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
