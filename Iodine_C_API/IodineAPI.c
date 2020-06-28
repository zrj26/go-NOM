#include <windows.h>
#include <stdio.h>
#include "..\Iodine_Dll\Iodine.h"

typedef __stdcall int (*MYFunc)(char *, int);
typedef __stdcall char*(*MYFunc2)(int);

HINSTANCE LibIodine = NULL;

int init(){
    LibIodine = LoadLibrary(TEXT("../Iodine_Dll/Iodine.dll"));
    if (LibIodine == NULL)
    {
        return -1;
    }
    printf("init\n");
    return 0;
}

// int newNetwork(char* p0, int p1);
int NewNetwork(char *name){
    if (LibIodine == NULL)
    {
        printf("lib Null");
        return -1;
    }
    MYFunc newNetwork;
    newNetwork = (MYFunc)GetProcAddress(LibIodine, "newNetwork");
    if (newNetwork == NULL){
        printf("func Null: newNetwork");
        return -1;
    }
    int err = newNetwork(name, strlen(name));
    return err;
}

char* GetNetworkID(int index)
{
    if (LibIodine = NULL){
        printf("lib Null");
        return "error";
    }
    MYFunc2 getNetworkID;
    getNetworkID = (MYFunc2)GetProcAddress(LibIodine, "getNetworkID");
    if (getNetworkID == NULL){
        printf("func Null: getNetworkID");
        return "error";
    }
    printf("123");
    char *id;
    id = getNetworkID(index);
    return id;
}
