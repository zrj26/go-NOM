import ctypes

libIodine = ctypes.cdll.LoadLibrary('../Iodine_Dll/Iodine.dll')

#########################   argtypes   #########################
libIodine.cFree.argtypes = [ctypes.c_char_p]
libIodine.newNetwork.argtypes = [ctypes.c_char_p]
libIodine.getNetworkIndex.argtypes = [ctypes.c_char_p]
libIodine.saveNetworkAsJSON.argtypes = [
    ctypes.c_int,  ctypes.c_char_p]
libIodine.readNetworkFromJSON.argtypes = [
    ctypes.c_char_p]
libIodine.deleteNetwork.argtypes = [ctypes.c_int]
libIodine.getNetworkID.argtypes = [ctypes.c_int]
libIodine.getNetworkBool.argtypes = [ctypes.c_int]
libIodine.addNode.argtypes = [ctypes.c_int, ctypes.c_char_p,
                              ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float]
libIodine.getNodeIndex.argtypes = [ctypes.c_int, ctypes.c_char_p]
libIodine.deleteNode.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.clearNetwork.argtypes = [ctypes.c_int]
libIodine.getNumberOfNodes.argtypes = [ctypes.c_int]
libIodine.getLargestNodeIndex.argtypes = [ctypes.c_int]
libIodine.getNodeCenterX.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeCenterY.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeID.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeBool.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeX.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeY.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeW.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeH.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFillColorRGB.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFillColorAlpha.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeOutlineColorRGB.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeOutlineColorAlpha.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeOutlineThickness.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontPointSize.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontFamily.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontStyle.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontWeight.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontName.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontColorRGB.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getNodeFontColorAlpha.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.setNodeID.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setNodeCoordinate.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float, ctypes.c_float]
libIodine.setNodeSize.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float, ctypes.c_float]
libIodine.setNodeFillColorRGB.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
libIodine.setNodeFillColorAlpha.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.setNodeOutlineColorRGB.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
libIodine.setNodeOutlineColorAlpha.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.setNodeOutlineThickness.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.setNodeFontPointSize.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_int]
libIodine.setNodeFontFamily.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setNodeFontStyle.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setNodeFontWeight.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setNodeFontName.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setNodeFontColorRGB.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
libIodine.setNodeFontColorAlpha.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]

libIodine.createReaction.argtypes = [ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionIndex.argtypes = [ctypes.c_int, ctypes.c_char_p]
libIodine.deleteReaction.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.clearReactions.argtypes = [ctypes.c_int]
libIodine.getNumberOfReactions.argtypes = [ctypes.c_int]
libIodine.getLargestReactionIndex.argtypes = [ctypes.c_int]
libIodine.getReactionID.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionBool.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionRateLaw.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionFillColorRGB.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionFillColorAlpha.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionLineThickness.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionCenterHandleX.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionCenterHandleY.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionSrcNodeStoich.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionDestNodeStoich.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionSrcNodeHandleX.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionSrcNodeHandleY.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionDestNodeHandleX.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getReactionDestNodeHandleY.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.getNumberOfSrcNodes.argtypes = [
    ctypes.c_int, ctypes.c_int]
libIodine.getNumberOfDestNodes.argtypes = [
    ctypes.c_int, ctypes.c_int]
libIodine.getListOfReactionSrcNodes.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getListOfReactionDestNodes.argtypes = [ctypes.c_int, ctypes.c_int]
libIodine.getReactionNodeID.argtypes = [ctypes.c_int]
libIodine.addSrcNode.argtypes = [ctypes.c_int,
                                 ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.addDestNode.argtypes = [ctypes.c_int,
                                  ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.deleteSrcNode.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.deleteDestNode.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setReactionID.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setRateLaw.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
libIodine.setReactionSrcNodeStoich.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_float]
libIodine.setReactionDestNodeStoich.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_float]
libIodine.setReactionSrcNodeHandlePosition.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_float, ctypes.c_float]
libIodine.setReactionDestNodeHandlePosition.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_float, ctypes.c_float]
libIodine.setReactionFillColorRGB.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
libIodine.setReactionFillColorAlpha.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.setReactionLineThickness.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float]
libIodine.setReactionCenterHandlePosition.argtypes = [
    ctypes.c_int, ctypes.c_int, ctypes.c_float, ctypes.c_float]


