#include "IodineAPI.c"

int main()
{
    int err;
    const char *Id;
    err = loadDll("../Iodine_Dll/Iodine.dll");
    if (err != 0)
    {
        printf(Iod_getErrorMessage(err)); 
        //two possible results: "can't find function in dll"; "Iodine DLL missing";
        return err; 
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
    //List1 is an array with 100 elements. if the network has 3 element, the 4th element: List1[3]==NULL.
    //As the result, Iod_getListOfXX()functions can only support maximum  99 elements. The final element should be NULL.
    //You can change the maximum number of elements manually in "ListOfIDs" or"ListOfStoich" in IodineAPI.c.
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

    char *List2[100]={"node1","node2"};
    //100 is recommended because List1 is an array with 100 element.
    printf("Equal?: %d\n",Iod_strArrayEqual(List1, &List2[0]));

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

    float *List3;
    List3 = Iod_getListOfReactionSrcStoich(0, 0);
    //SrcNodes and DestNodes are sorted in alphabetical order,
    //so the list of stoich will be sorted in the same order--the first '2.2' is the stoich of node1.
    printf("getListOfReactionSrcStoich in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfStoich" in IodineAPI.c.
        if (List3[i] != 0.0)
        {
            printf("%f\t", List3[i]);
        }
    }
    printf("\n");

    List3 = Iod_getListOfReactionDestStoich(0, 0);
    //SrcNodes and DestNodes are sorted in alphabetical order,
    //so the list of stoich will be sorted in the same order.
    printf("getListOfReactionDestStoich in network[0], reaction[0]: \n");
    for (int i = 0; i < 100; i++)
    { //100 is the length of "ListOfStoich" in IodineAPI.c.
        if (List3[i] != 0.0)
        {
            printf("%f\t", List3[i]);
        }
    }
    printf("\n");

    float List4[100]= {3.2,4.2};
    printf("Equal?: %d\n", Iod_floatArrayEqual(List3, &List4[0],0.01));

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