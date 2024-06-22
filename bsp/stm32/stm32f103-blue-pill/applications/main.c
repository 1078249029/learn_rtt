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
/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(C, 13)

/*
* �����嵥��systemview ��ʾ����
*
* ��������н�����һ����̬�ź���(��ʼֵΪ0)��������̬�̣߳������������̬�߳���
* �߳�2����ͼ������Զ�ȴ���ʽȥ�����ź��������гɹ�֮�������б�־��
* �߳�1���ȷ����������б�־��Ȼ���ͷ�һ���ź��������߳�2�����ȼ��ϸߣ��߳�2���е��ź������߳�1���ϡ�
* Ȼ���߳�2�������б�־֮�󣬻�ȡ�����ź������������߳�1��������
*/

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5
/* ָ���ź�����ָ�� */
rt_sem_t sem_food;
/* �߳�1��� */
void thread1_entry(void* parameter)
{
    while (1)
    {
        /* �߳�1��һ������ */
        rt_kprintf("thread1 is run!\n");
        /* �ͷ�һ���ź��� */
        rt_sem_release(sem_food);
        /* �߳�1�ڶ������� */
        rt_kprintf("thread1 run again!\n");
        /* �߳�1��ʱ1�� */
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}
/* �߳�2��� */
void thread2_entry(void* parameter)
{
    while (1)
    {
        /* ��ͼ�����ź���������Զ�ȴ�ֱ�����е��ź��� */
        rt_sem_take(sem_food, RT_WAITING_FOREVER);
        /* �߳�2�������� */
        rt_kprintf("thread2 is run!\n");
    }
}
/* DEMO��ʼ������ */
void demo_init(void)
{
    /* ָ���߳̿��ƿ��ָ�� */
    rt_thread_t thread1_id, thread2_id;
    /* ����һ���ź�������ʼֵ��0 */
    sem_food = rt_sem_create("sem_food", 0, RT_IPC_FLAG_PRIO);
    if (sem_food == RT_NULL)
    {
        rt_kprintf("sem created fail!\n");
        return ;
    }
    /* �����߳�1 */
    thread1_id = rt_thread_create("thread1",
                    thread1_entry, RT_NULL,/* �߳������thread1_entry, ����RT_NULL */
                    THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread1_id != RT_NULL)
        rt_thread_startup(thread1_id);
    /* �����߳�2 */
    thread2_id = rt_thread_create("thread2",
                    thread2_entry, RT_NULL,/* �߳������thread2_entry, ����RT_NULL */
                    THREAD_STACK_SIZE, THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    if (thread2_id != RT_NULL)
        rt_thread_startup(thread2_id);
}

int main(void)
{
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        demo_init();
    }
}
