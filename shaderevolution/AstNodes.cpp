#include "AstNodes.h"
#include <random>
#include <vector>
#include <sstream>
#include <iomanip>


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

bool GenotypeNode::containsClassification(GenotypeNodeClassification c){
    std::vector<GenotypeNodeClassification> v = getClassifications();
    return std::find (v.begin(), v.end(), c) != v.end();
}

std::vector<GenotypeNodeClassification> GenotypeNode::getClassifications(){
    return {};
}

//Little helper funciton to print nicer shader sources...
//https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros
std::string float_to_string(float f){
    std::ostringstream oss;
    oss << std::setprecision(8) << std::noshowpoint << f;
    return oss.str();
}



//******************LEAF NODES******************
std::string XPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.x+ " + float_to_string(offsetX)
            + ", pos.x+" + float_to_string(offsetY)
            + ", pos.x+" + float_to_string(offsetZ) + ")";
}

std::vector<GenotypeNodeClassification> XPositionNode::getClassifications(){
    return {LEAF};
}
//***

std::string YPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.y+" + float_to_string(offsetX)
            + ", pos.y+" + float_to_string(offsetY)
            + ", pos.y+" + float_to_string(offsetZ) + ")";
}

std::vector<GenotypeNodeClassification> YPositionNode::getClassifications(){
    return {LEAF};
}

//***

std::string ZPositionNode::stringifyDispatch(bool a){
    return "vec3(pos.z+" + float_to_string(offsetX)
            + ", pos.z+" + float_to_string(offsetY)
            + ", pos.z+" + float_to_string(offsetZ) + ")";
}

std::vector<GenotypeNodeClassification> ZPositionNode::getClassifications(){
    return {LEAF};
}

//***

std::string TimeNode::stringifyDispatch(bool a){
    return "vec3(timevar+" + float_to_string(offsetX)
            + ", timevar+" + float_to_string(offsetY)
            + ", timevar+" + float_to_string(offsetZ) + ")";
}

std::vector<GenotypeNodeClassification> TimeNode::getClassifications(){
    return {LEAF, TIME_BOUND};
}

//***


RandomVecNode::RandomVecNode(int seed):
    offsetX(0), offsetY(0), offsetZ(0)
{
    m_seed = seed;
}

std::string RandomVecNode::stringifyDispatch(bool a){
    std::minstd_rand rng(m_seed);
    std::uniform_real_distribution<> dist(min,max);

    float x = dist(rng);
    float y = dist(rng);
    float z = dist(rng);

    return "vec3(" + float_to_string(x) + "+" + float_to_string(offsetX)
            + "," + float_to_string(y) + "+" +  float_to_string(offsetY)
            + "," + float_to_string(z) + "+" +  float_to_string(offsetZ) + ")";
}

std::vector<GenotypeNodeClassification> RandomVecNode::getClassifications(){
    return {LEAF};
}

//***


//******************OPERATION NODES******************

std::string AdditionNode::stringifyDispatch(bool a){
    return children[0]->stringify(a) + " + " + children[1]->stringify(a);
}

std::vector<GenotypeNodeClassification> AdditionNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string SubtractionNode::stringifyDispatch(bool a){
    return children[0]->stringify(a) + " - " + children[1]->stringify(a);
}

std::vector<GenotypeNodeClassification> SubtractionNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string MultiplicationNode::stringifyDispatch(bool a){
    return "(" + children[0]->stringify(a) + "* " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> MultiplicationNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string DivisionNode::stringifyDispatch(bool a){
    return "(" + children[0]->stringify(a) + " / " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> DivisionNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string AbsoluteValueNode::stringifyDispatch(bool a){
    return "abs(" + children[0]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> AbsoluteValueNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string ModulusNode::stringifyDispatch(bool a){
    return "mod(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> ModulusNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string CrossProductNode::stringifyDispatch(bool a){
    return "my_cross(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> CrossProductNode::getClassifications(){
    return {BINARY_OPERATION};
}
//***

std::string SinNode::stringifyDispatch(bool a){
    return "sin(" + children[0]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> SinNode::getClassifications(){
    return {TRIGONOMETRIC, BINARY_OPERATION};
}
//***

std::string CosNode::stringifyDispatch(bool a){
    return "cos(" + children[0]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> CosNode::getClassifications(){
    return {TRIGONOMETRIC, BINARY_OPERATION};
}
//***

std::string AtanNode::stringifyDispatch(bool a){
    return "atan(" + children[0]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> AtanNode::getClassifications(){
    return {TRIGONOMETRIC, UNARY_OPERATION};
}
//***

std::string MinNode::stringifyDispatch(bool a){
    return "min(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> MinNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string MaxNode::stringifyDispatch(bool a){
    return "max(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> MaxNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***

std::string PerlinNoiseNode::stringifyDispatch(bool a){
    return "perlinNoiseVec3(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> PerlinNoiseNode::getClassifications(){
    return {NOISE, BINARY_OPERATION};
}
//***

std::string XTransplantNode::stringifyDispatch(bool a){
    return "transplantX(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> XTransplantNode::getClassifications(){
    return {BINARY_OPERATION};
}
//***

std::string YTransplantNode::stringifyDispatch(bool a){
    return "transplantY(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> YTransplantNode::getClassifications(){
    return {BINARY_OPERATION};
}
//***

std::string ZTransplantNode::stringifyDispatch(bool a){
    return "transplantZ(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> ZTransplantNode::getClassifications(){
    return {BINARY_OPERATION};
}
//***

std::string AverageNode::stringifyDispatch(bool a){
    return "average(" + children[0]->stringify(a) + ",  " + children[1]->stringify(a) + ")";
}

std::vector<GenotypeNodeClassification> AverageNode::getClassifications(){
    return {ARITHMETIC, BINARY_OPERATION};
}
//***
