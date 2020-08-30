#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
HINSTANCE Iod_hinstLib;
typedef int (*getErrorCodeProc)();
typedef void (*setErrorCodeProc)(int err);
typedef int (*undoProc)();
typedef int (*redoProc)();
typedef void (*startGroupProc)();
typedef void (*endGroupProc)();
typedef int (*cFreeProc)(const char *cString);
typedef char *(*getErrorMessageProc)();
typedef char *(*getDetailErrorMessageProc)();
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
typedef unsigned int (*getNodeFillColorRGBProc)(int netIndex, int nodeIndex);
typedef float (*getNodeFillColorAlphaProc)(int netIndex, int nodeIndex);
typedef unsigned int (*getNodeOutlineColorRGBProc)(int netIndex, int nodeIndex);
typedef float (*getNodeOutlineColorAlphaProc)(int netIndex, int nodeIndex);
typedef float (*getNodeOutlineThicknessProc)(int netIndex, int nodeIndex);
typedef int (*getNodeFontPointSizeProc)(int netIndex, int nodeIndex);
typedef char *(*getNodeFontFamilyProc)(int netIndex, int nodeIndex);
typedef char *(*getNodeFontStyleProc)(int netIndex, int nodeIndex);
typedef char *(*getNodeFontWeightProc)(int netIndex, int nodeIndex);
typedef char *(*getNodeFontNameProc)(int netIndex, int nodeIndex);
typedef unsigned int (*getNodeFontColorRGBProc)(int netIndex, int nodeIndex);
typedef float (*getNodeFontColorAlphaProc)(int netIndex, int nodeIndex);
typedef int (*setNodeIDProc)(int netIndex, int nodeIndex, const char *newID);
typedef int (*setNodeCoordinateProc)(int netIndex, int nodeIndex, float x, float y);
typedef int (*setNodeSizeProc)(int netIndex, int nodeIndex, float w, float h);
typedef int (*setNodeFillColorRGBProc)(int netIndex, int nodeIndex, int R, int G, int B);
typedef int (*setNodeFillColorAlphaProc)(int netIndex, int nodeIndex, float A);
typedef int (*setNodeOutlineColorRGBProc)(int netIndex, int nodeIndex, int R, int G, int B);
typedef int (*setNodeOutlineColorAlphaProc)(int netIndex, int nodeIndex, float A);
typedef int (*setNodeOutlineThicknessProc)(int netIndex, int nodeIndex, float thickness);
typedef int (*setNodeFontPointSizeProc)(int netIndex, int nodeIndex, int fontPointSize);
typedef int (*setNodeFontFamilyProc)(int netIndex, int nodeIndex, const char *fontFamily);
typedef int (*setNodeFontStyleProc)(int netIndex, int nodeIndex, const char *fontStyle);
typedef int (*setNodeFontWeightProc)(int netIndex, int nodeIndex, const char *fontWeight);
typedef int (*setNodeFontNameProc)(int netIndex, int nodeIndex, const char *fontName);
typedef int (*setNodeFontColorRGBProc)(int netIndex, int nodeIndex, int R, int G, int B);
typedef int (*setNodeFontColorAlphaProc)(int netIndex, int nodeIndex, float A);
typedef int (*createReactionProc)(int netIndex, const char *reactionID);
typedef int (*getReactionIndexProc)(int netIndex, const char *reactionID);
typedef int (*deleteReactionProc)(int netIndex, int reactionIndex);
typedef int (*clearReactionsProc)(int netIndex);
typedef int (*getNumberOfReactionsProc)(int netIndex);
typedef char *(*getReactionIDProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionRateLawProc)(int netIndex, int reactionIndex);
typedef unsigned int (*getReactionFillColorRGBProc)(int netIndex, int reactionIndex);
typedef float (*getReactionFillColorAlphaProc)(int netIndex, int reactionIndex);
typedef float (*getReactionLineThicknessProc)(int netIndex, int reactionIndex);
typedef float (*getReactionCenterHandleXProc)(int netIndex, int reactionIndex);
typedef float (*getReactionCenterHandleYProc)(int netIndex, int reactionIndex);
typedef float (*getReactionSrcNodeStoichProc)(int netIndex, int reactionIndex, const char *srcNodeID);
typedef float (*getReactionDestNodeStoichProc)(int netIndex, int reactionIndex, const char *destNodeID);
typedef float (*getReactionSrcNodeHandleXProc)(int netIndex, int reactionIndex, const char *srcNodeID);
typedef float (*getReactionSrcNodeHandleYProc)(int netIndex, int reactionIndex, const char *srcNodeID);
typedef float (*getReactionDestNodeHandleXProc)(int netIndex, int reactionIndex, const char *destNodeID);
typedef float (*getReactionDestNodeHandleYProc)(int netIndex, int reactionIndex, const char *destNodeID);
typedef int (*getNumberOfSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getNumberOfDestNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionSrcNodesProc)(int netIndex, int reactionIndex);
typedef int (*getListOfReactionDestNodesProc)(int netIndex, int reactionIndex);
typedef char *(*getReactionNodeIDProc)(int index);
typedef int (*addSrcNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*addDestNodeProc)(int netIndex, int reactionIndex, int nodeIndex, float stoich);
typedef int (*deleteSrcNodeProc)(int netIndex, int reactionIndex, const char *nodeID);
typedef int (*deleteDestNodeProc)(int netIndex, int reactionIndex, const char *nodeID);
typedef int (*setReactionIDProc)(int netIndex, int reactionIndex, const char *newID);
typedef int (*setRateLawProc)(int netIndex, int reactionIndex, const char *rateLaw);
typedef int (*setReactionSrcNodeStoichProc)(int netIndex, int reactionIndex, const char *srcNodeID, float newStoich);
typedef int (*setReactionDestNodeStoichProc)(int netIndex, int reactionIndex, const char *destNodeID, float newStoich);
typedef int (*setReactionSrcNodeHandlePositionProc)(int netIndex, int reactionIndex, const char *srcNodeID, float handleX, float handleY);
typedef int (*setReactionDestNodeHandlePositionProc)(int netIndex, int reactionIndex, const char *destNodeID, float handleX, float handleY);
typedef int (*setReactionFillColorRGBProc)(int netIndex, int reactionIndex, int R, int G, int B);
typedef int (*setReactionFillColorAlphaProc)(int netIndex, int reactionIndex, float A);
typedef int (*setReactionLineThicknessProc)(int netIndex, int reactionIndex, float thickness);
typedef int (*setReactionCenterHandlePositionProc)(int netIndex, int reactionIndex, float thickness);

