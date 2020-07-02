#include "IodineAPI.c"

int main()
{
    int errorCode;
    int err;
    const char *Id;
    err = loadDll(&errorCode);
    if (!err)
    {
        return -1; //can't load the lib
    }
    err = Iod_newNetwork("net1"); //it will return minus int if it fails.
    //I haven't added error handling now so you need to check it manually.
    if (err < 0)
    {
        printf(Iod_getErrorMessage(err));
    }
    err = Iod_newNetwork("net2"); //add another network.
    err = Iod_newNetwork("net3"); //add another network.

    Id = Iod_getNetworkID(0); //the network with index '0' should be "net1",
    //as it was added first. if you are not sure about the index, use Iod_getXXIndex(),
    //for example: int Index1 = Iod_getNetworkIndex("net1")
    err = Iod_getErrorCode();
    if (err < 0)
    {
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
    printf("reaction1 in net1 has %d srcNodes\n", num1);
    int num2 = Iod_getNumberOfDestNodes(0, 0); //netIndex, reactionIndex
    printf("reaction1 in net1 has %d destNodes\n", num2);

    char **List1;
    List1 = Iod_getListofNetworks();
    printf("getListOfNetworks: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (List1[i] != NULL)
        {
            printf("%s\t", List1[i]);
        }
    }
    printf("\n");

    List1 = Iod_getListOfNodesIDs(0);
    printf("getListOfNodesIDs in network[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (List1[i] != NULL)
        {
            printf("%s\t", List1[i]);
        }
    }
    printf("\n");

    List1 = Iod_getListOfReactionIDs(0);
    printf("getListOfReactionIDs in network[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (List1[i] != NULL)
        {
            printf("%s\t", List1[i]);
        }
    }
    printf("\n");

    List1 = Iod_getListOfReactionSrcNodes(0, 0);
    //SrcNodes and DestNodes aren't stored in order, 
    //so the list of ids will be sorted in alphabetical order.
    //that's why the result is ["node1","node2"] even node2 is added first.
    printf("getListOfReactionSrcNodes in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (List1[i] != NULL)
        {
            printf("%s\t", List1[i]);
        }
    }
    printf("\n");

    List1 = Iod_getListOfReactionDestNodes(0, 0);
    //SrcNodes and DestNodes aren't stored in order,
    //so the list of ids will be sorted in alphabetical order.
    printf("getListOfReactionDestNodes in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfIDs" in IodineAPI.c.
        if (List1[i] != NULL)
        {
            printf("%s\t", List1[i]);
        }
    }
    printf("\n");

    float *list2;
    list2 = Iod_getListOfReactionSrcStoich(0, 0);
    //SrcNodes and DestNodes are sorted in alphabetical order,
    //so the list of stoich will be sorted in the same order--the first '2.2' is the stoich of node1.
    printf("getListOfReactionSrcStoich in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfStoich" in IodineAPI.c.
        if (list2[i] != 0.0)
        {
        printf("%f\t", list2[i]);
        }
    }
    printf("\n");

    list2 = Iod_getListOfReactionDestStoich(0, 0);
    //SrcNodes and DestNodes are sorted in alphabetical order,
    //so the list of stoich will be sorted in the same order.
    printf("getListOfReactionDestStoich in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfStoich" in IodineAPI.c.
        if (list2[i] != 0.0)
        {
            printf("%f\t", list2[i]);
        }
    }
    printf("\n");

    //###########################################################
    //need free library manually at the end of the program.
    bool fFreeResult = FreeLibrary(Iod_hinstLib);
    if (!fFreeResult)
    {
        printf("free error");
    }
    //###########################################################

    return 0;
}