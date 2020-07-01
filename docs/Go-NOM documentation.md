# Basic Tutorial of GO-NOM

## Abbreviation in function parameter

| abbreviation | full name                              |
| :----------- | :------------------------------------- |
| neti:        | net index, index in network list       |
| nodei:       | node index, index in node list         |
| reai:        | reaction index, index in reaction list |
| errCode:     | error code                             |

## ReadNetworkFromJSON(filePath string) int

Read Network from JSON to current network list  

### Return:

+ errCode

| errCode | meaning |
| :---- | :---|
| 0:      | ok     |
| -3:     | network id file repeat with id in current network list |
| -10:    |Json convert error
|-11: |File error                |

### Example:

```go
Iodine.ReadNetworkFromJSON("D:\\test.go")
```

## SaveNetworkAsJSON(neti int, fileName string) int

Save network (index: neti) as .json file, file name: filename

### Return: 

+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok|
-5: |net index out of range
-10: |Json convert error
-11: |File error

### Example:

```go
Iodine.SaveNetworkAsJSON(0, "test.json")
```

## Undo() int

Undo last change.Any function in Iodine that changes the network, for example SetXX(), NewXX(), will create a copy in stack and can do Undo().

### Return:

+ errCode

| errCode | meaning |  
|:---|:---| 
0: |ok
-9: |stack is empty

### Example:

```go
Iodine.NewNetwork("net1")
num := Iodine.GetNumberOfNetworks()  //result: 1
Iodine.Undo()
num2 := Iodine.GetNumberOfNetworks()  //result: 0  //undo the "NewNetwork()"
```

## Redo() int

Redo last Undo.It works only if last change is Undo().Any function in Iodine that changes the network, for example SetXX(), NewXX(), will empty redo stack and redo() will not be supported.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---| 
0: |ok
-9: |stack is empty

### Example:

```go
errCode:= 0
Iodine.NewNetwork("net1")
Iodine.Redo()  //return: error code: -9  //last change is not Undo()
num := Iodine.GetNumberOfNetworks()  //result: 1
Iodine.Undo()
num2 := Iodine.GetNumberOfNetworks()  //result: 0  //undo the "NewNetwork"
Iodine.Redo() 
num3 := Iodine.GetNumberOfNetworks()  //result: 1  //redo the "NewNetwork"
```

## NewNetwork(id string) int

Create a new network with ID: id.Note that given id can’t repeat with any network id exist in the current network list.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---| 
 0:|ok
 -3:| id repeat

### Example:

```go
errCode1:= Iodine.NewNetwork("net1")
```

## GetNetworkIndex(id string) int

Get index(integer) of network in network list by id. 

### Return:

+ errCode (<0)
+ index (>=0)

| errCode | meaning |  
|:---|:---|
-2: |net id can't find

### Example:

```go
Iodine.NewNetwork("net1")
index := Iodine.GetNetworkIndex("net1")  // result: 0
```

## DeleteNetwork(neti int) int

Delete network (neti) in network list.All nodes, reactions etc.in it are also deleted.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5: |net index out of range

### Example:

```go
errCode:= 0
Iodine.NewNetwork("net1")
Iodine.NewNetwork("ne2")
num := Iodine.GetNumberOfNetworks()  //result: 2
Iodine.DeleteNetwork(0, &errCode)  //delete "net1"
num1 := Iodine.GetNumberOfNetworks()  //result: 1
```

## ClearNetworks()

Delete all networks.

### Return:

