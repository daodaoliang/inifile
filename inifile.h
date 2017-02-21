/*

Configuration File Management
Read/Write .ini files

version 0.2 2001/10/30 13:20:00
Author: ��־ǿ (czhiqiang@163.net)��modified from iodbc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

*/

#ifndef _INIFILE_H
#define _INIFILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <stdarg.h>
#ifndef _MAC
#include <sys/types.h>
#endif

#define CFG_MAX_LINE_LENGTH 1024

/* configuration file entry */
typedef struct TCFGENTRY
  {
    char *section;
    char *id;
    char *value;
    char *comment;
    unsigned short flags;
  }
TCFGENTRY, *PCFGENTRY;

/* values for flags */
#define CFE_MUST_FREE_SECTION	0x8000
#define CFE_MUST_FREE_ID	0x4000
#define CFE_MUST_FREE_VALUE	0x2000
#define CFE_MUST_FREE_COMMENT	0x1000

/* configuration file */
typedef struct TCFGDATA
  {
    char *fileName;		/* Current file name */

    int dirty;			/* Did we make modifications? */

    char *image;		/* In-memory copy of the file */
    size_t size;		/* Size of this copy (excl. \0) */
    time_t mtime;		/* Modification time */

    unsigned int numEntries;
    unsigned int maxEntries;
    PCFGENTRY entries;

    /* Compatibility */
    unsigned int cursor;
    char *section;
    char *id;
    char *value;
    char *comment;
    unsigned short flags;

  }
TCONFIG, *PCONFIG;

#define CFG_VALID		0x8000
#define CFG_EOF			0x4000

#define CFG_ERROR		0x0000
#define CFG_SECTION		0x0001
#define CFG_DEFINE		0x0002
#define CFG_CONTINUE		0x0003

#define CFG_TYPEMASK		0x000F
#define CFG_TYPE(X)		((X) & CFG_TYPEMASK)
#define cfg_valid(X)	((X) != NULL && ((X)->flags & CFG_VALID))
#define cfg_eof(X)	((X)->flags & CFG_EOF)
#define cfg_section(X)	(CFG_TYPE((X)->flags) == CFG_SECTION)
#define cfg_define(X)	(CFG_TYPE((X)->flags) == CFG_DEFINE)
#define cfg_cont(X)	(CFG_TYPE((X)->flags) == CFG_CONTINUE)

/*
 * Name��   cfg_file_exist
 * Desc��   �ж������ļ��Ƿ����
 * param1�� �����ļ��� 
 * */
int cfg_file_exist (const char *filename);

/*
 * Name��    cfg_init 
 * Desc��    ��ʼ�������ļ�
 * param1��  ���淵�ص� �����ļ��ṹ 
 * param2��  Ҫ��ʼ���� �����ļ���
 * param3��  ����ļ������ڣ��Ƿ񴴽�; ��0������
 * */
int cfg_init (PCONFIG * ppconf, const char *filename, int doCreate);

/*
 * Name��   cfg_done
 * Desc��   �ͷ����к������ļ���ص��ڴ�
 * param1�� �����ļ��ṹ
 * */
int cfg_done (PCONFIG pconfig);

/*
 * Name��   cfg_freeimage 
 * Desc��   �ͷ����ýṹ�е�image����ռ�õ��ڴ�
 * param1�� �����ļ��ṹ
 * */
int cfg_freeimage (PCONFIG pconfig);

/*
 * Name��   cfg_freeimage 
 * Desc��   (��������ļ��޸�)ˢ��pconfig�ṹ 
 * param1�� �����ļ��ṹ
 * */
int cfg_refresh (PCONFIG pconfig);

int cfg_storeentry (PCONFIG pconfig, char *section, char *id,
    char *value, char *comment, int dynamic);

int cfg_rewind (PCONFIG pconfig);
int cfg_nextentry (PCONFIG pconfig);
int cfg_find (PCONFIG pconfig, char *section, char *id);
int cfg_next_section (PCONFIG pconfig);

/*
 * Name��   cfg_write
 * Desc��   ��Դ򿪵����ýṹ��д��һ��ʵ��(һ�����ü�¼)��ֻ��д�뵽���ýṹ����δ���� 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ʵ��ֵ
 * */
int cfg_write (PCONFIG pconfig, char *section, char *id, char *value);

/*
 * Name��   cfg_commit
 * Desc��   �����ýṹ�е�����д��Ӳ���ļ�(����) 
 * param1�� �����ļ��ṹ
 * */
int cfg_commit (PCONFIG pconfig);

/*
 * Name��   cfg_getstring
 * Desc��   ��ȡ�����ļ��е�ʵ��ֵ 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ���ص�ʵ��ֵ�Ĵ��λ��
 * */
int cfg_getstring (PCONFIG pconfig, char *section, char *id, char *valptr);

/*
 * Name��   cfg_getlong
 * Desc��   ��ȡlong����ֵ 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ���ص�ʵ��ֵ�Ĵ��λ��
 * */
int cfg_getlong (PCONFIG pconfig, char *section, char *id, long *valptr);

/*
 * Name��   cfg_getint
 * Desc��   ��ȡint����ֵ 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ���ص�ʵ��ֵ�Ĵ��λ��
 * */
int cfg_getint (PCONFIG pconfig, char *section, char *id, int *valptr);

/*
 * Name��   cfg_get_item
 * Desc��   ����param4ָ���ĸ�ʽ��ȡ�����ļ���ʵ��ֵ 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ָ��Ҫ��ȡ��ʵ��ĸ�ʽ 
 * param5�� ���ո�ʽ��ȡ����ʵ��ֵ�Ĵ��λ��(������)
 * */
int cfg_get_item (PCONFIG pconfig, char *section, char *id, char * fmt, ...);

/*
 * Name��   cfg_write_item
 * Desc��   ����param4ָ���ĸ�ʽд�������ļ���ʵ��ֵ 
 * param1�� �����ļ��ṹ
 * param2�� section��
 * param3�� ʵ����
 * param4�� ָ��Ҫд���ʵ��ĸ�ʽ 
 * param5�� ���ո�ʽ��Ҫд���ʵ��ֵ(������)
 * */
int cfg_write_item(PCONFIG pconfig, char *section, char *id, char * fmt, ...);

int list_entries (PCONFIG pCfg, const char * lpszSection, char * lpszRetBuffer, int cbRetBuffer);
int list_sections (PCONFIG pCfg, char * lpszRetBuffer, int cbRetBuffer);

int GetPrivateProfileString (char * lpszSection, char * lpszEntry,
    char * lpszDefault, char * lpszRetBuffer, int cbRetBuffer,
    char * lpszFilename);
int GetPrivateProfileInt (char * lpszSection, char * lpszEntry,
    int iDefault, char * lpszFilename);

/*
 * Name��   WritePrivateProfileString
 * Desc��   �ڲ����ȵ���cfg_init��ɳ�ʼ������cfg_writeд�����ݣ����Լ�������̵���cfg_commit���ڴ��ͷ�cfg_done 
 * param1�� section��
 * param2�� ʵ����
 * param3�� ָ��Ҫд���ʵ��ĸ�ʽ 
 * param4�� �����ļ���
 * */
int WritePrivateProfileString (char * lpszSection, char * lpszEntry,
    char * lpszString, char * lpszFilename);

#ifdef  __cplusplus
}
#endif

#endif /* _INIFILE_H */
