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

void test_getNodeCoordinateAndSize()
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

void test_getNodeOutlineColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1 = Iod_getNodeOutlineColor(0, 0);
    ERR = ERR && assertIntEqual((int)color1, 4284764415); //hex: '0xff6450ff'
    color1 = Iod_getNodeOutlineColor(-1, 1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getNodeOutlineColor(3, 1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getNodeOutlineColor(1, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -7);
    color1 = Iod_getNodeOutlineColor(1, 4);
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
void test_getNodeOutlineThickness()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num1 = Iod_getNodeOutlineThickness(0, 0);
    ERR = ERR && assertIntEqual(num1, 3);
    num1 = Iod_getNodeOutlineThickness(-1, 1);
    ERR = ERR && assertIntEqual(num1, -5);
    num1 = Iod_getNodeOutlineThickness(3, 1);
    ERR = ERR && assertIntEqual(num1, -5);
    num1 = Iod_getNodeOutlineThickness(1, -1);
    ERR = ERR && assertIntEqual(num1, -7);
    num1 = Iod_getNodeOutlineThickness(1, 4);
    ERR = ERR && assertIntEqual(num1, -7);
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

void test_setNodeID()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *id1 = Iod_getNodeID(0, 1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    char *id2 = "node2";
    ERR = ERR && (strcmp(id1, id2) == 0);
    err = Iod_setNodeID(0,1,"Node2");
    ERR = ERR && assertIntEqual(err, 0);
    id1 = Iod_getNodeID(0, 1);
    char *id3 = "Node2";
    ERR = ERR && (strcmp(id1, id3) == 0);

    err = Iod_setNodeID(-1, 1, "Node2");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeID(3, 1, "Node2");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeID(1, -1, "Node2");
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_setNodeID(1, 1, "Node2");
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_setNodeID(0, 1, "node1");
    ERR = ERR && assertIntEqual(err, -3);
    err = Iod_setNodeID(0, 1, "node3");
    ERR = ERR && assertIntEqual(err, -3);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    id1 = Iod_getNodeID(0, 1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    ERR = ERR && (strcmp(id1, id2) == 0);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    id1 = Iod_getNodeID(0, 1);
    ERR = ERR && (strcmp(id1, id3) == 0);

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

void test_setNodeCoordinateAndSize()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, 0);
    float f1 = Iod_getNodeH(0,1);
    ERR = ERR && Iod_floatEqual(f1, 6.4, 0.01);

    err = Iod_setNodeCoordinateAndSize(-1, 1, 1.2, 3.2, 2.5, 4.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeCoordinateAndSize(3, 1, 1.2, 3.2, 2.5, 4.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeCoordinateAndSize(1, -1, 1.2, 3.2, 2.5, 4.1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_setNodeCoordinateAndSize(1, 4, 1.2, 3.2, 2.5, 4.1);
    ERR = ERR && assertIntEqual(err, -7);

    err = Iod_setNodeCoordinateAndSize(0, 1, -1, 2.5, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, -1, 5.4, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, 2.5, -1, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, 2.5, 0, 6.4);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, 2.5, 5.4, -1);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeCoordinateAndSize(0, 1, 1.1, 2.5, 5.4, 0);
    ERR = ERR && assertIntEqual(err, -12);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    f1 = Iod_getNodeH(0, 1);
    ERR = ERR && Iod_floatEqual(f1, 4.1, 0.01);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    f1 = Iod_getNodeH(0, 1);
    ERR = ERR && Iod_floatEqual(f1, 6.4, 0.01);

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

void test_setNodeFillColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1 = Iod_getNodeFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    int err = Iod_setNodeFillColor(0, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'
    
    err = Iod_setNodeFillColor(-1, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeFillColor(3, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeFillColor(0, -1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_setNodeFillColor(0, 4, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -7);

    err = Iod_setNodeFillColor(0, 1, -1, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 256, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, -1, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, 256, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, 180, -1, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, 180, 256, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, 180, 160, -1);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeFillColor(0, 1, 30, 180, 160, 256);
    ERR = ERR && assertIntEqual(err, -12);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'

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

void test_setNodeOutlineColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1 = Iod_getNodeOutlineColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4284764415); //hex: '0xff6450ff'
    int err = Iod_setNodeOutlineColor(0, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeOutlineColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'

    err = Iod_setNodeOutlineColor(-1, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeOutlineColor(3, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setNodeOutlineColor(0, -1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_setNodeOutlineColor(0, 4, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -7);

    err = Iod_setNodeOutlineColor(0, 1, -1, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 256, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, -1, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, 256, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, 180, -1, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, 180, 256, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, 180, 160, -1);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setNodeOutlineColor(0, 1, 30, 180, 160, 256);
    ERR = ERR && assertIntEqual(err, -12);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeOutlineColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4284764415); //hex: '0xff6450ff'
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getNodeOutlineColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'

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

void test_setNodeOutlineThickness()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

   int t1 = Iod_getNodeOutlineThickness(0,1);
   ERR = ERR && assertIntEqual(t1, 3);
   int err = Iod_setNodeOutlineThickness(0,1,1);
   ERR = ERR && assertIntEqual(err, 0);
   t1 = Iod_getNodeOutlineThickness(0, 1);
   ERR = ERR && assertIntEqual(t1, 1);

   err = Iod_setNodeOutlineThickness(-1, 1, 1);
   ERR = ERR && assertIntEqual(err, -5);
   err = Iod_setNodeOutlineThickness(3, 1, 1);
   ERR = ERR && assertIntEqual(err, -5);
   err = Iod_setNodeOutlineThickness(0, -1, 1);
   ERR = ERR && assertIntEqual(err, -7);
   err = Iod_setNodeOutlineThickness(0, 4, 1);
   ERR = ERR && assertIntEqual(err, -7);
   err = Iod_setNodeOutlineThickness(0, 1, 0);
   ERR = ERR && assertIntEqual(err, -12);
   err = Iod_setNodeOutlineThickness(0, 1, -1);
   ERR = ERR && assertIntEqual(err, -12);

   err = Iod_redo();
   ERR = ERR && assertIntEqual(err, -9);
   err = Iod_undo();
   ERR = ERR && assertIntEqual(err, 0);
   t1 = Iod_getNodeOutlineThickness(0, 1);
   ERR = ERR && assertIntEqual(t1, 3);
   err = Iod_redo();
   ERR = ERR && assertIntEqual(err, 0);
   t1 = Iod_getNodeOutlineThickness(0, 1);
   ERR = ERR && assertIntEqual(t1, 1);

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

void test_setup3()
{
    Iod_newNetwork("network1");
    Iod_addNode(0, "node1", 1.1, 2.5, 5.4, 6.4);
    Iod_addNode(0, "node2", 1.2, 3.2, 2.5, 4.1);
    Iod_addNode(0, "node3", 2.2, 3.1, 1.5, 4.5);
    Iod_addNode(0, "node4", 7.2, 3.5, 1.6, 4.8);
    Iod_createBiBi(0, "Rea1", "k1*A", 0, 1, 2, 3, 1.1, 2.2, 3.3, 4.4);
    Iod_createBiBi(0, "Rea2", "k2*A", 1, 3, 0, 2, 2.1, 5.2, 8.3, 7.4);
}

void test_createReaction()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_createReaction(0,"Rea3");
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea1", "Rea2", "Rea3"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    
    err = Iod_createReaction(0, "Rea1");
    ERR = ERR && assertIntEqual(err, -3);
    err = Iod_createReaction(-1, "Rea4");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_createReaction(1, "Rea4");
    ERR = ERR && assertIntEqual(err, -5);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List3[100] = {"Rea1", "Rea2"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
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

void test_getReactionIndex()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int index1 = Iod_getReactionIndex(0,"Rea1");
    ERR = ERR && assertIntEqual(index1, 0);
    int err = Iod_getReactionIndex(-1, "Rea1");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getReactionIndex(1, "Rea1");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getReactionIndex(0, "Rea3");
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

void test_deleteReaction()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_deleteReaction(0,0);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea2"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_deleteReaction(-1, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteReaction(1, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteReaction(0, -1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_deleteReaction(0, 1);
    ERR = ERR && assertIntEqual(err, -6);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List3[100] = {"Rea1", "Rea2"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
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

void test_clearReactions()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea1", "Rea2"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    int err = Iod_clearReactions(0);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    char *List3[100] = {};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionIDs(0);
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

void test_getNumberOfReactions()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num = Iod_getNumberOfReactions(0);
    ERR = ERR && assertIntEqual(num, 2);
    int err = Iod_getNumberOfReactions(-1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getNumberOfReactions(1);
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

void test_getReactionID()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *id1 = Iod_getReactionID(0, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    char *id2 = "Rea1";
    ERR = ERR && (strcmp(id1, id2) == 0);
    id1 = Iod_getReactionID(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    id1 = Iod_getReactionID(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    id1 = Iod_getReactionID(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    id1 = Iod_getReactionID(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getListOfReactionIDs()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea1", "Rea2"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    List1 = Iod_getListOfReactionIDs(-1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionIDs(1);
    err = Iod_getErrorCode();
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

void test_getReactionRateLaw()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *str1 = Iod_getReactionRateLaw(0, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    char *str2 = "k1*A";
    ERR = ERR && (strcmp(str1, str2) == 0);
    str1 = Iod_getReactionRateLaw(-1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    str1 = Iod_getReactionRateLaw(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    str1 = Iod_getReactionRateLaw(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    str1 = Iod_getReactionRateLaw(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getReactionFillColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1 = Iod_getReactionFillColor(0, 0);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    color1 = Iod_getReactionFillColor(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getReactionFillColor(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    color1 = Iod_getReactionFillColor(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    color1 = Iod_getReactionFillColor(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getReactionLineThickness()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int t1 = Iod_getReactionLineThickness(0,0);
    ERR = ERR && assertIntEqual(t1, 3);
    int err = Iod_getReactionLineThickness(-1, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getReactionLineThickness(1, 0);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_getReactionLineThickness(0, -1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_getReactionLineThickness(0, 2);
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getReactionSrcNodeStoich()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    float s1 = Iod_getReactionSrcNodeStoich(0,1,"node4");
    ERR = ERR && Iod_floatEqual(s1, 5.20, 0.01);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    s1 = Iod_getReactionSrcNodeStoich(-1, 0, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    s1 = Iod_getReactionSrcNodeStoich(1, 0, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    s1 = Iod_getReactionSrcNodeStoich(0, -1, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    s1 = Iod_getReactionSrcNodeStoich(0, 2, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    s1 = Iod_getReactionSrcNodeStoich(0, 0, "node");
    err = Iod_getErrorCode();
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

void test_getReactionDestNodeStoich()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    float s1 = Iod_getReactionDestNodeStoich(0, 1, "node3");
    ERR = ERR && Iod_floatEqual(s1, 7.40, 0.01);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    s1 = Iod_getReactionDestNodeStoich(-1, 0, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    s1 = Iod_getReactionDestNodeStoich(1, 0, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    s1 = Iod_getReactionDestNodeStoich(0, -1, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    s1 = Iod_getReactionDestNodeStoich(0, 2, "node1");
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    s1 = Iod_getReactionDestNodeStoich(0, 0, "node");
    err = Iod_getErrorCode();
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

void test_getNumberOfSrcNodes()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num = Iod_getNumberOfSrcNodes(0,1);
    ERR = ERR && assertIntEqual(num, 2);
    Iod_addSrcNode(0, 1, 2, 3.1);
    num = Iod_getNumberOfSrcNodes(0, 1);
    ERR = ERR && assertIntEqual(num, 3);
    num = Iod_getNumberOfSrcNodes(-1, 0);
    ERR = ERR && assertIntEqual(num, -5);
    num = Iod_getNumberOfSrcNodes(1, 0);
    ERR = ERR && assertIntEqual(num, -5);
    num = Iod_getNumberOfSrcNodes(0, -1);
    ERR = ERR && assertIntEqual(num, -6);
    num = Iod_getNumberOfSrcNodes(0, 2);
    ERR = ERR && assertIntEqual(num, -6);

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

void test_getNumberOfDestNodes()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int num = Iod_getNumberOfDestNodes(0, 1);
    ERR = ERR && assertIntEqual(num, 2);
    Iod_addDestNode(0, 1, 1, 5.5);
    num = Iod_getNumberOfDestNodes(0, 1);
    ERR = ERR && assertIntEqual(num, 3);
    num = Iod_getNumberOfDestNodes(-1, 0);
    ERR = ERR && assertIntEqual(num, -5);
    num = Iod_getNumberOfDestNodes(1, 0);
    ERR = ERR && assertIntEqual(num, -5);
    num = Iod_getNumberOfDestNodes(0, -1);
    ERR = ERR && assertIntEqual(num, -6);
    num = Iod_getNumberOfDestNodes(0, 2);
    ERR = ERR && assertIntEqual(num, -6);

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

void test_getListOfReactionSrcNodes()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfReactionSrcNodes(0,1);
    char *List2[100] = {"node2", "node4"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    Iod_addSrcNode(0, 1, 2, 3.1);
    List1 = Iod_getListOfReactionSrcNodes(0, 1);
    char *List3[100] = {"node2", "node3", "node4"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    List1 = Iod_getListOfReactionSrcNodes(-1,0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionSrcNodes(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionSrcNodes(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    List1 = Iod_getListOfReactionSrcNodes(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getListOfReactionDestNodes()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfReactionDestNodes(0, 1);
    char *List2[100] = {"node1", "node3"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    Iod_addDestNode(0, 1, 1, 5.5);
    List1 = Iod_getListOfReactionDestNodes(0, 1);
    char *List3[100] = {"node1", "node2", "node3"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    List1 = Iod_getListOfReactionDestNodes(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionDestNodes(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionDestNodes(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    List1 = Iod_getListOfReactionDestNodes(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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

void test_getListOfReactionSrcStoich()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    float *List1;

    List1 = Iod_getListOfReactionSrcStoich(0, 1);
    float List2[100] = {2.1, 5.2};
    ERR = ERR && Iod_floatArrayEqual(List1, &List2[0], 0.01);
    List1 = Iod_getListOfReactionSrcStoich(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionSrcStoich(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionSrcStoich(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    List1 = Iod_getListOfReactionSrcStoich(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
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

void test_getListOfReactionDestStoich()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    float *List1;

    List1 = Iod_getListOfReactionDestStoich(0, 1);
    float List2[100] = {8.3, 7.4};
    ERR = ERR && Iod_floatArrayEqual(List1, &List2[0], 0.01);
    List1 = Iod_getListOfReactionDestStoich(-1, 0);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionDestStoich(1, 0);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -5);
    List1 = Iod_getListOfReactionDestStoich(0, -1);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);
    List1 = Iod_getListOfReactionDestStoich(0, 2);
    err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, -6);

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



void test_setup4()
{
    Iod_newNetwork("network1");
    Iod_addNode(0, "node1", 1.1, 2.5, 5.4, 6.4);
    Iod_addNode(0, "node2", 1.2, 3.2, 2.5, 4.1);
    Iod_addNode(0, "node3", 2.2, 3.1, 1.5, 4.5);
    Iod_addNode(0, "node4", 7.2, 3.5, 1.6, 4.8);
    Iod_addNode(0, "node5", 6.4, 7.1, 9.9, 1.2);
    Iod_addNode(0, "node6", 5.8, 7.3, 4.5, 6.2);
    Iod_createBiBi(0, "Rea1", "k1*A", 0, 1, 2, 3, 1.1, 2.2, 3.3, 4.4);
    Iod_createBiBi(0, "Rea2", "k2*A", 1, 3, 0, 2, 2.1, 5.2, 8.3, 7.4);
}

void test_addSrcNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_addSrcNode(0, 0, 4, 5.1);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 0);
    char *List2[100] = {"node1", "node2", "node5"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_addSrcNode(-1, 0, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_addSrcNode(1, 0, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_addSrcNode(0, -1, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_addSrcNode(0, 2, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_addSrcNode(0, 0, -1, 1.1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_addSrcNode(0, 0, 6, 1.1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_addSrcNode(0, 0, 3, -1);
    ERR = ERR && assertIntEqual(err, -8);
    err = Iod_addSrcNode(0, 0, 3, 0);
    ERR = ERR && assertIntEqual(err, -8);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 0);
    char *List3[100] = {"node1", "node2"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 0);
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

void test_addDestNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    int err = Iod_addDestNode(0, 0, 4, 5.1);
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 0);
    char *List2[100] = {"node3", "node4", "node5"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_addDestNode(-1, 0, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_addDestNode(1, 0, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_addDestNode(0, -1, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_addDestNode(0, 2, 3, 1.1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_addDestNode(0, 0, -1, 1.1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_addDestNode(0, 0, 6, 1.1);
    ERR = ERR && assertIntEqual(err, -7);
    err = Iod_addDestNode(0, 0, 3, -1);
    ERR = ERR && assertIntEqual(err, -8);
    err = Iod_addDestNode(0, 0, 3, 0);
    ERR = ERR && assertIntEqual(err, -8);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 0);
    char *List3[100] = {"node3", "node4"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 0);
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

void test_deleteSrcNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    Iod_addSrcNode(0, 1, 4, 5.5);
    Iod_addSrcNode(0, 1, 2, 5.6);
    List1 = Iod_getListOfReactionSrcNodes(0, 1);
    char *List2[100] = {"node2", "node3", "node4", "node5"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    int err = Iod_deleteSrcNode(0, 1, "node2");
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 1);
    char *List3[100] = {"node3", "node4", "node5"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_deleteSrcNode(-1, 1, "node4");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteSrcNode(1, 1, "node4");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteSrcNode(0, -1, "node4");
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_deleteSrcNode(0, 2, "node4");
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_deleteSrcNode(0, 1, "node2");
    ERR = ERR && assertIntEqual(err, -2);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 1);
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionSrcNodes(0, 1);
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

void test_deleteDestNode()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    Iod_addDestNode(0, 1, 5, 5.3);
    List1 = Iod_getListOfReactionDestNodes(0, 1);
    char *List2[100] = {"node1", "node3", "node6"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    int err = Iod_deleteDestNode(0, 1, "node1");
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 1);
    char *List3[100] = {"node3", "node6"};
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);

    err = Iod_deleteDestNode(-1, 1, "node4");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteDestNode(1, 1, "node4");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_deleteDestNode(0, -1, "node4");
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_deleteDestNode(0, 2, "node4");
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_deleteDestNode(0, 1, "node5");
    ERR = ERR && assertIntEqual(err, -2);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 1);
    equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    List1 = Iod_getListOfReactionDestNodes(0, 1);
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

void test_setRateLaw()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    char *str1 = Iod_getReactionRateLaw(0, 1);
    int err = Iod_getErrorCode();
    ERR = ERR && assertIntEqual(err, 0);
    char *str2 = "k2*A";
    ERR = ERR && (strcmp(str1, str2) == 0);
    err = Iod_setRateLaw(0, 1,  "ABC");
    ERR = ERR && assertIntEqual(err, 0);
    char *str3 = "ABC";
    str1 = Iod_getReactionRateLaw(0, 1);
    ERR = ERR && (strcmp(str1, str3) == 0);

    err = Iod_setRateLaw(-1, 1, "ABC");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setRateLaw(1, 1, "ABC");
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setRateLaw(0, -1, "ABC");
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_setRateLaw(0, 2, "ABC");
    ERR = ERR && assertIntEqual(err, -6);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    str1 = Iod_getReactionRateLaw(0, 1);
    ERR = ERR && (strcmp(str1, str2) == 0);
    err = Iod_redo();
    str1 = Iod_getReactionRateLaw(0, 1);
    ERR = ERR && (strcmp(str1, str3) == 0);

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

void test_setReactionFillColor()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    unsigned color1 = Iod_getReactionFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    int err = Iod_setReactionFillColor(0, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getReactionFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'
    err = Iod_setReactionFillColor(-1, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setReactionFillColor(3, 1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setReactionFillColor(0, -1, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_setReactionFillColor(0, 4, 30, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -6);

    err = Iod_setReactionFillColor(0, 1, -1, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 256, 180, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, -1, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, 256, 160, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, 180, -1, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, 180, 256, 255);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, 180, 160, -1);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionFillColor(0, 1, 30, 180, 160, 256);
    ERR = ERR && assertIntEqual(err, -12);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getReactionFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 4288041215); //hex: '0xff9650ff'
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    color1 = Iod_getReactionFillColor(0, 1);
    ERR = ERR && assertIntEqual((int)color1, 515154175); //hex: '0x1eb4a0ff'

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

void test_setReactionLineThickness()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int t1= Iod_getReactionLineThickness(0,1);
    ERR = ERR && assertIntEqual(t1, 3);
    int err = Iod_setReactionLineThickness(0,1,1);
    ERR = ERR && assertIntEqual(err, 0);
    t1 = Iod_getReactionLineThickness(0, 1);
    ERR = ERR && assertIntEqual(t1, 1);

    err = Iod_setReactionLineThickness(-1, 1, 1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setReactionLineThickness(3, 1, 1);
    ERR = ERR && assertIntEqual(err, -5);
    err = Iod_setReactionLineThickness(0, -1, 1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_setReactionLineThickness(0, 4, 1);
    ERR = ERR && assertIntEqual(err, -6);
    err = Iod_setReactionLineThickness(0, 1, 0);
    ERR = ERR && assertIntEqual(err, -12);
    err = Iod_setReactionLineThickness(0, 1, -1);
    ERR = ERR && assertIntEqual(err, -12);

    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, -9);
    err = Iod_undo();
    ERR = ERR && assertIntEqual(err, 0);
    t1 = Iod_getReactionLineThickness(0, 1);
    ERR = ERR && assertIntEqual(t1, 3);
    err = Iod_redo();
    ERR = ERR && assertIntEqual(err, 0);
    t1 = Iod_getReactionLineThickness(0, 1);
    ERR = ERR && assertIntEqual(t1, 1);

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

void test_saveNetworkAsJSON_readNetworkFromJSON()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;

    int err= Iod_saveNetworkAsJSON(0, "../JSON_files/testfile.json");
    ERR = ERR && assertIntEqual(err, 0);
    err = Iod_readNetworkFromJSON("../JSON_files/testfile1.json");
    ERR = ERR && assertIntEqual(err, 0);
    err = Iod_readNetworkFromJSON("testfdfjsd.json");
    ERR = ERR && assertIntEqual(err, -11);
    err = Iod_readNetworkFromJSON("../JSON_files/testfile1.json");
    ERR = ERR && assertIntEqual(err, -3);

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

void test_startGroup_endGroup()
{
    COUNT_FUNCTIONS++;
    bool ERR = TRUE;
    char **List1;

    List1 = Iod_getListOfReactionIDs(0);
    char *List2[100] = {"Rea1", "Rea2"};
    bool equal1 = Iod_strArrayEqual(List1, &List2[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    Iod_undo();
    char *List3[100] = {"Rea1"};
    List1 = Iod_getListOfReactionIDs(0);
    equal1 = Iod_strArrayEqual(List1, &List3[0]);
    ERR = ERR && assertIntEqual(equal1, 1);
    Iod_startGroup();
    int err = Iod_createReaction(0,"rea2");
    ERR = ERR && assertIntEqual(err, 0);
    err = Iod_addSrcNode(0, 0, 4, 5.1);
    ERR = ERR && assertIntEqual(err, 0);
    Iod_endGroup();
    Iod_undo();
    List1 = Iod_getListOfReactionIDs(0);
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
    test_getNodeCoordinateAndSize,
    test_getNodeFillColor,
    test_getNodeOutlineColor,
    test_getNodeOutlineThickness,
    test_setNodeID,
    test_setNodeCoordinateAndSize,
    test_setNodeFillColor,
    test_setNodeOutlineColor,
    test_setNodeOutlineThickness,
};

void (*func_array3[])() = {
    test_createReaction,
    test_getReactionIndex,
    test_deleteReaction,
    test_clearReactions,
    test_getNumberOfReactions,
    test_getReactionID,
    test_getListOfReactionIDs,
    test_getReactionRateLaw,
    test_getReactionFillColor,
    test_getReactionLineThickness,
    test_getReactionSrcNodeStoich,
    test_getReactionDestNodeStoich,
    test_getNumberOfSrcNodes,
    test_getNumberOfDestNodes,
    test_getListOfReactionSrcNodes,
    test_getListOfReactionDestNodes,
    test_getListOfReactionSrcStoich,
    test_getListOfReactionDestStoich,
};

void (*func_array4[])() = {
    test_addSrcNode,
    test_addDestNode,
    test_deleteSrcNode,
    test_deleteDestNode,
    test_setRateLaw,
    test_setReactionFillColor,
    test_setReactionLineThickness,
    test_saveNetworkAsJSON_readNetworkFromJSON,
    test_startGroup_endGroup,
};

int main(void)
{
    int err;
    int i;
    int func_array1_size = sizeof(func_array1) / sizeof(func_array1[0]);
    int func_array2_size = sizeof(func_array2) / sizeof(func_array2[0]);
    int func_array3_size = sizeof(func_array3) / sizeof(func_array3[0]);
    int func_array4_size = sizeof(func_array4) / sizeof(func_array4[0]);
    err = loadDll("../Iodine_Dll/Iodine.dll");
    if (err != 0)
    {
        printf(Iod_getErrorMessage(err));
        //two possible results: "can't find function in dll"; "Iodine DLL missing";
        return err;
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

    for (i = 0; i < func_array3_size; i++)
    {
        test_setup3();
        (func_array3[i])();
        test_tear_down();
    }

    for (i = 0; i < func_array4_size; i++)
    {
        test_setup4();
        (func_array4[i])();
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