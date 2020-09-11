/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package command-line-arguments */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h> /* for ptrdiff_t below */

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */


#line 6 "Iodine_GoLang_to_dll.go"
 #include <stdio.h>
 #include <stdlib.h>

#line 1 "cgo-generated-wrapper"


/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif

extern int getErrorCode();

//designed for C api
extern void setErrorCode(int err);
extern int undo();
extern int redo();
extern void startGroup();
extern void endGroup();
extern void cFree(char* cs);
extern char* getErrorMessage();
extern char* getDetailErrorMessage();

//errCode -3: ID repeat, 0 :ok
extern int newNetwork(char* id);

//return:  -2: net ID can't find, >=0: ok
extern int getNetworkIndex(char* id);

//errCode:  0:ok, -5: net index out of range
//-10: "Json convert error", -11: "File error",
extern int saveNetworkAsJSON(int neti, char* name);

//errCode -3: name repeat, 0 :ok
//-10: "Json convert error", -11: "File error",
extern int readNetworkFromJSON(char* path);

//errCode:  0:ok, -5: net index out of range
extern int deleteNetwork(int neti);
extern void clearNetworks();

//no error handling
extern int getNumberOfNetworks();

//no error handling
extern int getLargestNetworkIndex();

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -5: net index out of range
extern char* getNetworkID(int neti);

//errCode: 0:ok, -5: net index out of range
extern int getNetworkBool(int neti);

//return -3: ID repeat, 0 :ok
//-5: net index out of range
//-12: Variable out of range:
extern int addNode(int neti, char* id, float x, float y, float w, float h);

//return:  -2: node ID can't find, >=0: ok
//-5: net index out of range
extern int getNodeIndex(int neti, char* id);

//flag: 0: ok, -7: node index out of range,
//-4: node is not free
//-5: net index out of range
extern int deleteNode(int neti, int nodei);

//-5: net index out of range
extern int clearNetwork(int neti);

//-5: net index out of range
extern int getNumberOfNodes(int neti);

