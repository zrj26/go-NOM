#include "IodineAPI.c"

int main()
{
    int errorCode;
    int err;
    char *Id;
    if (loadDll(&errorCode))
    {
        printf("Error code from iodine = %d\n", getErrorCode());
        err = newNetwork("net1");
        printf("errCode = %d\n", err);
        Id = getNetworkID(0);
        printf("Network Id = %s\n", Id);
    }
    else
    {
        printf("Failed to load DLL: %d\n", errorCode);
    }

    bool fFreeResult = FreeLibrary(hinstLib);
    if (!fFreeResult){
        printf("free error");
    }

    return 0;
}