#include "IodineAPI.c"
#include <string.h>

void test_setup()
{
    newNetwork("network1");
    newNetwork("network2");
    // printf("setup\n");
}

void test_tear_down()
{
    clearNetworks();
    // printf("tear down\n");
}

// enum DAY
// {
//     MON = 1,
//     TUE,
//     WED,
//     THU,
//     FRI,
//     SAT,
//     SUN
// };

int COUNT_FAIL =0;
int COUNT_FUNCTIONS = 0;
char *Failed_FUNCTIONS[100];
char **p = Failed_FUNCTIONS;
void (*function)(void);

(*function) **function[100];


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
    int err = newNetwork("network1");
    ERR = ERR && assertError(err,-3);
    err = newNetwork("network3");
    ERR = ERR && assertError(err, 0);
    err = newNetwork("network4");
    ERR = ERR && assertError(err, 0);

    if (ERR == TRUE){
        printf(".");
    }else{
        printf("X");
        COUNT_FAIL++;
        *p = "newNetwork";
        p++;
    }

}

void test_newNetwork2()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err = newNetwork("network1");
    ERR = ERR && assertError(err, -3);
    err = newNetwork("network3");
    ERR = ERR && assertError(err, -2);//error
    err = newNetwork("network4");
    ERR = ERR && assertError(err, 0);

    if (ERR == TRUE)
    {
        printf(".");
    }
    else
    {
        printf("X");
        COUNT_FAIL++;
        *p = "newNetwork2";
        p++;
    }
}

void test_newNetwork3()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err = newNetwork("network1");
    ERR = ERR && assertError(err, -3);
    err = newNetwork("network3");
    ERR = ERR && assertError(err, -2); //error
    err = newNetwork("network4");
    ERR = ERR && assertError(err, 0);

    if (ERR == TRUE)
    {
        printf(".");
    }
    else
    {
        printf("X");
        COUNT_FAIL++;
        *p = "newNetwork3";
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

int main(void)
{
    int errorCode;
    int err;
    err = loadDll(&errorCode);
    if (!err)
    {
        return -1; //can't load the lib
    }
    test_setup();
    test_newNetwork();
    test_tear_down();

    test_setup();
    test_newNetwork2();
    test_tear_down();

    test_setup();
    test_newNetwork3();
    test_tear_down();

    printf("\nYou tested %d functions, %d of them failed.\n", COUNT_FUNCTIONS,COUNT_FAIL);
    if (COUNT_FAIL != 0){
        printf("They are: \n");
    }
    for (int i= 0; i<100; i++){
        if (Failed_FUNCTIONS[i] != NULL){
            printf("%s\t",Failed_FUNCTIONS[i]);
        }
    }
}