#include "IodineAPI.c"
#include <string.h>

int COUNT_FAIL = 0;
int COUNT_FUNCTIONS = 0;
char *Failed_FUNCTIONS[100];
char **p = Failed_FUNCTIONS;

bool assertIntEqual(int errCode, int expectValue)
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

void test_tear_down()
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
    ERR = ERR && assertIntEqual(err, -3);
    err = Iod_newNetwork("network3");
    ERR = ERR && assertIntEqual(err, 0);
    err = Iod_newNetwork("network4");
    ERR = ERR && assertIntEqual(err, 0);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    List1 = Iod_getListofNetworks();
    char *List2[100] = {"network1", "network2", "network3", "network4"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();
    char *List3[100] = {"network1", "network2", "network3"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();

    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

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

void test_getNetworkIndex()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    int err = Iod_getNetworkIndex("network3");
    ERR = ERR && assertIntEqual(err, -2);
    err = Iod_getNetworkIndex("network2");
    ERR = ERR && assertIntEqual(err, 1);
    err = Iod_getNetworkIndex("network1");
    ERR = ERR && assertIntEqual(err, 0);

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

void test_deleteNetwork()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;
    int err = Iod_deleteNetwork(2);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteNetwork(1);
    List1 = Iod_getListofNetworks();
    char *List2[100] = {"network1"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();
    char *List3[100] = {"network1","network2"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

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

void test_clearNetworks()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    Iod_clearNetworks();
    List1 = Iod_getListofNetworks();
    char *List2[100] = {};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    int err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();
    char *List3[100] = {"network1", "network2"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListofNetworks();
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

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

void test_getNumberOfNetworks()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num1 = Iod_getNumberOfNetworks();
    ERR = ERR && assertIntEqual(num1, 2);

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

void test_getNetworkID()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *id1 = Iod_getNetworkID(2);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    id1 = Iod_getNetworkID(0);
    char *id2 = "network1";
    ERR = (strcmp(id1, id2)==0);
    
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

void test_getListOfNetworks()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListofNetworks();
    char *List2[100] = {"network1", "network2"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

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


void test_setup2()
{
    Iod_newNetwork("network1");
    Iod_newNetwork("network2");
    Iod_addNode(0, "node1", 1.1, 2.5, 5.4, 6.4);
    Iod_addNode(0, "node2", 1.2, 3.2, 2.5, 4.1);
    Iod_addNode(0, "node3", 2.2, 3.1, 1.5, 4.5);
    Iod_addNode(1, "node1", 1.1, 3.5, 7.4, 6.0);
}


void test_addNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_addNode(0, "node4", 1.1, 2.5, 5.4, 6.4);
    List1= Iod_getListOfNodesIDs(0);
    char *List2[100] = {"node1", "node2", "node3", "node4"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_addNode(0, "node2", 1.1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -3);
    err = Iod_addNode(-1, "node5", 1.1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_addNode(2, "node5", 1.1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -5);

    err = Iod_addNode(0, "node5", -1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_addNode(0, "node5", 1.1, -1, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_addNode(0, "node5", 1.1, 2.5, -1, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_addNode(0, "node5", 1.1, 2.5, 0, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_addNode(0, "node5", 1.1, 2.5, 5.4, -1);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_addNode(0, "node5", 1.1, 2.5, 5.4, 0);
    ERR = ERR && assertIntEqual(err, -12);

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

void test_getNodeIndex()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int index1 = Iod_getNodeIndex(0, "node1");
    ERR = ERR && assertIntEqual(index1, 0);
    int err = Iod_getNodeIndex(-1, "node2");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getNodeIndex(0, "node5");
    ERR = ERR && assertIntEqual(err, -2);

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

void test_deleteNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_deleteNode(0, 1);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    char *List2[100] = {"node1", "node3"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    char *List3[100] = {"node1","node2", "node3"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_deleteNode(-1, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteNode(5, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteNode(0, -1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_deleteNode(0, 3);
    ERR = ERR && assertIntEqual(err, -7);
    Iod_createReaction(0, "rea1");
    Iod_addSrcNode(0, 0, 0, 1);
    Iod_addDestNode(0, 0, 1, 6);
    err = Iod_deleteNode(0, 0);
    ERR = ERR && assertIntEqual(err, -4);
    err = Iod_deleteNode(0, 01);
    ERR = ERR && assertIntEqual(err, -4);

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

void test_clearNetwork()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    Iod_createBiBi(0, "Rea1", "k1*A",0, 1, 2, 1, 1, 2, 3, 4);
    char **List1;

    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea1"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    int err = Iod_clearNetwork(0);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List3[100] = {};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    List1 = Iod_getListOfNodesIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    char *List4[100] = {"node1", "node2", "node3"};
    equal1 = Iod_strArrayEqual(List1, &List4[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    List1 = Iod_getListOfReactionIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    List1 = Iod_getListOfReactionIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_clearNetwork(-1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_clearNetwork(2);
    ERR = ERR && assertIntEqual(err, -5);

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

void test_getNumberOfNodes()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num1 = Iod_getNumberOfNodes(0);
    ERR = ERR && assertIntEqual(num1, 3);
    int err = Iod_getNumberOfNodes(-1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getNumberOfNodes(2);
    ERR = ERR && assertIntEqual(err, -5);

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

void test_getNodeCenterXY()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    float num1 = Iod_getNodeCenterX(0,0);
    ERR = ERR && Iod_floatEqual(num1, 3.80, 0.01);
    num1 = Iod_getNodeCenterY(0, 0);
    ERR = ERR && Iod_floatEqual(num1, 5.70, 0.01);
    Iod_getNodeCenterX(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    Iod_getNodeCenterY(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    Iod_getNodeCenterX(2, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    Iod_getNodeCenterY(2, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);

    Iod_getNodeCenterX(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    Iod_getNodeCenterY(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    Iod_getNodeCenterX(0,3);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    Iod_getNodeCenterY(0,3);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);

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

void test_getNodeID()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *id1 = Iod_getNodeID(0,0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    char *id2 = "node1";
    ERR = (strcmp(id1, id2) == 0);

    id1 = Iod_getNodeID(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    id1 = Iod_getNodeID(3, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    id1 = Iod_getNodeID(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    id1 = Iod_getNodeID(0, 4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);

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

void test_getListOfNodesIDs()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfNodesIDs(0);
    char *List2[100] = {"node1", "node2", "node3"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    List1 = Iod_getListOfNodesIDs(-1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfNodesIDs(2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_clearNetwork(0);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfNodesIDs(0);
    char *List3[100] = {};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

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

void test_getNodeXYWH()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    float f1 = Iod_getNodeX(0,0);
    ERR = ERR && Iod_floatEqual(f1, 1.1, 0.01);
    f1 = Iod_getNodeY(0, 0);
    ERR = ERR && Iod_floatEqual(f1, 2.5, 0.01);
    f1 = Iod_getNodeW(0, 0);
    ERR = ERR && Iod_floatEqual(f1, 5.4, 0.01);
    f1 = Iod_getNodeH(0, 0);
    ERR = ERR && Iod_floatEqual(f1, 6.4, 0.01);
    f1 = Iod_getNodeX(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeY(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeW(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeH(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);

    f1 = Iod_getNodeX(3, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeY(3, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeW(3, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    f1 = Iod_getNodeH(3, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);

    f1 = Iod_getNodeX(1,-1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeY(1,-1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeW(1,-1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeH(1,-1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);

    f1 = Iod_getNodeX(1,4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeY(1,4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeW(1,4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    f1 = Iod_getNodeH(1,4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
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

void test_getNodeFillColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1= Iod_getNodeFillColor(0,0);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    color1 = Iod_getNodeFillColor(-1, 1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getNodeFillColor(3, 1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getNodeFillColor(1, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    color1 = Iod_getNodeFillColor(1, 4);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);

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
    test_getNetworkIndex,
    test_deleteNetwork,
    test_clearNetworks,
    test_getNumberOfNetworks,
    test_getNetworkID,
    test_getListOfNetworks,
};

void (*func_array2[])() = {
    test_addNode,
    test_getNodeIndex,
    test_deleteNode,
    test_clearNetwork,
    test_getNumberOfNodes,
    test_getNodeCenterXY,
    test_getNodeID,
    test_getListOfNodesIDs,
    test_getNodeXYWH,
    test_getNodeFillColor,
    };

int main(void)
{
    int errorCode;
    int err;
    int i;
    int func_array1_size = sizeof(func_array1) / sizeof(func_array1[0]);
    int func_array2_size = sizeof(func_array2) / sizeof(func_array2[0]);
    err = loadDll(&errorCode, "../Iodine_Dll/Iodine.dll");
    if (!err)
    {
        return -1; //can't load the lib
    }

    for (i = 0; i < func_array1_size; i++)
    {
        test_setup1();
        (func_array1[i])();
        test_tear_down();
    }

    for (i = 0; i < func_array2_size; i++)
    {
        test_setup2();
        (func_array2[i])();
        test_tear_down();
    }

    printf("\nYou tested %d functions, %d of them failed.\n", COUNT_FUNCTIONS, COUNT_FAIL);
    if (COUNT_FAIL > 1)
    {
        printf("They are: \n");
    }
    else if (COUNT_FAIL == 1)
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