#########################   restype   #########################
libIodine.getErrorCode.restype = ctypes.c_int
libIodine.undo.restype = ctypes.c_int
libIodine.redo.restype = ctypes.c_int
libIodine.getErrorMessage.restype = ctypes.c_char_p
libIodine.getDetailErrorMessage.restype = ctypes.c_char_p
libIodine.newNetwork.restype = ctypes.c_int
libIodine.getNetworkIndex.restype = ctypes.c_int
libIodine.saveNetworkAsJSON.restype = ctypes.c_int
libIodine.readNetworkFromJSON.restype = ctypes.c_int
libIodine.deleteNetwork.restype = ctypes.c_int
libIodine.getNumberOfNetworks.restype = ctypes.c_int
libIodine.getLargestNetworkIndex.restype = ctypes.c_int
libIodine.getNetworkID.restype = ctypes.c_char_p
libIodine.getNetworkBool.restype = ctypes.c_int
libIodine.addNode.restype = ctypes.c_int
libIodine.getNodeIndex.restype = ctypes.c_int
libIodine.deleteNode.restype = ctypes.c_int
libIodine.clearNetwork.restype = ctypes.c_int
libIodine.getNumberOfNodes.restype = ctypes.c_int
libIodine.getLargestNodeIndex.restype = ctypes.c_int
libIodine.getNodeCenterX.restype = ctypes.c_float
libIodine.getNodeCenterY.restype = ctypes.c_float
libIodine.getNodeID.restype = ctypes.c_char_p
libIodine.getNodeBool.restype = ctypes.c_int
libIodine.getNodeX.restype = ctypes.c_float
libIodine.getNodeY.restype = ctypes.c_float
libIodine.getNodeW.restype = ctypes.c_float
libIodine.getNodeH.restype = ctypes.c_float
libIodine.getNodeFillColorRGB.restype = ctypes.c_uint32
libIodine.getNodeFillColorAlpha.restype = ctypes.c_float
libIodine.getNodeOutlineColorRGB.restype = ctypes.c_uint32
libIodine.getNodeOutlineColorAlpha.restype = ctypes.c_float
libIodine.getNodeOutlineThickness.restype = ctypes.c_float
libIodine.getNodeFontPointSize.restype = ctypes.c_int
libIodine.getNodeFontFamily.restype = ctypes.c_char_p
libIodine.getNodeFontStyle.restype = ctypes.c_char_p
libIodine.getNodeFontWeight.restype = ctypes.c_char_p
libIodine.getNodeFontName.restype = ctypes.c_char_p
libIodine.getNodeFontColorRGB.restype = ctypes.c_uint32
libIodine.getNodeFontColorAlpha.restype = ctypes.c_float
libIodine.setNodeID.restype = ctypes.c_int
libIodine.setNodeCoordinate.restype = ctypes.c_int
libIodine.setNodeSize.restype = ctypes.c_int
libIodine.setNodeFillColorRGB.restype = ctypes.c_int
libIodine.setNodeFillColorAlpha.restype = ctypes.c_int
libIodine.setNodeOutlineColorRGB.restype = ctypes.c_int
libIodine.setNodeOutlineColorAlpha.restype = ctypes.c_int
libIodine.setNodeOutlineThickness.restype = ctypes.c_int
libIodine.setNodeFontPointSize.restype = ctypes.c_int
libIodine.setNodeFontFamily.restype = ctypes.c_int
libIodine.setNodeFontStyle.restype = ctypes.c_int
libIodine.setNodeFontWeight.restype = ctypes.c_int
libIodine.setNodeFontName.restype = ctypes.c_int
libIodine.setNodeFontColorRGB.restype = ctypes.c_int
libIodine.setNodeFontColorAlpha.restype = ctypes.c_int