//-5: net index out of range
extern int getLargestNodeIndex(int neti);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeCenterX(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeCenterY(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern char* getNodeID(int neti, int nodei);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern int getNodeBool(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeX(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeY(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeW(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeH(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern unsigned int getNodeFillColorRGB(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeFillColorAlpha(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern unsigned int getNodeOutlineColorRGB(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeOutlineColorAlpha(int neti, int nodei);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeOutlineThickness(int neti, int nodei);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern int getNodeFontPointSize(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern char* getNodeFontFamily(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern char* getNodeFontStyle(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern char* getNodeFontWeight(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern char* getNodeFontName(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern unsigned int getNodeFontColorRGB(int neti, int nodei);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
extern float getNodeFontColorAlpha(int neti, int nodei);

//setNodeID set the id of a node
//errCode -3: id repeat, 0 :ok
//-5: net index out of range
//-7: node index out of range
extern int setNodeID(int neti, int nodei, char* newID);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeCoordinate(int neti, int nodei, float x, float y);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeSize(int neti, int nodei, float w, float h);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeFillColorRGB(int neti, int nodei, int r, int g, int b);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeFillColorAlpha(int neti, int nodei, float a);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeOutlineColorRGB(int neti, int nodei, int r, int g, int b);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeOutlineColorAlpha(int neti, int nodei, float a);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range
extern int setNodeOutlineThickness(int neti, int nodei, float thickness);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range
extern int setNodeFontPointSize(int neti, int nodei, int fontPointSize);

//setNodeFontFamily set the fontFamily of a node
//errCode 5: net index out of range
//-12: Variable out of range
extern int setNodeFontFamily(int neti, int nodei, char* fontFamily);

//setNodeFontStyle set the fontStyle of a node
//errCode 5: net index out of range
//-12: Variable out of range
extern int setNodeFontStyle(int neti, int nodei, char* fontStyle);

//setNodeFontWeight set the fontWeight of a node
//errCode 5: net index out of range
//-12: Variable out of range
extern int setNodeFontWeight(int neti, int nodei, char* fontWeight);

//setNodeFontName set the FontName of a node
//errCode 5: net index out of range
//-12: Variable out of range
extern int setNodeFontName(int neti, int nodei, char* fontName);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeFontColorRGB(int neti, int nodei, int r, int g, int b);

//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
extern int setNodeFontColorAlpha(int neti, int nodei, float a);

//errCode: 0: ok, -3: ID repeat
//-5: net index out of range
extern int createReaction(int neti, char* reaid);

//return: -2: ID can't find, >=0: ok
//-5: net index out of range
extern int getReactionIndex(int neti, char* reaid);

//errCode:  0:ok, -6: reaction index out of range
//-5: net index out of range
extern int deleteReaction(int neti, int reai);
extern int clearReactions(int neti);

//return: >=0: ok, -5: net index out of range
extern int getNumberOfReactions(int neti);

//return: >=0: ok, -5: net index out of range
extern int getLargestReactionIndex(int neti);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern char* getReactionID(int neti, int reai);

//return: >=0: ok, -5: net index out of range
extern int getReactionBool(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern char* getReactionRateLaw(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern unsigned int getReactionFillColorRGB(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern float getReactionFillColorAlpha(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern float getReactionLineThickness(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern float getReactionCenterHandleX(int neti, int reai);

//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern float getReactionCenterHandleY(int neti, int reai);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionSrcNodeStoich(int neti, int reai, char* srcNodeid);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionDestNodeStoich(int neti, int reai, char* destNodeid);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionSrcNodeHandleX(int neti, int reai, char* srcNodeid);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionSrcNodeHandleY(int neti, int reai, char* srcNodeid);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionDestNodeHandleX(int neti, int reai, char* destNodeid);

//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
extern float getReactionDestNodeHandleY(int neti, int reai, char* destNodeid);

//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
extern int getNumberOfSrcNodes(int neti, int reai);

//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
extern int getNumberOfDestNodes(int neti, int reai);

// store list in var nodeList, need getReactionNodeID(index int) to get ID one by one
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
extern int getListOfReactionSrcNodes(int neti, int reai);

// store list in var nodeList, need getReactionNodeID(index int) to get ID one by one
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
extern int getListOfReactionDestNodes(int neti, int reai);

//used in APi functions getListOfReactionSrc/DestNodes()
extern char* getReactionNodeID(GoInt index);

//errCode:  0:ok, -6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-5: net index out of range
extern int addSrcNode(int neti, int reai, int nodei, float stoich);

//errCode:  0:ok, -6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-5: net index out of range
extern int addDestNode(int neti, int reai, int nodei, float stoich);

//errCode: 0:ok, -6: reaction index out of range,
//-7: node index out of range
//-5: net index out of range
extern int deleteSrcNode(int neti, int reai, char* srcNodeid);

//errCode: 0:ok, -6: reaction index out of range,
//-7: node index out of range
//-5: net index out of range
extern int deleteDestNode(int neti, int reai, char* destNodeid);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
//-3: id repeat
extern int setReactionID(int neti, int reai, char* newID);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern int setRateLaw(int neti, int reai, char* ratelaw);

//errCode: -6: reaction index out of range,
//-5: net index out of range, -2: id not found
//-8: wrong stoich
extern int setReactionSrcNodeStoich(int neti, int reai, char* srcNodeID, float newStoich);

//errCode: -6: reaction index out of range,
//-5: net index out of range, -2: id not found
//-8: wrong stoich
extern int setReactionDestNodeStoich(int neti, int reai, char* destNodeID, float newStoich);

//errCode: -6: reaction index out of range,
//-5: net index out of range, -2: id not found
//-8: wrong stoich
extern int setReactionSrcNodeHandlePosition(int neti, int reai, char* srcNodeID, float handleX, float handleY);

//errCode: -6: reaction index out of range,
//-5: net index out of range, -2: id not found
//-8: wrong stoich
extern int setReactionDestNodeHandlePosition(int neti, int reai, char* destNodeID, float handleX, float handleY);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern int setReactionFillColorRGB(int neti, int reai, int r, int g, int b);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern int setReactionFillColorAlpha(int neti, int reai, float a);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
extern int setReactionLineThickness(int neti, int reai, float thickness);

//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
//-12: Variable out of range
extern int setReactionCenterHandlePosition(int neti, int reai, float centerHandleX, float centerHandleY);

#ifdef __cplusplus
}
#endif
