package Iodine

// package main
// import 	"fmt"
import (
	"encoding/json"
	"image/color"
	"io/ioutil"
	"sort"
)

var stackFlag bool = true
var netSetStack TNetSetStack
var redoStack TNetSetStack
var networkSet TNetworkSet

//TNetSetStack stack of the 'state of networkset'
type TNetSetStack []TNetworkSet

//TNetworkSet list of network
type TNetworkSet []TNetwork

//TNode A  node with a id, an x,y coordinate
//(top/left corner of node) and w, h (width and height)
type TNode struct {
	ID               string     `json:"id"`
	X                float64    `json:"x"`
	Y                float64    `json:"y"`
	W                float64    `json:"w"`
	H                float64    `json:"h"`
	FillColor        color.RGBA `json:"fillColor"`
	OutlineColor     color.RGBA `json:"outlineColor"`
	OutlineThickness int        `json:"outlineThickness"`
}

//TNetwork The list of Nodes
type TNetwork struct {
	MagicIdentifier string      `json:"magicIdentifier"`
	ID              string      `json:"id"`
	Nodes           []TNode     `json:"nodes"`
	ReactionSet     []TReaction `json:"reactions"`
}

//TReaction a reaction with multiple species
type TReaction struct {
	ID        string                `json:"id"`
	RateLaw   string                `json:"rateLaw"`
	Species   [2]map[string]float64 `json:"species"`
	FillColor color.RGBA            `json:"fillColor"`
	Thickness int                   `json:"thickness"`
}

//###############################################################

func (s *TNetSetStack) isEmpty() bool {
	return len(*s) == 0
}

func (s *TNetSetStack) push(set TNetworkSet) {
	Set := set.deepcopy()
	*s = append(*s, Set)
}

func (s *TNetSetStack) pop() TNetworkSet {
	theStack := *s
	lastState := theStack[len(theStack)-1]
	*s = theStack[:len(theStack)-1]
	return lastState
}

func (n *TNetworkSet) deepcopy() TNetworkSet {
	NewNetworkSet := TNetworkSet{}
	for i := range *n {
		NewNetworkX := TNetwork{
			ID:              (*n)[i].ID,
			MagicIdentifier: (*n)[i].MagicIdentifier}

		for j := range (*n)[i].Nodes {
			NewNodeX := TNode{ID: (*n)[i].Nodes[j].ID,
				X:                (*n)[i].Nodes[j].X,
				Y:                (*n)[i].Nodes[j].Y,
				W:                (*n)[i].Nodes[j].W,
				H:                (*n)[i].Nodes[j].H,
				FillColor:        color.RGBA{},
				OutlineColor:     color.RGBA{},
				OutlineThickness: (*n)[i].Nodes[j].OutlineThickness,
			}
			NewNodeX.FillColor.R = (*n)[i].Nodes[j].FillColor.R
			NewNodeX.FillColor.G = (*n)[i].Nodes[j].FillColor.G
			NewNodeX.FillColor.B = (*n)[i].Nodes[j].FillColor.B
			NewNodeX.FillColor.A = (*n)[i].Nodes[j].FillColor.A
			NewNodeX.OutlineColor.R = (*n)[i].Nodes[j].OutlineColor.R
			NewNodeX.OutlineColor.G = (*n)[i].Nodes[j].OutlineColor.G
			NewNodeX.OutlineColor.B = (*n)[i].Nodes[j].OutlineColor.B
			NewNodeX.OutlineColor.A = (*n)[i].Nodes[j].OutlineColor.A

			NewNetworkX.Nodes = append(NewNetworkX.Nodes, NewNodeX)
		}

		for k := range (*n)[i].ReactionSet {
			NewReactionX := TReaction{
				ID:        (*n)[i].ReactionSet[k].ID,
				RateLaw:   (*n)[i].ReactionSet[k].RateLaw,
				FillColor: color.RGBA{},
				Thickness: (*n)[i].ReactionSet[k].Thickness,
			}

			NewReactionX.Species[0] = make(map[string]float64, 0)
			NewReactionX.Species[1] = make(map[string]float64, 0)

			for l := range (*n)[i].ReactionSet[k].Species[0] {
				NewReactionX.Species[0][l] = (*n)[i].ReactionSet[k].Species[0][l]
			}
			for m := range (*n)[i].ReactionSet[k].Species[1] {
				NewReactionX.Species[1][m] = (*n)[i].ReactionSet[k].Species[1][m]
			}
			NewReactionX.FillColor.R = (*n)[i].ReactionSet[k].FillColor.R
			NewReactionX.FillColor.G = (*n)[i].ReactionSet[k].FillColor.G
			NewReactionX.FillColor.B = (*n)[i].ReactionSet[k].FillColor.B
			NewReactionX.FillColor.A = (*n)[i].ReactionSet[k].FillColor.A

			NewNetworkX.ReactionSet = append(NewNetworkX.ReactionSet, NewReactionX)
		}

		NewNetworkSet = append(NewNetworkSet, NewNetworkX)
	}
	return NewNetworkSet
}

