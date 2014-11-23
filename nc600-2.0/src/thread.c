//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   thread.c
/// @brief  �߳̿⺯��
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



#include "thread.h"
#include <stdio.h>
#include "log.h"

//////////////////////////////////////////////////////////////////////////
///
///     �����������߳�
///     @param trd_id
///     @param *func    Ŀ���߳�
///     @param *arg     ��������
///     @return 0-�ɹ�<0 ʧ��
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
int trd_create(TRD_t *trd_id, void *(*func)(void *), void *arg)
{
    int ret = -1;

    ret = pthread_create(trd_id, NULL, func, arg);
	

    if (ret != 0)
    {
        perror("trd_create: pthread_create");
        return -1;
    }

    ret = pthread_detach(*trd_id);

    if (ret != 0)
    {
        perror("trd_create: pthread_detach");
        return -2;
    }

    return 0;
}


//////////////////////////////////////////////////////////////////////////
///
///     ��������ʼ��
///     @param *lock
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
inline void trd_lock_init(LOCK_t *lock)
{
    pthread_mutex_init(lock, NULL);
}


