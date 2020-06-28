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
    printf("init\n");
    return 0;
}

// int newNetwork(char* p0, int p1);
int NewNetwork(char *name){
    MYFunc newNetwork;
    if (LibIodine = NULL){
        return -1;
    }
    newNetwork = (MYFunc)GetProcAddress(LibIodine, "newNetwork");
    if (newNetwork = NULL){
        return -1;
    }
    int err = newNetwork(name, strlen(name));
    return err;
}

char* getNetworkID(int index)
{
    MYFunc2 getNetworkID;
    char* id;
    if (LibIodine = NULL){
        return "error";
    }
    getNetworkID = (MYFunc2)GetProcAddress(LibIodine, "getNetworkID");
    if (NULL != getNetworkID){
        id = getNetworkID(index);
    }
    return id;
}
