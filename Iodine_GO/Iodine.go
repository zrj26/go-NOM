package Iodine

// package main
// import 	"fmt"
import (
	"encoding/json"
	"image/color"
	"io/ioutil"
	"runtime"
	"sort"
	"strconv"
)

var stackFlag bool = true
var netSetStack TNetSetStack
var redoStack TNetSetStack
var networkSet TNetworkSet

//TNetSetStack stack of the 'state of networkset'
type TNetSetStack []TNetworkSet

//TNetworkSet list of network
type TNetworkSet struct {
	netSet     []TNetwork
	netSetBool []bool
}

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
	OutlineThickness float64    `json:"outlineThickness"`
	FontPointSize    int        `json:"fontPointSize"`
	FontFamily       string     `json:"fontFamily"`
	FontStyle        string     `json:"fontStyle"`  //0: normal, 1: Italic
	FontWeight       string     `json:"fontWeight"` //0: default, -1: light, 1: bold
	FontName         string     `json:"fontName"`
	FontColor        color.RGBA `json:"fontColor"`
}

//TNetwork The list of Nodes
type TNetwork struct {
	MagicIdentifier string  `json:"magicIdentifier"`
	ID              string  `json:"id"`
	Nodes           []TNode `json:"nodes"`
	nodes           []bool
	ReactionSet     []TReaction `json:"reactions"`
	reactionset     []bool
}

//TReaction a reaction with multiple species
type TReaction struct {
	ID            string                     `json:"id"`
	RateLaw       string                     `json:"rateLaw"`
	Species       [2]map[string]TSpeciesNode `json:"species"`
	FillColor     color.RGBA                 `json:"fillColor"`
	Thickness     float64                    `json:"thickness"`
	CenterHandleX float64                    `json:"centerHandleX"`
	CenterHandleY float64                    `json:"centerHandleY"`
}

//TSpeciesNode info of nodes in reactions
type TSpeciesNode struct {
	Stoich  float64 `json:"stoich"`
	HandleX float64 `json:"handleX"`
	HandleY float64 `json:"handleY"`
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
	for i := range (*n).netSet {
		NewNetworkX := TNetwork{
			ID:              (*n).netSet[i].ID,
			MagicIdentifier: (*n).netSet[i].MagicIdentifier}
		for x1 := range (*n).netSet[i].nodes {
			NewNetworkX.nodes = append(NewNetworkX.nodes, (*n).netSet[i].nodes[x1])
		}
		for y1 := range (*n).netSet[i].reactionset {
			NewNetworkX.reactionset = append(NewNetworkX.reactionset, (*n).netSet[i].reactionset[y1])
		}
		for j := range (*n).netSet[i].Nodes {
			NewNodeX := TNode{ID: (*n).netSet[i].Nodes[j].ID,
				X:                (*n).netSet[i].Nodes[j].X,
				Y:                (*n).netSet[i].Nodes[j].Y,
				W:                (*n).netSet[i].Nodes[j].W,
				H:                (*n).netSet[i].Nodes[j].H,
				FillColor:        color.RGBA{},
				OutlineColor:     color.RGBA{},
				OutlineThickness: (*n).netSet[i].Nodes[j].OutlineThickness,
				FontPointSize:    (*n).netSet[i].Nodes[j].FontPointSize,
				FontFamily:       (*n).netSet[i].Nodes[j].FontFamily,
				FontStyle:        (*n).netSet[i].Nodes[j].FontStyle,
				FontWeight:       (*n).netSet[i].Nodes[j].FontWeight,
				FontName:         (*n).netSet[i].Nodes[j].FontName,
				FontColor:        color.RGBA{},
			}
			NewNodeX.FillColor.R = (*n).netSet[i].Nodes[j].FillColor.R
			NewNodeX.FillColor.G = (*n).netSet[i].Nodes[j].FillColor.G
			NewNodeX.FillColor.B = (*n).netSet[i].Nodes[j].FillColor.B
			NewNodeX.FillColor.A = (*n).netSet[i].Nodes[j].FillColor.A
			NewNodeX.OutlineColor.R = (*n).netSet[i].Nodes[j].OutlineColor.R
			NewNodeX.OutlineColor.G = (*n).netSet[i].Nodes[j].OutlineColor.G
			NewNodeX.OutlineColor.B = (*n).netSet[i].Nodes[j].OutlineColor.B
			NewNodeX.OutlineColor.A = (*n).netSet[i].Nodes[j].OutlineColor.A
			NewNodeX.FontColor.R = (*n).netSet[i].Nodes[j].FontColor.R
			NewNodeX.FontColor.G = (*n).netSet[i].Nodes[j].FontColor.G
			NewNodeX.FontColor.B = (*n).netSet[i].Nodes[j].FontColor.B
			NewNodeX.FontColor.A = (*n).netSet[i].Nodes[j].FontColor.A

			NewNetworkX.Nodes = append(NewNetworkX.Nodes, NewNodeX)
		}

		for k := range (*n).netSet[i].ReactionSet {
			NewReactionX := TReaction{
				ID:            (*n).netSet[i].ReactionSet[k].ID,
				RateLaw:       (*n).netSet[i].ReactionSet[k].RateLaw,
				FillColor:     color.RGBA{},
				Thickness:     (*n).netSet[i].ReactionSet[k].Thickness,
				CenterHandleX: (*n).netSet[i].ReactionSet[k].CenterHandleX,
				CenterHandleY: (*n).netSet[i].ReactionSet[k].CenterHandleY,
			}

			NewReactionX.Species[0] = make(map[string]TSpeciesNode, 0)
			NewReactionX.Species[1] = make(map[string]TSpeciesNode, 0)

			for l := range (*n).netSet[i].ReactionSet[k].Species[0] {
				NewReactionX.Species[0][l] = TSpeciesNode{
					Stoich:  (*n).netSet[i].ReactionSet[k].Species[0][l].Stoich,
					HandleX: (*n).netSet[i].ReactionSet[k].Species[0][l].HandleX,
					HandleY: (*n).netSet[i].ReactionSet[k].Species[0][l].HandleY,
				}
			}
			for m := range (*n).netSet[i].ReactionSet[k].Species[1] {
				NewReactionX.Species[1][m] = TSpeciesNode{
					Stoich:  (*n).netSet[i].ReactionSet[k].Species[1][m].Stoich,
					HandleX: (*n).netSet[i].ReactionSet[k].Species[1][m].HandleX,
					HandleY: (*n).netSet[i].ReactionSet[k].Species[1][m].HandleY,
				}
			}
			NewReactionX.FillColor.R = (*n).netSet[i].ReactionSet[k].FillColor.R
			NewReactionX.FillColor.G = (*n).netSet[i].ReactionSet[k].FillColor.G
			NewReactionX.FillColor.B = (*n).netSet[i].ReactionSet[k].FillColor.B
			NewReactionX.FillColor.A = (*n).netSet[i].ReactionSet[k].FillColor.A

			NewNetworkX.ReactionSet = append(NewNetworkX.ReactionSet, NewReactionX)
		}

		NewNetworkSet.netSet = append(NewNetworkSet.netSet, NewNetworkX)
	}
	for i := range (*n).netSetBool {
		NewNetworkSet.netSetBool = append(NewNetworkSet.netSetBool, (*n).netSetBool[i])
	}
	return NewNetworkSet
}