No return

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.NewNetwork("net2")
Iodine.ClearNetworks()
```

## GetNumberOfNetworks() int

Get number of networks in current network list.

### Return:

+ Number of networks, integer
+ no error handling

### Example:

```go
Iodine.NewNetwork("net1")
num := Iodine.GetNumberOfNetworks()  //result: 1
```

## GetNetworkID(neti int, errCode *int) string

Get ID of the network.
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ Network ID, string
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5: |net index out of range

### Example:

```go
errCode := 0
Iodine.NewNetwork("net1")
id := Iodine.GetNetworkID(0, &errCode)  //result: "net1"
fmt.Println(errCode)  //result: 0
id2 := Iodine.GetNetworkID(1, &errCode)  //result: "error" //net index out of range
fmt.Println(errCode)  //result: -5
```

## AddNode(neti int, id string, x, y, w, h float64) int

Add a note in network[neti].x and y have to be non-negative, w, h have to be positive.

### default values:

|variable|value|
|:---|:---|
FillColor: |R: 255, G: 150, B: 80, A: 255, hex value: '0xff9650ff' 
OutlineColor:|R: 255, G: 100, B: 80, A: 255, hex value: '0xff6450ff'
OutlineThickness: |3

### Return: 

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5: |net index out of range
-3: |id repeat
-12: |Variable out of range

### Example:

```go
Iodine.NewNetwork("net1")
err0:= Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: 0
err1:= Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: -3
err2:= Iodine.AddNode (0, "node1", -1, 2.2, 3.1, 4.1) //result: -12
```

## GetNodeIndex(neti int, id string) int

Get index of node by id

### Return:

+ index (>=0)
+ errCode(<0)

| errCode | meaning |  
|:---|:---|
-5: |net index out of range
-2: |node id can't find

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: 0
index1 :=Iodine.GetNodeIndex(0, "node1")  //result: 0
index2 :=Iodine.GetNodeIndex(0, "net")  //result: -2
index3 :=Iodine.GetNodeIndex(1, "node1")  //result:-5
```

## DeleteNode(neti, nodei int) int

Delete node by index (nodei).It can delete node only if it’s not in any reaction.(node is "free")

### Return: 

+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5: |net index out of range
-7: |node index out of range
-4: |node is not free

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: 0
Iodine.AddNode (0, "node2", 5.1, 2.5, 3.1, 4.1) //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0,0,0,1.1)
err0:= Iodine.DeleteNode(0,1) //result: 0  //ok
err1:= Iodine.DeleteNode(0,0) //result: -4  //node1 is in rea1
err2:= Iodine.DeleteNode(1,1) //result: -5  
err3:= Iodine.DeleteNode(0,2) //result: -7
```

## ClearNetwork(neti int) int

clear all nodes and reactions in this network.other features, for example id, are not changed.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5:|net index out of range

### Example:

```go
errCode:= 0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: 0
Iodine.AddNode (0, "node2", 5.1, 2.5, 3.1, 4.1) //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0,0,0,1.1)
Iodine.ClearNetwork(0)  //clear all nodes and reactions in net1
id := Iodine.GetNetworkID(0, &errCode)  //result: "net1"
id2 := Iodine.GetNodeID(0,0,&errCode)   //result: "error"//there is no node in net1
```

## GetNumberOfNodes(neti int) int

Get number of nodes.

### Return:

+ num(>=0)
+ errCode

| errCode | meaning |  
|:---|:---|
-5:|net index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1) //result: 0
num := Iodine.GetNumberOfNodes(0)  //result: 1
err := Iodine.GetNumberOfNodes(1)  //result: -5
```

## GetNodeCenterX(neti, nodei int, errCode *int) float64

Get X coordinate of node center.
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ X coordinate of node center, float64
+ errCode

| errCode | meaning |  
|:---|:---|
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
x := Iodine.GetNodeCenterX(0,0,&errCode)  //result: 2.65
fmt.Println(errCode)  //result: 0
x1 := Iodine.GetNodeCenterX(-1,0,&errCode) //result: -10000000 // meaningless number
fmt.Println(errCode)  //result: -5
x2 := Iodine.GetNodeCenterX(0,2,&errCode) //result: -10000000 // meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeCenterY(neti, nodei int, errCode *int) float64

Get Y coordinate of node center.
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ Y coordinate of node center, float64
+ errCode

