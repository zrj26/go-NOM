#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
HINSTANCE Iod_hinstLib;
typedef int (*getErrorCodeProc)();
typedef int (*undoProc)();
typedef int (*redoProc)();
typedef int (*newNetworkProc)(const char *netID);
typedef int (*getNetworkIndexProc)(const char *netID);
typedef int (*saveNetworkAsJSONProc)(int netIndex, const char *fileName);
typedef int (*readNetworkFromJSONProc)(const char *path);
typedef int (*deleteNetworkProc)(int netIndex);
typedef void (*clearNetworksProc)();
typedef int (*getNumberOfNetworksProc)();
typedef char *(*getNetworkIDProc)(int netIndex);
typedef int (*addNodeProc)(int netIndex, const char *nodeName, float x, float y, float w, float h);
typedef int (*getNodeIndexProc)(int netIndex, const char *nodeID);
typedef int (*deleteNodeProc)(int netIndex, int nodeIndex);
typedef int (*clearNetworkProc)(int netIndex);
typedef int (*getNumberOfNodesProc)(int netIndex);
typedef float (*getNodeCenterXProc)(int netIndex, int nodeIndex);
typedef float (*getNodeCenterYProc)(int netIndex, int nodeIndex);
typedef char *(*getNodeIDProc)(int netIndex, int nodeIndex);
typedef float (*getNodeXProc)(int netIndex, int nodeIndex);
typedef float (*getNodeYProc)(int netIndex, int nodeIndex);
typedef float (*getNodeWProc)(int netIndex, int nodeIndex);
typedef float (*getNodeHProc)(int netIndex, int nodeIndex);
typedef unsigned int (*getNodeFillColorProc)(int netIndex, int nodeIndex);
typedef unsigned int (*getNodeOutlineColorProc)(int netIndex, int nodeIndex);
typedef int (*getNodeOutlineThicknessProc)(int netIndex, int nodeIndex);
typedef int (*setNodeIDProc)(int netIndex, int nodeIndex, const char *newID);
typedef int (*setNodeCoordinateAndSizeProc)(int netIndex, int nodeIndex, float x, float y, float w, float h);
typedef int (*setNodeFillColorProc)(int netIndex, int nodeIndex, int R, int G, int B, int A);
typedef int (*setNodeOutlineColorProc)(int netIndex, int nodeIndex, int R, int G, int B, int A);
typedef int (*setNodeOutlineThicknessProc)(int netIndex, int nodeIndex, int thickness);
typedef int (*createReactionProc)(int netIndex, const char *reactionID);
typedef int (*getReactionIndexProc)(int netIndex, const char *reactionID);
typedef int (*deleteReactionProc)(int netIndex, int reactionIndex);
typedef int (*clearReactionsProc)(int netIndex);
typedef int (*getNumberOfReactionsProc)(int netIndex);
typedef char *(*getReactionIDProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionRateLawProc)(int netIndex, int reactionIndex);
typedef unsigned int (*getReactionFillColorProc)(int netIndex, int reactionIndex);
typedef int (*getReactionLineThicknessProc)(int netIndex, int reactionIndex);
typedef float (*getReactionSrcNodeStoichProc)(int netIndex, int reactionIndex, const char *srcNodeID);
typedef float (*getReactionDestNodeStoichProc)(int netIndex, int reactionIndex, const char *destNodeID);
typedef int (*getNumberOfSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getNumberOfDestNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionDestNodesProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionNodeIDProc)(int index);
typedef int (*addSrcNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*addDestNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*deleteSrcNodeProc)(int netIndex, int reactionIndex, const char *nodeID);
typedef int (*deleteDestNodeProc)(int netIndex, int reactionIndex, const char *nodeID);
typedef int (*setRateLawProc)(int netIndex, int reactionIndex, const char *rateLaw);
typedef int (*setReactionFillColorProc)(int netIndex, int reactionIndex, int R, int G, int B, int A);
typedef int (*setReactionLineThicknessProc)(int netIndex, int reactionIndex, int thickness);