//GetNetworkSet GetNetworkSet
//used in Iodine_C.go functions
func GetNetworkSet() *[]TNetwork {
	return &networkSet.netSet
}

//Undo ge back to last state
//errCode :  0: ok, -9: stack is empty
func Undo() int {
	if netSetStack.isEmpty() {
		errCode := -9
		addErrorMessage(errCode, "()", "", "")
		return errCode
	}
	redoStack.push(networkSet)
	networkSet = netSetStack.pop()
	return 0
}

//Redo redo
//0: ok, -9: stack is empty
func Redo() int {
	if redoStack.isEmpty() {
		errCode := -9
		addErrorMessage(errCode, "()", "", "")
		return errCode
	}
	netSetStack.push(networkSet)
	networkSet = redoStack.pop()
	return 0
}

//StartGroup used at the start of a group operaction or secondary function.
func StartGroup() {
	redoStack = TNetSetStack{}
	netSetStack.push(networkSet)
	stackFlag = false
}

//EndGroup used at the end of a group operaction or secondary function.
func EndGroup() {
	stackFlag = true
}

var errorDict map[int]string = map[int]string{
	0:   "ok",
	-1:  "other",
	-2:  "id not found: ",
	-3:  "id repeat: ",
	-4:  "node is not free: ",
	-5:  "invalid net index",
	-6:  "invalid reaction index",
	-7:  "invalid node index",
	-8:  "invalid stoich: ",
	-9:  "stack is empty",
	-10: "Json convert error",
	-11: "File error",
	-12: "Variable out of range: ",
}

var errMSG1 string
var errMSG2 string

//GetErrorMessage GetErrorMessage
func GetErrorMessage() string {
	return errMSG1
}

//GetDetailErrorMessage GetDetailErrorMessage
func GetDetailErrorMessage() string {
	return errMSG2
}

func addErrorMessage(errCode int, errorMessage1, errorMessage2, errorMessage3 string) {
	pc, _, _, _ := runtime.Caller(1)
	_, file, line, _ := runtime.Caller(2)
	callerName := runtime.FuncForPC(pc).Name()
	errMSG2 += file + ", line " + strconv.Itoa(line) + ", " + callerName + errorMessage1 + "\n"
	errMSG1 += "Error: " + errorDict[errCode]
	errMSG2 += "Error: " + errorDict[errCode]
	switch errCode {
	case -2:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -3:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -4:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -5:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -6:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -7:
		errMSG1 += errorMessage2 + ".\n"
		errMSG2 += errorMessage2 + ".\n"
	case -8:
		errMSG1 += "error stoich and it's node" + errorMessage2 + ", stoich has to be positive.\n"
		errMSG2 += "error stoich and it's node" + errorMessage2 + ", stoich has to be positive.\n"
	case -9:
		errMSG1 += "\n"
		errMSG2 += "\n"
	case -10:
		errMSG1 += "see more details in doc of go function json.MarshalIndent() or json.Unmarshal()\n"
		errMSG2 += "see more details in doc of go function json.MarshalIndent() or json.Unmarshal()\n"
	case -11:
		errMSG1 += "wrong path or other error\n"
		errMSG2 += "wrong path or other error\n"
	case -12:
		errMSG1 += errorMessage2
		errMSG2 += errorMessage2
		if errorMessage3 == "xy" {
			errMSG1 += ", x or y has to be non-negative.\n"
			errMSG2 += ", x or y has to be non-negative.\n"
		}
		if errorMessage3 == "wh" {
			errMSG1 += ", w or h has to be positive.\n"
			errMSG2 += ", w or h has to be positive.\n"
		}
		if errorMessage3 == "color" {
			errMSG1 += ", RGB range int[0,255]; alpha range float[0,1].\n"
			errMSG2 += ", RGB range int[0,255]; alpha range float[0,1].\n"
		}
		if errorMessage3 == "positive" {
			errMSG1 += ", thickness, fontPointSize has to be positive.\n"
			errMSG2 += ", thickness, fontPointSize has to be positive.\n"
		}
		if errorMessage3 == "not found" {
			errMSG1 += ", fontFamily, fontStyle or fontWeight not found in list.\n"
			errMSG2 += ", fontFamily, fontStyle or fontWeight not found in list.\n"
		}
	default:
		errMSG1 += "other error.\n"
		errMSG2 += "other error.\n"
	}
}

