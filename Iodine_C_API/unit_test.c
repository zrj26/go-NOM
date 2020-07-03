#include "IodineAPI.c"
#include <string.h>

int COUNT_FAIL = 0;
int COUNT_FUNCTIONS = 0;
char *Failed_FUNCTIONS[100];
char **p = Failed_FUNCTIONS;

bool assertError(int errCode, int expectValue)
{
    if (errCode == expectValue)
    {
        return TRUE;
    }
    return FALSE;
}

void test_setup1()
{
    Iod_newNetwork("network1");
    Iod_newNetwork("network2");
}

void test_tear_down1()
{
    Iod_clearNetworks();
}

void test_newNetwork()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err;
    
    
    char **List1;
    err = Iod_newNetwork("network1");
    ERR = ERR && assertError(err, -3);
    err = Iod_newNetwork("network3");
    ERR = ERR && assertError(err, 0);
    err = Iod_newNetwork("network4");
    ERR = ERR && assertError(err, 0);
    err = Iod_redo();
    ERR = ERR && assertError(err, -9);
    List1 = Iod_getListofNetworks();
    char *List2[100] = {"network1", "network2", "network3", "network4"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertError(equal1, 1);
    err = Iod_undo();
    ERR = ERR && assertError(err, 0);
    List1 = Iod_getListofNetworks();
    char *List3[100] = {"network1", "network2", "network3"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertError(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertError(err, 0);
    List1 = Iod_getListofNetworks();
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertError(equal1, 1);

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

void (*func_array1[])() = {
    test_newNetwork,
    test_newNetwork2,
    // test_newNetwork3,
};
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
    int i;
    int func_array1_size = sizeof(func_array1) / sizeof(func_array1[0]);
    err = loadDll(&errorCode);
    if (!err)
    {
        return -1; //can't load the lib
    }

    for (i = 0; i < func_array1_size; i++)
    {
        test_setup1();
        (func_array1[i])();
        test_tear_down1();
    }

    printf("\nYou tested %d functions, %d of them failed.\n", COUNT_FUNCTIONS, COUNT_FAIL);
    if (COUNT_FAIL > 1)
    {
        printf("They are: \n");
    }
    else if (COUNT_FAIL = 1)
    {
        printf("It is: \n");
    }
    if (COUNT_FAIL != 0)
    {
        for (int i = 0; i < 100; i++)
        {
            if (Failed_FUNCTIONS[i] != NULL)
            {
                printf("%s\t", Failed_FUNCTIONS[i]);
            }
        }
        printf("\n");
    }
}