//GetNetworkSet GetNetworkSet
//used in Iodine_C.go functions
func GetNetworkSet() *TNetworkSet {
	return &networkSet
}

//Undo ge back to last state
//errCode :  0: ok, -9: stack is empty
func Undo() int {
	if netSetStack.isEmpty() {
		return -9
	}
	redoStack.push(networkSet)
	networkSet = netSetStack.pop()
	return 0
}

//Redo redp
//0: ok, -9: stack is empty
func Redo() int {
	if redoStack.isEmpty() {
		return -9
	}
	netSetStack.push(networkSet)
	networkSet = redoStack.pop()
	return 0
}

//StartGroup used at the start of a group operaction or secondary function.
func StartGroup(){
	redoStack = TNetSetStack{}
	netSetStack.push(networkSet)
	stackFlag = false
}

//EndGroup used at the end of a group operaction or secondary function.
func EndGroup(){
	stackFlag = true
}

//NewNetwork Create a new network
//errCode -3: id repeat, 0 :ok
func NewNetwork(id string) int {
	errCode := 0
	for i := range networkSet {
		if networkSet[i].ID == id {
			errCode = -3
			return errCode
		}
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	newNetwork := TNetwork{MagicIdentifier: "NM01", ID: id}
	networkSet = append(networkSet, newNetwork)
	return errCode
}

//GetNetworkIndex GetNetIndex
//return:  -2: net id can't find, >=0: ok
func GetNetworkIndex(id string) int {
	errCode := -2
	for i := range networkSet {
		if networkSet[i].ID == id {
			index := i
			return index
		}
	}
	return errCode
}

//SaveNetworkAsJSON SaveNetworkAsJSON
//errCode:  0:ok, -5: net index out of range
//-10: "Json convert error", -11: "File error",
func SaveNetworkAsJSON(neti int, fileName string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	file, err1 := json.MarshalIndent(networkSet[neti], "", "    ")
	if err1 != nil {
		errCode = -10
		return errCode
	}
	err2 := ioutil.WriteFile(fileName, file, 0644)
	if err2 != nil {
		errCode = -11
		return errCode
	}
	return errCode
}

//ReadNetworkFromJSON ReadNetworkFromJSON
//errCode -3: id repeat, 0 :ok
//-10: "Json convert error", -11: "File error",
func ReadNetworkFromJSON(filePath string) int {
	errCode := 0
	file, err1 := ioutil.ReadFile(filePath)
	if err1 != nil {
		errCode = -11
		return errCode
	}
	newNet := TNetwork{}
	err2 := json.Unmarshal([]byte(file), &newNet)
	if err2 != nil {
		errCode = -10
		return errCode
	}
	for i := range networkSet {
		if newNet.ID == networkSet[i].ID {
			errCode = -3
			return errCode
		}
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet = append(networkSet, newNet)
	// fmt.Println(networkSet)
	return errCode
}

//DeleteNetwork DeleteNetwork
//errCode:  0:ok, -5: net index out of range
func DeleteNetwork(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	if neti == 0 {
		networkSet = networkSet[1:]
	} else if neti == len(networkSet)-1 {
		networkSet = networkSet[:len(networkSet)-1]
	} else {
		networkSet = append(networkSet[:neti], networkSet[neti+1:]...)
	}
	return errCode
}

//ClearNetworks ClearNetworks
func ClearNetworks() {
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet = TNetworkSet{}
}

//GetNumberOfNetworks GetNumberOfNetworks
//no error handling
func GetNumberOfNetworks() int {
	return len(networkSet)
}

//GetNetworkID GetID of network
//errCode: 0:ok, -5: net index out of range
func GetNetworkID(neti int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return "error"
	}
	return networkSet[neti].ID
}

//AddNode adds a node to the network
//errCode -3: id repeat, 0 :ok
//-5: net index out of range
//-12: Variable out of range:
func AddNode(neti int, id string, x, y, w, h float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	for i := range n.Nodes {
		if n.Nodes[i].ID == id {
			errCode = -3
			return errCode
		}
	}
	if x < 0 || y < 0 || w <= 0 || h <= 0 {
		errCode = -12
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	newNode := TNode{ID: id, X: x, Y: y, W: w, H: h,
		FillColor:        color.RGBA{R: 255, G: 150, B: 80, A: 255},
		OutlineColor:     color.RGBA{R: 255, G: 100, B: 80, A: 255},
		OutlineThickness: 3}
	n.Nodes = append(n.Nodes, newNode)
	networkSet[neti] = n
	return errCode
}

//GetNodeIndex get node index by id
//index:  -2: node id can't find, >=0: ok
//-5: net index out of range
func GetNodeIndex(neti int, id string) int {
	if neti < 0 || neti >= len(networkSet) {
		errCode := -5
		return errCode
	}
	errCode := -2
	n := networkSet[neti]
	for i := range n.Nodes {
		if n.Nodes[i].ID == id {
			index := i
			return index
		}
	}
	return errCode
}

//get list of nodes not in any existed reactions
func (n *TNetwork) getFreeNodes() []int {
	reaNodeSet := make(map[string]string)
	for i := range n.ReactionSet {
		for j := range n.ReactionSet[i].Species[0] {
			reaNodeSet[j] = ""
		}
		for j := range n.ReactionSet[i].Species[1] {
			reaNodeSet[j] = ""
		}
	}
	s := []int{}
	for i := range n.Nodes {
		flag := 0
		for j := range reaNodeSet {
			if n.Nodes[i].ID == j {
				flag = 1
			}
		}
		if flag == 0 {
			s = append(s, i)
		}
	}
	return s
}

//DeleteNode delete the node with index
//return: 0: ok, -7: node index out of range, -4: node is not free
//-5: net index out of range
func DeleteNode(neti, nodei int) int {
	errCode := -4
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	s := n.getFreeNodes()
	for i := range s {
		if nodei == s[i] {
			errCode = 0
			break
		}
	}
	if errCode == -4 {
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	if nodei == 0 {
		n.Nodes = n.Nodes[1:]
	} else if nodei == len(n.Nodes)-1 {
		n.Nodes = n.Nodes[:len(n.Nodes)-1]
	} else {
		n.Nodes = append(n.Nodes[:nodei], n.Nodes[nodei+1:]...)
	}
	networkSet[neti] = n
	return errCode
}

//ClearNetwork clear all nodes and reactions in this network
//errCode: 0: ok, -5:  net index out of range
func ClearNetwork(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet[neti].Nodes = make([]TNode, 0)
	networkSet[neti].ReactionSet = make([]TReaction, 0)
	return errCode
}

//GetNumberOfNodes get the number of nodes in the current network
//num: >=0: ok, -5:  net index out of range
func GetNumberOfNodes(neti int) int {
	if neti < 0 || neti >= len(networkSet) {
		errCode := -5
		return errCode
	}
	n := networkSet[neti]
	return len(n.Nodes)
}

//GetNodeCenterX Get the X coordinate of the Center of node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeCenterX(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].X + n.Nodes[nodei].W*0.5
}

//GetNodeCenterY Get the X coordinate of the Center of node
//errCode: 0:ok, -7: index out of range
//-5: net index out of range
func GetNodeCenterY(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].Y + n.Nodes[nodei].H*0.5
}

//GetNodeID Get the id of the node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeID(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return "error"
	}
	return n.Nodes[nodei].ID
}