var fontFamilyDict map[string]int = map[string]int{
	"default":    0,
	"decorative": 1,
	"roman":      2,
	"script":     3,
	"swiss":      4,
	"modern":     5,
}

var fontStyleDict map[string]int = map[string]int{
	"normal": 0,
	"italic": 1,
}

var fontWeightDict map[string]int = map[string]int{
	"default": 0,
	"light":   1,
	"bold":    2,
}

// func getFuncName() string {
// 	pc, _, _, _ := runtime.Caller(1)
// 	return runtime.FuncForPC(pc).Name()
// }
// func getCallerName() string {
// 	pc, file, line, _ := runtime.Caller(2)
// 	return runtime.FuncForPC(pc).Name()
// }

//NewNetwork Create a new network
//errCode -3: id repeat, 0 :ok
func NewNetwork(id string) int {
	errCode := 0
	if id == "" {
		errCode = -3
		addErrorMessage(errCode, ("(\"" + id + "\")"), id, "")
		return errCode
	}
	for i := range networkSet.netSet {
		if networkSet.netSet[i].ID == id {
			errCode = -3
			addErrorMessage(errCode, ("(\"" + id + "\")"), id, "")
			return errCode
		}
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	newNetwork := TNetwork{MagicIdentifier: "NM01", ID: id}
	networkSet.netSet = append(networkSet.netSet, newNetwork)
	networkSet.netSetBool = append(networkSet.netSetBool, true)
	return errCode
}

//GetNetworkIndex GetNetIndex
//return:  -2: net id can't find, >=0: ok
func GetNetworkIndex(id string) int {
	errCode := -2
	if id == "" {
		return errCode
	}
	for i := range networkSet.netSet {
		if networkSet.netSet[i].ID == id {
			index := i
			return index
		}
	}
	addErrorMessage(errCode, ("(\"" + id + "\")"), id, "")
	return errCode
}

//SaveNetworkAsJSON SaveNetworkAsJSON
//errCode:  0:ok, -5: invalid net index
//-10: "Json convert error", -11: "File error",
func SaveNetworkAsJSON(neti int, fileName string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	file, err1 := json.MarshalIndent(networkSet.netSet[neti], "", "    ")
	if err1 != nil {
		errCode = -10
		addErrorMessage(errCode, "()", "", "")
		return errCode
	}
	err2 := ioutil.WriteFile(fileName, file, 0644)
	if err2 != nil {
		errCode = -11
		addErrorMessage(errCode, "()", "", "")
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
		addErrorMessage(errCode, "(\""+filePath+"\")", "", "")
		return errCode
	}
	newNet := TNetwork{}
	err2 := json.Unmarshal([]byte(file), &newNet)
	if err2 != nil {
		errCode = -10
		addErrorMessage(errCode, "(\""+filePath+"\")", "", "")
		return errCode
	}
	for i := range networkSet.netSet {
		if newNet.ID == networkSet.netSet[i].ID {
			errCode = -3
			addErrorMessage(errCode, ("(\"" + filePath + "\")"), newNet.ID, "")
			return errCode
		}
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet.netSet = append(networkSet.netSet, newNet)
	return errCode
}

//DeleteNetwork DeleteNetwork
//errCode:  0:ok, -5: invalid net index
func DeleteNetwork(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet.netSet[neti] = TNetwork{}
	networkSet.netSetBool[neti] = false

	return errCode
}

//ClearNetworks ClearNetworks
func ClearNetworks() {
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet = TNetworkSet{}
	errMSG1 = ""
	errMSG2 = ""
}

//GetNumberOfNetworks GetNumberOfNetworks
//no error handling
func GetNumberOfNetworks() int {
	count := 0
	for i := range networkSet.netSetBool {
		if networkSet.netSetBool[i] == true {
			count++
		}
	}
	return count
}

//GetLargestNetworkIndex GetLargestNetworkIndex
//no error handling
func GetLargestNetworkIndex() int {
	return len(networkSet.netSetBool)
}

//GetNetworkID GetID of network
//errCode: 0:ok, -5: invalid net index
func GetNetworkID(neti int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error"
	}
	return networkSet.netSet[neti].ID
}
//GetNetworkBool return 0 if this network is deleted
//errCode: 0:ok, -5: invalid net index
func GetNetworkBool(neti int) int {
	bool1 := 0
	if neti < 0 || neti >= len(networkSet.netSet) {
		bool1 = -5
		addErrorMessage(bool1, "()", strconv.Itoa(neti), "")
		return bool1
	}
	if networkSet.netSetBool[neti] == true {
		bool1 = 1
		return bool1
	}

	return bool1
}

//AddNode adds a node to the network
//errCode -3: id repeat, 0 :ok
//-5: invalid net index
//-12: Variable out of range:
func AddNode(neti int, id string, x, y, w, h float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if id == "" {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
		return errCode
	}
	for i := range n.Nodes {
		if n.Nodes[i].ID == id {
			errCode = -3
			addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
			return errCode
		}
	}
	if x < 0 || y < 0 {
		errCode = -12
		m2 := strconv.FormatFloat(x, 'f', 3, 64) + ", " + strconv.FormatFloat(y, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "xy")
		return errCode
	}
	if w <= 0 || h <= 0 {
		errCode = -12
		m2 := strconv.FormatFloat(w, 'f', 3, 64) + ", " + strconv.FormatFloat(h, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "wh")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	newNode := TNode{ID: id, X: x, Y: y, W: w, H: h,
		FillColor:        color.RGBA{R: 255, G: 150, B: 80, A: 255},
		OutlineColor:     color.RGBA{R: 255, G: 100, B: 80, A: 255},
		OutlineThickness: 3,
		FontPointSize:    20,
		FontFamily:       "default",
		FontStyle:        "normal",
		FontWeight:       "default",
		FontName:         "",
		FontColor:        color.RGBA{R: 0, G: 0, B: 0, A: 255},
	}
	n.Nodes = append(n.Nodes, newNode)
	n.nodes = append(n.nodes, true)
	networkSet.netSet[neti] = n
	return errCode
}

//GetNodeIndex get node index by id
//index:  -2: node id can't find, >=0: ok
//-5: invalid net index
func GetNodeIndex(neti int, id string) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	errCode := -2
	if id == "" {
		return errCode
	}
	n := networkSet.netSet[neti]
	for i := range n.Nodes {
		if n.Nodes[i].ID == id {
			index := i
			return index
		}
	}
	addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
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
//return: 0: ok, -7: invalid node index, -4: node is not free
//-5: invalid net index
func DeleteNode(neti, nodei int) int {
	errCode := -4
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
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
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + strconv.Itoa(nodei)), "node"+strconv.Itoa(nodei), "")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei] = TNode{}
	n.nodes[nodei] = false
	// if nodei == 0 {
	// 	n.Nodes = n.Nodes[1:]
	// } else if nodei == len(n.Nodes)-1 {
	// 	n.Nodes = n.Nodes[:len(n.Nodes)-1]
	// } else {
	// 	n.Nodes = append(n.Nodes[:nodei], n.Nodes[nodei+1:]...)
	// }
	// networkSet.netSet[neti] = n
	return errCode
}

