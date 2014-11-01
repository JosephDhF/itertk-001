//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file  file.c
/// @brief  �ļ���ز���
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
#include <unistd.h>
#include "file.h"




//////////////////////////////////////////////////////////////////////////
///
///     �ж��ļ��Ƿ����
///     @param  file_name   �ļ���
///     @return 1������ 0��������
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
int file_is_existed(const char *file_name)
{
    return access(file_name, F_OK) == 0;
}

//////////////////////////////////////////////////////////////////////////
///
///     ���ļ����
///     @param  file_name   �ļ���
///     @param  flags   ������
///     @return �ļ����
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
FILE *sys_file_open(char *file_name, DWORD flags)
{
    FILE *fp = NULL;

    switch (flags)
    {
    case MODE_READ:
        fp = fopen(file_name, "rb");
        break;

    case MODE_WRITE:
        fp = fopen(file_name, "wb");
        break;

    case MODE_READWRITE:
        fp = fopen(file_name, "wb+");
        break;

    case MODE_APPEND:
        fp = fopen(file_name, "ab");
        break;

    case MODE_UPDATE:
        fp = fopen(file_name, "rb+");
        break;

    case MODE_READ_T:
        fp = fopen(file_name, "r");
        break;
    case MODE_WRITE_T:
        fp = fopen(file_name, "w");
        break;
    case MODE_APPEND_T:
        fp = fopen(file_name, "a+");
        break;
    case MODE_RW_T:
        fp = fopen(file_name, "w+");
        break;
    case MODE_UPDATE_T:
        fp = fopen(file_name, "r+");
        break;
    default:
        break;
    }

    /*! error process */
    return fp;
}

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
int sys_file_write(FILE *file_hd, void *data, DWORD count)
{
    BYTE *p_data = data;
    DWORD write_cnt = 0;

    if (count == 0 || data == NULL || file_hd == NULL)
    {
        return FAILURE;
    }

    while (1)
    {
        write_cnt = fwrite(p_data, 1, count, file_hd);

        if (write_cnt == count)
        {
            break;
        }
        else
        {
            p_data += write_cnt;
            count -= write_cnt;
        }
    }

    return SUCCESS;
//	return
}
//////////////////////////////////////////////////////////////////////////
///
///     ���ļ���������
///     @param  file_hd   �ļ�
///     @param  *data   ����
///     @param  count   ���ݳ���
///     @return �������ݳ���
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
int sys_file_read(FILE *file_hd, void *buf, DWORD count)
{
    if (count == 0)
    {
        return FAILURE;
    }

    if (!file_hd)
    {
        return FAILURE;
    }
    int ret = fread( buf, 1, count, file_hd );

    return ret;
}
//////////////////////////////////////////////////////////////////////////
///
///     �ر��ļ����
///     @param  file_hd   �ļ�
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
void sys_file_close( FILE *fp )
{

    if (!fp)
    {
        return;
    }

    fclose(fp);

//	fp = NULL;
}