| errCode | meaning |  
|:---|:---|
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
x := Iodine.GetNodeCenterY(0,0,&errCode)  //result: 4.25
fmt.Println(errCode)  //result: 0
x1 := Iodine.GetNodeCenterY(-1,0,&errCode) //result: -10000000 // meaningless number
fmt.Println(errCode)  //result: -5
x2 := Iodine.GetNodeCenterY(0,2,&errCode) //result: -10000000 // meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeID(neti, nodei int, errCode *int) string

Get the id of the node.
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ id of the node, string
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
id := Iodine.GetNodeID(0, 0, &errCode) //result: "net1"
fmt.Println(errCode)  //result: 0
id := Iodine.GetNodeID(-1, 0, &errCode) //result: "error"
fmt.Println(errCode)  //result: -5
id := Iodine.GetNodeID(0, -1, &errCode) //result: "error"
fmt.Println(errCode)  //result: -7
```

## GetNodeX(neti, nodei int, errCode *int) float64

Get the X coordinate of the node
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ X coordinate of the node, float64
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
id := Iodine.GetNodeX (0, 0, &errCode) //result: 1.1
fmt.Println(errCode)  //result: 0
id := Iodine.GetNodeX (-1, 0, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -5
id := Iodine.GetNodeX (0, -1, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeY(neti, nodei int, errCode *int) float64

Get the Y coordinate of the node
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ Y coordinate of the node, float64
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
id := Iodine.GetNodeY (0, 0, &errCode) //result: 2.2
fmt.Println(errCode)  //result: 0
id := Iodine.GetNodeY (-1, 0, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -5
id := Iodine.GetNodeY (0, -1, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeW(neti, nodei int, errCode *int) float64

Get the Width of the node
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ Width of the node, float64
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
id := Iodine.GetNodeW (0, 0, &errCode) //result: 2.2
fmt.Println(errCode)  //result: 0
id := Iodine.GetNodeW (-1, 0, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -5
id := Iodine.GetNodeW (0, -1, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeH(neti, nodei int, errCode *int) float64 

Get the Height of the node
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ Height of the node, float64
+ errCode
  
| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
id := Iodine.GetNodeH (0, 0, &errCode) //result: 2.2
fmt.Println(errCode)  //result: 0
id := Iodine.GetNodeH (-1, 0, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -5
id := Iodine.GetNodeH (0, -1, &errCode) //result: -10000000 //meaningless number
fmt.Println(errCode)  //result: -7
```

## GetNodeFillColor(neti, nodei int, errCode *int) uint32

get RGBA format fillcolor of the node.
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ RGBA format fillcolor of the node, uint32
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
color := Iodine.GetNodeFillColor(0, 0, &errCode)
fmt.Printf("%x", color)  //0xff9650ff, default fillcolor
```

## GetNodeOutlineColor(neti, nodei int, errCode *int) uint32

get RGBA format outline color of the node
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ RGBA format outline color of the node, uint32
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
color := Iodine.GetNodeOutlineColor (0, 0, &errCode)
fmt.Printf("%x", color)  //0xff6450ff, default outline color
```

## GetNodeOutlineThickness(neti, nodei int) int

Get Outline Thickness of the Node.

### Return:

+ Outline Thickness of the Node, positive integer.
+ errCode

| errCode | meaning |  
|:---|:---|
-5:|net index out of range
-7:|node index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
thickness1 := Iodine.GetNodeOutlineThickness (0, 0)  //result: 3 //default thickness
```

## SetNodeID(neti, nodei int, newID string) int

set the id of a node. new ID can't repeat with any other IDs in the same network.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range
-3:|id repeat

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err:= Iodine.SetNodeID(0,0, "Node1" )
fmt.Println(err) //result: 0
errCode:= 0
Id1:= Iodine.GetNodeID(0, 0, &errCode)  //result: "Node1"
fmt.Println(errCode) //result: 0
```

