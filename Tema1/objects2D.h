#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

    Mesh* CreateSquareInOrigin(const std::string& name, float length, glm::vec3 color, bool fill, float z = 0);


    Mesh* CreateSquare1(const std::string& name, float length, glm::vec3 color, bool fill);

    // Create hexagon with color and z coordinate
    Mesh* CreateHexagon(const std::string &name, glm::vec3 color, float z);

    // create a star
    Mesh* CreateStar(const std::string& name, glm::vec3 color, float z = 5);
}

