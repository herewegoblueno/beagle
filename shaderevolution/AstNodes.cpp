#include "AstNodes.h"
#include <random>


//******************LEAF NODES******************
std::string XPositionNode::stringify(){
    return "vec3(pos.x)";
}

std::string YPositionNode::stringify(){
    return "vec3(pos.y)";
}

std::string ZPositionNode::stringify(){
    return "vec3(pos.z)";
}

std::string TimeNode::stringify(){
    return "vec3(timevar)";
}


RandomVecNode::RandomVecNode(int seed){
    m_seed = seed;
}

std::string RandomVecNode::stringify(){
    std::minstd_rand rng(m_seed);
    std::uniform_real_distribution<> dist(min,max);

    float x = dist(rng);
    float y = dist(rng);
    float z = dist(rng);
    return "vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}


//******************OPERATION NODES******************

std::string AdditionNode::stringify(){
    return children[0]->stringify() + " + " + children[1]->stringify();
}

std::string SubtractionNode::stringify(){
    return children[0]->stringify() + " - " + children[1]->stringify();
}

std::string MultiplicationNode::stringify(){
    return "(" + children[0]->stringify() + "* " + children[1]->stringify() + ")";
}

std::string DivisionNode::stringify(){
    return "(" + children[0]->stringify() + " / " + children[1]->stringify() + ")";
}

std::string AbsoluteValueNode::stringify(){
    return "abs(" + children[0]->stringify() + ")";
}

std::string ModulusNode::stringify(){
    return "mod(" + children[0]->stringify() + ",  " + children[1]->stringify() + ")";
}

std::string CrossProductNode::stringify(){
    return "my_cross(" + children[0]->stringify() + ",  " + children[1]->stringify() + ")";
}

std::string SinNode::stringify(){
    return "sin(" + children[0]->stringify() + ")";
}

std::string CosNode::stringify(){
    return "cos(" + children[0]->stringify() + ")";
}

std::string AtanNode::stringify(){
    return "atan(" + children[0]->stringify() + ")";
}

std::string MinNode::stringify(){
    return "min(" + children[0]->stringify() + ",  " + children[1]->stringify() + ")";
}

std::string MaxNode::stringify(){
    return "max(" + children[0]->stringify() + ",  " + children[1]->stringify() + ")";
}

std::string PerlinNoiseNode::stringify(){
    return "perlinNoiseVec3(" + children[0]->stringify() + ",  " + children[1]->stringify() + ")";
}