## SetNodeCoordinateAndSize(neti, nodei int, x, y, w, h float64) int

Set coordinate and size of the node. x and y have to be non-negative, w, h have to be positive.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range
-12:|Variable out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err:= Iodine.SetNodeCoordinateAndSize(0,0, 2.1, 2.2, 3.1, 4.1 )
fmt.Println(err) //result: 0
errCode:= 0
x1:= Iodine.GetNodeX(0, 0, &errCode)  //result: 2.1
fmt.Println(errCode) //result: 0
```

## SetNodeFillColor(neti, nodei, r, g, b, a int) int

Set Fill Color of the node.(RGBA, range: 0-255 integer)

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range
-12:|Variable out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err := Iodine.SetNodeFillColor(0,0,255,255,0,255)
```

## SetNodeOutlineColor(neti, nodei, r, g, b, a int) int

Set outline Color of the node.(RGBA, range: 0-255 integer) 

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range
-12:|Variable out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err := Iodine.SetNodeOutlineColor (0,0,255,255,0,255)
```

## SetNodeOutlineThickness(neti, nodei, thickness int) int

Set outline thickness of the node. Thickness has to be positive integer.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-7:|node index out of range
-12:|Variable out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err := Iodine.SetNodeOutlineThickness (0,0,2)
```

## CreateReaction(neti int, id string) int

Create a reaction in the network[neti]. id can not repeat with any existing reactions.  
**AddSrcNode(neti, reai, nodei int, stoich float64),   AddDestNode(neti, reai, nodei int, stoich float64),  SetRateLaw(neti, reai int, rateLaw string),  SetReactionFillColor(neti, reai, R, G, B, A int),  SetReactionLineThickness(neti, reai, thickness int)** may be needed to set features in this reaction.  

### default values:

|variable|value|
|:---|:---|
FillColor: |R: 255, G: 150, B: 80, A: 255
Thickness: |3
SrcNode: |Nil
DestNode:|Nil
RateLaw: |""

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5:|net index out of range
-3:|id repeat

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
err: = Iodine.CreateReaction(0, "rea1")
```

## GetReactionIndex(neti int, id string) int

Get index of reaction in the reaction list.Search reaction by id.

### Return:

+ index, non-negative int
+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5:|net index out of range
-2:|id can't find,

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   
Iodine.CreateReaction(0, "rea1")
index1:= Iodine.GetReactionIndex(0, "rea1")  //result: 0
```

## DeleteReaction(neti, reai int) int

Delete reaction in network[neti]

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)
Iodine.CreateReaction(0, "rea1")
Iodine.CreateReaction(0, "rea2")
errCode:= 0
err0 := Iodine.GetReactionID(0,1, &errCode)  //result: "rea2"
err1:= Iodine.DeleteReaction(0,1)
err2:= Iodine.GetReactionID(0,1, &errCode)   //result: "error"
fmt.Println(err2)  //result: -6 //reaction index out or range
```

## ClearReactions(neti int) int

Clear all reactions in network[neti].

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)
Iodine.CreateReaction(0, "rea1")
Iodine.CreateReaction(0, "rea2")
errCode:= 0
err0 := Iodine.GetReactionID(0,1, &errCode)  //result: "rea2"
err1:= Iodine.ClearReactions (0)
err2:= Iodine.GetReactionID(0,0, &errCode)   //result: "error"
fmt.Println(err2)  //result: -6 //reaction index out or range
```

## GetNumberOfReactions(neti int) int

Get number of reactions in network[neti].

### Return:

+ num(>=0)
+ errCode(<0)

| errCode | meaning |  
|:---|:---|
-5:|net index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)
Iodine.CreateReaction(0, "rea1")
Iodine.CreateReaction(0, "rea2")
num := Iodine.GetNumberOfReactions (0)  //result: 2
```

## GetReactionID(neti, reai int, errCode *int) string

Get id of reaction[reai] in network[neti].
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ id, string
+ errCode

| errCode | meaning |  
|:---|:---|
0: |ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   
Iodine.CreateReaction(0, "rea1")
errCode:= 0
id := Iodine.GetReactionID (0, 0, &errCode)  //result: "rea1"
fmt.Println(errCode) //result: 0
```