//GetNodeX Get the X coordinate of the node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeX(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].X
}

//GetNodeY Get the Y coordinate of the node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeY(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].Y
}

//GetNodeW Get the Width of the node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeW(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].W
}

//GetNodeH Get the Height of the node
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeH(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].H
}

//GetNodeFillColorRGB GetNodeFillColor rgb format
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeFillColorRGB(neti, nodei int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return 0 //meaningless number. won't be passed to next layer
	}
	color1 := uint32(n.Nodes[nodei].FillColor.R)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FillColor.G)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FillColor.B)
	return color1
}

//GetNodeFillColorAlpha GetNodeFillColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeFillColorAlpha(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return 0 //meaningless number. won't be passed to next layer
	}
	alpha1 := float64(n.Nodes[nodei].FillColor.A)/255
	return alpha1
}

//GetNodeOutlineColorRGB GetNodeOutlineColorRGB
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeOutlineColorRGB(neti, nodei int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return 0 //meaningless number. won't be passed to next layer
	}
	color1 := uint32(n.Nodes[nodei].OutlineColor.R)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].OutlineColor.G)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].OutlineColor.B)
	return color1
}

//GetNodeOutlineColorAlpha GetNodeOutlineColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
func GetNodeOutlineColorAlpha(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		*errCode = -7
		return 0 //meaningless number. won't be passed to next layer
	}
	alpha1 := float64(n.Nodes[nodei].OutlineColor.A)/255
	return alpha1
}

