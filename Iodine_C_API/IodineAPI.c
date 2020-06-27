#include <windows.h>
#include <stdio.h>
#include "..\Iodine_Dll\Iodine.h"

typedef int(__cdecl *MYFunc)(char*, int);
typedef char*(__cdecl *MYFunc2)(int);

HINSTANCE LibIodine = NULL;

int init(){
    LibIodine = LoadLibrary(TEXT("Iodine_Dll/Iodine.dll"));
    if (LibIodine != NULL)
    {
        return -1;
    }
    return 0;
}

// int newNetwork(char* p0, int p1);
int NewNetwork(char *name)
{
    MYFunc newNetwork;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    if (LibIodine = NULL)
    {
        return -1;
    }

    newNetwork = (MYFunc)GetProcAddress(LibIodine, "newNetwork");

    // If the function address is valid, call the function.
    if (newNetwork = NULL)
    {
        return -1;
    }
            // fRunTimeLinkSuccess = TRUE;
    newNetwork(name, strlen(name));
    
        // Free the DLL module.
        // fFreeResult = FreeLibrary(LibIodine);
    return 0;
}

char* getNetworkID(int index)
{
    MYFunc2 getNetworkID;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
    char* id;
    if (LibIodine != NULL)
    {
        getNetworkID = (MYFunc2)GetProcAddress(LibIodine, "getNetworkID");

        // If the function address is valid, call the function.
        if (NULL != getNetworkID)
        {
            fRunTimeLinkSuccess = TRUE;
            id = getNetworkID(index);
        }

    }
    return id;
}