## GetReactionRateLaw(neti, reai int, errCode *int) string

Get RateLaw of the reaction.
To make it compatible with the other API, errCode is stored in a pointer.

### Return:

+ RateLaw, string
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)
Iodine.CreateReaction(0, "rea1")
errCode:= 0
rateLaw1 := Iodine.GetReactionRateLaw (0, 0, &errCode)  //result: "" //default value
fmt.Println(errCode) //result: 0
```

## GetReactionFillColor(neti, reai int, errCode *int) uint32

Get FillColor of the Reaction, RGBA
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 
+ RGBA format fill color of the node, uint32
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
color := Iodine.GetReactionFillColor (0, 0, &errCode)
fmt.Printf("%x", color)  //0xff9650ff, default fillcolor
```

## GetReactionLineThickness(neti, reai int) int

Get Thickness of the Reaction line.

### Return:

+ Thickness of the Reaction line, positive integer.
+ errCode

| errCode | meaning |  
|:---|:---|
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
thickness1 := Iodine.GetNodeOutlineThickness (0, 0)  //result: 3 //default thickness
```

## GetReactionSrcNodeStoich(neti, reai int, srcNodeID string, errCode *int) float64

Get Reaction Source node stoichiometry
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ Reaction Source node stoichiometry, float64
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-2:|id not found

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0, 0, 1, 1.3)  //add "node2" as srcNode
stoich1 := Iodine.GetReactionSrcNodeStoich(0,0, "node2",&errCode) //result: 1.3
fmt.Println(errCode) //result: 0
```

## GetReactionDestNodeStoich(neti, reai int, destNodeID string, errCode *int) float64

Get Reaction DestNode stoichiometry
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ Reaction DestNode stoichiometry, float64
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-2:|id not found

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddDestNode(0, 0, 1, 1.3)  //add "node2" as destNode
stoich1 := Iodine.GetReactionDestNodeStoich (0,0, "node2",&errCode) //result: 1.3
fmt.Println(errCode) //result: 0
```

## GetNumberOfSrcNodes(neti, reai int) int

Get Number of SrcNodes

### Return:

+ Number of SrcNodes
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0, 0, 1, 1.3)  //add "node2" as srcNode of rea1
Iodine.AddSrcNode(0, 0, 0, 1.5)  //add "node1" as srcNode of rea1
num1:= Iodine.GetNumberOfSrcNodes(0,0)  //result: 2
```

## GetNumberOfDestNodes(neti, reai int) int

Get Number of DestNodes

### Return:

+ Number of DestNodes
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddDestNode(0, 0, 1, 1.3)  //add "node2" as destNode of rea1
Iodine.AddDestNode(0, 0, 0, 1.5)  //add "node1" as destNode of rea1
num1:= Iodine.GetNumberOfDestNodes(0,0)  //result: 2
```

## GetListOfReactionSrcNodes(neti, reai int, errCode *int) []string

Get list of reaction SrcNodes ids.ids are sorted in alphabet order.
To make it compatible with the other API, errCode is stored in a pointer.

### Return: 

+ list of reaction SrcNodes
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0, 0, 1, 1.3)  //add "node2" as srcNode of rea1
Iodine.AddSrcNode(0, 0, 0, 1.5)  //add "node1" as srcNode of rea1
list1:= Iodine.GetListOfReactionSrcNodes (0,0, &errCode)  //result: ["node1","node2"]
```

## GetListOfReactionDestNodes(neti, reai int, errCode *int) []string

Get list of reaction DestNodes ids.ids are sorted in alphabet order.  
To make it compatible with the other API, errCode is stored in a pointer.

## Return:

