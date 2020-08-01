import IodineAPI
import unittest


class TestNetworkFunc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        IodineAPI.newNetwork("network1")
        IodineAPI.newNetwork("network2")

    def tearDown(self):
        IodineAPI.clearNetworks()

    def test_newNetwork(self):
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.newNetwork("network1")
        self.assertEqual(IodineAPI.newNetwork("network3"),  None)
        self.assertEqual(IodineAPI.newNetwork("network4"),  None)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1', "network2", "network3", "network4"])
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(), [
                         'network1', "network2", "network3"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1', "network2", "network3", "network4"])


    def test_getNetworkIndex(self):
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.getNetworkIndex("network3")
        self.assertEqual(IodineAPI.getNetworkIndex("network2"),  1)
        self.assertEqual(IodineAPI.getNetworkIndex("network1"),  0)

    def test_deleteNetwork(self):
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteNetwork(2)
        self.assertEqual(IodineAPI.deleteNetwork(1),  None)
        self.assertEqual(IodineAPI.getListOfNetworks(), ['network1'])
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1', "network2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1'])

    def test_clearNetworks(self):
        self.assertEqual(IodineAPI.clearNetworks(),  None)
        self.assertEqual(IodineAPI.getListOfNetworks(), [])
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1', "network2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNetworks(), [])

    def test_getNumberOfNetworks(self):
        self.assertEqual(IodineAPI.getNumberOfNetworks(),  2)

    def test_getNetworkId(self):
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNetworkId(2)
        self.assertEqual(IodineAPI.getNetworkId(0),  'network1')

    def test_getListOfNetworks(self):
        self.assertEqual(IodineAPI.getListOfNetworks(),
                         ['network1',  'network2'])


