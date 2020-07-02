#include "IodineAPI.c"

int main()
{
    int errorCode;
    int err;
    const char *Id;
    err = loadDll(&errorCode);
    if (!err){
        return -1;//can't load the lib
    }
    err = Iod_newNetwork("net1"); //it will return minus int if it fails.
    //I haven't added error handling now so you need to check it manually.
    if (err<0){
        printf(Iod_getErrorMessage(err));
    }
    err = Iod_newNetwork("net2"); //add another network.

    Id = Iod_getNetworkID(0); //the network with index '0' should be "net1",
    //as it was added first. if you are not sure about the index, use getXXIndex(), 
    //for example: int Index1 = getNetworkIndex("net1")
    err = Iod_getErrorCode();
    if (err < 0){
        printf(Iod_getErrorMessage(err));
    }
    //for those functions return not an int, errCode can be got by getErrorCode()
    printf("Network[0] Id = %s\n", Id);

    err = Iod_addNode(0, "node1", 1.1, 2.2, 3.3, 4.4); // netindex, nodeName, x,y,w,h
    err = Iod_addNode(0, "node2", 1.1, 2.2, 3.3, 4.4); //name can't repeat
    err = Iod_addNode(0, "node3", 1.1, 2.2, 3.3, 4.4);
    err = Iod_addNode(0, "node4", 1.1, 2.2, 3.3, 4.4);

    err = Iod_setNodeCoordinateAndSize(0, 0, 2.2, 2.2, 2.2, 2.2); //NetIndex, nodeIndex, x,y,w,h
    err = Iod_setNodeFillColor(0, 0, 255, 255, 255, 255);         //netIndex, nodeIndex,R,G,B,A (range 0-255)

    err = Iod_createReaction(0, "reaction1");
    err = Iod_setRateLaw(0, 0, "k1*A");
    err = Iod_addSrcNode(0, 0, 1, 1.2); //netIndex, ReactionIndex, NodeIndex, Node stoich
    err = Iod_addSrcNode(0, 0, 0, 2.2);
    err = Iod_addDestNode(0, 0, 2, 3.2);
    err = Iod_addDestNode(0, 0, 3, 4.2);
    //now reaction1 is 1.2 Node2 + 2.2 Node1 ->  3.2 Node3 + 4.2 node4

    int num1 = Iod_getNumberOfSrcNodes(0, 0); //netIndex, reactionIndex
    printf("reaction1 in net1 has %d srcNodes\n",num1);
    int num2 = Iod_getNumberOfDestNodes(0, 0); //netIndex, reactionIndex
    printf("reaction1 in net1 has %d destNodes\n", num2);

    bool fFreeResult = FreeLibrary(Iod_hinstLib); //need free library manually at the end of the program.
    if (!fFreeResult){
        printf("free error");
    }

    return 0;
}