+ list of reaction DestNodes
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddDestNode(0, 0, 1, 1.3)  //add "node2" as destNode of rea1
Iodine.AddDestNode(0, 0, 0, 1.5)  //add "node1" as destNode of rea1
list1:= Iodine.GetListOfReactionDestNodes (0,0, &errCode)  //result: ["node1","node2"]
```

## AddSrcNode(neti, reai, nodei int, stoich float64) int

Add srcNode to the reaction.The node has to be in the network and it’s id can’t repeat with any existed srcNode.if id repeats, it will return errCode: -3.Note that stoich of a node has to be positive float.

### Return: 

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-7:|node index out of range
-8:|wrong stoich: stoich has to be positive
-3:|id repeat

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
errCode1 :=Iodine.AddSrcNode(0, 0, 1, 1.3)  //add "node2" as srcNode of rea1
```

## AddDestNode(neti, reai, nodei int, stoich float64) int

Add destNode to the reaction.The node has to be in the network and it’s id can’t repeat with any existed destNode.if id repeats, it will return errCode: -3.Note that stoich of a node has to be positive float.

### Return: 

+ errCode  

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-7:|node index out of range
-8:|wrong stoich: stoich has to be positive
-3:|id repeat

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
errCode1 :=Iodine.AddDestNode(0, 0, 1, 1.3)  //add "node2" as destNode of rea1
```

## DeleteSrcNode(neti, reai int, srcNodeID string) int

Delete SrcNode by id.

### Return: 
+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-2:|id not found

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddSrcNode(0, 0, 1, 1.3)  //add "node2" as srcNode of rea1
Iodine.AddSrcNode(0, 0, 0, 1.5)  //add "node1" as srcNode of rea1
list1:= Iodine.GetListOfReactionSrcNodes (0,0, &errCode)  //result: ["node1","node2"]
err1:= Iodine.DeleteSrcNode(0,0, "node1)"
list2:= Iodine.GetListOfReactionSrcNodes (0,0, &errCode)  //result: ["node2"]
```

## DeleteDestNode(neti, reai int, destNodeID string) int

Delete destNode by id.

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-2:|id not found

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.AddNode (0, "node2", 1.2, 3.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
Iodine.AddDestNode(0, 0, 1, 1.3)  //add "node2" as DestNode of rea1
Iodine.AddDestNode(0, 0, 0, 1.5)  //add "node1" as DestNode of rea1
list1:= Iodine.GetListOfReactionDestNodes (0,0, &errCode)  //result: ["node1","node2"]
err1:= Iodine.DeleteDestNode(0,0, "node1)"
list2:= Iodine.GetListOfReactionDestNodes (0,0, &errCode)  //result: ["node2"]
```

## SetRateLaw(neti, reai int, rateLaw string) int

Set rateLaw of a reaction.

## Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
err1:= Iodine.SetRateLaw(0, 0, "k1*A")
ratelaw1:= Iodine.GetReactionRateLaw(0, 0, &errCode)  //result: "k1*A"
```

## SetReactionFillColor(neti, reai, R, G, B, A int) int

Set Reaction’s FillColor (RGBA, 0-255)

### Return:

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-12: |Variable out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
err1:= Iodine.SetReactionFillColor(0,0, 255,255,0,255) //result: 0
```

## SetReactionLineThickness(neti, reai, thickness int) int
Set Line Thickness of a reaction.Thickness has to be positive int.

### Return: 

+ errCode

| errCode | meaning |  
|:---|:---|
0:|ok
-5:|net index out of range
-6:|reaction index out of range
-12: |Variable out of range

### Example:

```go
errCode:=0
Iodine.NewNetwork("net1")
Iodine.AddNode (0, "node1", 1.1, 2.2, 3.1, 4.1)   //result: 0
Iodine.CreateReaction(0, "rea1")
err1:= Iodine.SetReactionLineThickness(0,0, 1) //result: 0
```