//ClearNetwork clear all nodes and reactions in this network
//errCode: 0: ok, -5:  invalid net index
func ClearNetwork(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet.netSet[neti].Nodes = make([]TNode, 0)
	networkSet.netSet[neti].nodes = make([]bool, 0)
	networkSet.netSet[neti].ReactionSet = make([]TReaction, 0)
	networkSet.netSet[neti].reactionset = make([]bool, 0)
	return errCode
}

//GetNumberOfNodes get the number of nodes in the current network
//num: >=0: ok, -5:  invalid net index
func GetNumberOfNodes(neti int) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	count := 0
	for i := range n.nodes {
		if n.nodes[i] == true {
			count++
		}
	}
	return count
}

//GetLargestNodeIndex GetLargestNodeIndex
//num: >=0: ok, -5:  invalid net index
func GetLargestNodeIndex(neti int) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	return len(n.nodes)
}

//GetNodeCenterX Get the X coordinate of the Center of node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeCenterX(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].X + n.Nodes[nodei].W*0.5
}

//GetNodeCenterY Get the X coordinate of the Center of node
//errCode: 0:ok, -7: index out of range
//-5: invalid net index
func GetNodeCenterY(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].Y + n.Nodes[nodei].H*0.5
}

//GetNodeID Get the id of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeID(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return "error"
	}
	return n.Nodes[nodei].ID
}


//GetNodeBool return 0 if this node is deleted
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeBool(neti, nodei int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if n.nodes[nodei] == true {
		errCode = 1
		return errCode
	}
	return errCode
}

//GetNodeX Get the X coordinate of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeX(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].X
}

//GetNodeY Get the Y coordinate of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeY(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].Y
}

//GetNodeW Get the Width of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeW(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].W
}

//GetNodeH Get the Height of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeH(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return -10000000 //meaningless number. won't be passed to next layer
	}
	return n.Nodes[nodei].H
}

//GetNodeFillColorRGB GetNodeFillColor rgb format
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFillColorRGB(neti, nodei int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	color1 := uint32(n.Nodes[nodei].FillColor.R)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FillColor.G)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FillColor.B)
	return color1
}

//GetNodeFillColorAlpha GetNodeFillColorAlpha
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFillColorAlpha(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	alpha1 := float64(n.Nodes[nodei].FillColor.A) / 255
	return alpha1
}

//GetNodeOutlineColorRGB GetNodeOutlineColorRGB
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeOutlineColorRGB(neti, nodei int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	color1 := uint32(n.Nodes[nodei].OutlineColor.R)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].OutlineColor.G)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].OutlineColor.B)
	return color1
}

//GetNodeOutlineColorAlpha GetNodeOutlineColorAlpha
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeOutlineColorAlpha(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	alpha1 := float64(n.Nodes[nodei].OutlineColor.A) / 255
	return alpha1
}

//GetNodeOutlineThickness GetNodeOutlineThickness
//errCode: -7: invalid node index
//-5: invalid net index
func GetNodeOutlineThickness(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0
	}
	return n.Nodes[nodei].OutlineThickness
}

//GetNodeFontPointSize GetNodeFontPointSize
//errCode: -7: invalid node index
//-5: invalid net index
func GetNodeFontPointSize(neti, nodei int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	return n.Nodes[nodei].FontPointSize
}

//GetNodeFontFamily Get the FontFamily of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontFamily(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return "error"
	}
	return n.Nodes[nodei].FontFamily
}

//GetNodeFontStyle GetNodeFontStyle
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontStyle(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return "error"
	}
	return n.Nodes[nodei].FontStyle
}

//GetNodeFontWeight GetNodeFontWeight
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontWeight(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return "error"
	}
	return n.Nodes[nodei].FontWeight
}

//GetNodeFontName Get the fontName of the node
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontName(neti, nodei int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error" //meaningless string. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return "error"
	}
	return n.Nodes[nodei].FontName
}

//GetNodeFontColorRGB GetNodeFontColorRGB
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontColorRGB(neti, nodei int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	color1 := uint32(n.Nodes[nodei].FontColor.R)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FontColor.G)
	color1 = (color1 << 8) | uint32(n.Nodes[nodei].FontColor.B)
	return color1
}

