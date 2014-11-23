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
#include "system.h"
#include "config.h"
#include "log.h"
#include "web_net.h"
#include "com.h"
#include "mode.h"

//////////////////////////////////////////////////////////////////////////
///
///     �������
///     @param argc ��������
///     @param *argv[] ��������
///     @return always 0
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
int main ( int argc, char* argv[] )
{
static int cnt =0;
    sys_version_show ( stdout );
    config_init();
    web_init();
    mode_init();
    com_init();
    while(1)
    {
    sys_log(FUNC, LOG_DBG,"%d\n",cnt++);
        web_process();
    }
    return 0;
}
