#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
HINSTANCE hinstLib;
typedef int (*getErrorCodeProc)();
typedef int (*undoProc)();
typedef int (*redoProc)();
typedef int (*newNetworkProc)(char *netID);
typedef int(*getNetworkIndexProc)(char *netID);
typedef int(*saveNetworkAsJSONProc)(int netIndex, char *fileName);
typedef int(*readNetworkFromJSONProc)(char *path);
typedef int(*deleteNetworkProc)(int netIndex);
typedef void(*clearNetworksProc)();
typedef int(*getNumberOfNetworksProc)();
typedef char *(*getNetworkIDProc)(int netIndex);
typedef int(*addNodeProc)(int netIndex, char *nodeName, float x, float y, float w, float h);
typedef int(*getNodeIndexProc)(int netIndex, char *nodeID);
typedef int(*deleteNodeProc)(int netIndex, int nodeIndex);
typedef int(*clearNetworkProc)(int netIndex);
typedef int(*getNumberOfNodesProc)(int netIndex);
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
typedef int (*setNodeIDProc)(int netIndex, int nodeIndex, char *newID);
typedef int (*setNodeCoordinateAndSizeProc)(int netIndex, int nodeIndex, float x, float y, float w, float h);
typedef int (*setNodeFillColorProc)(int netIndex, int nodeIndex, int R, int G, int B, int A);
typedef int (*setNodeOutlineColorProc)(int netIndex, int nodeIndex, int R, int G, int B, int A);
typedef int (*setNodeOutlineThicknessProc)(int netIndex, int nodeIndex, int thickness);
typedef int (*createReactionProc)(int netIndex, char *reactionID);
typedef int (*getReactionIndexProc)(int netIndex, char *reactionID);
typedef int (*deleteReactionProc)(int netIndex, int reactionIndex);
typedef int (*clearReactionsProc)(int netIndex);
typedef int (*getNumberOfReactionsProc)(int netIndex);
typedef char *(*getReactionIDProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionRateLawProc)(int netIndex, int reactionIndex);
typedef unsigned int (*getReactionFillColorProc)(int netIndex, int reactionIndex);
typedef int (*getReactionLineThicknessProc)(int netIndex, int reactionIndex);
typedef float (*getReactionSrcNodeStoichProc)(int netIndex, int reactionIndex, char *srcNodeID);
typedef float (*getReactionDestNodeStoichProc)(int netIndex, int reactionIndex, char *destNodeID);
typedef int (*getNumberOfSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getNumberOfDestNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionDestNodesProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionNodeIDProc)(int index);
typedef int (*addSrcNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*addDestNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*deleteSrcNodeProc)(int netIndex, int reactionIndex, char *nodeID);
typedef int (*deleteDestNodeProc)(int netIndex, int reactionIndex, char *nodeID);
typedef int (*setRateLawProc)(int netIndex, int reactionIndex, char *rateLaw);
typedef int (*setReactionFillColorProc)(int netIndex, int reactionIndex, int R, int G, int B, int A);
typedef int (*setReactionLineThicknessProc)(int netIndex, int reactionIndex, int thickness);

getErrorCodeProc getErrorCode;
undoProc undo;
redoProc redo;
newNetworkProc newNetwork;
getNetworkIndexProc getNetworkIndex;
saveNetworkAsJSONProc saveNetworkAsJSON;
readNetworkFromJSONProc readNetworkFromJSON;
deleteNetworkProc deleteNetwork;
clearNetworksProc clearNetworks;
getNumberOfNetworksProc getNumberOfNetworks;
getNetworkIDProc getNetworkID;
addNodeProc addNode;
getNodeIndexProc getNodeIndex;
deleteNodeProc deleteNode;
clearNetworkProc clearNetwork;
getNumberOfNodesProc getNumberOfNodes;
getNodeCenterXProc getNodeCenterX;
getNodeCenterYProc getNodeCenterY;
getNodeIDProc getNodeID;
getNodeXProc getNodeX;
getNodeYProc getNodeY;
getNodeWProc getNodeW;
getNodeHProc getNodeH;
getNodeFillColorProc getNodeFillColor;
getNodeOutlineColorProc getNodeOutlineColor;
getNodeOutlineThicknessProc getNodeOutlineThickness;
setNodeIDProc setNodeID;
setNodeCoordinateAndSizeProc setNodeCoordinateAndSize;
setNodeFillColorProc setNodeFillColor;
setNodeOutlineColorProc setNodeOutlineColor;
setNodeOutlineThicknessProc setNodeOutlineThickness;
createReactionProc createReaction;
getReactionIndexProc getReactionIndex;
deleteReactionProc deleteReaction;
clearReactionsProc clearReactions;
getNumberOfReactionsProc getNumberOfReactions;
getReactionIDProc getReactionID;
getReactionRateLawProc getReactionRateLaw;
getReactionFillColorProc getReactionFillColor;
getReactionLineThicknessProc getReactionLineThickness;
getReactionSrcNodeStoichProc getReactionSrcNodeStoich;
getReactionDestNodeStoichProc getReactionDestNodeStoich;
getNumberOfSrcNodesProc getNumberOfSrcNodes;
getNumberOfDestNodesProc getNumberOfDestNodes;
getListOfReactionSrcNodesProc getListOfReactionSrcNodes;
getListOfReactionDestNodesProc getListOfReactionDestNodes;
getReactionNodeIDProc getReactionNodeID;
addSrcNodeProc addSrcNode;
addDestNodeProc addDestNode;
deleteSrcNodeProc deleteSrcNode;
deleteDestNodeProc deleteDestNode;
setRateLawProc setRateLaw;
setReactionFillColorProc setReactionFillColor;
setReactionLineThicknessProc setReactionLineThickness;