//GetNodeOutlineThickness GetNodeOutlineThickness
//errCode: -7: node index out of range
//-5: net index out of range
func GetNodeOutlineThickness(neti, nodei int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	return n.Nodes[nodei].OutlineThickness
}


//SetNodeID set the id of a node
//errCode -3: id repeat, 0 :ok
//-5: net index out of range
//-7: node index out of range
func SetNodeID(neti, nodei int, newID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	for i := range n.Nodes {
		if n.Nodes[i].ID == newID {
			errCode = -3
			return errCode
		}
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].ID = newID
	return errCode
}

//SetNodeCoordinate SetNodeCoordinate
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeCoordinate(neti, nodei int, x, y float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if x < 0 || y < 0 {
		errCode = -12
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].X = x
	n.Nodes[nodei].Y = y

	return errCode
}

//SetNodeSize SetNodeSize
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeSize(neti, nodei int, w, h float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if w <= 0 || h <= 0 {
		errCode = -12
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].W = w
	n.Nodes[nodei].H = h

	return errCode
}

//SetNodeFillColorRGB SetNodeFillColorRGB
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeFillColorRGB(neti, nodei, r, g, b int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255{
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	R1 := uint8(r)
	G1 := uint8(g)
	B1 := uint8(b)
	n.Nodes[nodei].FillColor.R = R1
	n.Nodes[nodei].FillColor.G = G1
	n.Nodes[nodei].FillColor.B = B1

	return errCode
}

//SetNodeFillColorAlpha SetNodeFillColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeFillColorAlpha(neti, nodei int,a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	A1 := uint8(a*255)
	n.Nodes[nodei].FillColor.A = A1

	return errCode
}

//SetNodeOutlineColorRGB SetNodeOutlineColorRGB
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeOutlineColorRGB(neti, nodei, r, g, b int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	R1 := uint8(r)
	G1 := uint8(g)
	B1 := uint8(b)
	n.Nodes[nodei].OutlineColor.R = R1
	n.Nodes[nodei].OutlineColor.G = G1
	n.Nodes[nodei].OutlineColor.B = B1

	return errCode
}

