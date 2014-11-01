//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   log.h
/// @brief  ��־�������
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

#ifndef __LOG_H__
#define __LOG_H__

#define FUNC    (char*)__FUNCTION__

typedef enum tagLOG_Lv
{
    LOG_NONE,
    LOG_TRACE,    
    LOG_DBG,
    LOG_MSG,
    LOG_WARN,
    LOG_ERR,
    LOG_FATAL,
}LOG_Lv;



//////////////////////////////////////////////////////////////////////////
///
///     ��ӡ��־
///     @param  module  ��������
///     @param  level   ��־�ȼ�
///     @param  format  ��������
///     @return SUCCESS FAILURE
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern  int sys_log(char* module, LOG_Lv level, char* format, ...);

#endif
