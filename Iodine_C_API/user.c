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

    char* id = GetNetworkID(0);
    printf("%S",id);
    return 0;
}