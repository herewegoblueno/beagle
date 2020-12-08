#ifndef LSYSTEMUTILS_H
#define LSYSTEMUTILS_H

#include <map>
#include <string>
#include <math.h>

namespace LSystemUtils {

enum LSystemType {
    SEAWEED, MAPLE
};

const std::string seaweed_start = "F";
const std::map<std::string, std::string> seaweed_map {
    {std::string("F"), std::string("FF+[+F-F-F]-[-F+F+F]")}
};
const float seaweed_angle = M_PI/6.f;

const std::string maple_start = "X";
const std::map<std::string, std::string> maple_map {
    {std::string("X"), std::string("F[+X][-X]FX")},
    {std::string("F"), std::string("FF")}
};
const float maple_angle = M_PI/7.f;

const std::string natur_start = "X";
const std::map<std::string, std::string> natur_map {
    {std::string("X"), std::string("F-[[X]+X]+F[+FX]-X")},
    {std::string("F"), std::string("FF")}
};
const float natur_angle = M_PI/8.f;

}

#endif // LSYSTEMUTILS_H
