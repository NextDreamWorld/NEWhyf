#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

int checkUnique(char* pszFile, char* pszPro);       // ������Ψһ
int IsProExist(char* pszPro);                       // �������Ƿ��Ѿ�����   