getErrorCodeProc Iod_getErrorCode;
undoProc Iod_undo;
redoProc Iod_redo;
newNetworkProc Iod_newNetwork;
getNetworkIndexProc Iod_getNetworkIndex;
saveNetworkAsJSONProc Iod_saveNetworkAsJSON;
readNetworkFromJSONProc Iod_readNetworkFromJSON;
deleteNetworkProc Iod_deleteNetwork;
clearNetworksProc Iod_clearNetworks;
getNumberOfNetworksProc Iod_getNumberOfNetworks;
getNetworkIDProc Iod_getNetworkID;
addNodeProc Iod_addNode;
getNodeIndexProc Iod_getNodeIndex;
deleteNodeProc Iod_deleteNode;
clearNetworkProc Iod_clearNetwork;
getNumberOfNodesProc Iod_getNumberOfNodes;
getNodeCenterXProc Iod_getNodeCenterX;
getNodeCenterYProc Iod_getNodeCenterY;
getNodeIDProc Iod_getNodeID;
getNodeXProc Iod_getNodeX;
getNodeYProc Iod_getNodeY;
getNodeWProc Iod_getNodeW;
getNodeHProc Iod_getNodeH;
getNodeFillColorProc Iod_getNodeFillColor;
getNodeOutlineColorProc Iod_getNodeOutlineColor;
getNodeOutlineThicknessProc Iod_getNodeOutlineThickness;
setNodeIDProc Iod_setNodeID;
setNodeCoordinateAndSizeProc Iod_setNodeCoordinateAndSize;
setNodeFillColorProc Iod_setNodeFillColor;
setNodeOutlineColorProc Iod_setNodeOutlineColor;
setNodeOutlineThicknessProc Iod_setNodeOutlineThickness;
createReactionProc Iod_createReaction;
getReactionIndexProc Iod_getReactionIndex;
deleteReactionProc Iod_deleteReaction;
clearReactionsProc Iod_clearReactions;
getNumberOfReactionsProc Iod_getNumberOfReactions;
getReactionIDProc Iod_getReactionID;
getReactionRateLawProc Iod_getReactionRateLaw;
getReactionFillColorProc Iod_getReactionFillColor;
getReactionLineThicknessProc Iod_getReactionLineThickness;
getReactionSrcNodeStoichProc Iod_getReactionSrcNodeStoich;
getReactionDestNodeStoichProc Iod_getReactionDestNodeStoich;
getNumberOfSrcNodesProc Iod_getNumberOfSrcNodes;
getNumberOfDestNodesProc Iod_getNumberOfDestNodes;
getListOfReactionSrcNodesProc getListOfReactionSrcNodes;
getListOfReactionDestNodesProc getListOfReactionDestNodes;
getReactionNodeIDProc getReactionNodeID;
addSrcNodeProc Iod_addSrcNode;
addDestNodeProc Iod_addDestNode;
deleteSrcNodeProc Iod_deleteSrcNode;
deleteDestNodeProc Iod_deleteDestNode;
setRateLawProc Iod_setRateLaw;
setReactionFillColorProc Iod_setReactionFillColor;
setReactionLineThicknessProc Iod_setReactionLineThickness;

const char *Iod_getErrorMessage(int errCode)
{
    switch (errCode)
    {
    case 0:
        return "ok";
    case -1:
        return "other";
    case -2:
        return "id not found: ";
    case -3:
        return "id repeat: ";
    case -4:
        return "node is not free: ";
    case -5:
        return "net index out of range: ";
    case -6:
        return "reaction index out of range: ";
    case -7:
        return "node index out of range: ";
    case -8:
        return "wrong stoich: stoich has to be positive: ";
    case -9:
        return "stack is empty";
    case -10:
        return "Json convert error";
    case -11:
        return "File error";
    case -12:
        return "Variable out of range: ";
    case -13:
        return "Loading DLL error";
    default:
        return "Other error";
    }
}

