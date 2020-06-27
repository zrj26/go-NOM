#include "IodineAPI.c"

void main()
{
    int success = init();
    if (success==-1){
        // failed
        printf("init library failed");
        return;
    }

    char *name = "network1";
    int res = NewNetwork(name);
    char* id = getNetworkID(0);
    printf(id);
    printf("sdds");
}