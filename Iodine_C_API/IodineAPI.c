#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
HINSTANCE hinstLib;
typedef int (*getErrorCodeProc)();
typedef int (*undoProc)();
typedef int (*redoProc)();
typedef int (*newNetworkProc)(char *p0);
typedef int(*getNetworkIndexProc)(char *p0);
typedef int(*saveNetworkAsJSONProc)(int p0, char *p1);
typedef int(*readNetworkFromJSONProc)(char *p0);
typedef int(*deleteNetworkProc)(int p0);
typedef void(*clearNetworksProc)();
typedef int(*getNumberOfNetworksProc)();
typedef char *(*getNetworkIDProc)(int p0);
typedef int(*addNodeProc)(int p0, char *p1, float p2, float p3, float p4, float p5);
typedef int(*getNodeIndexProc)(int p0, char *p1);
typedef int(*deleteNodeProc)(int p0, int p1);
typedef int(*clearNetworkProc)(int p0);
typedef int(*getNumberOfNodesProc)(int p0);
typedef float(*getNodeCenterXProc)(int p0, int p1);
typedef float(*getNodeCenterYProc)(int p0, int p1);
typedef char *(*getNodeIDProc)(int p0, int p1);
typedef float(*getNodeXProc)(int p0, int p1);
typedef float(*getNodeYProc)(int p0, int p1);
typedef float(*getNodeWProc)(int p0, int p1);
typedef float(*getNodeHProc)(int p0, int p1);
typedef unsigned int(*getNodeFillColorProc)(int p0, int p1);
typedef unsigned int(*getNodeOutlineColorProc)(int p0, int p1);
typedef int(*getNodeOutlineThicknessProc)(int p0, int p1);
typedef int(*setNodeCoordinateAndSizeProc)(int p0, int p1, float p2, float p3, float p4, float p5);
typedef int(*setNodeFillColorProc)(int p0, int p1, int p2, int p3, int p4, int p5);
typedef int(*setNodeOutlineColorProc)(int p0, int p1, int p2, int p3, int p4, int p5);
typedef int(*setNodeOutlineThicknessProc)(int p0, int p1, int p2);
typedef int(*createReactionProc)(int p0, char *p1);
typedef int(*getReactionIndexProc)(int p0, char *p1);
typedef int(*deleteReactionProc)(int p0, int p1);
typedef int(*clearReactionsProc)(int p0);
typedef int(*getNumberOfReactionsProc)(int p0);
typedef char *(*getReactionIDProc)(int p0, int p1);
typedef char *(*getReactionRateLawProc)(int p0, int p1);
typedef unsigned int(*getReactionFillColorProc)(int p0, int p1);
typedef int(*getReactionLineThicknessProc)(int p0, int p1);
typedef float(*getReactionSrcNodeStoichProc)(int p0, int p1, char *p2);
typedef float(*getReactionDestNodeStoichProc)(int p0, int p1, char *p2);
typedef int(*getNumberOfSrcNodesProc)(int p0, int p1);
typedef int(*getNumberOfDestNodesProc)(int p0, int p1);
typedef int(*getListOfReactionSrcNodesProc)(int p0, int p1);
typedef int(*getListOfReactionDestNodesProc)(int p0, int p1);
typedef char *(*getReactionNodeIDProc)(int p0);
typedef int(*addSrcNodeProc)(int p0, int p1, int p2, float p3);
typedef int(*addDestNodeProc)(int p0, int p1, int p2, float p3);
typedef int(*deleteSrcNodeProc)(int p0, int p1, char *p2);
typedef int(*deleteDestNodeProc)(int p0, int p1, char *p2);
typedef int(*setRateLawProc)(int p0, int p1, char *p2);
typedef int(*setReactionFillColorProc)(int p0, int p1, int p2, int p3, int p4, int p5);
typedef int(*setReactionLineThicknessProc)(int p0, int p1, int p2);

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