class TestNodeFunc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        IodineAPI.newNetwork("network1")
        IodineAPI.addNode(0, "node1", 1.1, 2.5, 5.4, 6.4)
        IodineAPI.addNode(0, "node2", 1.2, 3.2, 2.5, 4.1)
        IodineAPI.addNode(0, "node3", 2.2, 3.1, 1.5, 4.5)
        IodineAPI.newNetwork("network2")
        IodineAPI.addNode(1, "node1", 1.1, 3.5, 7.4, 6.0)

    def tearDown(self):
        IodineAPI.clearNetworks()

    def test_addNode(self):
        self.assertEqual(IodineAPI.addNode(
            0, "node4", 1.1, 2.5, 5.4, 6.4), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(
            0), ["node1", "node2", "node3", "node4"])
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.addNode(0, "node2", 1.2, 3.2, 2.5, 4.1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addNode(-1, "node5", 1.2, 3.2, 2.5, 4.1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addNode(2, "node5", 1.2, 3.2, 2.5, 4.1)
        
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", -1, 2.5, 5.4, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", 1.1, -1, 5.4, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", 1.1, 2.5, -1, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", 1.1, 2.5,  0, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", 1.1, 2.5, 5.4, -1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.addNode(0, "node5", 1.1, 2.5, 5.4,  0)
        
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0),
                         ["node1", "node2", "node3"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0), [
                         "node1", "node2", "node3", "node4"])

    def test_getNodeIndex(self):
        self.assertEqual(IodineAPI.getNodeIndex(0, "node1"), 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeIndex(-1, "node2")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.getNodeIndex(0, "node5")


    def test_deleteNode(self):
        self.assertEqual(IodineAPI.deleteNode(0, 1), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(
            0), ["node1", "node3"])
        self.assertEqual(IodineAPI.deleteNode(1, 0), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(1), [])
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(1),
                         ["node1"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(1), [])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteNode(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteNode(2, 0)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.deleteNode(0, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.deleteNode(0, 3)
        IodineAPI.createReaction(0, "rea1")
        IodineAPI.addSrcNode(0, 0, 0, 1)
        with self.assertRaises(IodineAPI.NodeNotFreeError):
            IodineAPI.deleteNode(0, 0)
        IodineAPI.addDestNode(0, 0, 1, 6)
        with self.assertRaises(IodineAPI.NodeNotFreeError):
            IodineAPI.deleteNode(0, 1)

    def test_clearNetwork(self):
        IodineAPI.CreateBiBi(0, "Rea1", "k1*A",
                             0, 1, 2, 1, 1, 2, 3, 4)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1"])
        self.assertEqual(IodineAPI.clearNetwork(0), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0), [])
        self.assertEqual(IodineAPI.getListOfReactionIds(0), [])
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0),
                         ["node1", "node2", "node3"])
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0), [])
        self.assertEqual(IodineAPI.getListOfReactionIds(0), [])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.clearNetwork(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.clearNetwork(2)

            
    def test_getNumberOfNodes(self):
        self.assertEqual(IodineAPI.getNumberOfNodes(0), 3)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfNodes(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfNodes(2)

    def test_getNodeCenter(self):
        self.assertEqual(IodineAPI.getNodeCenter(0, 0), (3.80, 5.70))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeCenter(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeCenter(2, 0)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeCenter(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeCenter(0, 3)

    def test_getNodeId(self):
        self.assertEqual(IodineAPI.getNodeId(0, 0), "node1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeId(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeId(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeId(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeId(1, 4)

    def test_getListOfNodeIds(self):
        self.assertEqual(IodineAPI.getListOfNodeIds(
            0), ["node1", "node2", "node3"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfNodeIds(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfNodeIds(2)
        self.assertEqual(IodineAPI.clearNetwork(0), None)
        self.assertEqual(IodineAPI.getListOfNodeIds(0), [])

    def test_getNodeCoordinateAndSize(self):
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 0), (1.1, 2.5, 5.4, 6.4))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeCoordinateAndSize(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeCoordinateAndSize(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeCoordinateAndSize(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeCoordinateAndSize(1, 4)

    def test_getNodeFillColor(self):
        self.assertEqual(IodineAPI.getNodeFillColor(0, 0), (255, 150, 80, 1.0))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColor(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColor(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColor(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColor(1, 4)

    def test_getNodeFillColorRGB(self):
        self.assertEqual(hex(IodineAPI.getNodeFillColorRGB(0, 0)), '0xff9650')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColorRGB(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColorRGB(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColorRGB(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColorRGB(1, 4)

    def test_getNodeFillColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getNodeFillColorAlpha(0, 0), 1, 2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColorAlpha(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeFillColorAlpha(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColorAlpha(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeFillColorAlpha(1, 4)


    def test_getNodeOutlineColor(self):
        self.assertEqual(
            IodineAPI.getNodeOutlineColor(0, 0), (255, 100, 80, 1.0))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColor(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColor(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColor(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColor(1, 4)


    def test_getNodeOutlineColorRGB(self):
        self.assertEqual(
            hex(IodineAPI.getNodeOutlineColorRGB(0, 0)), '0xff6450')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorRGB(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorRGB(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorRGB(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorRGB(1, 4)

    def test_getNodeOutlineColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getNodeOutlineColorAlpha(0, 0), 1, 2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorAlpha(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorAlpha(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorAlpha(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineColorAlpha(1, 4)

    def test_getNodeOutlineThickness(self):
        self.assertEqual(IodineAPI.getNodeOutlineThickness(0, 1), 3)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineThickness(-1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNodeOutlineThickness(3, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineThickness(1, -1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.getNodeOutlineThickness(1, 4)

    def test_setNodeId(self):
        self.assertEqual(IodineAPI.getNodeId(0, 1), "node2")
        self.assertEqual(IodineAPI.setNodeId(0, 1, "Node2"), None)
        self.assertEqual(IodineAPI.getNodeId(0, 1), "Node2")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeId(-1, 1, "Node2")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeId(3, 1, "Node2")
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeId(1, -1, "Node2") 
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeId(1, 1, "Node2")
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.setNodeId(0, 1, "node1")
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.setNodeId(0, 1, "node3")

        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getNodeId(0, 1), "node2")
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getNodeId(0, 1), "Node2")


    def test_setNodeCoordinate(self):
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 2.5, 4.1))
        self.assertEqual(IodineAPI.setNodeCoordinate(
            0, 1, 1.1, 2.5), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.1, 2.5, 2.5, 4.1))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeCoordinate(-1, 1, 1.2, 3.2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeCoordinate(3, 1, 1.2, 3.2)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeCoordinate(1, -1, 1.2, 3.2)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeCoordinate(1, 4, 1.2, 3.2)
        
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeCoordinate(0, 1, -1, 2.5)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeCoordinate(0, 1, 1.1, -1)


        
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 2.5, 4.1))
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.1, 2.5, 2.5, 4.1))

    def test_setNodeSize(self):
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 2.5, 4.1))
        self.assertEqual(IodineAPI.setNodeSize(
            0, 1, 5.4, 6.4), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 5.4, 6.4))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeSize(-1, 1, 2.5, 4.1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeSize(3, 1, 2.5, 4.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeSize(1, -1, 2.5, 4.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeSize(1, 4, 2.5, 4.1)

        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeSize(0, 1, -1, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeSize(0, 1, 0, 6.4)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeSize(0, 1, 5.4, -1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeSize(0, 1, 5.4, 0)

        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 2.5, 4.1))
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getNodeCoordinateAndSize(
            0, 1), (1.2, 3.2, 5.4, 6.4))

    def test_setNodeFillColorRGB(self):
        self.assertEqual(hex(IodineAPI.getNodeFillColorRGB(0, 1)), '0xff9650')
        self.assertEqual(IodineAPI.setNodeFillColorRGB(
            0, 1, 30, 180, 160), None)
        self.assertEqual(hex(IodineAPI.getNodeFillColorRGB(0, 1)), '0x1eb4a0')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(-1, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(3, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(1, -1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(1, 4, 30, 180, 160)
        
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, -1, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, 256, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, 30, -1, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, 30, 256, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, 30, 180, -1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorRGB(0, 1, 30, 180, 256)

        
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(hex(IodineAPI.getNodeFillColorRGB(0, 1)), '0xff9650')
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(hex(IodineAPI.getNodeFillColorRGB(0, 1)), '0x1eb4a0')

    def test_setNodeFillColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getNodeFillColorAlpha(0, 1), 1, 2)
        self.assertEqual(IodineAPI.setNodeFillColorAlpha(0, 1, 0.5), None)
        self.assertAlmostEqual(IodineAPI.getNodeFillColorAlpha(0, 1), 0.5,2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(-1, 1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(3, 1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(1, -1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(1, 4, 1)

        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(0, 1, -0.1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeFillColorAlpha(0, 1, 1.1)


        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertAlmostEqual(IodineAPI.getNodeFillColorAlpha(0, 1), 1,2)
        self.assertEqual(IodineAPI.redo(), None)
        self.assertAlmostEqual(IodineAPI.getNodeFillColorAlpha(0, 1), 0.5,2)

    def test_setNodeOutlineColorRGB(self):
        self.assertEqual(
            hex(IodineAPI.getNodeOutlineColorRGB(0, 1)), '0xff6450')
        self.assertEqual(IodineAPI.setNodeOutlineColorRGB(
            0, 1, 30, 180, 160), None)
        self.assertEqual(
            hex(IodineAPI.getNodeOutlineColorRGB(0, 1)), '0x1eb4a0')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(-1, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(3, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(1, -1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(1, 4, 30, 180, 160)

        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, -1, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, 256, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, 30, -1, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, 30, 256, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, 30, 180, -1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorRGB(0, 1, 30, 180, 256)


        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(
            hex(IodineAPI.getNodeOutlineColorRGB(0, 1)), '0xff6450')
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(
            hex(IodineAPI.getNodeOutlineColorRGB(0, 1)), '0x1eb4a0')


    def test_setNodeOutlineColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getNodeOutlineColorAlpha(0, 1), 1,2)
        self.assertEqual(IodineAPI.setNodeOutlineColorAlpha(0, 1, 0.5), None)
        self.assertAlmostEqual(IodineAPI.getNodeOutlineColorAlpha(0, 1), 0.5,2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(-1, 1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(3, 1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(1, -1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(1, 4, 1)
        
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(0, 1, -0.1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineColorAlpha(0, 1, 1.1)


        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertAlmostEqual(IodineAPI.getNodeOutlineColorAlpha(0, 1), 1, 2)
        self.assertEqual(IodineAPI.redo(), None)
        self.assertAlmostEqual(IodineAPI.getNodeOutlineColorAlpha(0, 1), 0.5, 2)


    def test_setNodeOutlineThickness(self):
        self.assertEqual(IodineAPI.getNodeOutlineThickness(0, 1), 3)
        self.assertEqual(IodineAPI.setNodeOutlineThickness(0, 1, 1), None)
        self.assertEqual(IodineAPI.getNodeOutlineThickness(0, 1), 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(-1, 1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(3, 1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(1, -1, 1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(1, 4, 1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(0, 1, 0)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setNodeOutlineThickness(0, 1, -1)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getNodeOutlineThickness(0, 1), 3)
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getNodeOutlineThickness(0, 1), 1)


class TestReactionFunc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        IodineAPI.newNetwork("network1")
        IodineAPI.addNode(0, "node1", 1.1, 2.5, 5.4, 6.4)
        IodineAPI.addNode(0, "node2", 1.2, 3.2, 2.5, 4.1)
        IodineAPI.addNode(0, "node3", 2.2, 3.1, 1.5, 4.5)
        IodineAPI.addNode(0, "node4", 7.2, 3.5, 1.6, 4.8)
        IodineAPI.CreateBiBi(0, "Rea1", "k1*A",
                             0, 1, 2, 3, 1.1, 2.2, 3.3, 4.4)
        IodineAPI.CreateBiBi(0, "Rea2", "k2*A",
                             1, 3, 0, 2, 2.1, 5.2, 8.3, 7.4)

    def tearDown(self):
        IodineAPI.clearNetworks()

    def test_createReaction(self):
        self.assertEqual(IodineAPI.createReaction(0, "Rea3"), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(
            0), ["Rea1", "Rea2", "Rea3"])
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.createReaction(0, "Rea1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.createReaction(-1, "Rea4")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.createReaction(1, "Rea4")
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0),
                         ["Rea1", "Rea2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0),
                         ["Rea1", "Rea2", "Rea3"])

    def test_getReactionIndex(self):
        self.assertEqual(IodineAPI.getReactionIndex(0, "Rea1"), 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionIndex(-1, "Rea1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionIndex(1, "Rea1")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.getReactionIndex(0, "Rea3")

    def test_deleteReaction(self):
        self.assertEqual(IodineAPI.deleteReaction(0, 0), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea2"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteReaction(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteReaction(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteReaction(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteReaction(0, 1)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0),
                         ["Rea1", "Rea2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0),
                         ["Rea2"])

    def test_clearReactions(self):
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1", "Rea2"])
        self.assertEqual(IodineAPI.clearReactions(0), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), [])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.clearReactions(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.clearReactions(1)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0),
                         ["Rea1", "Rea2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), [])

    def test_getNumberOfReactions(self):
        self.assertEqual(IodineAPI.getNumberOfReactions(0), 2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfReactions(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfReactions(1)

    def test_getReactionId(self):
        self.assertEqual(IodineAPI.getReactionId(0, 0), "Rea1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionId(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionId(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionId(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionId(0, 2)

    def test_getListOfReactionIds(self):
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1", "Rea2"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionIds(-1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionIds(1)

    def test_getReactionRateLaw(self):
        self.assertEqual(IodineAPI.getReactionRateLaw(0, 0), "k1*A")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionRateLaw(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionRateLaw(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionRateLaw(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionRateLaw(0, 2)

    def test_getReactionFillColor(self):
        self.assertEqual(
            IodineAPI.getReactionFillColor(0, 0), (255, 150, 80, 1.0))
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColor(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColor(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColor(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColor(0, 2)

    def test_getReactionFillColorRGB(self):
        self.assertEqual(
            hex(IodineAPI.getReactionFillColorRGB(0, 0)), '0xff9650')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColorRGB(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColorRGB(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColorRGB(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColorRGB(0, 2)

    def test_getReactionFillColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getReactionFillColorAlpha(0, 0),1,2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColorAlpha(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionFillColorAlpha(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColorAlpha(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionFillColorAlpha(0, 2)

    def test_getReactionLineThickness(self):
        self.assertEqual(IodineAPI.getReactionLineThickness(0, 0), 3)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionLineThickness(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionLineThickness(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionLineThickness(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionLineThickness(0, 2)


    def test_getReactionSrcNodeStoich(self):
        self.assertEqual(
            IodineAPI.getReactionSrcNodeStoich(0, 1, "node4"), 5.2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionSrcNodeStoich(-1, 0, "node1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionSrcNodeStoich(1, 0, "node1")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionSrcNodeStoich(0, -1, "node1")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionSrcNodeStoich(0, 2, "node1")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.getReactionSrcNodeStoich(0, 0, "node")



    def test_getReactionDestNodeStoich(self):
        self.assertEqual(
            IodineAPI.getReactionDestNodeStoich(0, 1, "node3"), 7.4)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionDestNodeStoich(-1, 0, "node1")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getReactionDestNodeStoich(1, 0, "node1")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionDestNodeStoich(0, -1, "node1")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getReactionDestNodeStoich(0, 2, "node1")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.getReactionDestNodeStoich(0, 0, "node")



    def test_getNumberOfSrcNodes(self):
        self.assertEqual(IodineAPI.getNumberOfSrcNodes(0, 1), 2)
        IodineAPI.addSrcNode(0, 1, 2, 3.1)
        self.assertEqual(IodineAPI.getNumberOfSrcNodes(0, 1), 3)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfSrcNodes(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfSrcNodes(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getNumberOfSrcNodes(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getNumberOfSrcNodes(0, 2)

    def test_getNumberOfDestNodes(self):
        self.assertEqual(IodineAPI.getNumberOfDestNodes(0, 1), 2)
        IodineAPI.addDestNode(0, 1, 1, 5.5)
        self.assertEqual(IodineAPI.getNumberOfDestNodes(0, 1), 3)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfDestNodes(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getNumberOfDestNodes(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getNumberOfDestNodes(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getNumberOfDestNodes(0, 2)

    def test_getListOfReactionSrcNodes(self):
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(
            0, 1), ["node2", "node4"])
        IodineAPI.addSrcNode(0, 1, 2, 3.1)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(
            0, 1), ["node2", "node3", "node4"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcNodes(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcNodes(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcNodes(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcNodes(0, 2)

    def test_getListOfReactionDestNodes(self):
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(
            0, 1), ["node1", "node3"])
        IodineAPI.addDestNode(0, 1, 1, 5.5)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(
            0, 1), ["node1", "node2", "node3"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestNodes(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestNodes(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestNodes(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestNodes(0, 2)

    def test_getListOfReactionSrcStoich(self):
        self.assertEqual(IodineAPI.getListOfReactionSrcStoich(
            0, 1), [2.1, 5.2])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcStoich(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcStoich(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcStoich(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionSrcStoich(0, 2)

    def test_getListOfReactionDestStoich(self):
        self.assertEqual(IodineAPI.getListOfReactionDestStoich(
            0, 1), [8.3, 7.4])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestStoich(-1, 0)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestStoich(1, 0)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestStoich(0, -1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.getListOfReactionDestStoich(0, 2)


class TestReactionNodeFunc(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        pass

    @classmethod
    def tearDownClass(cls):
        pass

    def setUp(self):
        IodineAPI.newNetwork("network1")
        IodineAPI.addNode(0, "node1", 1.1, 2.5, 5.4, 6.4)
        IodineAPI.addNode(0, "node2", 1.2, 3.2, 2.5, 4.1)
        IodineAPI.addNode(0, "node3", 2.2, 3.1, 1.5, 4.5)
        IodineAPI.addNode(0, "node4", 7.2, 3.5, 1.6, 4.8)
        IodineAPI.addNode(0, "node5", 6.4, 7.1, 9.9, 1.2)
        IodineAPI.addNode(0, "node6", 5.8, 7.3, 4.5, 6.2)
        IodineAPI.CreateBiBi(0, "Rea1", "k1*A",
                             0, 1, 2, 3, 1.1, 2.2, 3.3, 4.4)
        IodineAPI.CreateBiBi(0, "Rea2", "k2*A",
                             3, 1, 2, 0, 2.1, 5.2, 8.3, 7.4)

    def tearDown(self):
        IodineAPI.clearNetworks()

    def test_addSrcNode(self):
        self.assertEqual(IodineAPI.addSrcNode(0, 0, 4, 5.1), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(
            0, 0), ["node1", "node2", "node5"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addSrcNode(-1, 0, 3, 1.1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addSrcNode(1, 0, 3, 1.1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.addSrcNode(0, -1, 3, 1.1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.addSrcNode(0, 2, 3, 1.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.addSrcNode(0, 0, -1, 1.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.addSrcNode(0, 0, 6, 1.1)
        with self.assertRaises(IodineAPI.StoichError):
            IodineAPI.addSrcNode(0, 0, 3, -1)
        with self.assertRaises(IodineAPI.StoichError):
            IodineAPI.addSrcNode(0, 0, 3, 0)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 0),
                         ["node1", "node2"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 0),
                         ["node1", "node2", "node5"])

    def test_addDestNode(self):
        self.assertEqual(IodineAPI.addDestNode(0, 0, 4, 5.1), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(
            0, 0), ["node3", "node4", "node5"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addDestNode(-1, 0, 3, 1.1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.addDestNode(1, 0, 3, 1.1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.addDestNode(0, -1, 3, 1.1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.addDestNode(0, 2, 3, 1.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.addDestNode(0, 0, -1, 1.1)
        with self.assertRaises(IodineAPI.NodeIndexOutOfRangeError):
            IodineAPI.addDestNode(0, 0, 6, 1.1)
        with self.assertRaises(IodineAPI.StoichError):
            IodineAPI.addDestNode(0, 0, 3, -1.1)
        with self.assertRaises(IodineAPI.StoichError):
            IodineAPI.addDestNode(0, 0, 3, 0.0)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(0, 0),
                         ["node3", "node4"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(0, 0),
                         ["node3", "node4", "node5"])

    def test_deleteSrcNode(self):
        IodineAPI.addSrcNode(0, 1, 4, 5.5)
        IodineAPI.addSrcNode(0, 1, 2, 5.6)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 1),
                         ["node2", "node3", "node4", "node5"])
        self.assertEqual(IodineAPI.deleteSrcNode(0, 1, "node2"), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 1),
                         ["node3", "node4", "node5"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteSrcNode(-1, 1, "node4")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteSrcNode(1, 1, "node4")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteSrcNode(0, -1, "node4")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteSrcNode(0, 2, "node4")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.deleteSrcNode(0, 1, "node2")
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 1),
                         ["node2", "node3", "node4", "node5"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionSrcNodes(0, 1),
                         ["node3", "node4", "node5"])

                         

    def test_deleteDestNode(self):
        IodineAPI.addDestNode(0, 1, 5, 5.3)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(
            0, 1), ["node1", "node3", "node6"])
        self.assertEqual(IodineAPI.deleteDestNode(0, 1, "node1"), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(
            0, 1), ["node3", "node6"])
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteDestNode(-1, 1, "node4")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.deleteDestNode(1, 1, "node4")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteDestNode(0, -1, "node4")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.deleteDestNode(0, 2, "node4")
        with self.assertRaises(IodineAPI.IdNotFoundError):
            IodineAPI.deleteDestNode(0, 1, "node5")
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(0, 1),
                         ["node1", "node3", "node6"])
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getListOfReactionDestNodes(0, 1),
                         ["node3", "node6"])

                         
    def test_setRateLaw(self):
        self.assertEqual(IodineAPI.getReactionRateLaw(
            0, 1), "k2*A")
        self.assertEqual(IodineAPI.setRateLaw(
            0, 1,  "ABC"), None)
        self.assertEqual(IodineAPI.getReactionRateLaw(
            0, 1), "ABC")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setRateLaw(-1, 1, "ABC")
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setRateLaw(1, 1, "ABC")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setRateLaw(0, -1, "ABC")
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setRateLaw(0, 2, "ABC")
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getReactionRateLaw(0, 1), "k2*A")
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getReactionRateLaw(0, 1), "ABC")

    def test_setReactionFillColorRGB(self):
        self.assertEqual(
            hex(IodineAPI.getReactionFillColorRGB(0, 1)), '0xff9650')
        self.assertEqual(IodineAPI.setReactionFillColorRGB(
            0, 1, 30, 180, 160), None)
        self.assertEqual(
            hex(IodineAPI.getReactionFillColorRGB(0, 1)), '0x1eb4a0')
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(-1, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(3, 1, 30, 180, 160)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, -1, 30, 180, 160)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 4, 30, 180, 160)
        
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, -1, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, 256, 180, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, 30, -1, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, 30, 256, 160)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, 30, 180, -1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorRGB(0, 1, 30, 180, 256)


        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(
            hex(IodineAPI.getReactionFillColorRGB(0, 1)), '0xff9650')
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(
            hex(IodineAPI.getReactionFillColorRGB(0, 1)), '0x1eb4a0')

    def test_setReactionFillColorAlpha(self):
        self.assertAlmostEqual(IodineAPI.getReactionFillColorAlpha(0, 1), 1, 2)
        self.assertEqual(IodineAPI.setReactionFillColorAlpha(
            0, 1, 0.5), None)
        self.assertAlmostEqual(IodineAPI.getReactionFillColorAlpha(0, 1), 0.5, 2)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(-1, 1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(3, 1, 1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(0, -1, 1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(0, 4, 1)

        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(0, 1, -0.1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionFillColorAlpha(0, 1, 1.1)


        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertAlmostEqual(IodineAPI.getReactionFillColorAlpha(0, 1), 1, 2)
        self.assertEqual(IodineAPI.redo(), None)
        self.assertAlmostEqual(IodineAPI.getReactionFillColorAlpha(0, 1), 0.5, 2)

    def test_setReactionLineThickness(self):
        self.assertEqual(IodineAPI.getReactionLineThickness(0, 1), 3)
        self.assertEqual(IodineAPI.setReactionLineThickness(0, 1, 1), None)
        self.assertEqual(IodineAPI.getReactionLineThickness(0, 1), 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionLineThickness(-1, 1, 1)
        with self.assertRaises(IodineAPI.NetIndexOutOfRangeError):
            IodineAPI.setReactionLineThickness(3, 1, 1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionLineThickness(0, -1, 1)
        with self.assertRaises(IodineAPI.ReactionIndexOutOfRangeError):
            IodineAPI.setReactionLineThickness(0, 4, 1)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionLineThickness(0, 1, 0)
        with self.assertRaises(IodineAPI.VariableOutOfRangeError):
            IodineAPI.setReactionLineThickness(0, 1, -1)
        with self.assertRaises(IodineAPI.StackEmptyError):
            IodineAPI.redo()
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getReactionLineThickness(0, 1), 3)
        self.assertEqual(IodineAPI.redo(), None)
        self.assertEqual(IodineAPI.getReactionLineThickness(0, 1), 1)


    def test_saveNetworkAsJSON_readNetworkFromJSON(self):
        self.assertEqual(IodineAPI.saveNetworkAsJSON(0, "../JSON_files/testfile.json"), None)
        self.assertEqual(IodineAPI.readNetworkFromJSON(
            "../JSON_files/testfile1.json"), None)
        with self.assertRaises(IodineAPI.FileError):
            IodineAPI.readNetworkFromJSON("testfdfjsd.json")
        with self.assertRaises(IodineAPI.IdRepeatError):
            IodineAPI.readNetworkFromJSON("../JSON_files/testfile1.json")

    def test_startGroup_endGroup(self):
        self.assertEqual(IodineAPI.getListOfReactionIds(0),["Rea1", "Rea2"])
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1"])
        self.assertEqual(IodineAPI.startGroup(),None)
        self.assertEqual(IodineAPI.createReaction(0, "rea2"),None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1", "rea2"])
        self.assertEqual(IodineAPI.addSrcNode(0, 0, 4, 5.1), None)
        self.assertEqual(IodineAPI.endGroup(), None)
        self.assertEqual(IodineAPI.undo(), None)
        self.assertEqual(IodineAPI.getListOfReactionIds(0), ["Rea1"])




if __name__ == '__main__':
    unittest.main()


