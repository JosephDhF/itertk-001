//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   system.h
/// @brief  ϵͳ��������
///
///
///
/// @version    2.0
/// @author     xuliang<gxuliang@gmail.com>
/// @date       2010��04��24
///
///
///     �޶�˵��������汾
//////////////////////////////////////////////////////////////////////////#include <stdio.h>

#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include <stdio.h>
#include "def.h"


#define PRODUCT_NAME    "NC616"
#define PROGRAM_VERSION "V2.0"
//////////////////////////////////////////////////////////////////////////
///
///     ��ӡ�汾��Ϣ
///     @param *stream fprintf�ĵ�һ������
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern  void sys_version_show ( FILE * stream );
//////////////////////////////////////////////////////////////////////////
///
///     ip��ַ�ַ�תת����DWORD
///     @param *str �ַ���
///     @return ip
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern  DWORD sys_str2ip(char *str);
//////////////////////////////////////////////////////////////////////////
///
///     ip��ַ�ַ�תת����DWORD
///     @param ip ip��ַ
///     @return *str ip�ַ���
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern  char* sys_ip2str_static ( DWORD ip );
//////////////////////////////////////////////////////////////////////////
///
///     Get the count of millisecond
///     @return mscnt -- count of microsecond
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern UQWORD system_mscount_get(void);
//////////////////////////////////////////////////////////////////////////
///
///     ��װwrite
///     @param fd-�ļ�������
///     @param *ptr-�����׵�ַ
///     @param nbytes-���ݳ���
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010-05-05
//////////////////////////////////////////////////////////////////////////
extern int  writen( int fd, void *ptr, int nbytes);
extern int  writen_rs485( int fd, void *ptr, int nbytes);
#endif