libIodine.createReaction.restype = ctypes.c_int
libIodine.getReactionIndex.restype = ctypes.c_int
libIodine.deleteReaction.restype = ctypes.c_int
libIodine.clearReactions.restype = ctypes.c_int
libIodine.getNumberOfReactions.restype = ctypes.c_int
libIodine.getLargestReactionIndex.restype = ctypes.c_int
libIodine.getReactionID.restype = ctypes.c_char_p
libIodine.getReactionBool.restype = ctypes.c_int
libIodine.getReactionRateLaw.restype = ctypes.c_char_p
libIodine.getReactionFillColorRGB.restype = ctypes.c_uint32
libIodine.getReactionFillColorAlpha.restype = ctypes.c_float
libIodine.getReactionLineThickness.restype = ctypes.c_float
libIodine.getReactionCenterHandleX.restype = ctypes.c_float
libIodine.getReactionCenterHandleY.restype = ctypes.c_float
libIodine.getReactionSrcNodeStoich.restype = ctypes.c_float
libIodine.getReactionDestNodeStoich.restype = ctypes.c_float
libIodine.getReactionSrcNodeHandleX.restype = ctypes.c_float
libIodine.getReactionSrcNodeHandleY.restype = ctypes.c_float
libIodine.getReactionDestNodeHandleX.restype = ctypes.c_float
libIodine.getReactionDestNodeHandleY.restype = ctypes.c_float
libIodine.getNumberOfSrcNodes.restype = ctypes.c_int
libIodine.getNumberOfDestNodes.restype = ctypes.c_int
libIodine.getListOfReactionSrcNodes.restype = ctypes.c_int
libIodine.getListOfReactionDestNodes.restype = ctypes.c_int
libIodine.getReactionNodeID.restype = ctypes.c_char_p
libIodine.addSrcNode.restype = ctypes.c_int
libIodine.addDestNode.restype = ctypes.c_int
libIodine.deleteSrcNode.restype = ctypes.c_int
libIodine.deleteDestNode.restype = ctypes.c_int
libIodine.setReactionID.restype = ctypes.c_int
libIodine.setRateLaw.restype = ctypes.c_int
libIodine.setReactionSrcNodeStoich.restype = ctypes.c_int
libIodine.setReactionDestNodeStoich.restype = ctypes.c_int
libIodine.setReactionSrcNodeHandlePosition.restype = ctypes.c_int
libIodine.setReactionDestNodeHandlePosition.restype = ctypes.c_int
libIodine.setReactionFillColorRGB.restype = ctypes.c_int
libIodine.setReactionFillColorAlpha.restype = ctypes.c_int
libIodine.setReactionLineThickness.restype = ctypes.c_int
libIodine.setReactionCenterHandlePosition.restype = ctypes.c_int


class Error(Exception):
    """Base class for other exceptions"""
    pass


class IDNotFoundError(Error):
    pass


class IDRepeatError(Error):
    pass


class NodeNotFreeError(Error):
    pass


class NetIndexOutOfRangeError(Error):
    pass


class ReactionIndexOutOfRangeError(Error):
    pass


class NodeIndexOutOfRangeError(Error):
    pass


class StoichError(Error):
    pass


class StackEmptyError(Error):
    pass


class JSONError(Error):
    pass


class FileError(Error):
    pass


class VariableOutOfRangeError(Error):
    pass


errorDict = {
    0: "ok",
    -1: "other",
    -2: "id not found: ",
    -3: "id repeat: ",
    -4: "node is not free: ",
    -5: "invalid net index: ",
    -6: "invalid reaction index: ",
    -7: "invalid node index: ",
    -8: "wrong stoich: stoich has to be positive: ",
    -9: "stack is empty",
    -10: "Json convert error",
    -11: "File error",
    -12: "Variable out of range: "
}


ExceptionDict = {
    -2: IDNotFoundError,
    -3: IDRepeatError,
    -4: NodeNotFreeError,
    -5: NetIndexOutOfRangeError,
    -6: ReactionIndexOutOfRangeError,
    -7: NodeIndexOutOfRangeError,
    -8: StoichError,
    -9: StackEmptyError,
    -10: JSONError,
    -11: FileError,
    -12: VariableOutOfRangeError
}


def getErrorCode():
    """get the error code of last function"""
    errCode = libIodine.getErrorCode()
    return errCode


def undo():
    errCode = libIodine.undo()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode])


def redo():
    errCode = libIodine.redo()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode])


def startGroup():
    libIodine.startGroup()


def endGroup():
    libIodine.endGroup()


def cFree(cString):
    libIodine.cFree(cString)


def getErrorMessage():
    return libIodine.getErrorMessage().decode("utf-8")


def getDetailErrorMessage():
    return libIodine.getDetailErrorMessage().decode("utf-8")


