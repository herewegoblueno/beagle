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

    std::string stringify(bool showGenAnnotations = false); //Making this an abstract class
    virtual std::string stringifyDispatch(bool showAnnotations) = 0;

    int numberOfChildrenNeeded = 0;
    std::vector<std::unique_ptr<GenotypeNode>> children;
    int generation = 0; //The generation of the AST that this node came into existence
};

class ShaderGenotype{
public:
    ShaderGenotype(std::unique_ptr<GenotypeNode> rt);
    std::unique_ptr<GenotypeNode> root;
    int currentGeneration;
};


//******************LEAF NODES******************

//Leaf nodes will inheret from this
class XPositionNode : public GenotypeNode {
public:
    std::string stringifyDispatch(bool a) override;
};

class YPositionNode : public GenotypeNode {
public:
    std::string stringifyDispatch(bool a) override;
};

class ZPositionNode : public GenotypeNode {
public:
    std::string stringifyDispatch(bool a) override;
};

class TimeNode : public GenotypeNode {
public:
    std::string stringifyDispatch(bool a) override;
};

class RandomVecNode : public GenotypeNode {
public:
    RandomVecNode(int seed);
    std::string stringifyDispatch(bool a) override;
    int m_seed;

private:
    float min = -0.8;
    float max = 1.7;
};



//******************OPERATION NODES******************

class AdditionNode : public GenotypeNode {
public:
    AdditionNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class SubtractionNode : public GenotypeNode {
public:
    SubtractionNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class DivisionNode : public GenotypeNode {
public:
    DivisionNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class MultiplicationNode : public GenotypeNode {
public:
    MultiplicationNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class ModulusNode : public GenotypeNode {
public:
    ModulusNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class AbsoluteValueNode : public GenotypeNode {
public:
    AbsoluteValueNode() : GenotypeNode(1){}
    std::string stringifyDispatch(bool a) override;
};

class CrossProductNode : public GenotypeNode {
public:
    CrossProductNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class SinNode : public GenotypeNode {
public:
    SinNode() : GenotypeNode(1){}
    std::string stringifyDispatch(bool a) override;
};

class CosNode : public GenotypeNode {
public:
    CosNode() : GenotypeNode(1){}
    std::string stringifyDispatch(bool a) override;
};

class AtanNode : public GenotypeNode {
public:
    AtanNode() : GenotypeNode(1){}
    std::string stringifyDispatch(bool a) override;
};

class MaxNode : public GenotypeNode {
public:
    MaxNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class MinNode : public GenotypeNode {
public:
    MinNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class PerlinNoiseNode : public GenotypeNode {
public:
    PerlinNoiseNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class XTransplantNode : public GenotypeNode {
public:
    XTransplantNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class YTransplantNode : public GenotypeNode {
public:
    YTransplantNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class ZTransplantNode : public GenotypeNode {
public:
    ZTransplantNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

class AverageNode : public GenotypeNode {
public:
    AverageNode() : GenotypeNode(2){}
    std::string stringifyDispatch(bool a) override;
};

#endif // ASTNODES_H
