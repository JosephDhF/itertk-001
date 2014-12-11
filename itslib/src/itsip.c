//////////////////////////////////////////////////////////////////////////
///    COPYRIGHT NOTICE
///    Copyright (c) 2010, �㽭�����������޹�˾
///    All rights reserved.
///
/// @file   itsip.c
/// @brief  Э��⺯������
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

#include <string.h>
#include "itsip.h"

//////////////////////////////////////////////////////////////////////////
///
///     ���Э������
///     @param  cmd   ������
///     @param  extlen  ��չ����
///     @param  dev_t   �豸����
///     @param  *data   ��չ����
///     @param  *its_pkt   Э��ṹ��
///     @author     xuliang<gxuliang@gmail.com>
///     @date       2010��04��24
//////////////////////////////////////////////////////////////////////////
inline void itsip_pack(BYTE cmd, WORD extlen, BYTE dev_t, void *data, ITSIP_PACKET *its_pkt)
{
	its_pkt->head.itsip_head = ITS_HEAD;
	its_pkt->head.itsip_cmd = cmd;
	its_pkt->head.itsip_ver = ITSIP_VERSION;
	its_pkt->head.itsip_thl = ITSIP_THLEN;
	its_pkt->head.itsip_extlen = extlen;

	its_pkt->head.itsip_dev_t = dev_t;

	if (extlen > 0 && data != NULL)
		memcpy(its_pkt->data, data, extlen);
	
}

