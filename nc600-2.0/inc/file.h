//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   file.h
/// @brief  fileͷ�ļ�
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

#ifndef __FILE_H__
#define __FILE_H__
#include "def.h"

/*! \enum OPEN_FLAGS
 */
enum OPEN_FLAGS
{
    MODE_READ      =    0x00,	//!< only read in binary format
    MODE_WRITE,					//!< only write in binary format
    MODE_READWRITE,				//!< read and write dual mode
    MODE_CREATE,				//!< create a file
    MODE_APPEND,				//!< append new content to the existed file tail
    MODE_UPDATE,				//!< Open file for update the contents
    MODE_READ_T,				//!< read text file
    MODE_WRITE_T,				//!< write text file
    MODE_RW_T,                  //!< read and write text file, clean existed contents
    MODE_CREATE_T,				//!< create text file
    MODE_APPEND_T,				//!< append content to text file's tail
    MODE_UPDATE_T,              //!< Open text file for update the contents
};

//////////////////////////////////////////////////////////////////////////
///
///     �ж��ļ��Ƿ����
///     @param  file_name   �ļ���
///     @return 1������ 0��������
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern int file_is_existed ( const    char *file_name );
//////////////////////////////////////////////////////////////////////////
///
///     ���ļ����
///     @param  file_name   �ļ���
///     @param  flags   ������
///     @return �ļ����
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern FILE *sys_file_open(char *file_name, DWORD flags);
//////////////////////////////////////////////////////////////////////////
///
///     ������д���ļ�
///     @param  file_hd   �ļ�
///     @param  *data   ����
///     @param  count   ���ݳ���
///     @return SUCCESS FAILURE
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern int sys_file_write(FILE *file_hd, void *data, DWORD count);
//////////////////////////////////////////////////////////////////////////
///
///     ���ļ���������
///     @param  file_hd   �ļ�
///     @param  *data   ����
///     @param  count   ���ݳ���
///     @return SUCCESS FAILURE
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern int sys_file_read(FILE *file_hd, void *buf, DWORD count);
//////////////////////////////////////////////////////////////////////////
///
///     �ر��ļ����
///     @param  file_hd   �ļ�
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
extern void sys_file_close( FILE *fp );

#endif


