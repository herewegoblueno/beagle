#ifndef ASTNODES_H
#define ASTNODES_H

#include <string>
#include <vector>

//The base class that all genotype nodes will inherit from
class GenotypeNode {
public:
    GenotypeNode() {}; //Number of needed children will be 0 (for leaves)
    GenotypeNode(int no_of_children): numberOfChildrenNeeded(no_of_children) {}; //For operator nodes
    virtual ~GenotypeNode() {};

    virtual std::string stringify() = 0; //Making this an abstract class
    int numberOfChildrenNeeded = 0;
    std::vector<std::unique_ptr<GenotypeNode>> children;
};


//******************LEAF NODES******************

//Leaf nodes will inheret from this
class XPositionNode : public GenotypeNode {
public:
    std::string stringify() override;
};

class YPositionNode : public GenotypeNode {
public:
    std::string stringify() override;
};

class ZPositionNode : public GenotypeNode {
public:
    std::string stringify() override;
};

class TimeNode : public GenotypeNode {
public:
    std::string stringify() override;
};

class RandomVecNode : public GenotypeNode {
public:
    RandomVecNode(int seed);
    std::string stringify() override;
    int m_seed;

private:
    float min = 0;
    float max = 1.7;
};



//******************OPERATION NODES******************

class AdditionNode : public GenotypeNode {
public:
    AdditionNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class SubtractionNode : public GenotypeNode {
public:
    SubtractionNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class DivisionNode : public GenotypeNode {
public:
    DivisionNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class MultiplicationNode : public GenotypeNode {
public:
    MultiplicationNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class ModulusNode : public GenotypeNode {
public:
    ModulusNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class AbsoluteValueNode : public GenotypeNode {
public:
    AbsoluteValueNode() : GenotypeNode(1){}
    std::string stringify() override;
};

class CrossProductNode : public GenotypeNode {
public:
    CrossProductNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class SinNode : public GenotypeNode {
public:
    SinNode() : GenotypeNode(1){}
    std::string stringify() override;
};

class CosNode : public GenotypeNode {
public:
    CosNode() : GenotypeNode(1){}
    std::string stringify() override;
};

class AtanNode : public GenotypeNode {
public:
    AtanNode() : GenotypeNode(1){}
    std::string stringify() override;
};

class MaxNode : public GenotypeNode {
public:
    MaxNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class MinNode : public GenotypeNode {
public:
    MinNode() : GenotypeNode(2){}
    std::string stringify() override;
};

class PerlinNoiseNode : public GenotypeNode {
public:
    PerlinNoiseNode() : GenotypeNode(2){}
    std::string stringify() override;
};

#endif // ASTNODES_H
