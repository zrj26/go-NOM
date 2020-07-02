#include "IodineAPI.c"
#include <string.h>

void test_setup()
{
    Iod_newNetwork("network1");
    Iod_newNetwork("network2");
    // printf("setup\n");
}

void test_tear_down()
{
    Iod_clearNetworks();
    // printf("tear down\n");
}



int COUNT_FAIL =0;
int COUNT_FUNCTIONS = 0;
char *Failed_FUNCTIONS[100];
char **p = Failed_FUNCTIONS;



bool assertError(int errCode, int expectValue)
{
    if (errCode == expectValue){
        return TRUE;
    }
    return FALSE;
}

void test_newNetwork(){
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err = Iod_newNetwork("network1");
    ERR = ERR && assertError(err,-3);
    err = Iod_newNetwork("network3");
    ERR = ERR && assertError(err, 0);
    err = Iod_newNetwork("network4");
    ERR = ERR && assertError(err, 0);

    if (ERR == TRUE){
        printf(".");
    }else{
        printf("X");
        COUNT_FAIL++;
        *p = (char *)__FUNCTION__;
        p++;
    }

}

void test_newNetwork2()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err = Iod_newNetwork("network1");
    ERR = ERR && assertError(err, -3);
    err = Iod_newNetwork("network3");
    ERR = ERR && assertError(err, 0);
    err = Iod_newNetwork("network4");
    ERR = ERR && assertError(err, 10);

    if (ERR == TRUE)
    {
        printf(".");
    }
    else
    {
        printf("X");
        COUNT_FAIL++;
        *p = (char *)__FUNCTION__;
        p++;
    }
}



    // with self.assertRaises(IodineAPI.StackEmptyError):
    //     IodineAPI.redo()
    // self.assertEqual(IodineAPI.getListOfNetworks(),
    //                     ['network1', "network2", "network3", "network4"])
    // self.assertEqual(IodineAPI.undo(), None)
    // self.assertEqual(IodineAPI.getListOfNetworks(), [
    //                     'network1', "network2", "network3"])
    // self.assertEqual(IodineAPI.redo(), None)
    // self.assertEqual(IodineAPI.getListOfNetworks(),
    //                     ['network1', "network2", "network3", "network4"])

void (*func_array[])() = {
    test_newNetwork,
    test_newNetwork2,
    test_newNetwork3,
    };

int main(void)
{
    int errorCode;
    int err;
    int i;
    int func_array_size = sizeof(func_array) / sizeof(func_array[0]);
    err = loadDll(&errorCode);
    if (!err){
        return -1; //can't load the lib
    }

    for (i = 0; i < func_array_size; i++){
        test_setup();
        (func_array[i])();
        test_tear_down;
    }

    // printf(__FUNCTION__,"\n");
    printf("\nYou tested %d functions, %d of them failed.\n", COUNT_FUNCTIONS, COUNT_FAIL);
    if (COUNT_FAIL != 0){
        printf("They are: \n");
    }
    for (int i= 0; i<100; i++){
        if (Failed_FUNCTIONS[i] != NULL){
            printf("%s\t",Failed_FUNCTIONS[i]);
        }
    }
    printf("\n");

}