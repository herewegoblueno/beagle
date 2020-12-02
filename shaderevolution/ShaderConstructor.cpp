#include "ShaderConstructor.h"

std::string ShaderConstructor::beginning = R"(
    #version 400 core

   in vec3 color;
   in vec3 pos; //(object space)
   in float timevar;

   out vec4 fragColor;

   void main(){
       //Default value of fragColor
       vec3 evolvedval = )";

std::string ShaderConstructor::end;

std::string ShaderConstructor::genShader(std::string input){
    return ShaderConstructor::beginning +
            input +
            "; \n fragColor = vec4(evolvedval, 1); \n }";
}