getErrorCodeProc Iod_getErrorCode;
setErrorCodeProc setErrorCode;
undoProc Iod_undo;
redoProc Iod_redo;
startGroupProc Iod_startGroup;
endGroupProc Iod_endGroup;
cFreeProc Iod_cFree;
getErrorMessageProc Iod_getErrorMessage;
getDetailErrorMessageProc Iod_getDetailErrorMessage;
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
getNodeFillColorRGBProc Iod_getNodeFillColorRGB;
getNodeFillColorAlphaProc Iod_getNodeFillColorAlpha;
getNodeOutlineColorRGBProc Iod_getNodeOutlineColorRGB;
getNodeOutlineColorAlphaProc Iod_getNodeOutlineColorAlpha;
getNodeOutlineThicknessProc Iod_getNodeOutlineThickness;
getNodeFontPointSizeProc Iod_getNodeFontPointSize;
getNodeFontFamilyProc Iod_getNodeFontFamily;
getNodeFontStyleProc Iod_getNodeFontStyle;
getNodeFontWeightProc Iod_getNodeFontWeight;
getNodeFontNameProc Iod_getNodeFontName;
getNodeFontColorRGBProc Iod_getNodeFontColorRGB;
getNodeFontColorAlphaProc Iod_getNodeFontColorAlpha;
setNodeIDProc Iod_setNodeID;
setNodeCoordinateProc Iod_setNodeCoordinate;
setNodeSizeProc Iod_setNodeSize;
setNodeFillColorRGBProc Iod_setNodeFillColorRGB;
setNodeFillColorAlphaProc Iod_setNodeFillColorAlpha;
setNodeOutlineColorRGBProc Iod_setNodeOutlineColorRGB;
setNodeOutlineColorAlphaProc Iod_setNodeOutlineColorAlpha;
setNodeOutlineThicknessProc Iod_setNodeOutlineThickness;
setNodeFontPointSizeProc Iod_setNodeFontPointSize;
setNodeFontFamilyProc Iod_setNodeFontFamily;
setNodeFontStyleProc Iod_setNodeFontStyle;
setNodeFontWeightProc Iod_setNodeFontWeight;
setNodeFontNameProc Iod_setNodeFontName;
setNodeFontColorRGBProc Iod_setNodeFontColorRGB;
setNodeFontColorAlphaProc Iod_setNodeFontColorAlpha;
createReactionProc Iod_createReaction;
getReactionIndexProc Iod_getReactionIndex;
deleteReactionProc Iod_deleteReaction;
clearReactionsProc Iod_clearReactions;
getNumberOfReactionsProc Iod_getNumberOfReactions;
getReactionIDProc Iod_getReactionID;
getReactionRateLawProc Iod_getReactionRateLaw;
getReactionFillColorRGBProc Iod_getReactionFillColorRGB;
getReactionFillColorAlphaProc Iod_getReactionFillColorAlpha;
getReactionLineThicknessProc Iod_getReactionLineThickness;
getReactionCenterHandleXProc Iod_getReactionCenterHandleX;
getReactionCenterHandleYProc Iod_getReactionCenterHandleY;
getReactionSrcNodeStoichProc Iod_getReactionSrcNodeStoich;
getReactionDestNodeStoichProc Iod_getReactionDestNodeStoich;
getReactionSrcNodeHandleXProc Iod_getReactionSrcNodeHandleX;
getReactionSrcNodeHandleYProc Iod_getReactionSrcNodeHandleY;
getReactionDestNodeHandleXProc Iod_getReactionDestNodeHandleX;
getReactionDestNodeHandleYProc Iod_getReactionDestNodeHandleY;
getNumberOfSrcNodesProc Iod_getNumberOfSrcNodes;
getNumberOfDestNodesProc Iod_getNumberOfDestNodes;
getListOfReactionSrcNodesProc getListOfReactionSrcNodes;
getListOfReactionDestNodesProc getListOfReactionDestNodes;
getReactionNodeIDProc getReactionNodeID;
addSrcNodeProc Iod_addSrcNode;
addDestNodeProc Iod_addDestNode;
deleteSrcNodeProc Iod_deleteSrcNode;
deleteDestNodeProc Iod_deleteDestNode;
setReactionIDProc Iod_setReactionID;
setRateLawProc Iod_setRateLaw;
setReactionSrcNodeStoichProc Iod_setReactionSrcNodeStoich;
setReactionDestNodeStoichProc Iod_setReactionDestNodeStoich;
setReactionSrcNodeHandlePositionProc Iod_setReactionSrcNodeHandlePosition;
setReactionDestNodeHandlePositionProc Iod_setReactionDestNodeHandlePosition;
setReactionFillColorRGBProc Iod_setReactionFillColorRGB;
setReactionFillColorAlphaProc Iod_setReactionFillColorAlpha;
setReactionLineThicknessProc Iod_setReactionLineThickness;
setReactionCenterHandlePositionProc Iod_setReactionCenterHandlePosition;