def newNetwork(netID: str):
    errCode = libIodine.newNetwork(netID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], netID)


def getNetworkIndex(netID: str):
    neti = libIodine.getNetworkIndex(netID.encode())
    if neti < 0:
        raise ExceptionDict[neti](errorDict[neti], netID)
    else:
        return neti


def saveNetworkAsJSON(neti: int, fileName: str):
    errCode = libIodine.saveNetworkAsJSON(
        neti, fileName.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, fileName)


def readNetworkFromJSON(filePath: str):
    errCode = libIodine.readNetworkFromJSON(filePath.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], filePath)


def deleteNetwork(neti: int):
    errCode = libIodine.deleteNetwork(neti)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti)


def clearNetworks():
    libIodine.clearNetworks()


def getNumberOfNetworks():
    return libIodine.getNumberOfNetworks()

def getLargestNetworkIndex():
    return libIodine.getLargestNetworkIndex()

def getNetworkID(neti: int):
    netID = libIodine.getNetworkID(neti).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode],  neti)
    else:
        return netID

def getNetworkBool(neti: int):
    bool1 = libIodine.getNetworkBool(neti)
    if bool1 < 0:
        raise ExceptionDict[bool1](errorDict[bool1],  neti)
    else:
        return bool1


def getListOfNetworks():
    a = getLargestNetworkIndex()
    idList = []
    for neti in range(a):
        bool1 = getNetworkBool(neti)
        if bool1 == 1:
            idList.append(getNetworkID(neti))
    return idList


def addNode(neti: int, nodeID: str, x: float, y: float, w: float, h: float):
    errCode = libIodine.addNode(neti, nodeID.encode(), x, y, w, h)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodeID, x, y, w, h)


def getNodeIndex(neti: int, nodeID: str):
    nodei = libIodine.getNodeIndex(neti, nodeID.encode())
    if nodei < 0:
        raise ExceptionDict[nodei](errorDict[nodei], neti, nodeID)
    else:
        return nodei


def deleteNode(neti: int, nodei: int):
    errCode = libIodine.deleteNode(neti, nodei)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def clearNetwork(neti: int):
    errCode = libIodine.clearNetwork(neti)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti)


def getNumberOfNodes(neti: int):
    num = libIodine.getNumberOfNodes(neti)
    if num < 0:
        raise ExceptionDict[num](errorDict[num], neti)
    else:
        return num

def getLargestNodeIndex(neti: int):
    num = libIodine.getLargestNodeIndex(neti)
    if num < 0:
        raise ExceptionDict[num](errorDict[num], neti)
    else:
        return num

