#include "func.h"


/*********************** ���Ľṹ
 struct flock{
 short l_type;          // F_RDLCK:�������, F_WRLCK:��ռд��, F_UNLCK:����
 off_t l_start;         // ƫ����
 short l_whence;        // ����ʼλ��: SEEK_SET, SEEK_CUR,SEEK_END
 off_t l_len;           // �������򳤶�, 0 ��ʾ���ļ�ĩβ
 pid_t l_pid;           // ʹ��F_GETLK ���Ի�ȡ���ñ���
};
************************/

/**********************************************
*funcname: checkUnique(char* pszFile,char* pszPro)
*desc    : ������Ψһ��
*return  ��-1:  ����
            0:  �����ڸó���,�������ɹ�
           >0:  ���ڽ��� 
***********************************************/

int checkUnique(char* pszFile, char* pszPro )
{  
    if( MAX_STR_LEN <= strlen(pszFile))
    {
        return -1;
    } 
    
    if( NULL == pszPro)
    {
        return -1;
    }
    
    char szFileName[MAX_STR_LEN];               // ���������ļ���
    memset(szFileName, 0, sizeof(szFileName));
    
    if(NULL != pszFile)
    {
        strcpy(szFileName, pszFile);
    }
    strcat(szFileName, pszPro);
    strcat(szFileName, ".lk");  
    
    // ������
    struct flock lk;                
    lk.l_type   = F_WRLCK;          
    lk.l_start  = 0;                
    lk.l_whence = SEEK_SET;         
    lk.l_len    = 0;                
  
    int rev =   IsProcExist(szFileName);         // ����Ƿ��н��̴���
    if( 0 <rev )                                // ���̴���
    {
        return rev;
    }
    
    if( -1 == rev)                              // ִ�г���
    {
        return -1;
    }
    else                                        
    {
        // ���������������򲻴���       
        // ���̲����ڣ����ļ�����
        
        // �����ļ�
        int fd = -1;
        if( -1 == (fd = open(szFileName, O_RDWR|O_CREAT, 0666)))
        {
            printf(" open or create %s failed!\n", szFileName);
            return -1;
        }
        
        // ���ļ�����
        if( -1 == fcntl(fd, F_SETLK, &lk))
        {
            // ����ʧ��
            printf("set lock fialed!\n");
            close(fd);
            return -1;
        }
        printf("set lock successful!\n");
        
        return 0;
    }   
}


/**********************************************
*funcname: IsProExist(char* pszPro)
*desc    : �������Ƿ����
*argu    : pszPro: �����жϽ����Ƿ���ڵ��ļ� 
*return  ��-1:  ����
            0:  �����ڸó���
           >0:  ���ڽ��� 
***********************************************/

int IsProcExist(char* pszProFile)
{
    if( NULL == pszProFile)
    {
        printf("pszProFile is NULL\n");
        return -1;
    }
    
    // ������
    struct flock lk;
    lk.l_type   = F_WRLCK;          
    lk.l_start  = 0;                
    lk.l_whence = SEEK_SET;         
    lk.l_len    = 0;     
    
    // ���ļ�
    int fd;
    if( -1 == (fd = open(pszProFile, O_RDWR|O_CREAT, 0666)))
    {
        printf("open %s error!\n", pszProFile);
        return -1;
    }
    
    // ��ȡ�ļ���
    int rev;
    if( -1 == (rev = fcntl(fd, F_GETLK, &lk)))
    {
        printf("get lock from %s error!\n", pszProFile);
        close(fd);
        return -1;
    }
    
    // �ļ������������н��̴���
    if( F_UNLCK != lk.l_type)
    {
        printf(" Exist %d programe!\n", lk.l_pid);
        close(fd);
        return lk.l_pid;
    }
    
    //  �����ڽ���
    close(fd);
    
    return 0;  
}
