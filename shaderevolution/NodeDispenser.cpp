#include "NodeDispenser.h"

std::minstd_rand NodeDispenser::rng(std::time(0));

int NodeDispenser::numberOfLeavesPossible = 5;
std::uniform_int_distribution<> NodeDispenser::leafDist(1, NodeDispenser::numberOfLeavesPossible);

int NodeDispenser::numberOfOperatorsPossible = 2;
std::uniform_int_distribution<> NodeDispenser::operatorDist(1, NodeDispenser::numberOfOperatorsPossible);

std::unique_ptr<GenotypeNode> NodeDispenser::getLeafNode(){
    int choice = NodeDispenser::leafDist(NodeDispenser::rng);

    if (choice == 1) return std::unique_ptr<XPositionNode>(new XPositionNode());
    if (choice == 2) return std::unique_ptr<ZPositionNode>(new ZPositionNode());
    if (choice == 3) return std::unique_ptr<YPositionNode>(new YPositionNode());
    if (choice == 4) return std::unique_ptr<TimeNode>(new TimeNode());
    if (choice == 5) return std::unique_ptr<RandomVecNode>(new RandomVecNode(rng()));
    return nullptr;
}


std::unique_ptr<GenotypeNode> NodeDispenser::getOperationNode(){
    int choice = NodeDispenser::operatorDist(NodeDispenser::rng);

    if (choice == 1) return std::unique_ptr<AdditionNode>(new AdditionNode());
    if (choice == 2) return std::unique_ptr<SubtractionNode>(new SubtractionNode());
    return nullptr;
}
