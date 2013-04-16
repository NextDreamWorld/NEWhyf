#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

int checkUnique(char* pszFile, char* pszPro);       // 检查进程唯一
int IsProExist(char* pszPro);                       // 检查进程是否已经存在   