//GetNodeFontColorAlpha GetNodeFontColorAlpha
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func GetNodeFontColorAlpha(neti, nodei int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		*errCode = -7
		addErrorMessage(*errCode, "()", strconv.Itoa(nodei), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	alpha1 := float64(n.Nodes[nodei].FontColor.A) / 255
	return alpha1
}

//SetNodeID set the id of a node
//errCode -3: id repeat, 0 :ok
//-5: invalid net index
//-7: invalid node index
func SetNodeID(neti, nodei int, newID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if newID == "" {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(nodei) + ", \"" + newID + "\")"), newID, "")
		return errCode
	}
	for i := range n.Nodes {
		if n.Nodes[i].ID == newID {
			errCode = -3
			addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(nodei) + ", \"" + newID + "\")"), newID, "")
			return errCode
		}
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].ID = newID
	return errCode
}

//SetNodeCoordinate SetNodeCoordinate
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeCoordinate(neti, nodei int, x, y float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if x < 0 || y < 0 {
		errCode = -12
		m2 := strconv.FormatFloat(x, 'f', 3, 64) + ", " + strconv.FormatFloat(y, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "xy")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].X = x
	n.Nodes[nodei].Y = y

	return errCode
}

//SetNodeSize SetNodeSize
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeSize(neti, nodei int, w, h float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if w <= 0 || h <= 0 {
		errCode = -12
		m2 := strconv.FormatFloat(w, 'f', 3, 64) + ", " + strconv.FormatFloat(h, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "wh")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].W = w
	n.Nodes[nodei].H = h

	return errCode
}