typedef struct
{
    int r;
    int g;
    int b;
    float a;
} Color;

// Returns TRUE if successful load dll file and all functions in it.
// else returns FALSE
int loadDll(const char *pathToDll)
{
    Iod_hinstLib = LoadLibrary(pathToDll);
    if (Iod_hinstLib == NULL)
    {
        return -11;
    }

    Iod_getErrorCode = (getErrorCodeProc)GetProcAddress(Iod_hinstLib, "getErrorCode");
    if (Iod_getErrorCode == NULL)
    {
        return -13;
    }

    setErrorCode = (setErrorCodeProc)GetProcAddress(Iod_hinstLib, "setErrorCode");
    if (setErrorCode == NULL)
    {
        return -13;
    }

    Iod_undo = (undoProc)GetProcAddress(Iod_hinstLib, "undo");
    if (Iod_undo == NULL)
    {
        return -13;
    }
    Iod_redo = (redoProc)GetProcAddress(Iod_hinstLib, "redo");
    if (Iod_redo == NULL)
    {
        return -13;
    }
    Iod_startGroup = (startGroupProc)GetProcAddress(Iod_hinstLib, "startGroup");
    if (Iod_startGroup == NULL)
    {
        return -13;
    }
    Iod_endGroup = (endGroupProc)GetProcAddress(Iod_hinstLib, "endGroup");
    if (Iod_endGroup == NULL)
    {
        return -13;
    }
    Iod_cFree = (cFreeProc)GetProcAddress(Iod_hinstLib, "cFree");
    if (Iod_cFree == NULL)
    {
        return -13;
    }
    Iod_getErrorMessage = (getErrorMessageProc)GetProcAddress(Iod_hinstLib, "getErrorMessage");
    if (Iod_getErrorMessage == NULL)
    {
        return -13;
    }
    Iod_getDetailErrorMessage = (getDetailErrorMessageProc)GetProcAddress(Iod_hinstLib, "getDetailErrorMessage");
    if (Iod_cFree == NULL)
    {
        return -13;
    }
    Iod_newNetwork = (newNetworkProc)GetProcAddress(Iod_hinstLib, "newNetwork");
    if (Iod_newNetwork == NULL)
    {
        return -13;
    }
    Iod_getNetworkIndex = (getNetworkIndexProc)GetProcAddress(Iod_hinstLib, "getNetworkIndex");
    if (Iod_getNetworkIndex == NULL)
    {
        return -13;
    }
    Iod_saveNetworkAsJSON = (saveNetworkAsJSONProc)GetProcAddress(Iod_hinstLib, "saveNetworkAsJSON");
    if (Iod_saveNetworkAsJSON == NULL)
    {
        return -13;
    }
    Iod_readNetworkFromJSON = (readNetworkFromJSONProc)GetProcAddress(Iod_hinstLib, "readNetworkFromJSON");
    if (Iod_readNetworkFromJSON == NULL)
    {
        return -13;
    }
    Iod_deleteNetwork = (deleteNetworkProc)GetProcAddress(Iod_hinstLib, "deleteNetwork");
    if (Iod_deleteNetwork == NULL)
    {
        return -13;
    }
    Iod_clearNetworks = (clearNetworksProc)GetProcAddress(Iod_hinstLib, "clearNetworks");
    if (Iod_clearNetworks == NULL)
    {
        return -13;
    }
    Iod_getNumberOfNetworks = (getNumberOfNetworksProc)GetProcAddress(Iod_hinstLib, "getNumberOfNetworks");
    if (Iod_getNumberOfNetworks == NULL)
    {
        return -13;
    }
    Iod_getNetworkID = (getNetworkIDProc)GetProcAddress(Iod_hinstLib, "getNetworkID");
    if (Iod_getNetworkID == NULL)
    {
        return -13;
    }
    Iod_addNode = (addNodeProc)GetProcAddress(Iod_hinstLib, "addNode");
    if (Iod_addNode == NULL)
    {
        return -13;
    }
    Iod_getNodeIndex = (getNodeIndexProc)GetProcAddress(Iod_hinstLib, "getNodeIndex");
    if (Iod_getNodeIndex == NULL)
    {
        return -13;
    }
    Iod_deleteNode = (deleteNodeProc)GetProcAddress(Iod_hinstLib, "deleteNode");
    if (Iod_deleteNode == NULL)
    {
        return -13;
    }
    Iod_clearNetwork = (clearNetworkProc)GetProcAddress(Iod_hinstLib, "clearNetwork");
    if (Iod_clearNetwork == NULL)
    {
        return -13;
    }
    Iod_getNumberOfNodes = (getNumberOfNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfNodes");
    if (Iod_getNumberOfNodes == NULL)
    {
        return -13;
    }
    Iod_getNodeCenterX = (getNodeCenterXProc)GetProcAddress(Iod_hinstLib, "getNodeCenterX");
    if (Iod_getNodeCenterX == NULL)
    {
        return -13;
    }
    Iod_getNodeCenterY = (getNodeCenterYProc)GetProcAddress(Iod_hinstLib, "getNodeCenterY");
    if (Iod_getNodeCenterY == NULL)
    {
        return -13;
    }
    Iod_getNodeID = (getNodeIDProc)GetProcAddress(Iod_hinstLib, "getNodeID");
    if (Iod_getNodeID == NULL)
    {
        return -13;
    }
    Iod_getNodeX = (getNodeXProc)GetProcAddress(Iod_hinstLib, "getNodeX");
    if (Iod_getNodeX == NULL)
    {
        return -13;
    }
    Iod_getNodeY = (getNodeYProc)GetProcAddress(Iod_hinstLib, "getNodeY");
    if (Iod_getNodeY == NULL)
    {
        return -13;
    }
    Iod_getNodeW = (getNodeWProc)GetProcAddress(Iod_hinstLib, "getNodeW");
    if (Iod_getNodeW == NULL)
    {
        return -13;
    }
    Iod_getNodeH = (getNodeHProc)GetProcAddress(Iod_hinstLib, "getNodeH");
    if (Iod_getNodeH == NULL)
    {
        return -13;
    }
    Iod_getNodeFillColorRGB = (getNodeFillColorRGBProc)GetProcAddress(Iod_hinstLib, "getNodeFillColorRGB");
    if (Iod_getNodeFillColorRGB == NULL)
    {
        return -13;
    }
    Iod_getNodeFillColorAlpha = (getNodeFillColorAlphaProc)GetProcAddress(Iod_hinstLib, "getNodeFillColorAlpha");
    if (Iod_getNodeFillColorAlpha == NULL)
    {
        return -13;
    }
    Iod_getNodeOutlineColorRGB = (getNodeOutlineColorRGBProc)GetProcAddress(Iod_hinstLib, "getNodeOutlineColorRGB");
    if (Iod_getNodeOutlineColorRGB == NULL)
    {
        return -13;
    }
    Iod_getNodeOutlineColorAlpha = (getNodeOutlineColorAlphaProc)GetProcAddress(Iod_hinstLib, "getNodeOutlineColorAlpha");
    if (Iod_getNodeOutlineColorAlpha == NULL)
    {
        return -13;
    }
    Iod_getNodeOutlineThickness = (getNodeOutlineThicknessProc)GetProcAddress(Iod_hinstLib, "getNodeOutlineThickness");
    if (Iod_getNodeOutlineThickness == NULL)
    {
        return -13;
    }
    Iod_getNodeFontPointSize = (getNodeFontPointSizeProc)GetProcAddress(Iod_hinstLib, "getNodeFontPointSize");
    if (Iod_getNodeFontPointSize == NULL)
    {
        return -13;
    }
    Iod_getNodeFontFamily = (getNodeFontFamilyProc)GetProcAddress(Iod_hinstLib, "getNodeFontFamily");
    if (Iod_getNodeFontFamily == NULL)
    {
        return -13;
    }
    Iod_getNodeFontStyle = (getNodeFontStyleProc)GetProcAddress(Iod_hinstLib, "getNodeFontStyle");
    if (Iod_getNodeFontStyle == NULL)
    {
        return -13;
    }
    Iod_getNodeFontWeight = (getNodeFontWeightProc)GetProcAddress(Iod_hinstLib, "getNodeFontWeight");
    if (Iod_getNodeFontWeight == NULL)
    {
        return -13;
    }
    Iod_getNodeFontName = (getNodeFontNameProc)GetProcAddress(Iod_hinstLib, "getNodeFontName");
    if (Iod_getNodeFontName == NULL)
    {
        return -13;
    }
    Iod_getNodeFontColorRGB = (getNodeFontColorRGBProc)GetProcAddress(Iod_hinstLib, "getNodeFontColorRGB");
    if (Iod_getNodeFontColorRGB == NULL)
    {
        return -13;
    }
    Iod_getNodeFontColorAlpha = (getNodeFontColorAlphaProc)GetProcAddress(Iod_hinstLib, "getNodeFontColorAlpha");
    if (Iod_getNodeFontColorAlpha == NULL)
    {
        return -13;
    }
    Iod_setNodeID = (setNodeIDProc)GetProcAddress(Iod_hinstLib, "setNodeID");
    if (Iod_setNodeID == NULL)
    {
        return -13;
    }
    Iod_setNodeCoordinate = (setNodeCoordinateProc)GetProcAddress(Iod_hinstLib, "setNodeCoordinate");
    if (Iod_setNodeCoordinate == NULL)
    {
        return -13;
    }
    Iod_setNodeSize = (setNodeSizeProc)GetProcAddress(Iod_hinstLib, "setNodeSize");
    if (Iod_setNodeSize == NULL)
    {
        return -13;
    }
    Iod_setNodeFillColorRGB = (setNodeFillColorRGBProc)GetProcAddress(Iod_hinstLib, "setNodeFillColorRGB");
    if (Iod_setNodeFillColorRGB == NULL)
    {
        return -13;
    }
    Iod_setNodeFillColorAlpha = (setNodeFillColorAlphaProc)GetProcAddress(Iod_hinstLib, "setNodeFillColorAlpha");
    if (Iod_setNodeFillColorAlpha == NULL)
    {
        return -13;
    }
    Iod_setNodeOutlineColorRGB = (setNodeOutlineColorRGBProc)GetProcAddress(Iod_hinstLib, "setNodeOutlineColorRGB");
    if (Iod_setNodeOutlineColorRGB == NULL)
    {
        return -13;
    }
    Iod_setNodeOutlineColorAlpha = (setNodeOutlineColorAlphaProc)GetProcAddress(Iod_hinstLib, "setNodeOutlineColorAlpha");
    if (Iod_setNodeOutlineColorAlpha == NULL)
    {
        return -13;
    }
    Iod_setNodeOutlineThickness = (setNodeOutlineThicknessProc)GetProcAddress(Iod_hinstLib, "setNodeOutlineThickness");
    if (Iod_setNodeOutlineThickness == NULL)
    {
        return -13;
    }
    Iod_setNodeFontPointSize = (setNodeFontPointSizeProc)GetProcAddress(Iod_hinstLib, "setNodeFontPointSize");
    if (Iod_setNodeFontPointSize == NULL)
    {
        return -13;
    }
    Iod_setNodeFontFamily = (setNodeFontFamilyProc)GetProcAddress(Iod_hinstLib, "setNodeFontFamily");
    if (Iod_setNodeFontFamily == NULL)
    {
        return -13;
    }
    Iod_setNodeFontStyle = (setNodeFontStyleProc)GetProcAddress(Iod_hinstLib, "setNodeFontStyle");
    if (Iod_setNodeFontStyle == NULL)
    {
        return -13;
    }
    Iod_setNodeFontWeight = (setNodeFontWeightProc)GetProcAddress(Iod_hinstLib, "setNodeFontWeight");
    if (Iod_setNodeFontWeight == NULL)
    {
        return -13;
    }
    Iod_setNodeFontName = (setNodeFontNameProc)GetProcAddress(Iod_hinstLib, "setNodeFontName");
    if (Iod_setNodeFontName == NULL)
    {
        return -13;
    }
    Iod_setNodeFontColorRGB = (setNodeFontColorRGBProc)GetProcAddress(Iod_hinstLib, "setNodeFontColorRGB");
    if (Iod_setNodeFontColorRGB == NULL)
    {
        return -13;
    }
    Iod_setNodeFontColorAlpha = (setNodeFontColorAlphaProc)GetProcAddress(Iod_hinstLib, "setNodeFontColorAlpha");
    if (Iod_setNodeFontColorAlpha == NULL)
    {
        return -13;
    }
    Iod_createReaction = (createReactionProc)GetProcAddress(Iod_hinstLib, "createReaction");
    if (Iod_createReaction == NULL)
    {
        return -13;
    }
    Iod_getReactionIndex = (getReactionIndexProc)GetProcAddress(Iod_hinstLib, "getReactionIndex");
    if (Iod_getReactionIndex == NULL)
    {
        return -13;
    }
    Iod_deleteReaction = (deleteReactionProc)GetProcAddress(Iod_hinstLib, "deleteReaction");
    if (Iod_deleteReaction == NULL)
    {
        return -13;
    }
    Iod_clearReactions = (clearReactionsProc)GetProcAddress(Iod_hinstLib, "clearReactions");
    if (Iod_clearReactions == NULL)
    {
        return -13;
    }
    Iod_getNumberOfReactions = (getNumberOfReactionsProc)GetProcAddress(Iod_hinstLib, "getNumberOfReactions");
    if (Iod_getNumberOfReactions == NULL)
    {
        return -13;
    }
    Iod_getReactionID = (getReactionIDProc)GetProcAddress(Iod_hinstLib, "getReactionID");
    if (Iod_getReactionID == NULL)
    {
        return -13;
    }
    Iod_getReactionRateLaw = (getReactionRateLawProc)GetProcAddress(Iod_hinstLib, "getReactionRateLaw");
    if (Iod_getReactionRateLaw == NULL)
    {
        return -13;
    }
    Iod_getReactionFillColorRGB = (getReactionFillColorRGBProc)GetProcAddress(Iod_hinstLib, "getReactionFillColorRGB");
    if (Iod_getReactionFillColorRGB == NULL)
    {
        return -13;
    }
    Iod_getReactionFillColorAlpha = (getReactionFillColorAlphaProc)GetProcAddress(Iod_hinstLib, "getReactionFillColorAlpha");
    if (Iod_getReactionFillColorAlpha == NULL)
    {
        return -13;
    }
    Iod_getReactionLineThickness = (getReactionLineThicknessProc)GetProcAddress(Iod_hinstLib, "getReactionLineThickness");
    if (Iod_getReactionLineThickness == NULL)
    {
        return -13;
    }
    Iod_getReactionCenterHandleX = (getReactionCenterHandleXProc)GetProcAddress(Iod_hinstLib, "getReactionCenterHandleX");
    if (Iod_getReactionCenterHandleX == NULL)
    {
        return -13;
    }
    Iod_getReactionCenterHandleY = (getReactionCenterHandleYProc)GetProcAddress(Iod_hinstLib, "getReactionCenterHandleY");
    if (Iod_getReactionCenterHandleY == NULL)
    {
        return -13;
    }
    Iod_getReactionSrcNodeStoich = (getReactionSrcNodeStoichProc)GetProcAddress(Iod_hinstLib, "getReactionSrcNodeStoich");
    if (Iod_getReactionSrcNodeStoich == NULL)
    {
        return -13;
    }
    Iod_getReactionDestNodeStoich = (getReactionDestNodeStoichProc)GetProcAddress(Iod_hinstLib, "getReactionDestNodeStoich");
    if (Iod_getReactionDestNodeStoich == NULL)
    {
        return -13;
    }
    Iod_getReactionSrcNodeHandleX = (getReactionSrcNodeHandleXProc)GetProcAddress(Iod_hinstLib, "getReactionSrcNodeHandleX");
    if (Iod_getReactionSrcNodeHandleX == NULL)
    {
        return -13;
    }
    Iod_getReactionSrcNodeHandleY = (getReactionSrcNodeHandleYProc)GetProcAddress(Iod_hinstLib, "getReactionSrcNodeHandleY");
    if (Iod_getReactionSrcNodeHandleY == NULL)
    {
        return -13;
    }
    Iod_getReactionDestNodeHandleX = (getReactionDestNodeHandleXProc)GetProcAddress(Iod_hinstLib, "getReactionDestNodeHandleX");
    if (Iod_getReactionDestNodeHandleX == NULL)
    {
        return -13;
    }
    Iod_getReactionDestNodeHandleY = (getReactionDestNodeHandleYProc)GetProcAddress(Iod_hinstLib, "getReactionDestNodeHandleY");
    if (Iod_getReactionDestNodeHandleY == NULL)
    {
        return -13;
    }
    Iod_getNumberOfSrcNodes = (getNumberOfSrcNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfSrcNodes");
    if (Iod_getNumberOfSrcNodes == NULL)
    {
        return -13;
    }
    Iod_getNumberOfDestNodes = (getNumberOfDestNodesProc)GetProcAddress(Iod_hinstLib, "getNumberOfDestNodes");
    if (Iod_getNumberOfDestNodes == NULL)
    {
        return -13;
    }
    getListOfReactionSrcNodes = (getListOfReactionSrcNodesProc)GetProcAddress(Iod_hinstLib, "getListOfReactionSrcNodes");
    if (getListOfReactionSrcNodes == NULL)
    {
        return -13;
    }
    getListOfReactionDestNodes = (getListOfReactionDestNodesProc)GetProcAddress(Iod_hinstLib, "getListOfReactionDestNodes");
    if (getListOfReactionDestNodes == NULL)
    {
        return -13;
    }
    getReactionNodeID = (getReactionNodeIDProc)GetProcAddress(Iod_hinstLib, "getReactionNodeID");
    if (getReactionNodeID == NULL)
    {
        return -13;
    }
    Iod_addSrcNode = (addSrcNodeProc)GetProcAddress(Iod_hinstLib, "addSrcNode");
    if (Iod_addSrcNode == NULL)
    {
        return -13;
    }
    Iod_addDestNode = (addDestNodeProc)GetProcAddress(Iod_hinstLib, "addDestNode");
    if (Iod_addDestNode == NULL)
    {
        return -13;
    }
    Iod_deleteSrcNode = (deleteSrcNodeProc)GetProcAddress(Iod_hinstLib, "deleteSrcNode");
    if (Iod_deleteSrcNode == NULL)
    {
        return -13;
    }
    Iod_deleteDestNode = (deleteDestNodeProc)GetProcAddress(Iod_hinstLib, "deleteDestNode");
    if (Iod_deleteDestNode == NULL)
    {
        return -13;
    }
    Iod_setReactionID = (setReactionIDProc)GetProcAddress(Iod_hinstLib, "setReactionID");
    if (Iod_setReactionID == NULL)
    {
        return -13;
    }
    Iod_setRateLaw = (setRateLawProc)GetProcAddress(Iod_hinstLib, "setRateLaw");
    if (Iod_setRateLaw == NULL)
    {
        return -13;
    }
    Iod_setReactionSrcNodeStoich = (setReactionSrcNodeStoichProc)GetProcAddress(Iod_hinstLib, "setReactionSrcNodeStoich");
    if (Iod_setReactionSrcNodeStoich == NULL)
    {
        return -13;
    }
    Iod_setReactionDestNodeStoich = (setReactionDestNodeStoichProc)GetProcAddress(Iod_hinstLib, "setReactionDestNodeStoich");
    if (Iod_setReactionDestNodeStoich == NULL)
    {
        return -13;
    }
    Iod_setReactionSrcNodeHandlePosition = (setReactionSrcNodeHandlePositionProc)GetProcAddress(Iod_hinstLib, "setReactionSrcNodeHandlePosition");
    if (Iod_setReactionSrcNodeHandlePosition == NULL)
    {
        return -13;
    }
    Iod_setReactionDestNodeHandlePosition = (setReactionDestNodeHandlePositionProc)GetProcAddress(Iod_hinstLib, "setReactionDestNodeHandlePosition");
    if (Iod_setReactionDestNodeHandlePosition == NULL)
    {
        return -13;
    }
    Iod_setReactionFillColorRGB = (setReactionFillColorRGBProc)GetProcAddress(Iod_hinstLib, "setReactionFillColorRGB");
    if (Iod_setReactionFillColorRGB == NULL)
    {
        return -13;
    }
    Iod_setReactionFillColorAlpha = (setReactionFillColorAlphaProc)GetProcAddress(Iod_hinstLib, "setReactionFillColorAlpha");
    if (Iod_setReactionFillColorAlpha == NULL)
    {
        return -13;
    }
    Iod_setReactionLineThickness = (setReactionLineThicknessProc)GetProcAddress(Iod_hinstLib, "setReactionLineThickness");
    if (Iod_setReactionLineThickness == NULL)
    {
        return -13;
    }
    Iod_setReactionCenterHandlePosition = (setReactionCenterHandlePositionProc)GetProcAddress(Iod_hinstLib, "setReactionCenterHandlePosition");
    if (Iod_setReactionCenterHandlePosition == NULL)
    {
        return -13;
    }
    return 0;
}

Color color;

void clearColor()
{
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
}

Color *Iod_getNodeFillColor(int neti, int nodei)
{
    int rgb = Iod_getNodeFillColorRGB(neti, nodei);
    int a = Iod_getNodeFillColorAlpha(neti, nodei);
    clearColor();
    color.r = rgb >> 16;
    color.g = (rgb >> 8) - (color.r << 8);
    color.b = rgb - (rgb >> 8 << 8);
    color.a = a;
    return &color;
}

Color *Iod_getNodeOutlineColor(int neti, int nodei)
{
    int rgb = Iod_getNodeOutlineColorRGB(neti, nodei);
    int a = Iod_getNodeOutlineColorAlpha(neti, nodei);
    clearColor();
    color.r = rgb >> 16;
    color.g = (rgb >> 8) - (color.r << 8);
    color.b = rgb - (rgb >> 8 << 8);
    color.a = a;
    return &color;
}

Color *Iod_getReactionFillColor(int neti, int reai)
{
    int rgb = Iod_getReactionFillColorRGB(neti, reai);
    int a = Iod_getReactionFillColorAlpha(neti, reai);
    clearColor();
    color.r = rgb >> 16;
    color.g = (rgb >> 8) - (color.r << 8);
    color.b = rgb - (rgb >> 8 << 8);
    color.a = a;
    return &color;
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
    setErrorCode(0);
    int a = Iod_getNumberOfNodes(netIndex);
    if (a < 0)
    {
        setErrorCode(a);
        return &ListOfIDs[0];
    }
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = Iod_getNodeID(netIndex, i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfReactionIDs(int netIndex)
{
    memset(ListOfIDs, 0, 100);
    setErrorCode(0);
    int a = Iod_getNumberOfReactions(netIndex);
    if (a < 0)
    {
        setErrorCode(a);
        return &ListOfIDs[0];
    }
    for (int i = 0; i < a; i++)
    {
        ListOfIDs[i] = Iod_getReactionID(netIndex, i);
    }
    return &ListOfIDs[0];
}

char **Iod_getListOfReactionSrcNodes(int netIndex, int reactionIndex)
{
    memset(ListOfIDs, 0, 100);
    setErrorCode(0);

    int a0 = getListOfReactionSrcNodes(netIndex, reactionIndex);
    if (a0 < 0)
    {
        setErrorCode(a0);
        return &ListOfIDs[0];
    }
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
    setErrorCode(0);

    int a0 = getListOfReactionDestNodes(netIndex, reactionIndex);
    if (a0 < 0)
    {
        setErrorCode(a0);
        return &ListOfIDs[0];
    }
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
    setErrorCode(0);

    Iod_getListOfReactionSrcNodes(netIndex, reactionIndex);
    int a = Iod_getErrorCode();
    if (a < 0)
    {
        return &ListOfStoich[0];
    }
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
    setErrorCode(0);

    Iod_getListOfReactionDestNodes(netIndex, reactionIndex);
    int a = Iod_getErrorCode();
    if (a < 0)
    {
        setErrorCode(a);
        return &ListOfStoich[0];
    }

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
    Iod_startGroup();
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, srci, srcStoich);
    Iod_addDestNode(neti, reai, desti, destStoich);
    Iod_setRateLaw(neti, reai, rateLaw);
    Iod_endGroup();
}

void Iod_createUniBi(int neti, const char *reaID, const char *rateLaw, int srci, int dest1i, int dest2i, float srcStoich, float dest1Stoich, float dest2Stoich)
{
    Iod_startGroup();
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, srci, srcStoich);
    Iod_addDestNode(neti, reai, dest1i, dest1Stoich);
    Iod_addDestNode(neti, reai, dest2i, dest2Stoich);
    Iod_setRateLaw(neti, reai, rateLaw);
    Iod_endGroup();
}

void Iod_createBiUni(int neti, const char *reaID, const char *rateLaw, int src1i, int src2i, int desti, float src1Stoich, float src2Stoich, float destStoich)
{
    Iod_startGroup();
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, src1i, src1Stoich);
    Iod_addSrcNode(neti, reai, src2i, src2Stoich);
    Iod_addDestNode(neti, reai, desti, destStoich);
    Iod_setRateLaw(neti, reai, rateLaw);
    Iod_endGroup();
}

void Iod_createBiBi(int neti, const char *reaID, const char *rateLaw, int src1i, int src2i, int dest1i, int dest2i, float src1Stoich, float src2Stoich, float dest1Stoich, float dest2Stoich)
{
    Iod_startGroup();
    Iod_createReaction(neti, reaID);
    int reai = Iod_getReactionIndex(neti, reaID);

    Iod_addSrcNode(neti, reai, src1i, src1Stoich);
    Iod_addSrcNode(neti, reai, src2i, src2Stoich);
    Iod_addDestNode(neti, reai, dest1i, dest1Stoich);
    Iod_addDestNode(neti, reai, dest2i, dest2Stoich);
    Iod_setRateLaw(neti, reai, rateLaw);
    Iod_endGroup();
}

bool Iod_strArrayEqual(char **array1, char **array2)
{
    bool equal = TRUE;

    for (int i = 0; i < 100; i++)
    {
        if (array1[i] != NULL && array2[i] != NULL)
        {
            if (strcmp(array1[i], array2[i]) != 0)
            {
                equal = FALSE;
                return equal;
            }
        }
        else if (array1[i] == NULL && array2[i] == NULL)
        {
            break;
        }
        else
        {
            equal = FALSE;
            return equal;
        }
    }
    return equal;
}

bool Iod_floatArrayEqual(float *array1, float *array2, float dicimal)
{
    bool equal = TRUE;

    for (int i = 0; i < 100; i++)
    {
        if (fabs(array1[i] - array2[i]) > dicimal)
        {
            equal = FALSE;
            return equal;
        }
    }
    return equal;
}

bool Iod_floatEqual(float float1, const float float2, float threshold)
{
    bool equal = TRUE;
    if (fabs(float1 - float2) > threshold)
    {
        equal = FALSE;
        return equal;
    }
    return equal;
}

bool Iod_colorEqual(Color *color1, Color *color2)
{
    bool equal = FALSE;
    if ((color1->r == color2->r) && (color1->g == color2->g) && (color1->b == color2->b) && (color1->a == color2->a))
    {
        equal = TRUE;
    }
    return equal;
}