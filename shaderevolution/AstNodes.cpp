#include "AstNodes.h"
#include <random>


ShaderGenotype::ShaderGenotype(std::unique_ptr<GenotypeNode> rt):
    root(std::move(rt)),
    currentGeneration(0)
{
}

std::string GenotypeNode::stringify(bool showAnnotations){
    if (showAnnotations){
        return ("<b><i><font color='#ff0000'>["
                + std::to_string(generation)
                + "]</font></i></b>"
                + stringifyDispatch(true));
    }
    return stringifyDispatch(false);
}


//******************LEAF NODES******************
std::string XPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.x)";
}

std::string YPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.y)";
}

std::string ZPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.z)";
}

std::string TimeNode::stringifyDispatch(bool a){
    return "vec3(timevar)";
}


RandomVecNode::RandomVecNode(int seed){
    m_seed = seed;
}

std::string RandomVecNode::stringifyDispatch(bool a){
    std::minstd_rand rng(m_seed);
    std::uniform_real_distribution<> dist(min,max);

    float x = dist(rng);
    float y = dist(rng);
    float z = dist(rng);
    return "vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}


//******************OPERATION NODES******************

std::string AdditionNode::stringifyDispatch(bool a){
    return children[0]->stringify(a) + " + " + children[1]->stringify(a);
}

std::string SubtractionNode::stringifyDispatch(bool a){
    return children[0]->stringify(a) + " - " + children[1]->stringify(a);
}

std::string MultiplicationNode::stringifyDispatch(bool a){
    return "(" + children[0]->stringify(a) + "* " + children[1]->stringify(a) + ")";
}

std::string DivisionNode::stringifyDispatch(bool a){
    return "(" + children[0]->stringify(a) + " / " + children[1]->stringify(a) + ")";
}

std::string AbsoluteValueNode::stringifyDispatch(bool a){
    return "abs(" + children[0]->stringify(a) + ")";
}

std::string ModulusNode::stringifyDispatch(bool a){
    return "mod(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string CrossProductNode::stringifyDispatch(bool a){
    return "my_cross(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string SinNode::stringifyDispatch(bool a){
    return "sin(" + children[0]->stringify(a) + ")";
}

std::string CosNode::stringifyDispatch(bool a){
    return "cos(" + children[0]->stringify(a) + ")";
}

std::string AtanNode::stringifyDispatch(bool a){
    return "atan(" + children[0]->stringify(a) + ")";
}

std::string MinNode::stringifyDispatch(bool a){
    return "min(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string MaxNode::stringifyDispatch(bool a){
    return "max(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string PerlinNoiseNode::stringifyDispatch(bool a){
    return "perlinNoiseVec3(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string XTransplantNode::stringifyDispatch(bool a){
    return "transplantX(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string YTransplantNode::stringifyDispatch(bool a){
    return "transplantY(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string ZTransplantNode::stringifyDispatch(bool a){
    return "transplantZ(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::string AverageNode::stringifyDispatch(bool a){
    return "average(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}