//SetNodeFillColorRGB SetNodeFillColorRGB
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeFillColorRGB(neti, nodei, r, g, b int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 {
		errCode = -12
		m2 := strconv.Itoa(r) + ", " + strconv.Itoa(g) + ", " + strconv.Itoa(b)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
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
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeFillColorAlpha(neti, nodei int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		m2 := strconv.FormatFloat(a, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	A1 := uint8(a * 255)
	n.Nodes[nodei].FillColor.A = A1

	return errCode
}

//SetNodeOutlineColorRGB SetNodeOutlineColorRGB
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeOutlineColorRGB(neti, nodei, r, g, b int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 {
		errCode = -12
		m2 := strconv.Itoa(r) + ", " + strconv.Itoa(g) + ", " + strconv.Itoa(b)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
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
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeOutlineColorAlpha(neti, nodei int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		m2 := strconv.FormatFloat(a, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	A1 := uint8(a * 255)

	n.Nodes[nodei].OutlineColor.A = A1

	return errCode
}

//SetNodeOutlineThickness SetNodeOutlineThickness
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range
func SetNodeOutlineThickness(neti, nodei int, thickness float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if thickness <= 0 {
		errCode = -12
		m2 := strconv.FormatFloat(thickness, 'f', 2, 64)
		addErrorMessage(errCode, "()", m2, "positive")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].OutlineThickness = thickness
	return errCode
}

//SetNodeFontPointSize SetNodeFontPointSize
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range
func SetNodeFontPointSize(neti, nodei, fontPointSize int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if fontPointSize <= 0 {
		errCode = -12
		m2 := strconv.Itoa(fontPointSize)
		addErrorMessage(errCode, "()", m2, "positive")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].FontPointSize = fontPointSize
	return errCode
}

//SetNodeFontFamily SetNodeFontFamily
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range
func SetNodeFontFamily(neti, nodei int, fontFamily string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	_, ok := fontFamilyDict[fontFamily]
	if ok == false {
		errCode = -12
		addErrorMessage(errCode, "()", fontFamily, "not found")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].FontFamily = fontFamily
	return errCode
}

//SetNodeFontStyle SetNodeFontStyle
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range
func SetNodeFontStyle(neti, nodei int, fontStyle string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	_, ok := fontStyleDict[fontStyle]
	if ok == false {
		errCode = -12
		addErrorMessage(errCode, "()", fontStyle, "not found")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].FontStyle = fontStyle
	return errCode
}

//SetNodeFontWeight SetNodeFontWeight
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range
func SetNodeFontWeight(neti, nodei int, fontWeight string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	_, ok := fontWeightDict[fontWeight]
	if ok == false {
		errCode = -12
		addErrorMessage(errCode, "()", fontWeight, "not found")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].FontWeight = fontWeight
	return errCode
}

//SetNodeFontName SetNodeFontName
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
func SetNodeFontName(neti, nodei int, fontName string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	n.Nodes[nodei].FontName = fontName
	return errCode
}

//SetNodeFontColorRGB SetNodeFontColorRGB
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeFontColorRGB(neti, nodei, r, g, b int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 {
		errCode = -12
		m2 := strconv.Itoa(r) + ", " + strconv.Itoa(g) + ", " + strconv.Itoa(b)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	R1 := uint8(r)
	G1 := uint8(g)
	B1 := uint8(b)
	n.Nodes[nodei].FontColor.R = R1
	n.Nodes[nodei].FontColor.G = G1
	n.Nodes[nodei].FontColor.B = B1

	return errCode
}

//SetNodeFontColorAlpha SetNodeFontColorAlpha
//errCode: 0:ok, -7: invalid node index
//-5: invalid net index
//-12: Variable out of range:
func SetNodeFontColorAlpha(neti, nodei int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	n := networkSet.netSet[neti]
	if nodei < 0 || nodei >= len(n.Nodes) || n.nodes[nodei] == false {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		m2 := strconv.FormatFloat(a, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	A1 := uint8(a * 255)

	n.Nodes[nodei].FontColor.A = A1

	return errCode
}

//CreateReaction create an empty reacton
//errCode: 0: ok, -3: id repeat
//-5: invalid net index
func CreateReaction(neti int, id string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if id == "" {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
		return errCode
	}
	for i := range r {
		if r[i].ID == id {
			errCode = -3
			addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
			return errCode
		}
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	newReact := TReaction{ID: id,
		FillColor: color.RGBA{R: 255, G: 150, B: 80, A: 255},
		Thickness: 3,
	}
	newReact.Species[0] = make(map[string]TSpeciesNode, 0)
	newReact.Species[1] = make(map[string]TSpeciesNode, 0)

	networkSet.netSet[neti].ReactionSet = append(networkSet.netSet[neti].ReactionSet, newReact)
	networkSet.netSet[neti].reactionset = append(networkSet.netSet[neti].reactionset, true)
	return errCode
}

//GetReactionIndex get reaction index by id
//return: -2: id can't find, >=0: ok
//-5: invalid net index
func GetReactionIndex(neti int, id string) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	errCode := -2
	if id == "" {
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	for i := range r {
		if r[i].ID == id {
			index := i
			return index
		}
	}
	addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", \"" + id + "\")"), id, "")
	return errCode
}

//DeleteReaction delete the reaction with index
//errCode:  0:ok, -6: invalid reaction index
//-5: invalid net index
func DeleteReaction(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet.netSet[neti].ReactionSet[reai] = TReaction{}
	networkSet.netSet[neti].reactionset[reai] = false

	// if reai == 0 {
	// 	r = r[1:]
	// } else if reai == len(r)-1 {
	// 	r = r[:len(r)-1]
	// } else {
	// 	r = append(r[:reai], r[reai+1:]...)
	// }
	// networkSet.netSet[neti].ReactionSet = r

	return errCode
}

//ClearReactions clear all reactions in this network
//errCode: 0: ok, -5: invalid net index
func ClearReactions(neti int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	networkSet.netSet[neti].ReactionSet = make([]TReaction, 0)
	networkSet.netSet[neti].reactionset = make([]bool, 0)
	return errCode
}

//GetNumberOfReactions get the number of reactions in the current Reactionset
//return: >=0: ok, -5: invalid net index
func GetNumberOfReactions(neti int) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	count := 0
	for i := range networkSet.netSet[neti].reactionset {
		if networkSet.netSet[neti].reactionset[i] == true {
			count++
		}
	}
	return count
}

//GetLargestReactionIndex GetLargestReactionIndex
//return: >=0: ok, -5: invalid net index
func GetLargestReactionIndex(neti int) int {
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode := -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	return len(networkSet.netSet[neti].reactionset)
}

//GetReactionID Get the id of Reaction
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
func GetReactionID(neti, reai int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error"
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return "error"
	}
	return r[reai].ID
}

//GetReactionBool return 0 if this reaction is deleted
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
func GetReactionBool(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if networkSet.netSet[neti].reactionset[reai] == true {
		errCode = 1
		return errCode
	}
	return errCode
}

//GetReactionRateLaw Get the ratelaw of Reaction
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
func GetReactionRateLaw(neti, reai int, errCode *int) string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return "error"
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return "error"
	}
	return r[reai].RateLaw
}

//GetReactionFillColorRGB GetReactionFillColorRGB
//errCode: 0:ok,  -6: invalid reaction index
//-5: invalid net index
func GetReactionFillColorRGB(neti, reai int, errCode *int) uint32 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return 0
	}
	color1 := uint32(r[reai].FillColor.R)
	color1 = (color1 << 8) | uint32(r[reai].FillColor.G)
	color1 = (color1 << 8) | uint32(r[reai].FillColor.B)
	return color1
}

//GetReactionFillColorAlpha GetReactionFillColorAlpha
//errCode: 0:ok,  -6: invalid reaction index
//-5: invalid net index
func GetReactionFillColorAlpha(neti, reai int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0 //meaningless number. won't be passed to next layer
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return 0
	}
	alpha1 := float64(r[reai].FillColor.A) / 255
	return alpha1
}

//GetReactionLineThickness GetReactionLineThickness
//errCode: -6: invalid reaction index
//-5: invalid net index
func GetReactionLineThickness(neti, reai int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return 0
	}
	return r[reai].Thickness
}

//GetReactionCenterHandleX GetReactionCenterHandleX
//errCode: -6: invalid reaction index
//-5: invalid net index
func GetReactionCenterHandleX(neti, reai int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return 0
	}
	return r[reai].CenterHandleX
}

//GetReactionCenterHandleY GetReactionCenterHandleY
//errCode: -6: invalid reaction index
//-5: invalid net index
func GetReactionCenterHandleY(neti, reai int, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return 0
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return 0
	}
	return r[reai].CenterHandleY
}

//GetReactionSrcNodeStoich Get the SrcNode stoichiometry of Reaction
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
func GetReactionSrcNodeStoich(neti, reai int, srcNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return -1000000
	}
	return r[reai].Species[0][srcNodeID].Stoich
}

//GetReactionDestNodeStoich Get the DestNode stoichiometry of Reaction
//return: positive float : ok, -6: invalid reaction index, -7: invalid node index
//-5: invalid net index
func GetReactionDestNodeStoich(neti, reai int, destNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return -1000000
	}
	return r[reai].Species[1][destNodeID].Stoich
}

//GetReactionSrcNodeHandleX Get the SrcNode handel X of Reaction
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
func GetReactionSrcNodeHandleX(neti, reai int, srcNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return -1000000
	}
	return r[reai].Species[0][srcNodeID].HandleX
}

//GetReactionSrcNodeHandleY Get the SrcNode handel Y of Reaction
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
func GetReactionSrcNodeHandleY(neti, reai int, srcNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return -1000000
	}
	return r[reai].Species[0][srcNodeID].HandleY
}

