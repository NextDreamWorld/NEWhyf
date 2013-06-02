/**
 * =============================================================================
 * 
 * \file getprotobynumber.c
 * \breif 
 * \version 1.0
 * \date 2013年06月02日 15时03分12秒
 * \author  Yuan Feng.Hong (Hong), tigger.Feng@gmail.com
 * \copyright Copyright (c) 2013, NA 
 *
 * =============================================================================
 */

#include<stdio.h>
#include<netdb.h>
#include<string.h>

int main(int argc, char** argv)
{
   if( argc != 2)
   {
       printf("usage: getservbyport prot\n");
       return 1;
   }
   struct serv prot;
   memcpy(&prot, getservbyport(int)atoi(argv[1])), sizeof(prot));
   printf("name:%s\n prot: %d\n", prot.s_name, prot.s_proto);
}