//SetNodeOutlineColorAlpha SetNodeOutlineColorAlpha
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetNodeOutlineColorAlpha(neti, nodei int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	A1 := uint8(a*255)

	n.Nodes[nodei].OutlineColor.A = A1

	return errCode
}

//SetNodeOutlineThickness SetNodeOutlineThickness
//errCode: 0:ok, -7: node index out of range
//-5: net index out of range
//-12: Variable out of range
func SetNodeOutlineThickness(neti, nodei, thickness int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	n := networkSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		return errCode
	}
	if thickness <= 0 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].OutlineThickness = thickness
	return errCode
}

//CreateReaction create an empty reacton
//errCode: 0: ok, -3: id repeat
//-5: net index out of range
func CreateReaction(neti int, id string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	for i := range r {
		if r[i].ID == id {
			errCode = -3
			return errCode
		}
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	
	newReact := TReaction{ID: id,
		FillColor: color.RGBA{R: 255, G: 150, B: 80, A: 255},
		Thickness: 3,
	}
	newReact.Species[0] = make(map[string]float64, 0)
	newReact.Species[1] = make(map[string]float64, 0)

	r = append(r, newReact)
	networkSet[neti].ReactionSet = r
	return errCode
}

//GetReactionIndex get reaction index by id
//return: -2: id can't find, >=0: ok
//-5: net index out of range
func GetReactionIndex(neti int, id string) int {
	if neti < 0 || neti >= len(networkSet) {
		errCode := -5
		return errCode
	}
	errCode := -2
	r := networkSet[neti].ReactionSet
	for i := range r {
		if r[i].ID == id {
			index := i
			return index
		}
	}
	return errCode
}

//DeleteReaction delete the reaction with index
//errCode:  0:ok, -6: reaction index out of range
//-5: net index out of range
func DeleteReaction(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	if reai == 0 {
		r = r[1:]
	} else if reai == len(r)-1 {
		r = r[:len(r)-1]
	} else {
		r = append(r[:reai], r[reai+1:]...)
	}
	networkSet[neti].ReactionSet = r

	return errCode
}

//ClearReactions clear all reactions in this network
//errCode: 0: ok, -5: net index out of range
func ClearReactions(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet[neti].ReactionSet = make([]TReaction, 0)
	return errCode
}

//GetNumberOfReactions get the number of reactions in the current Reactionset
//return: >=0: ok, -5: net index out of range
func GetNumberOfReactions(neti int) int {
	if neti < 0 || neti >= len(networkSet) {
		errCode := -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	return len(r)
}

//GetReactionID Get the id of Reaction
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func GetReactionID(neti, reai int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return "error"
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return "error"
	}
	return r[reai].ID
}

//GetReactionRateLaw Get the ratelaw of Reaction
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func GetReactionRateLaw(neti, reai int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return "error"
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return "error"
	}
	return r[reai].RateLaw
}

//GetReactionFillColorRGB GetReactionFillColorRGB
//errCode: 0:ok,  -6: reaction index out of range
//-5: net index out of range
func GetReactionFillColorRGB(neti, reai int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return 0
	}
	color1 := uint32(r[reai].FillColor.R)
	color1 = (color1 << 8) | uint32(r[reai].FillColor.G)
	color1 = (color1 << 8) | uint32(r[reai].FillColor.B)
	return color1
}

//GetReactionFillColorAlpha GetReactionFillColorAlpha
//errCode: 0:ok,  -6: reaction index out of range
//-5: net index out of range
func GetReactionFillColorAlpha(neti, reai int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return 0 //meaningless number. won't be passed to next layer
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return 0
	}
	alpha1 := float64(r[reai].FillColor.A)/255
	return alpha1
}

//GetReactionLineThickness GetReactionLineThickness
//errCode: -6: reaction index out of range
//-5: net index out of range
func GetReactionLineThickness(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	return r[reai].Thickness
}

