//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   mode.h
/// @brief  ���ڹ���ģʽ�������
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

#ifndef __MODE_H__
#define __MODE_H__

#include "config.h"

enum    WORK_MODE
{
    WORK_NO,
    WORK_SOCKET,
};

enum    TCP_MODE
{
    TCP_RAW,
    TCP_TELNET,
};

enum    TCP_PTL
{
    TCP_NO,
    TCP_CLI,
    TCP_SRV,
    TCP_UDP,
};

enum    CR_LF
{
    TO_CR,
    TO_LF,
};

typedef struct tagMODECONFIG
{
    int id;
    int fd;
    int sfd[MAX_SESSION];
    CONFIG_SESSION* session;
}MODECONFIG;
//////////////////////////////////////////////////////////////////////////
///
///     �������ݷ���
///     @param id �������
///     @param *data �����׵�ַ
///     @param len ���ݳ���
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
inline int SendComDataToNet(int id, void *data, int len);
//////////////////////////////////////////////////////////////////////////
///
///     �����ʼ��
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
extern void mode_init(void);

#endif