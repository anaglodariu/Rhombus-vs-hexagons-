#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Implement the translation matrix
        glm::mat3 translateM = glm::mat3(1, 0, 0, 
                                         0, 1, 0, 
                                         translateX, translateY, 1);
        //return glm::mat3(1);
        return translateM;

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // TODO(student): Implement the scaling matrix
        glm::mat3 scaleM = glm::mat3(scaleX, 0, 0, 
            						0, scaleY, 0, 
            						0, 0, 1);
        return scaleM;

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        // TODO(student): Implement the rotation matrix
        glm::mat3 rotateM = glm::mat3(cos(radians), sin(radians), 0, 
            						 -sin(radians), cos(radians), 0, 
            						 0, 0, 1);
        return rotateM;

    }
}   // namespace transform2D