//GetReactionSrcNodeStoich Get the SrcNode stoichiometry of Reaction
//errCode: -6: reaction index out of range,
//-5: net index out of range, -2: id not found
func GetReactionSrcNodeStoich(neti, reai int, srcNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -1000000
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return -1000000
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		*errCode = -2
		return -1000000
	}
	return r[reai].Species[0][srcNodeID]
}

//GetReactionDestNodeStoich Get the DestNode stoichiometry of Reaction
//return: positive float : ok, -6: reaction index out of range, -7: node index out of range
//-5: net index out of range
func GetReactionDestNodeStoich(neti, reai int, destNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return -1000000
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return -1000000
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		*errCode = -2
		return -1000000
	}
	return r[reai].Species[1][destNodeID]
}

//GetNumberOfSrcNodes Get the SrcNode length of Reaction
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func GetNumberOfSrcNodes(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	return len(r[reai].Species[0])
}

//GetNumberOfDestNodes Get the DestNode length of Reaction
//return: non-negative int: ok, -6: reaction index out of range
//-5: net index out of range
func GetNumberOfDestNodes(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	return len(r[reai].Species[1])
}

//GetListOfReactionSrcNodes GetListOfReactionSrcNodes in alphabetical order
//return: non-empty slice : ok, -6: reaction index out of range
//-5: net index out of range
func GetListOfReactionSrcNodes(neti, reai int, errCode *int) []string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return make([]string, 0)
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return make([]string, 0)
	}
	list := make([]string, 0)
	for k := range r[reai].Species[0] {
		list = append(list, k)
	}
	sort.Strings(list)
	return list
}

//GetListOfReactionDestNodes GetListOfReactionDestNodes in alphabetical order
//return: non-empty slice : ok, -6: reaction index out of range
//-5: net index out of range
func GetListOfReactionDestNodes(neti, reai int, errCode *int) []string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet) {
		*errCode = -5
		return make([]string, 0)
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		*errCode = -6
		return make([]string, 0)
	}
	list := make([]string, 0)
	for k := range r[reai].Species[1] {
		list = append(list, k)
	}
	sort.Strings(list)
	return list
}

//AddSrcNode add node and Stoich to reactionlist
//errCode:  0:ok,
//-5: net index out of range
//-6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-3: id repeat
func AddSrcNode(neti, reai, nodei int, stoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if nodei < 0 || nodei >= len(networkSet[neti].Nodes) {
		errCode = -7
		return errCode
	}
	if stoich <= 0.0 {
		errCode = -8
		return errCode
	}
	R := r[reai]
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	srcNodeID := networkSet[neti].Nodes[nodei].ID
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == true {
		errCode = -3
		return errCode
	}
	R.Species[0][srcNodeID] = stoich

	networkSet[neti].ReactionSet[reai] = R
	return errCode
}

//AddDestNode add node and Stoich to reactionlist
//errCode:  0:ok,
//-5: net index out of range
//-6: reaction index out of range,
//-7: node index out of range
//-8: "wrong stoich: stoich has to be positive"
//-3: id repeat
func AddDestNode(neti, reai, nodei int, stoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if nodei < 0 || nodei >= len(networkSet[neti].Nodes) {
		errCode = -7
		return errCode
	}
	if stoich <= 0 {
		errCode = -8
		return errCode
	}
	R := r[reai]
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	destNodeID := networkSet[neti].Nodes[nodei].ID
	_, ok := R.Species[1][destNodeID]
	if ok == true {
		errCode = -3
		return errCode
	}
	R.Species[1][destNodeID] = stoich
	networkSet[neti].ReactionSet[reai] = R

	return errCode
}