def getNodeCenter(neti: int, nodei: int):
    X = round(libIodine.getNodeCenterX(neti, nodei), 2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    Y = round(libIodine.getNodeCenterY(neti, nodei), 2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return (X, Y)


def getNodeID(neti: int, nodei: int):
    nodeID = libIodine.getNodeID(neti, nodei).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    else:
        return nodeID

def getNodeBool(neti: int, nodei: int):
    bool1 = libIodine.getNodeBool(neti, nodei)
    if bool1 < 0:
        raise ExceptionDict[bool1](errorDict[bool1], neti)
    else:
        return bool1


def getListOfNodeIDs(neti: int):
    n = getLargestNodeIndex(neti)
    nodeList = []
    for nodei in range(n):
        bool1 = getNodeBool(neti, nodei)
        if bool1 == 1:
            nodeList.append(getNodeID(neti, nodei))
    return nodeList


def getNodeCoordinateAndSize(neti: int, nodei: int):
    X = round(libIodine.getNodeX(neti, nodei), 2)
    Y = round(libIodine.getNodeY(neti, nodei), 2)
    W = round(libIodine.getNodeW(neti, nodei), 2)
    H = round(libIodine.getNodeH(neti, nodei), 2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return (X, Y, W, H)


def getNodeFillColor(neti: int, nodei: int):
    rgb = libIodine.getNodeFillColorRGB(neti, nodei)
    a = libIodine.getNodeFillColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    r = rgb >> 16
    g = (rgb >> 8)-(r << 8)
    b = rgb - (rgb >> 8 << 8)

    return (r, g, b, a)


def getNodeFillColorRGB(neti: int, nodei: int):
    color1 = libIodine.getNodeFillColorRGB(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return color1


def getNodeFillColorAlpha(neti: int, nodei: int):
    alpha1 = libIodine.getNodeFillColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return alpha1


def getNodeOutlineColor(neti: int, nodei: int):
    rgb = libIodine.getNodeOutlineColorRGB(neti, nodei)
    a = libIodine.getNodeOutlineColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    r = rgb >> 16
    g = (rgb >> 8)-(r << 8)
    b = rgb - (rgb >> 8 << 8)

    return (r, g, b, a)


def getNodeOutlineColorRGB(neti: int, nodei: int):
    color1 = libIodine.getNodeOutlineColorRGB(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return color1


def getNodeOutlineColorAlpha(neti: int, nodei: int):
    alpha1 = libIodine.getNodeOutlineColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return alpha1


def getNodeOutlineThickness(neti: int, nodei: int):
    thickness = libIodine.getNodeOutlineThickness(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return thickness


def getNodeFontPointSize(neti: int, nodei: int):
    fontPointSize = libIodine.getNodeFontPointSize(neti, nodei)
    if fontPointSize < 0:
        raise ExceptionDict[fontPointSize](
            errorDict[fontPointSize], neti, nodei)
    return fontPointSize


def getNodeFontFamily(neti: int, nodei: int):
    fontFamily = libIodine.getNodeFontFamily(neti, nodei).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    else:
        return fontFamily


def getNodeFontStyle(neti: int, nodei: int):
    fontStyle = libIodine.getNodeFontStyle(neti, nodei).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    else:
        return fontStyle


def getNodeFontWeight(neti: int, nodei: int):
    fontWeight = libIodine.getNodeFontWeight(neti, nodei).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    else:
        return fontWeight


def getNodeFontName(neti: int, nodei: int):
    fontName = libIodine.getNodeFontName(neti, nodei).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    else:
        return fontName


def getNodeFontColor(neti: int, nodei: int):
    rgb = libIodine.getNodeFontColorRGB(neti, nodei)
    a = libIodine.getNodeFontColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    r = rgb >> 16
    g = (rgb >> 8)-(r << 8)
    b = rgb - (rgb >> 8 << 8)

    return (r, g, b, a)


def getNodeFontColorRGB(neti: int, nodei: int):
    color1 = libIodine.getNodeFontColorRGB(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return color1


def getNodeFontColorAlpha(neti: int, nodei: int):
    alpha1 = libIodine.getNodeFontColorAlpha(neti, nodei)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)
    return alpha1


def setNodeID(neti: int, nodei: int, newID: str):
    errCode = libIodine.setNodeID(neti, nodei, newID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei, newID)


def setNodeCoordinate(neti: int, nodei: int, x: float, y: float):
    errCode = libIodine.setNodeCoordinate(neti, nodei, x, y)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei, x, y)


def setNodeSize(neti: int, nodei: int,  w: float, h: float):
    errCode = libIodine.setNodeSize(neti, nodei, w, h)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei, w, h)


def setNodeFillColorRGB(neti: int, nodei: int,  r: int, g: int, b: int):
    errCode = libIodine.setNodeFillColorRGB(neti, nodei, r, g, b)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def setNodeFillColorAlpha(neti: int, nodei: int,  a: float):
    errCode = libIodine.setNodeFillColorAlpha(neti, nodei, a)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def setNodeOutlineColorRGB(neti: int, nodei: int,  r: int, g: int, b: int):
    errCode = libIodine.setNodeOutlineColorRGB(neti, nodei, r, g, b)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def setNodeOutlineColorAlpha(neti: int, nodei: int, a: float):
    errCode = libIodine.setNodeOutlineColorAlpha(neti, nodei, a)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def setNodeOutlineThickness(neti: int, nodei: int,  thickness: float):
    errCode = libIodine.setNodeOutlineThickness(neti, nodei, thickness)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodei, thickness)


def setNodeFontPointSize(neti: int, nodei: int,  fontPointSize: int):
    errCode = libIodine.setNodeFontPointSize(neti, nodei, fontPointSize)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodei, fontPointSize)


def setNodeFontFamily(neti: int, nodei: int, fontFamily: str):
    errCode = libIodine.setNodeFontFamily(neti, nodei, fontFamily.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodei, fontFamily)


def setNodeFontStyle(neti: int, nodei: int, fontStyle: str):
    errCode = libIodine.setNodeFontStyle(neti, nodei, fontStyle.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodei, fontStyle)


def setNodeFontWeight(neti: int, nodei: int, fontWeight: str):
    errCode = libIodine.setNodeFontWeight(neti, nodei, fontWeight.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, nodei, fontWeight)


def setNodeFontName(neti: int, nodei: int, fontName: str):
    errCode = libIodine.setNodeFontName(neti, nodei, fontName.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei, fontName)


def setNodeFontColorRGB(neti: int, nodei: int,  r: int, g: int, b: int):
    errCode = libIodine.setNodeFontColorRGB(neti, nodei, r, g, b)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def setNodeFontColorAlpha(neti: int, nodei: int,  a: float):
    errCode = libIodine.setNodeFontColorAlpha(neti, nodei, a)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, nodei)


def createReaction(neti: int, reaID: str):
    errCode = libIodine.createReaction(neti, reaID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reaID)


def getReactionIndex(neti: int, reaID: str):
    reai = libIodine.getReactionIndex(neti, reaID.encode())
    if reai < 0:
        raise ExceptionDict[reai](errorDict[reai], neti, reaID)
    else:
        return reai


def deleteReaction(neti: int, reai: int):
    errCode = libIodine.deleteReaction(neti, reai)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)


