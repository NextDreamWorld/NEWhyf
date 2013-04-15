#include "func.h"


/*********************** 锁的结构
 struct flock{
 short l_type;          // F_RDLCK:共享读锁, F_WRLCK:独占写锁, F_UNLCK:解锁
 off_t l_start;         // 偏移量
 short l_whence;        // 锁开始位置: SEEK_SET, SEEK_CUR,SEEK_END
 off_t l_len;           // 锁的区域长度, 0 表示到文件末尾
 pid_t l_pid;           // 使用F_GETLK 可以获取到该变量
};
************************/

/**********************************************
*funcname: checkUnique(char* pszFile,char* pszPro)
*desc    : 检查程序唯一性
*return  ：-1:  出错
            0:  不存在该程序,并加锁成功
           >0:  存在进程 
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
    
    char szFileName[MAX_STR_LEN];               // 用于锁的文件名
    memset(szFileName, 0, sizeof(szFileName));
    
    if(NULL != pszFile)
    {
        strcpy(szFileName, pszFile);
    }
    strcat(szFileName, pszPro);
    strcat(szFileName, ".lk");  
    
    // 构造锁
    struct flock lk;                
    lk.l_type   = F_WRLCK;          
    lk.l_start  = 0;                
    lk.l_whence = SEEK_SET;         
    lk.l_len    = 0;                
  
    int rev =   IsProcExist(szFileName);         // 检查是否有进程存在
    if( 0 <rev )                                // 进程存在
    {
        return rev;
    }
    
    if( -1 == rev)                              // 执行出错
    {
        return -1;
    }
    else                                        
    {
        // 不存在锁，即程序不存在       
        // 进程不存在，给文件上锁
        
        // 打开锁文件
        int fd = -1;
        if( -1 == (fd = open(szFileName, O_RDWR|O_CREAT, 0666)))
        {
            printf(" open or create %s failed!\n", szFileName);
            return -1;
        }
        
        // 给文件上锁
        if( -1 == fcntl(fd, F_SETLK, &lk))
        {
            // 上锁失败
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
*desc    : 检查进程是否存在
*argu    : pszPro: 用于判断进程是否存在的文件 
*return  ：-1:  出错
            0:  不存在该程序
           >0:  存在进程 
***********************************************/

int IsProcExist(char* pszProFile)
{
    if( NULL == pszProFile)
    {
        printf("pszProFile is NULL\n");
        return -1;
    }
    
    // 构造锁
    struct flock lk;
    lk.l_type   = F_WRLCK;          
    lk.l_start  = 0;                
    lk.l_whence = SEEK_SET;         
    lk.l_len    = 0;     
    
    // 打开文件
    int fd;
    if( -1 == (fd = open(pszProFile, O_RDWR|O_CREAT, 0666)))
    {
        printf("open %s error!\n", pszProFile);
        return -1;
    }
    
    // 获取文件锁
    int rev;
    if( -1 == (rev = fcntl(fd, F_GETLK, &lk)))
    {
        printf("get lock from %s error!\n", pszProFile);
        close(fd);
        return -1;
    }
    
    // 文件存在锁，即有进程存在
    if( F_UNLCK != lk.l_type)
    {
        printf(" Exist %d programe!\n", lk.l_pid);
        close(fd);
        return lk.l_pid;
    }
    
    //  不存在进程
    close(fd);
    
    return 0;  
}
