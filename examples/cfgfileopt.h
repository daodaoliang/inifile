/************ write *****************
ʹ��inifile�������
����Ҫ����һ��write.ini���������£�
; write.ini
[section1]
entry1 = abc
entry2 = 123 0X12AC

Ȼ���entry2��Ϊ256 300,��������ķ���������
[section2]
entry1 = test
*/

/**************** read **************
ʹ��inifile�������
���赱ǰĿ¼����һ�ļ�read.ini���������£�
; read.ini
[section1]
entry1 = test1
entry2 = 123

[section2]
entry1 = 10.32abc
entry2 = adfasd dsf 100

����Ĵ�����ʾ����ζ�ȡ���ļ�,��û���ж��κδ���
*/

/**************** delete *************
ʹ��inifile�������
���赱ǰĿ¼����һ�ļ�delete.ini���������£�
; delete.ini
[section1]
entry1 = test1
entry2 = 123

[section2]
entry1 = 10.32abc
entry2 = adfasd dsf 100

����ɾ��section1:entry1,Ȼ��ɾ������section2
*/


#include "inifile.h"
#include "zlog.h"