def clearReactions(neti: int):
    errCode = libIodine.clearReactions(neti)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti)


def getNumberOfReactions(neti: int):
    reaNum = libIodine.getNumberOfReactions(neti)
    if reaNum < 0:
        raise ExceptionDict[reaNum](errorDict[reaNum], neti)
    else:
        return reaNum

def getLargestReactionIndex(neti: int):
    reaNum = libIodine.getLargestReactionIndex(neti)
    if reaNum < 0:
        raise ExceptionDict[reaNum](errorDict[reaNum], neti)
    else:
        return reaNum

def getReactionID(neti: int, reai: int):
    reaID = libIodine.getReactionID(neti, reai).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return reaID


def getReactionBool(neti: int, reai: int):
    bool1 = libIodine.getReactionBool(neti, reai)
    if bool1 < 0:
        raise ExceptionDict[bool1](errorDict[bool1], neti)
    else:
        return bool1

def getListOfReactionIDs(neti: int):
    n = getLargestReactionIndex(neti)
    reaList = []
    for i in range(n):
        bool1 = getReactionBool(neti, i)
        if bool1 == 1:
            reaList.append(getReactionID(neti, i))
    return reaList


def getReactionRateLaw(neti: int, reai: int):
    rateLaw = libIodine.getReactionRateLaw(neti, reai).decode("utf-8")
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return rateLaw


def getReactionFillColor(neti: int, reai: int):
    rgb = libIodine.getReactionFillColorRGB(neti, reai)
    a = libIodine.getReactionFillColorAlpha(neti, reai)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    r = rgb >> 16
    g = (rgb >> 8)-(r << 8)
    b = rgb - (rgb >> 8 << 8)

    return (r, g, b, a)


def getReactionFillColorRGB(neti: int, reai: int):
    color1 = libIodine.getReactionFillColorRGB(neti, reai)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return color1


def getReactionFillColorAlpha(neti: int, reai: int):
    alpha1 = libIodine.getReactionFillColorAlpha(neti, reai)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return alpha1


def getReactionLineThickness(neti: int, reai: int):
    thickness = libIodine.getReactionLineThickness(neti, reai)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return thickness


def getReactionCenterHandlePosition(neti: int, reai: int):
    handleX = round(libIodine.getReactionCenterHandleX(neti, reai),2)
    handleY = round(libIodine.getReactionCenterHandleY(neti, reai),2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai)
    else:
        return (handleX, handleY)



def getReactionSrcNodeStoich(neti: int, reai: int, srcNodeID: str):
    SrcNodeStoich = libIodine.getReactionSrcNodeStoich(
        neti, reai, srcNodeID.encode())
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, srcNodeID)
    else:
        return round(SrcNodeStoich, 2)


def getReactionDestNodeStoich(neti: int, reai: int, destNodeID: str):
    DestNodeStoich = libIodine.getReactionDestNodeStoich(
        neti, reai, destNodeID.encode())
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, destNodeID)
    else:
        return round(DestNodeStoich, 2)


