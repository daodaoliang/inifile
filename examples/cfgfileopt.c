#include "cfgfileopt.h"
#include "stdio.h"

// ʹ��inifile��������������ļ���ɾ��
int main()
{
    int rc;
    zlog_category_t *z_all;
    //�����ļ��ṹ
    PCONFIG pCfg;

    /***�����־ģ�飬ʹ��zlog��̬��־��****/
    rc = zlog_init("zlog.conf");
    if (rc) {
        printf("init failed\n");
        return -1;
    }
    z_all = zlog_get_category("sys_all");
    if (!z_all) {
        printf("get category fail\n");
        zlog_fini();
        return -2;
    }
    zlog_info(z_all, "zlog init completed.");

    /*************** write *************/
    cfg_init (&pCfg, "config.ini", 1);	/* ��config.ini�����ڣ�����config.ini */
    zlog_info(z_all, "create config.ini file completed.");

    cfg_write (pCfg, "section1", "entry1", "abc");	/* дsection1:entry1 */
    zlog_info(z_all, "write section1:entry1 completed.");

    cfg_write_item (pCfg, "section1", "entry2", "%d 0X%0X", 123,0X12AC);  /* ������ķ���дsection1:entry2 */
    zlog_info(z_all, "write section1:entry2 completed.");

    cfg_write_item (pCfg, "section1", "entry3", "%d", 2017);
    zlog_info(z_all, "write section1:entry3 completed.");

    cfg_commit(pCfg);	/* ���� */
    cfg_done(pCfg);

    WritePrivateProfileString("section1", "entry4", "256 300","config.ini");
    zlog_info(z_all, "section1:entry3 completed.");
    WritePrivateProfileString("section2", "entry1", "test","config.ini");
    zlog_info(z_all, "section2:entry1 completed.");

    
    /*************** read *************/
    /* ��ȡ�������ò���ӡ */
    char buf[128];
    int value, value1, tmp;
    cfg_init (&pCfg, "config.ini", 0);
    
    cfg_getstring(pCfg, "section1", "entry1", buf);
    printf("section1:entry1 -- %s\n", buf);
    zlog_info(z_all, "read-section1:entry1 -- %s.", buf);

    cfg_getstring(pCfg, "section1", "entry2", buf);
    printf("section1:entry2 -- %s\n", buf);
    zlog_info(z_all, "read-section1:entry2 -- %s.", buf);

    //���ֻ�ȡ����ֵ�ķ�����������ֵ
    cfg_getint(pCfg, "section1", "entry3", &value);
    printf("section1:entry3 -- %d\n", value);
    zlog_info(z_all, "read-section1:entry3 -- %d", value);

    cfg_get_item(pCfg, "section1", "entry3", "%d", &tmp);
    printf("cfg_get_item - section1:entry3 -- %d\n", tmp);
    zlog_info(z_all, "cfg_get_item - read-section1:entry3 -- %d.", tmp);
    //����ֵ
    cfg_write_item (pCfg, "section1", "entry3", "%d", 201702);
    cfg_get_item(pCfg, "section1", "entry3", "%d", &value1);
    printf("update - section1:entry3 -- %d\n", value1);
    zlog_info(z_all, "cfg_write_item - update-section1:entry3 -- %d.", value1);

    cfg_getstring(pCfg, "section2", "entry1", buf);
    printf("section2:entry1 -- %s\n", buf);
    zlog_info(z_all, "read-section2:entry1 -- %s.", buf);
    
    cfg_done(pCfg);

    /*************** delete *************/
    cfg_init (&pCfg, "config.ini", 0);
    cfg_write (pCfg, "section1", "entry1", NULL);  /* ɾ��section1:entry1 */
    zlog_info(z_all, "delete-section1:entry1.");

    cfg_write (pCfg, "section2", NULL, NULL);	/* ɾ��section2 */
    zlog_info(z_all, "delete-section2.");

    cfg_commit (pCfg);	/* ���� */
    cfg_done (pCfg);

    zlog_info(z_all, "zlog finish...");
    zlog_fini();
    return 0;
}

