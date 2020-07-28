package main

//this package converts Iodine_GO to dll by:
//go build -o Iodine.dll -buildmode=c-shared Iodine_GoLang_to_dll.go


// #include <stdio.h>
// #include <stdlib.h>
import "C"
import "unsafe"
import Iodine "IodinePkg/Iodine_GO"

var errCode int = 0
var networkSet = Iodine.GetNetworkSet()

//export getErrorCode
func getErrorCode() C.int {
	return C.int(errCode)
}


//export setErrorCode
//designed for C api
func setErrorCode(err C.int){
	errCode = int(err)
} 

//export undo
func undo() C.int {
	return C.int(Iodine.Undo())
}

//export redo
func redo() C.int {
	return C.int(Iodine.Redo())
}

//export startGroup
func startGroup(){
	Iodine.StartGroup()
}

//export endGroup
func endGroup(){
	Iodine.EndGroup()
}

//export cFree
func cFree(cs *C.char){
	C.free(unsafe.Pointer(cs))
}

//export newNetwork
//errCode -3: ID repeat, 0 :ok
func newNetwork(id *C.char) C.int {
	ID := C.GoString(id)
	return C.int(Iodine.NewNetwork(ID))
}

//export getNetworkIndex
//return:  -2: net ID can't find, >=0: ok
func getNetworkIndex(id *C.char) C.int {
	ID := C.GoString(id)
	return C.int(Iodine.GetNetworkIndex(ID))
}

//export saveNetworkAsJSON
//errCode:  0:ok, -5: net index out of range
//-10: "Json convert error", -11: "File error",
func saveNetworkAsJSON(neti C.int, name *C.char) C.int {
	netI := int(neti)
	fileName := C.GoString(name)
	return C.int(Iodine.SaveNetworkAsJSON(netI, fileName))
}

//export readNetworkFromJSON
//errCode -3: name repeat, 0 :ok
//-10: "Json convert error", -11: "File error",
func readNetworkFromJSON(path *C.char) C.int {
	filePath := C.GoString(path)
	return C.int(Iodine.ReadNetworkFromJSON(filePath))
}

//export deleteNetwork
//errCode:  0:ok, -5: net index out of range
func deleteNetwork(neti C.int) C.int {
	netI := int(neti)
	return C.int(Iodine.DeleteNetwork(netI))
}

//export clearNetworks
func clearNetworks() {
	Iodine.ClearNetworks()
}

//export getNumberOfNetworks
//no error handling
func getNumberOfNetworks() C.int {
	return C.int(Iodine.GetNumberOfNetworks())
}

//export getNetworkID
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -5: net index out of range
func getNetworkID(neti C.int) *C.char {
	netI := int(neti)
	iodineCString := C.CString(Iodine.GetNetworkID(netI, &errCode))
	return iodineCString
}

//export addNode
//return -3: ID repeat, 0 :ok
//-5: net index out of range
//-12: Variable out of range:
func addNode(neti C.int, id *C.char, x, y, w, h C.float) C.int {
	netI := int(neti)
	ID := C.GoString(id)
	x1 := float64(x)
	y1 := float64(y)
	w1 := float64(w)
	h1 := float64(h)
	err := Iodine.AddNode(netI, ID, x1, y1, w1, h1)
	return C.int(err)
}

//export getNodeIndex
//return:  -2: node ID can't find, >=0: ok
//-5: net index out of range
func getNodeIndex(neti C.int, id *C.char) C.int {
	netI := int(neti)
	ID := C.GoString(id)
	index := Iodine.GetNodeIndex(netI, ID)
	return C.int(index)
}

//export deleteNode
//flag: 0: ok, -7: node index out of range,
//-4: node is not free
//-5: net index out of range
func deleteNode(neti, nodei C.int) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	return C.int(Iodine.DeleteNode(netI, nodeI))
}

//export clearNetwork
//-5: net index out of range
func clearNetwork(neti C.int) C.int {
	netI := int(neti)
	return C.int(Iodine.ClearNetwork(netI))
}

//export getNumberOfNodes
//-5: net index out of range
func getNumberOfNodes(neti C.int) C.int {
	netI := int(neti)
	num := Iodine.GetNumberOfNodes(netI)
	return C.int(num)
}

