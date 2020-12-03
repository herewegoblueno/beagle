#include "NodeDispenser.h"

std::minstd_rand NodeDispenser::rng(std::time(0));

int NodeDispenser::numberOfLeavesPossible = 5;
std::uniform_int_distribution<> NodeDispenser::leafDist(1, NodeDispenser::numberOfLeavesPossible);

int NodeDispenser::numberOfOperatorsPossible = 16;
std::uniform_int_distribution<> NodeDispenser::operatorDist(1, NodeDispenser::numberOfOperatorsPossible);

std::unique_ptr<GenotypeNode> NodeDispenser::getLeafNode(){
    int choice = NodeDispenser::leafDist(NodeDispenser::rng);

    if (choice == 1) return std::make_unique<XPositionNode>();
    if (choice == 2) return std::make_unique<ZPositionNode>();
    if (choice == 3) return std::make_unique<YPositionNode>();
    if (choice == 4) return std::make_unique<TimeNode>();
    if (choice == 5) return std::make_unique<RandomVecNode>(rng());
    return nullptr;
}


std::unique_ptr<GenotypeNode> NodeDispenser::getOperationNode(){
    int choice = NodeDispenser::operatorDist(NodeDispenser::rng);

    if (choice == 1) return std::make_unique<AdditionNode>();
    if (choice == 2) return std::make_unique<SubtractionNode>();
    if (choice == 3) return std::make_unique<CrossProductNode>();
    if (choice == 4) return std::make_unique<MultiplicationNode>();
    if (choice == 5) return std::make_unique<DivisionNode>();
    if (choice == 6) return std::make_unique<AbsoluteValueNode>();
//    if (choice == 7) return std::make_unique<ModulusNode>();
    if (choice == 7) return std::make_unique<SinNode>();
    if (choice == 8) return std::make_unique<CosNode>();
    if (choice == 9) return std::make_unique<AtanNode>();
    if (choice == 10) return std::make_unique<MinNode>();
    if (choice == 11) return std::make_unique<MaxNode>();
    if (choice == 12) return std::make_unique<PerlinNoiseNode>();
    if (choice == 13) return std::make_unique<XTransplantNode>();
    if (choice == 14) return std::make_unique<YTransplantNode>();
    if (choice == 15) return std::make_unique<ZTransplantNode>();
    if (choice == 16) return std::make_unique<AverageNode>();

    return nullptr;
}
