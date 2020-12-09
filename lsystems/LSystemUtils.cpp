#include "LSystemUtils.h"

namespace LSystemUtils {

std::string getStart(int type) {
    switch (type) {
    case 0: {
        return natur_start;
        break;
    }
    case 1: {
        return seaweed_start;
        break;
    }
    case 2: {
        return maple_start;
        break;
    }
    case 3: {
        return bad_start;
        break;
    }
    case 4: {
        return bush_start;
        break;
    }
    case 5: {
        return simple_start;
        break;
    }
    default: {
        return natur_start;
    }
    }


}

std::map<std::string, std::string> getMap(int type) {

    switch (type) {
    case 0: {
        return natur_map;
        break;
    }
    case 1: {
        return seaweed_map;
        break;
    }
    case 2: {
        return maple_map;
        break;
    }
    case 3: {
        return bad_map;
        break;
    }
    case 4: {
        return bush_map;
        break;
    }
    case 5: {
        return simple_map;
        break;
    }
    default: {
        return natur_map;
    }
    }

}

float getAngle(int type) {
    switch (type) {
    case 0: {
        return natur_angle;
        break;
    }
    case 1: {
        return seaweed_angle;
        break;
    }
    case 2: {
        return maple_angle;
        break;
    }
    case 3: {
        return bad_angle;
        break;
    }
    case 4: {
        return bush_angle;
        break;
    }
    case 5: {
        return simple_angle;
        break;
    }
    default: {
        return natur_angle;
    }
    }

}



}
