#include "IodineAPI.c"
// #include <stdio.h>

int main()
{
    int success = init();
    if (success==-1){
        // failed
        printf("init library failed");
        return 0;
    }
    printf("sss");
    char *name = "network1";
    int err = NewNetwork(name);
    printf(err);
    char* id = getNetworkID(0);
    printf("sdfsd");
    printf("sdds");
    return 0;
}