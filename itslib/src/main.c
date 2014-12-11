//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   main.c
/// @brief  �����̵Ĺᴩ
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
#include <stdlib.h>
#include "def.h"
#include "utelnetd.h"
#include "thread.h"
#include "console.h"

int TelnetPort = 6000;//console port

//////////////////////////////////////////////////////////////////////////
///
///     �������
///     @param argc ��������
///     @param *argv[] ��������
///     @return always 0
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
int main ( int argc, char **argv )
{
    TRD_t telnet_trd;
    TRD_t console_trd;
    
    trd_create(&telnet_trd, (void*)&telnet_main, (void*)&TelnetPort);
    trd_create(&console_trd, (void*)&console_proc, (void*)&TelnetPort);
    while(1)
    {
       sleep(1); 
    }
    return 0;
}