def getReactionSrcNodeHandlePosition(neti: int, reai: int, srcNodeID: str):
    X = round(libIodine.getReactionSrcNodeHandleX(
        neti, reai, srcNodeID.encode()), 2)
    Y = round(libIodine.getReactionSrcNodeHandleY(
        neti, reai, srcNodeID.encode()), 2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, srcNodeID)
    else:
        return (X,Y)


def getReactionDestNodeHandlePosition(neti: int, reai: int, destNodeID: str):
    X = round(libIodine.getReactionDestNodeHandleX(
        neti, reai, destNodeID.encode()), 2)
    Y = round(libIodine.getReactionDestNodeHandleY(
        neti, reai, destNodeID.encode()), 2)
    errCode = getErrorCode()
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, destNodeID)
    else:
        return (X, Y)

def getNumberOfSrcNodes(neti: int, reai: int):
    Num = libIodine.getNumberOfSrcNodes(neti, reai)
    if Num < 0:
        raise ExceptionDict[Num](
            errorDict[Num], neti, reai)
    else:
        return Num


def getNumberOfDestNodes(neti: int, reai: int):
    Num = libIodine.getNumberOfDestNodes(neti, reai)
    if Num < 0:
        raise ExceptionDict[Num](
            errorDict[Num], neti, reai)
    else:
        return Num


def getListOfReactionSrcNodes(neti: int, reai: int):
    errCode = libIodine.getListOfReactionSrcNodes(neti, reai)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai)
    n = getNumberOfSrcNodes(neti, reai)
    nodeList = []
    for i in range(n):
        nodeList.append(libIodine.getReactionNodeID(i).decode("utf-8"))
    return nodeList


def getListOfReactionDestNodes(neti: int, reai: int):
    errCode = libIodine.getListOfReactionDestNodes(neti, reai)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai)
    n = getNumberOfDestNodes(neti, reai)
    nodeList = []
    for i in range(n):
        nodeList.append(libIodine.getReactionNodeID(i).decode("utf-8"))
    return nodeList


def getListOfReactionSrcStoich(neti: int, reai: int):
    n = getListOfReactionSrcNodes(neti, reai)
    srcStoichList = []
    for srcNodeID in n:
        srcStoichList.append(getReactionSrcNodeStoich(neti, reai, srcNodeID))
    return srcStoichList


def getListOfReactionDestStoich(neti: int, reai: int):
    n = getListOfReactionDestNodes(neti, reai)
    destStoichList = []
    for destNodeID in n:
        destStoichList.append(
            getReactionDestNodeStoich(neti, reai, destNodeID))
    return destStoichList


def printReactionInfo(neti: int, reai: int):
    print("id:", getReactionID(neti, reai))
    print("rateLaw:", getReactionRateLaw(neti, reai))
    print("SrcNodes:", getListOfReactionSrcNodes(neti, reai))
    print("DestNodes:", getListOfReactionDestNodes(neti, reai))
    print("SrcNodeStoichs:", getListOfReactionSrcStoich(neti, reai))
    print("DestNodeStoichs:", getListOfReactionDestStoich(neti, reai))


def addSrcNode(neti: int, reai: int, nodei: int, stoich: float):
    errCode = libIodine.addSrcNode(neti, reai, nodei, stoich)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, nodei, stoich)


def addDestNode(neti: int, reai: int, nodei: int, stoich: float):
    errCode = libIodine.addDestNode(neti, reai, nodei, stoich)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, nodei, stoich)


def deleteSrcNode(neti: int, reai: int, srcNodeID: str):
    errCode = libIodine.deleteSrcNode(
        neti, reai, srcNodeID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai, srcNodeID)


def deleteDestNode(neti: int, reai: int, destNodeID: str):
    errCode = libIodine.deleteDestNode(
        neti, reai, destNodeID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, destNodeID)


def setReactionID(neti: int, reai: int, newID: str):
    errCode = libIodine.setReactionID(neti, reai, newID.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai, newID)


def setRateLaw(neti: int, reai: int, rateLaw: str):
    errCode = libIodine.setRateLaw(neti, reai, rateLaw.encode())
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai, rateLaw)