// Returns TRUE if successful load dll file and all functions in it.
// else returns FALSE
bool loadDll(int *errorCode)
{
    Iod_hinstLib = LoadLibrary("../Iodine_Dll/Iodine.dll");
    if (Iod_hinstLib == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }

    Iod_getErrorCode = (getErrorCodeProc)GetProcAddress(Iod_hinstLib, "getErrorCode");
    if (Iod_getErrorCode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }

    Iod_undo = (undoProc)GetProcAddress(Iod_hinstLib, "undo");
    if (Iod_undo == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_redo = (redoProc)GetProcAddress(Iod_hinstLib, "redo");
    if (Iod_redo == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_newNetwork = (newNetworkProc)GetProcAddress(Iod_hinstLib, "newNetwork");
    if (Iod_newNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNetworkIndex = (getNetworkIndexProc)GetProcAddress(Iod_hinstLib, "getNetworkIndex");
    if (Iod_getNetworkIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_saveNetworkAsJSON = (saveNetworkAsJSONProc)GetProcAddress(Iod_hinstLib, "saveNetworkAsJSON");
    if (Iod_saveNetworkAsJSON == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_readNetworkFromJSON = (readNetworkFromJSONProc)GetProcAddress(Iod_hinstLib, "readNetworkFromJSON");
    if (Iod_readNetworkFromJSON == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_deleteNetwork = (deleteNetworkProc)GetProcAddress(Iod_hinstLib, "deleteNetwork");
    if (Iod_deleteNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_clearNetworks = (clearNetworksProc)GetProcAddress(Iod_hinstLib, "clearNetworks");
    if (Iod_clearNetworks == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNumberOfNetworks = (getNumberOfNetworksProc)GetProcAddress(Iod_hinstLib, "getNumberOfNetworks");
    if (Iod_getNumberOfNetworks == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNetworkID = (getNetworkIDProc)GetProcAddress(Iod_hinstLib, "getNetworkID");
    if (Iod_getNetworkID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_addNode = (addNodeProc)GetProcAddress(Iod_hinstLib, "addNode");
    if (Iod_addNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeIndex = (getNodeIndexProc)GetProcAddress(Iod_hinstLib, "getNodeIndex");
    if (Iod_getNodeIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_deleteNode = (deleteNodeProc)GetProcAddress(Iod_hinstLib, "deleteNode");
    if (Iod_deleteNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_clearNetwork = (clearNetworkProc)GetProcAddress(Iod_hinstLib, "clearNetwork");
    if (Iod_clearNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNumberOfNodes = (getNumberOfNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfNodes");
    if (Iod_getNumberOfNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeCenterX = (getNodeCenterXProc)GetProcAddress(Iod_hinstLib, "getNodeCenterX");
    if (Iod_getNodeCenterX == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeCenterY = (getNodeCenterYProc)GetProcAddress(Iod_hinstLib, "getNodeCenterY");
    if (Iod_getNodeCenterY == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeID = (getNodeIDProc)GetProcAddress(Iod_hinstLib, "getNodeID");
    if (Iod_getNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeX = (getNodeXProc)GetProcAddress(Iod_hinstLib, "getNodeX");
    if (Iod_getNodeX == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeY = (getNodeYProc)GetProcAddress(Iod_hinstLib, "getNodeY");
    if (Iod_getNodeY == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeW = (getNodeWProc)GetProcAddress(Iod_hinstLib, "getNodeW");
    if (Iod_getNodeW == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeH = (getNodeHProc)GetProcAddress(Iod_hinstLib, "getNodeH");
    if (Iod_getNodeH == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeFillColor = (getNodeFillColorProc)GetProcAddress(Iod_hinstLib, "getNodeFillColor");
    if (Iod_getNodeFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeOutlineColor = (getNodeOutlineColorProc)GetProcAddress(Iod_hinstLib, "getNodeOutlineColor");
    if (Iod_getNodeOutlineColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNodeOutlineThickness = (getNodeOutlineThicknessProc)GetProcAddress(Iod_hinstLib, "getNodeOutlineThickness");
    if (Iod_getNodeOutlineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setNodeID = (setNodeIDProc)GetProcAddress(Iod_hinstLib, "setNodeID");
    if (Iod_setNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setNodeCoordinateAndSize = (setNodeCoordinateAndSizeProc)GetProcAddress(Iod_hinstLib, "setNodeCoordinateAndSize");
    if (Iod_setNodeCoordinateAndSize == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setNodeFillColor = (setNodeFillColorProc)GetProcAddress(Iod_hinstLib, "setNodeFillColor");
    if (Iod_setNodeFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setNodeOutlineColor = (setNodeOutlineColorProc)GetProcAddress(Iod_hinstLib, "setNodeOutlineColor");
    if (Iod_setNodeOutlineColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setNodeOutlineThickness = (setNodeOutlineThicknessProc)GetProcAddress(Iod_hinstLib, "setNodeOutlineThickness");
    if (Iod_setNodeOutlineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_createReaction = (createReactionProc)GetProcAddress(Iod_hinstLib, "createReaction");
    if (Iod_createReaction == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionIndex = (getReactionIndexProc)GetProcAddress(Iod_hinstLib, "getReactionIndex");
    if (Iod_getReactionIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_deleteReaction = (deleteReactionProc)GetProcAddress(Iod_hinstLib, "deleteReaction");
    if (Iod_deleteReaction == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_clearReactions = (clearReactionsProc)GetProcAddress(Iod_hinstLib, "clearReactions");
    if (Iod_clearReactions == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNumberOfReactions = (getNumberOfReactionsProc)GetProcAddress(Iod_hinstLib, "getNumberOfReactions");
    if (Iod_getNumberOfReactions == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionID = (getReactionIDProc)GetProcAddress(Iod_hinstLib, "getReactionID");
    if (Iod_getReactionID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionRateLaw = (getReactionRateLawProc)GetProcAddress(Iod_hinstLib, "getReactionRateLaw");
    if (Iod_getReactionRateLaw == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionFillColor = (getReactionFillColorProc)GetProcAddress(Iod_hinstLib, "getReactionFillColor");
    if (Iod_getReactionFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionLineThickness = (getReactionLineThicknessProc)GetProcAddress(Iod_hinstLib, "getReactionLineThickness");
    if (Iod_getReactionLineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionSrcNodeStoich = (getReactionSrcNodeStoichProc)GetProcAddress(Iod_hinstLib, "getReactionSrcNodeStoich");
    if (Iod_getReactionSrcNodeStoich == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getReactionDestNodeStoich = (getReactionDestNodeStoichProc)GetProcAddress(Iod_hinstLib, "getReactionDestNodeStoich");
    if (Iod_getReactionDestNodeStoich == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNumberOfSrcNodes = (getNumberOfSrcNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfSrcNodes");
    if (Iod_getNumberOfSrcNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_getNumberOfDestNodes = (getNumberOfDestNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfDestNodes");
    if (Iod_getNumberOfDestNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getListOfReactionSrcNodes = (getListOfReactionSrcNodesProc)GetProcAddress(Iod_hinstLib, "getListOfReactionSrcNodes");
    if (getListOfReactionSrcNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getListOfReactionDestNodes = (getListOfReactionDestNodesProc)GetProcAddress(Iod_hinstLib, "getListOfReactionDestNodes");
    if (getListOfReactionDestNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionNodeID = (getReactionNodeIDProc)GetProcAddress(Iod_hinstLib, "getReactionNodeID");
    if (getReactionNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_addSrcNode = (addSrcNodeProc)GetProcAddress(Iod_hinstLib, "addSrcNode");
    if (Iod_addSrcNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_addDestNode = (addDestNodeProc)GetProcAddress(Iod_hinstLib, "addDestNode");
    if (Iod_addDestNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_deleteSrcNode = (deleteSrcNodeProc)GetProcAddress(Iod_hinstLib, "deleteSrcNode");
    if (Iod_deleteSrcNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_deleteDestNode = (deleteDestNodeProc)GetProcAddress(Iod_hinstLib, "deleteDestNode");
    if (Iod_deleteDestNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setRateLaw = (setRateLawProc)GetProcAddress(Iod_hinstLib, "setRateLaw");
    if (Iod_setRateLaw == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setReactionFillColor = (setReactionFillColorProc)GetProcAddress(Iod_hinstLib, "setReactionFillColor");
    if (Iod_setReactionFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    Iod_setReactionLineThickness = (setReactionLineThicknessProc)GetProcAddress(Iod_hinstLib, "setReactionLineThickness");
    if (Iod_setReactionLineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    return TRUE;
}

char *ListOfIDs[100];

char **Iod_getListofNetworks()
{
    memset(ListOfIDs, 0, 100);
    int a = Iod_getNumberOfNetworks();
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = Iod_getNetworkID(i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfNodesIDs(int netIndex)
{
    memset(ListOfIDs, 0, 100);
    int a = Iod_getNumberOfNodes(netIndex);
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = Iod_getNodeID(netIndex, i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfReactionIDs(int netIndex)
{
    memset(ListOfIDs, 0, 100);
    int a = Iod_getNumberOfReactions(netIndex);
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = Iod_getReactionID(netIndex, i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfReactionSrcNodes(int netIndex, int reactionIndex)
{
    memset(ListOfIDs, 0, 100);
    getListOfReactionSrcNodes(netIndex, reactionIndex);
    int a = Iod_getNumberOfSrcNodes(netIndex, reactionIndex);
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = getReactionNodeID(i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfReactionDestNodes(int netIndex, int reactionIndex)
{
    memset(ListOfIDs, 0, 100);
    getListOfReactionDestNodes(netIndex, reactionIndex);
    int a = Iod_getNumberOfDestNodes(netIndex, reactionIndex);
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = getReactionNodeID(i);
    }
    return &ListOfIDs[0];
}

float ListOfStoich[100];

float *Iod_getListOfReactionSrcStoich(int netIndex, int reactionIndex)
{
    memset(ListOfStoich, 0, 100);
    Iod_getListOfReactionSrcNodes(netIndex, reactionIndex);
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (ListOfIDs[i] != NULL)
        {
            ListOfStoich[i] = Iod_getReactionSrcNodeStoich(netIndex, reactionIndex, ListOfIDs[i]);
        }
    }
    return &ListOfStoich[0];
}

float *Iod_getListOfReactionDestStoich(int netIndex, int reactionIndex)
{
    memset(ListOfStoich, 0, 100);
    Iod_getListOfReactionDestNodes(netIndex, reactionIndex);
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (ListOfIDs[i] != NULL)
        {
            ListOfStoich[i] = Iod_getReactionDestNodeStoich(netIndex, reactionIndex, ListOfIDs[i]);
        }
    }
    return &ListOfStoich[0];
}

void Iod_createUniUni(int neti, const char *reaID, const char *rateLaw, int srci, int desti, float srcStoich, float destStoich)
{
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, srci, srcStoich);
    Iod_addDestNode(neti, reai, desti, destStoich);
    Iod_setRateLaw(neti, reai, rateLaw);
}

void Iod_createUniBi(int neti, const char *reaID, const char *rateLaw, int srci, int dest1i, int dest2i, float srcStoich, float dest1Stoich, float dest2Stoich)
{
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, srci, srcStoich);
    Iod_addDestNode(neti, reai, dest1i, dest1Stoich);
    Iod_addDestNode(neti, reai, dest2i, dest2Stoich);
    Iod_setRateLaw(neti, reai, rateLaw);
}

void Iod_createBiUni(int neti, const char *reaID, const char *rateLaw, int src1i, int src2i, int desti, float src1Stoich, float src2Stoich, float destStoich)
{
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, src1i, src1Stoich);
    Iod_addSrcNode(neti, reai, src2i, src2Stoich);
    Iod_addDestNode(neti, reai, desti, destStoich);
    Iod_setRateLaw(neti, reai, rateLaw);
}

void Iod_createBiBi(int neti, const char *reaID, const char *rateLaw, int src1i, int src2i, int dest1i, int dest2i, float src1Stoich, float src2Stoich, float dest1Stoich, float dest2Stoich)
{
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, src1i, src1Stoich);
    Iod_addSrcNode(neti, reai, src2i, src2Stoich);
    Iod_addDestNode(neti, reai, dest1i, dest1Stoich);
    Iod_addDestNode(neti, reai, dest2i, dest2Stoich);
    Iod_setRateLaw(neti, reai, rateLaw);
}