//export getNodeCenterX
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeCenterX(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	x := Iodine.GetNodeCenterX(netI, nodeI, &errCode)
	return C.float(x)
}

//export getNodeCenterY
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeCenterY(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	y := Iodine.GetNodeCenterY(netI, nodeI, &errCode)
	return C.float(y)
}

//export getNodeID
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeID(neti, nodei C.int) *C.char {
	netI := int(neti)
	nodeI := int(nodei)
	ID := Iodine.GetNodeID(netI, nodeI, &errCode)
	iodineCString :=  C.CString(ID)
	return iodineCString
}

//export getNodeX
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeX(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	x := Iodine.GetNodeX(netI, nodeI, &errCode)
	return C.float(x)
}

//export getNodeY
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeY(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	y := Iodine.GetNodeY(netI, nodeI, &errCode)
	return C.float(y)
}

//export getNodeW
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeW(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	w := Iodine.GetNodeW(netI, nodeI, &errCode)
	return C.float(w)
}

//export getNodeH
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeH(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	h := Iodine.GetNodeH(netI, nodeI, &errCode)
	return C.float(h)
}

//export getNodeFillColorRGB
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeFillColorRGB(neti, nodei C.int) C.uint {
	netI := int(neti)
	nodeI := int(nodei)
	color1 := Iodine.GetNodeFillColorRGB(netI, nodeI, &errCode)
	return C.uint(color1)
}

//export getNodeFillColorAlpha
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeFillColorAlpha(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	alpha1 := Iodine.GetNodeFillColorAlpha(netI, nodeI, &errCode)
	return C.float(alpha1)
}

//export getNodeOutlineColorRGB
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeOutlineColorRGB(neti, nodei C.int) C.uint {
	netI := int(neti)
	nodeI := int(nodei)
	color1 := Iodine.GetNodeOutlineColorRGB(netI, nodeI, &errCode)
	return C.uint(color1)
}

//export getNodeOutlineColorAlpha
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeOutlineColorAlpha(neti, nodei C.int) C.float {
	netI := int(neti)
	nodeI := int(nodei)
	alpha1 := Iodine.GetNodeOutlineColorAlpha(netI, nodeI, &errCode)
	return C.float(alpha1)
}

//export getNodeOutlineThickness
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func getNodeOutlineThickness(neti, nodei C.int) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	err := Iodine.GetNodeOutlineThickness(netI, nodeI)
	return C.int(err)
}

//export setNodeID
//setNodeID set the id of a node
//errCode -3: id repeat, 0 :ok
//-5: net index out of range
//-7: node index out of range
func setNodeID(neti, nodei C.int, newID *C.char) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	NewID := C.GoString(newID)
	err := Iodine.SetNodeID(netI, nodeI, NewID)
	return C.int(err)
}

//export setNodeCoordinate
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeCoordinate(neti, nodei C.int, x, y C.float) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	x1 := float64(x)
	y1 := float64(y)


	err := Iodine.SetNodeCoordinate(netI, nodeI, x1, y1)
	return C.int(err)
}

//export setNodeSize
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeSize(neti, nodei C.int, w, h C.float) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	w1 := float64(w)
	h1 := float64(h)

	err := Iodine.SetNodeSize(netI, nodeI, w1, h1)
	return C.int(err)
}

//export setNodeFillColorRGB
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeFillColorRGB(neti, nodei, r, g, b C.int) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	R := int(r)
	G := int(g)
	B := int(b)
	err := Iodine.SetNodeFillColorRGB(netI, nodeI, R, G, B)
	return C.int(err)
}

//export setNodeFillColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeFillColorAlpha(neti, nodei C.int, a C.float) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	A := float64(a)
	err := Iodine.SetNodeFillColorAlpha(netI, nodeI, A)
	return C.int(err)
}

//export setNodeOutlineColorRGB
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeOutlineColorRGB(neti, nodei, r, g, b C.int) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	R := int(r)
	G := int(g)
	B := int(b)
	err := Iodine.SetNodeOutlineColorRGB(netI, nodeI, R, G, B)
	return C.int(err)
}

