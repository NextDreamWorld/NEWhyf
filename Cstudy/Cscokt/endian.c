/**
 * =============================================================================
 * 
 * \file endian.c
 * \breif 
 * \version 1.0
 * \date 2013年06月02日 08时41分17秒
 * \author  Yuan Feng.Hong (Hong), tigger.Feng@gmail.com
 * \copyright Copyright (c) 2013, NA 
 *
 * =============================================================================
 */


#include<stdio.h>

int main()
{
    //查看机器大小端
    //第一种方法
    int i=0x01020304;
    char* p=(char*)&i;
    printf("%x\n",i);
    printf("%p:%d, %p:%d\n",&p[3],p[3],&p[0],p[0]);
    
    if ( p[0] == 4)
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }

    //第二种方法
    union check
    {
        int i;
        char ch;
    } c;
    c.i=1;
    if ( c.ch == 1)
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }
}