def setReactionSrcNodeStoich(neti: int, reai: int, srcNodeID: str, newStoich: float):
    errCode = libIodine.setReactionSrcNodeStoich(
        neti, reai, srcNodeID.encode(), newStoich)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, srcNodeID, newStoich)


def setReactionDestNodeStoich(neti: int, reai: int, destNodeID: str, newStoich: float):
    errCode = libIodine.setReactionDestNodeStoich(
        neti, reai, destNodeID.encode(), newStoich)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, destNodeID, newStoich)


def setReactionSrcNodeHandlePosition(neti: int, reai: int, srcNodeID: str, handleX: float, handleY: float):
    errCode = libIodine.setReactionSrcNodeHandlePosition(
        neti, reai, srcNodeID.encode(), handleX, handleY)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, srcNodeID, handleX, handleY)


def setReactionDestNodeHandlePosition(neti: int, reai: int, destNodeID: str, handleX: float, handleY: float):
    errCode = libIodine.setReactionDestNodeHandlePosition(
        neti, reai, destNodeID.encode(), handleX, handleY)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, destNodeID, handleX, handleY)

def setReactionFillColorRGB(neti: int, reai: int, r: int, g: int, b: int):
    errCode = libIodine.setReactionFillColorRGB(neti, reai, r, g, b)
    if errCode < 0:
        raise ExceptionDict[errCode](errorDict[errCode], neti, reai,  r, g, b)


def setReactionFillColorAlpha(neti: int, reai: int, a: float):
    errCode = libIodine.setReactionFillColorAlpha(neti, reai, a)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, a)


def setReactionLineThickness(neti: int, reai: int, thickness: float):
    errCode = libIodine.setReactionLineThickness(neti, reai, thickness)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, thickness)


def setReactionCenterHandlePosition(neti: int, reai: int, centerHandleX: float,centerHandleY: float):
    errCode = libIodine.setReactionCenterHandlePosition(
        neti, reai, centerHandleX, centerHandleY)
    if errCode < 0:
        raise ExceptionDict[errCode](
            errorDict[errCode], neti, reai, centerHandleX,centerHandleY)


def createUniUni(neti: int, reaID: str, rateLaw: str, srci: int, desti: int, srcStoich: float, destStoich: float):
    startGroup()
    createReaction(neti, reaID)
    reai = getReactionIndex(neti, reaID)

    addSrcNode(neti, reai, srci, srcStoich)
    addDestNode(neti, reai, desti, destStoich)
    setRateLaw(neti, reai, rateLaw)
    endGroup()


def CreateUniBi(neti: int, reaID: str, rateLaw: str, srci: int, dest1i: int, dest2i: int, srcStoich: float, dest1Stoich: float, dest2Stoich: float):
    startGroup()
    createReaction(neti, reaID)
    reai = getReactionIndex(neti, reaID)

    addSrcNode(neti, reai, srci, srcStoich)
    addDestNode(neti, reai, dest1i, dest1Stoich)
    addDestNode(neti, reai, dest2i, dest2Stoich)
    setRateLaw(neti, reai, rateLaw)
    endGroup()


def CreateBiUni(neti: int, reaID: str, rateLaw: str, src1i: int, src2i: int, desti: int, src1Stoich: float, src2Stoich: float, destStoich: float):
    startGroup()
    createReaction(neti, reaID)
    reai = getReactionIndex(neti, reaID)

    addSrcNode(neti, reai, src1i, src1Stoich)
    addSrcNode(neti, reai, src2i, src2Stoich)
    addDestNode(neti, reai, desti, destStoich)
    setRateLaw(neti, reai, rateLaw)
    endGroup()


def CreateBiBi(neti: int, reaID: str, rateLaw: str, src1i: int, src2i: int, dest1i: int, dest2i: int, src1Stoich: float, src2Stoich: float, dest1Stoich: float, dest2Stoich: float):
    startGroup()
    createReaction(neti, reaID)
    reai = getReactionIndex(neti, reaID)

    addSrcNode(neti, reai, src1i, src1Stoich)
    addSrcNode(neti, reai, src2i, src2Stoich)
    addDestNode(neti, reai, dest1i, dest1Stoich)
    addDestNode(neti, reai, dest2i, dest2Stoich)
    setRateLaw(neti, reai, rateLaw)
    endGroup()