//export setNodeOutlineColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func setNodeOutlineColorAlpha(neti, nodei C.int, a C.float) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	A := float64(a)
	err := Iodine.SetNodeOutlineColorAlpha(netI, nodeI, A)
	return C.int(err)
}

//export setNodeOutlineThickness
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range
func setNodeOutlineThickness(neti, nodei, thickness C.int) C.int {
	netI := int(neti)
	nodeI := int(nodei)
	Thickness := int(thickness)
	err := Iodine.SetNodeOutlineThickness(netI, nodeI, Thickness)
	return C.int(err)
}

//export createReaction
//errCode: 0: ok, -3: ID repeat
//-5: net index out of range
func createReaction(neti C.int, reaid *C.char) C.int {
	netI := int(neti)
	reaID := C.GoString(reaid)
	err := Iodine.CreateReaction(netI, reaID)
	return C.int(err)
}

//export getReactionIndex
//return: -2: ID can't find, >=0: ok
//-5: net index out of range
func getReactionIndex(neti C.int, reaid *C.char) C.int {
	netI := int(neti)
	reaID := C.GoString(reaid)
	index := Iodine.GetReactionIndex(netI, reaID)
	return C.int(index)
}

//export deleteReaction
//errCode:  0:ok, -6: reaction index out of range
//-5: net index out of range
func deleteReaction(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	err := Iodine.DeleteReaction(netI, reaI)
	return C.int(err)
}

//export clearReactions
func clearReactions(neti C.int) C.int {
	netI := int(neti)
	return C.int(Iodine.ClearReactions(netI))
}

//export getNumberOfReactions
//return: >=0: ok, -5: net index out of range
func getNumberOfReactions(neti C.int) C.int {
	netI := int(neti)
	num := Iodine.GetNumberOfReactions(netI)
	return C.int(num)
}

//export getReactionID
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func getReactionID(neti, reai C.int) *C.char {
	netI := int(neti)
	reaI := int(reai)
	ID := Iodine.GetReactionID(netI, reaI, &errCode)
	iodineCString :=  C.CString(ID)
	return iodineCString
}

//export getReactionRateLaw
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func getReactionRateLaw(neti, reai C.int) *C.char {
	netI := int(neti)
	reaI := int(reai)
	rateLaw := Iodine.GetReactionRateLaw(netI, reaI, &errCode)
	iodineCString :=  C.CString(rateLaw)
	return iodineCString
}

//export getReactionFillColorRGB
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func getReactionFillColorRGB(neti, reai C.int) C.uint {
	netI := int(neti)
	reaI := int(reai)
	color1 := Iodine.GetReactionFillColorRGB(netI, reaI, &errCode)
	return C.uint(color1)
}

//export getReactionFillColorAlpha
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func getReactionFillColorAlpha(neti, reai C.int) C.float {
	netI := int(neti)
	reaI := int(reai)
	alpha1 := Iodine.GetReactionFillColorAlpha(netI, reaI, &errCode)
	return C.float(alpha1)
}

//export getReactionLineThickness
//getErrorCode() is needed after this function in API
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func getReactionLineThickness(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	thickness := Iodine.GetReactionLineThickness(netI, reaI)
	return C.int(thickness)
}

//export getReactionSrcNodeStoich
//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
func getReactionSrcNodeStoich(neti, reai C.int, srcNodeid *C.char) C.float {
	netI := int(neti)
	reaI := int(reai)
	srcNodeID := C.GoString(srcNodeid)
	stoich := Iodine.GetReactionSrcNodeStoich(netI, reaI, srcNodeID, &errCode)
	return C.float(stoich)
}

//export getReactionDestNodeStoich
//getErrorCode() is needed after this function in API
//return: positive int: ok, -6: reaction index out of range,
//-5: net index out of range, -2: name not found
func getReactionDestNodeStoich(neti, reai C.int, destNodeid *C.char) C.float {
	netI := int(neti)
	reaI := int(reai)
	destNodeID := C.GoString(destNodeid)
	Stoich := Iodine.GetReactionDestNodeStoich(netI, reaI, destNodeID, &errCode)
	return C.float(Stoich)
}

