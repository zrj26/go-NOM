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
    char *name = "network1";
    int err = NewNetwork(name);
    // printf("123");

    // printf("%d", err);
    char* id = getNetworkID(0);
    printf("%S",id);
    return 0;
}