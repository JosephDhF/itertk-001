//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   com.h
/// @brief  �����������
///
///
///
/// @version    2.0
/// @author     xuliang<gxuliang@gmail.com>
/// @date       2010��04��24
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "config.h"

#ifndef __COM_H__
#define __COM_H__


#define TTY_DEV "/dev/ttyS"

enum    COM_CHK
{
    CHK_ODD = 1,//żУ��
    CHK_QI,
    CHK_NONE,
};

enum    COM_TYPE
{
    RS232 = 0,
    RS485,
    RS422,
};

//////////////////////////////////////////////////////////////////////////
///
///     ���ڳ�ʼ��
///     @param argc ��������
///     @param *argv[] ��������
///     @return always 0
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
extern void com_init(void);
//////////////////////////////////////////////////////////////////////////
///
///     �������ݷ���
///     @param id �������
///     @param *data �����׵�ַ
///     @param len ���ݳ���
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
inline int SendNetDataToCom(int id, void *data, int len);
//////////////////////////////////////////////////////////////////////////
///
///     ���ڲ�������
///     @param fd �����ļ�������
///     @param con_com �����ṹ��
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
extern void com_para_set(int fd, CONFIG_COM *con_com);

    
extern void com_set(CONFIG_COM *con_com);

extern pthread_mutex_t rs485_mutex;		/*rs485��˫����*/

#endif