//export getNumberOfSrcNodes
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func getNumberOfSrcNodes(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	len := Iodine.GetNumberOfSrcNodes(netI, reaI)
	return C.int(len)
}

//export getNumberOfDestNodes
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func getNumberOfDestNodes(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	len := Iodine.GetNumberOfDestNodes(netI, reaI)
	return C.int(len)
}

var nodeList []string

//export getListOfReactionSrcNodes
// store list in var nodeList, need getReactionNodeID(index int) to get ID one by one
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func getListOfReactionSrcNodes(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	nodeList = Iodine.GetListOfReactionSrcNodes(netI, reaI, &errCode)
	return getErrorCode()
}

//export getListOfReactionDestNodes
// store list in var nodeList, need getReactionNodeID(index int) to get ID one by one
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func getListOfReactionDestNodes(neti, reai C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	nodeList = Iodine.GetListOfReactionDestNodes(netI, reaI, &errCode)
	return getErrorCode()
}

//export getReactionNodeID
//used in python APi functions getListOfReactionSrc/DestNodes()
func getReactionNodeID(index int) *C.char {
	id := nodeList[index]
	iodineCString := C.CString(id)
	return iodineCString
}

//export addSrcNode
//errCode:  0:ok, -6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-5: net index out of range
func addSrcNode(neti, reai, nodei C.int, stoich C.float) C.int {
	netI := int(neti)
	reaI := int(reai)
	nodeI := int(nodei)
	Stoich := float64(stoich)
	err := Iodine.AddSrcNode(netI, reaI, nodeI, Stoich)
	return C.int(err)
}

//export addDestNode
//errCode:  0:ok, -6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-5: net index out of range
func addDestNode(neti, reai, nodei C.int, stoich C.float) C.int {
	netI := int(neti)
	reaI := int(reai)
	nodeI := int(nodei)
	Stoich := float64(stoich)
	err := Iodine.AddDestNode(netI, reaI, nodeI, Stoich)
	return C.int(err)
}

//export deleteSrcNode
//errCode: 0:ok, -6: reaction index out of range,
//-7: node index out of range
//-5: net index out of range
func deleteSrcNode(neti, reai C.int, srcNodeid *C.char) C.int {
	netI := int(neti)
	reaI := int(reai)
	srcNodeID := C.GoString(srcNodeid)
	err := Iodine.DeleteSrcNode(netI, reaI, srcNodeID)
	return C.int(err)
}

//export deleteDestNode
//errCode: 0:ok, -6: reaction index out of range,
//-7: node index out of range
//-5: net index out of range
func deleteDestNode(neti, reai C.int, destNodeid *C.char) C.int {
	netI := int(neti)
	reaI := int(reai)
	destNodeID := C.GoString(destNodeid)
	err := Iodine.DeleteDestNode(netI, reaI, destNodeID)
	return C.int(err)
}

//export setRateLaw
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func setRateLaw(neti, reai C.int, ratelaw *C.char) C.int {
	netI := int(neti)
	reaI := int(reai)
	rateLaw := C.GoString(ratelaw)
	err := Iodine.SetRateLaw(netI, reaI, rateLaw)
	return C.int(err)
}

//export setReactionFillColorRGB
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func setReactionFillColorRGB(neti, reai, r, g, b C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	R := int(r)
	G := int(g)
	B := int(b)
	err := Iodine.SetReactionFillColorRGB(netI, reaI, R, G, B)
	return C.int(err)
}

//export setReactionFillColorAlpha
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func setReactionFillColorAlpha(neti, reai C.int, a C.float) C.int {
	netI := int(neti)
	reaI := int(reai)
	A := float64(a)
	err := Iodine.SetReactionFillColorAlpha(netI, reaI, A)
	return C.int(err)
}

//export setReactionLineThickness
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func setReactionLineThickness(neti, reai, thickness C.int) C.int {
	netI := int(neti)
	reaI := int(reai)
	Thickness := int(thickness)
	err := Iodine.SetReactionLineThickness(netI, reaI, Thickness)
	return C.int(err)
}
func main() {}

