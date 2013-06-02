/**
 * =============================================================================
 * 
 * \file TCPservice.cpp
 * \breif 
 * \version 1.0
 * \date 2013年06月02日 07时59分02秒
 * \author  Yuan Feng.Hong (Hong), tigger.Feng@gmail.com
 * \copyright Copyright (c) 2013, NA 
 *
 * =============================================================================
 */

#include<iostream>
using namespace std;

class TSocket
{
private:
    int  iPort;         // 端口号
    char szIP[12];      // IP地址

public:
    TSockt(char* cpIP, int iPort):iPort(iport)
    {
        memcpy(szIP, cpIP, sizeof(szIP));
    }

    ~TSockt()
    {
        cout<<"relase TScokt!"<<endl;
    }
    
    

}

int main()
{

}
