#include "func.h"

int main(int argc, char** argv)
{
    printf("=============start==============\n");
    int rev = -1;
    rev = checkUnique(NULL, argv[0]);
    if( -1 == rev)
    {
        printf("checkUnique error!\n");
        return -1;
    }
    else if( 0 < rev )
    {
        printf("exist the same processs!\n");
        return rev;
    }
    printf("%d\n", rev);
    printf("I working....\n");
    sleep(60);
    printf("=============end===============\n");
    return 0;
}