char* getErrorMessage(int errCode){
    switch(errCode){
        case  0 :  return "ok";
        case -1 :  return "other";
        case -2 :  return "id not found: ";
        case -3 :  return "id repeat: ";
        case -4 :  return "node is not free: ";
        case -5 :  return "net index out of range: ";
        case -6 :  return "reaction index out of range: ";
        case -7 :  return "node index out of range: ";
        case -8 :  return "wrong stoich: stoich has to be positive: ";
        case -9 :  return "stack is empty";
        case -10 : return "Json convert error";
        case -11 : return "File error";
        case -12 : return "Variable out of range: ";
        case -13 : return "Loading DLL error";
        default  : return "Other error";
    }
}

// Returns TRUE if successful else returns FALSE
bool loadDll(int *errorCode)
{
    hinstLib = LoadLibrary("../Iodine_Dll/Iodine.dll");
    if (hinstLib == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }

    getErrorCode = (getErrorCodeProc)GetProcAddress(hinstLib,  "getErrorCode");
        if (getErrorCode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }

    undo = (undoProc)GetProcAddress(hinstLib, "undo");
    if (undo == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    redo = (redoProc)GetProcAddress(hinstLib, "redo");
    if (redo == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    newNetwork = (newNetworkProc)GetProcAddress(hinstLib, "newNetwork");
    if (newNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNetworkIndex = (getNetworkIndexProc)GetProcAddress(hinstLib, "getNetworkIndex");
    if (getNetworkIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    saveNetworkAsJSON = (saveNetworkAsJSONProc)GetProcAddress(hinstLib, "saveNetworkAsJSON");
    if (saveNetworkAsJSON == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    readNetworkFromJSON = (readNetworkFromJSONProc)GetProcAddress(hinstLib, "readNetworkFromJSON");
    if (readNetworkFromJSON == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    deleteNetwork = (deleteNetworkProc)GetProcAddress(hinstLib, "deleteNetwork");
    if (deleteNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    clearNetworks = (clearNetworksProc)GetProcAddress(hinstLib, "clearNetworks");
    if (clearNetworks == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNumberOfNetworks = (getNumberOfNetworksProc)GetProcAddress(hinstLib, "getNumberOfNetworks");
    if (getNumberOfNetworks == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNetworkID = (getNetworkIDProc)GetProcAddress(hinstLib, "getNetworkID");
    if (getNetworkID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    addNode = (addNodeProc)GetProcAddress(hinstLib, "addNode");
    if (addNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeIndex = (getNodeIndexProc)GetProcAddress(hinstLib, "getNodeIndex");
    if (getNodeIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    deleteNode = (deleteNodeProc)GetProcAddress(hinstLib, "deleteNode");
    if (deleteNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    clearNetwork = (clearNetworkProc)GetProcAddress(hinstLib, "clearNetwork");
    if (clearNetwork == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNumberOfNodes = (getNumberOfNodesProc)GetProcAddress(hinstLib, "getNumberOfNodes");
    if (getNumberOfNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeCenterX = (getNodeCenterXProc)GetProcAddress(hinstLib, "getNodeCenterX");
    if (getNodeCenterX == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeCenterY = (getNodeCenterYProc)GetProcAddress(hinstLib, "getNodeCenterY");
    if (getNodeCenterY == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeID = (getNodeIDProc)GetProcAddress(hinstLib, "getNodeID");
    if (getNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeX = (getNodeXProc)GetProcAddress(hinstLib, "getNodeX");
    if (getNodeX == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeY = (getNodeYProc)GetProcAddress(hinstLib, "getNodeY");
    if (getNodeY == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeW = (getNodeWProc)GetProcAddress(hinstLib, "getNodeW");
    if (getNodeW == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeH = (getNodeHProc)GetProcAddress(hinstLib, "getNodeH");
    if (getNodeH == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeFillColor = (getNodeFillColorProc)GetProcAddress(hinstLib, "getNodeFillColor");
    if (getNodeFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeOutlineColor = (getNodeOutlineColorProc)GetProcAddress(hinstLib, "getNodeOutlineColor");
    if (getNodeOutlineColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNodeOutlineThickness = (getNodeOutlineThicknessProc)GetProcAddress(hinstLib, "getNodeOutlineThickness");
    if (getNodeOutlineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setNodeID = (setNodeIDProc)GetProcAddress(hinstLib, "setNodeID");
    if (setNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setNodeCoordinateAndSize = (setNodeCoordinateAndSizeProc)GetProcAddress(hinstLib, "setNodeCoordinateAndSize");
    if (setNodeCoordinateAndSize == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setNodeFillColor = (setNodeFillColorProc)GetProcAddress(hinstLib, "setNodeFillColor");
    if (setNodeFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setNodeOutlineColor = (setNodeOutlineColorProc)GetProcAddress(hinstLib, "setNodeOutlineColor");
    if (setNodeOutlineColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setNodeOutlineThickness = (setNodeOutlineThicknessProc)GetProcAddress(hinstLib, "setNodeOutlineThickness");
    if (setNodeOutlineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    createReaction = (createReactionProc)GetProcAddress(hinstLib, "createReaction");
    if (createReaction == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionIndex = (getReactionIndexProc)GetProcAddress(hinstLib, "getReactionIndex");
    if (getReactionIndex == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    deleteReaction = (deleteReactionProc)GetProcAddress(hinstLib, "deleteReaction");
    if (deleteReaction == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    clearReactions = (clearReactionsProc)GetProcAddress(hinstLib, "clearReactions");
    if (clearReactions == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNumberOfReactions = (getNumberOfReactionsProc)GetProcAddress(hinstLib, "getNumberOfReactions");
    if (getNumberOfReactions == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionID = (getReactionIDProc)GetProcAddress(hinstLib, "getReactionID");
    if (getReactionID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionRateLaw = (getReactionRateLawProc)GetProcAddress(hinstLib, "getReactionRateLaw");
    if (getReactionRateLaw == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionFillColor = (getReactionFillColorProc)GetProcAddress(hinstLib, "getReactionFillColor");
    if (getReactionFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionLineThickness = (getReactionLineThicknessProc)GetProcAddress(hinstLib, "getReactionLineThickness");
    if (getReactionLineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionSrcNodeStoich = (getReactionSrcNodeStoichProc)GetProcAddress(hinstLib, "getReactionSrcNodeStoich");
    if (getReactionSrcNodeStoich == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionDestNodeStoich = (getReactionDestNodeStoichProc)GetProcAddress(hinstLib, "getReactionDestNodeStoich");
    if (getReactionDestNodeStoich == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNumberOfSrcNodes = (getNumberOfSrcNodesProc)GetProcAddress(hinstLib, "getNumberOfSrcNodes");
    if (getNumberOfSrcNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getNumberOfDestNodes = (getNumberOfDestNodesProc)GetProcAddress(hinstLib, "getNumberOfDestNodes");
    if (getNumberOfDestNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getListOfReactionSrcNodes = (getListOfReactionSrcNodesProc)GetProcAddress(hinstLib, "getListOfReactionSrcNodes");
    if (getListOfReactionSrcNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getListOfReactionDestNodes = (getListOfReactionDestNodesProc)GetProcAddress(hinstLib, "getListOfReactionDestNodes");
    if (getListOfReactionDestNodes == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    getReactionNodeID = (getReactionNodeIDProc)GetProcAddress(hinstLib, "getReactionNodeID");
    if (getReactionNodeID == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    addSrcNode = (addSrcNodeProc)GetProcAddress(hinstLib, "addSrcNode");
    if (addSrcNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    addDestNode = (addDestNodeProc)GetProcAddress(hinstLib, "addDestNode");
    if (addDestNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    deleteSrcNode = (deleteSrcNodeProc)GetProcAddress(hinstLib, "deleteSrcNode");
    if (deleteSrcNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    deleteDestNode = (deleteDestNodeProc)GetProcAddress(hinstLib, "deleteDestNode");
    if (deleteDestNode == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setRateLaw = (setRateLawProc)GetProcAddress(hinstLib, "setRateLaw");
    if (setRateLaw == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setReactionFillColor = (setReactionFillColorProc)GetProcAddress(hinstLib, "setReactionFillColor");
    if (setReactionFillColor == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }
    setReactionLineThickness = (setReactionLineThicknessProc)GetProcAddress(hinstLib, "setReactionLineThickness");
    if (setReactionLineThickness == NULL)
    {
        *errorCode = -13;
        return FALSE;
    }



    return TRUE;
}