//GetReactionDestNodeHandleX Get the DestNode handel X of Reaction
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
func GetReactionDestNodeHandleX(neti, reai int, destNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return -1000000
	}
	return r[reai].Species[1][destNodeID].HandleX
}

//GetReactionDestNodeHandleY Get the DestNode handel Y of Reaction
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
func GetReactionDestNodeHandleY(neti, reai int, destNodeID string, errCode *int) float64 {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return -1000000
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
		return -1000000
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		*errCode = -2
		addErrorMessage(*errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return -1000000
	}
	return r[reai].Species[1][destNodeID].HandleY
}

//GetNumberOfSrcNodes Get the SrcNode length of Reaction
//return: non-negative int: ok, -6: invalid reaction index
//-5: invalid net index
func GetNumberOfSrcNodes(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	return len(r[reai].Species[0])
}

//GetNumberOfDestNodes Get the DestNode length of Reaction
//return: non-negative int: ok, -6: invalid reaction index
//-5: invalid net index
func GetNumberOfDestNodes(neti, reai int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	return len(r[reai].Species[1])
}

//GetListOfReactionSrcNodes GetListOfReactionSrcNodes in alphabetical order
//return: non-empty slice : ok, -6: invalid reaction index
//-5: invalid net index
func GetListOfReactionSrcNodes(neti, reai int, errCode *int) []string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return make([]string, 0)
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
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
//return: non-empty slice : ok, -6: invalid reaction index
//-5: invalid net index
func GetListOfReactionDestNodes(neti, reai int, errCode *int) []string {
	*errCode = 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		*errCode = -5
		addErrorMessage(*errCode, "()", strconv.Itoa(neti), "")
		return make([]string, 0)
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		*errCode = -6
		addErrorMessage(*errCode, "()", strconv.Itoa(reai), "")
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
//-5: invalid net index
//-6: invalid reaction index,
//-7: invalid node index
//-8: "wrong stoich: stoich has to be positive"
//-3: id repeat
func AddSrcNode(neti, reai, nodei int, stoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if nodei < 0 || nodei >= len(networkSet.netSet[neti].Nodes) {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if stoich <= 0.0 {
		errCode = -8
		addErrorMessage(errCode, "()", strconv.FormatFloat(stoich, 'f', 3, 64), "")
		return errCode
	}
	R := r[reai]
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	srcNodeID := networkSet.netSet[neti].Nodes[nodei].ID
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == true {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", " + strconv.Itoa(nodei) + ", " + strconv.FormatFloat(stoich, 'f', 3, 64)), srcNodeID, "")
		return errCode
	}
	R.Species[0][srcNodeID] = TSpeciesNode{Stoich: stoich}

	return errCode
}

//AddDestNode add node and Stoich to reactionlist
//errCode:  0:ok,
//-5: invalid net index
//-6: invalid reaction index,
//-7: invalid node index
//-8: "wrong stoich: stoich has to be positive"
//-3: id repeat
func AddDestNode(neti, reai, nodei int, stoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if nodei < 0 || nodei >= len(networkSet.netSet[neti].Nodes) {
		errCode = -7
		addErrorMessage(errCode, "()", strconv.Itoa(nodei), "")
		return errCode
	}
	if stoich <= 0 {
		errCode = -8
		addErrorMessage(errCode, "()", strconv.FormatFloat(stoich, 'f', 3, 64), "")
		return errCode
	}
	R := r[reai]
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	destNodeID := networkSet.netSet[neti].Nodes[nodei].ID
	_, ok := R.Species[1][destNodeID]
	if ok == true {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", " + strconv.Itoa(nodei) + ", " + strconv.FormatFloat(stoich, 'f', 3, 64)), destNodeID, "")
		return errCode
	}
	R.Species[1][destNodeID] = TSpeciesNode{Stoich: stoich}
	networkSet.netSet[neti].ReactionSet[reai] = R

	return errCode
}

//DeleteSrcNode delete src nodes by id(ID).
//errCode: 0:ok, -6: invalid reaction index,
//-5: invalid net index
//-2: id not found
func DeleteSrcNode(neti, reai int, srcNodeID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	R := r[reai]
	_, ok := R.Species[0][srcNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	delete(R.Species[0], srcNodeID)
	networkSet.netSet[neti].ReactionSet[reai] = R
	return errCode
}

//DeleteDestNode delete all dest nodes by id
//errCode: 0:ok, -6: invalid reaction index,
//-5: invalid net index
//-2: id not found
func DeleteDestNode(neti, reai int, destNodeID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	R := r[reai]
	_, ok := R.Species[1][destNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return errCode
	}

	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	delete(R.Species[1], destNodeID)
	networkSet.netSet[neti].ReactionSet[reai] = R
	return errCode
}

//SetReactionID edit id of reaction
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
//-3: id repeat
func SetReactionID(neti, reai int, newID string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if newID == "" {
		errCode = -3
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + newID + "\")"), newID, "")
		return errCode
	}
	for i := range r {
		if r[i].ID == newID {
			errCode = -3
			addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + newID + "\")"), newID, "")
			return errCode
		}
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet.netSet[neti].ReactionSet[reai].ID = newID
	return errCode
}

//SetRateLaw edit rate law of reaction
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
func SetRateLaw(neti, reai int, rateLaw string) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet.netSet[neti].ReactionSet[reai].RateLaw = rateLaw
	return errCode
}

//SetReactionSrcNodeStoich edit Stoich by Reaction SrcNodeID
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
//-8: wrong stoich
func SetReactionSrcNodeStoich(neti, reai int, srcNodeID string, newStoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return errCode
	}
	if newStoich <= 0.0 {
		errCode = -8
		addErrorMessage(errCode, "()", strconv.FormatFloat(newStoich, 'f', 3, 64), "")
		return errCode
	}
	s := r[reai].Species[0][srcNodeID]
	s.Stoich = newStoich
	r[reai].Species[0][srcNodeID] = s

	return errCode
}