//DeleteSrcNode delete src nodes by id(ID).
//errCode: 0:ok, -6: reaction index out of range,
//-5: net index out of range
//-2: id not found
func DeleteSrcNode(neti, reai int, srcNodeID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	R := r[reai]
	_, ok := R.Species[0][srcNodeID]
	if ok == false {
		errCode = -2
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	delete(R.Species[0], srcNodeID)
	networkSet[neti].ReactionSet[reai] = R
	return errCode
}

//DeleteDestNode delete all dest nodes by id
//errCode: 0:ok, -6: reaction index out of range,
//-5: net index out of range
//-2: id not found
func DeleteDestNode(neti, reai int, destNodeID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	R := r[reai]
	_, ok := R.Species[1][destNodeID]
	if ok == false {
		errCode = -2
		return errCode
	}

	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	delete(R.Species[1], destNodeID)
	networkSet[neti].ReactionSet[reai] = R
	return errCode
}

//SetRateLaw edit rate law of reaction
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
func SetRateLaw(neti, reai int, rateLaw string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet[neti].ReactionSet[reai].RateLaw = rateLaw
	return errCode
}

//SetReactionFillColorRGB SetReactionFillColorRGB
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetReactionFillColorRGB(neti, reai, R, G, B int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	R1 := uint8(R)
	G1 := uint8(G)
	B1 := uint8(B)

	r[reai].FillColor.R = R1
	r[reai].FillColor.G = G1
	r[reai].FillColor.B = B1
	return errCode
}

//SetReactionFillColorAlpha SetReactionFillColorAlpha
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
//-12: Variable out of range:
func SetReactionFillColorAlpha(neti, reai int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	A1 := uint8(a*255)
	r[reai].FillColor.A = A1

	return errCode
}

//SetReactionLineThickness SetReactionLineThickness
//errCode: 0:ok, -6: reaction index out of range
//-5: net index out of range
//-12: Variable out of range
func SetReactionLineThickness(neti, reai, thickness int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet) {
		errCode = -5
		return errCode
	}
	r := networkSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		return errCode
	}
	if thickness <= 0 {
		errCode = -12
		return errCode
	}
	if stackFlag{
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet[neti].ReactionSet[reai].Thickness = thickness
	return errCode
}

func createBiBi(neti int, reaID, rateLaw string, src1i, src2i, dest1i, dest2i int, src1Stoich, src2Stoich, dest1Stoich, dest2Stoich float64) {
	StartGroup()

	CreateReaction(neti, reaID)
	reai := GetReactionIndex(neti, reaID)

	AddSrcNode(neti, reai, src1i, src1Stoich)
	AddSrcNode(neti, reai, src2i, src2Stoich)
	AddDestNode(neti, reai, dest1i, dest1Stoich)
	AddDestNode(neti, reai, dest2i, dest2Stoich)
	SetRateLaw(neti, reai, rateLaw)
	EndGroup()
}


//###################################################################

// func main() {
// 	err:= 0
// 	NewNetwork("network1")
// 	AddNode(0, "node1", 1.1, 2.5, 5.4, 6.4)
// 	SetNodeFillColorRGB(0,0,23,43,53)
// 	SetNodeFillColorAlpha(0,0,1)
// 	color1 := GetNodeFillColorRGB(0,0,&err)
// 	alpha1 := GetNodeFillColorAlpha(0,0,&err)
// 	fmt.Printf("%x\n",color1)
// 	fmt.Println(alpha1)
// 	AddNode(0, "node2", 1.2, 3.2, 2.5, 4.1)
// 	AddNode(0, "node3", 2.2, 3.1, 1.5, 4.5)
// 	AddNode(0, "node4", 7.2, 3.5, 1.6, 4.8)
// 	createBiBi(0, "Rea1", "k1*A",0, 1, 2, 3, 1.0, 2.0, 3.0, 4.0)
// 	createBiBi(0, "Rea2", "k2*A",1, 3, 0, 2, 2.0, 5.0, 8.0, 7.0)
// 	SaveNetworkAsJSON(0,"net1.json")
// 	Undo()
// 	SaveNetworkAsJSON(0,"net2.json")
// 	Redo()
// 	SaveNetworkAsJSON(0,"net3.json")
// }
