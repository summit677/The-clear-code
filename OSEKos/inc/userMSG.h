/**
 * @file 	userMSG.h
 * @brief
 *	<li>���ܣ���ͷ�ļ������û�Ӧ���ض������ݡ�</li>
 * @author 	Chenlr
 * @date 	2008-04-12
 * <p>���ţ�
 */


#ifndef _USER_MSG_H
#define _USER_MSG_H


#ifdef __cplusplus
extern "C" {
#endif



/* user defined structures for messages */
typedef struct
{
   char msgbuffer[6];
} string;

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint16
#define uint16 unsigned short
#endif

#ifdef __cplusplus
}
#endif

#endif