//SetReactionDestNodeStoich edit Stoich by Reaction DestNodeID
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
//-8: wrong stoich
func SetReactionDestNodeStoich(neti, reai int, destNodeID string, newStoich float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return errCode
	}
	if newStoich <= 0.0 {
		errCode = -8
		addErrorMessage(errCode, "()", strconv.FormatFloat(newStoich, 'f', 3, 64), "")
		return errCode
	}

	d := r[reai].Species[1][destNodeID]
	d.Stoich = newStoich
	r[reai].Species[1][destNodeID] = d
	return errCode
}

//SetReactionSrcNodeHandlePosition edit handleX and Y by Reaction SrcNodeID
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
//-12: Variable out of range
func SetReactionSrcNodeHandlePosition(neti, reai int, srcNodeID string, handleX, handleY float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	_, ok := r[reai].Species[0][srcNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + srcNodeID + "\")"), srcNodeID, "")
		return errCode
	}
	if handleX < 0 || handleY < 0 {
		errCode = -12
		addErrorMessage(errCode, "()", strconv.FormatFloat(handleX, 'f', 3, 64), "xy")
		return errCode
	}
	s := r[reai].Species[0][srcNodeID]
	s.HandleX = handleX
	s.HandleY = handleY
	r[reai].Species[0][srcNodeID] = s

	return errCode
}

//SetReactionDestNodeHandlePosition edit handleX and Y by Reaction DestNodeID
//errCode: -6: invalid reaction index,
//-5: invalid net index, -2: id not found
//-12: Variable out of range
func SetReactionDestNodeHandlePosition(neti, reai int, destNodeID string, handleX, handleY float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	_, ok := r[reai].Species[1][destNodeID]
	if ok == false {
		errCode = -2
		addErrorMessage(errCode, ("(" + strconv.Itoa(neti) + ", " + strconv.Itoa(reai) + ", \"" + destNodeID + "\")"), destNodeID, "")
		return errCode
	}
	if handleX < 0 || handleY < 0 {
		errCode = -12
		addErrorMessage(errCode, "()", strconv.FormatFloat(handleX, 'f', 3, 64), "xy")
		return errCode
	}
	s := r[reai].Species[1][destNodeID]
	s.HandleX = handleX
	s.HandleY = handleY
	r[reai].Species[1][destNodeID] = s

	return errCode
}

//SetReactionFillColorRGB SetReactionFillColorRGB
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
//-12: Variable out of range
func SetReactionFillColorRGB(neti, reai, R, G, B int) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255 {
		errCode = -12
		m2 := strconv.Itoa(R) + ", " + strconv.Itoa(G) + ", " + strconv.Itoa(B)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
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
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
//-12: Variable out of range:
func SetReactionFillColorAlpha(neti, reai int, a float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if a < 0 || a > 1 {
		errCode = -12
		m2 := strconv.FormatFloat(a, 'f', 3, 64)
		addErrorMessage(errCode, "()", m2, "color")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}
	A1 := uint8(a * 255)
	r[reai].FillColor.A = A1

	return errCode
}

//SetReactionLineThickness SetReactionLineThickness
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
//-12: Variable out of range
func SetReactionLineThickness(neti, reai int, thickness float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if thickness <= 0 {
		errCode = -12
		m2 := strconv.FormatFloat(thickness, 'f', 2, 64)
		addErrorMessage(errCode, "()", m2, "positive")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet.netSet[neti].ReactionSet[reai].Thickness = thickness
	return errCode
}

//SetReactionCenterHandlePosition SetReactionCenterHandlePosition
//errCode: 0:ok, -6: invalid reaction index
//-5: invalid net index
//-12: Variable out of range
func SetReactionCenterHandlePosition(neti, reai int, centerHandleX, centerHandleY float64) int {
	errCode := 0
	if neti < 0 || neti >= len(networkSet.netSet) || networkSet.netSetBool[neti] == false {
		errCode = -5
		addErrorMessage(errCode, "()", strconv.Itoa(neti), "")
		return errCode
	}
	r := networkSet.netSet[neti].ReactionSet
	if reai < 0 || reai >= len(r) || networkSet.netSet[neti].reactionset[reai] == false {
		errCode = -6
		addErrorMessage(errCode, "()", strconv.Itoa(reai), "")
		return errCode
	}
	if centerHandleX < 0 || centerHandleY < 0 {
		errCode = -12
		m2 := strconv.FormatFloat(centerHandleX, 'f', 2, 64)
		addErrorMessage(errCode, "()", m2, "xy")
		return errCode
	}
	if stackFlag {
		redoStack = TNetSetStack{}
		netSetStack.push(networkSet)
	}

	networkSet.netSet[neti].ReactionSet[reai].CenterHandleX = centerHandleX
	networkSet.netSet[neti].ReactionSet[reai].CenterHandleY = centerHandleY
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
// // 	err:= 0
// NewNetwork("network1")
// NewNetwork("network2")
// NewNetwork("network3")
// fmt.Println(NewNetwork(""))
// fmt.Println(networkSet.netSet)
// fmt.Println(networksetBool)
// fmt.Println(GetNumberOfNetworks())
// fmt.Println(GetLargestNetworkIndex())
// 	DeleteNetwork(1)
// 	fmt.Println(networkSet.netSet)
// 	fmt.Println(networksetBool)
// 	fmt.Println(GetNumberOfNetworks())

// fmt.Println(GetErrorMessage())
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
// SaveNetworkAsJSON(0,"net3.json")
// }
