#include "objects2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* objects2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objects2D::CreateSquareInOrigin(
    const std::string& name,
    float length,
    glm::vec3 color,
    bool fill,
    float z)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(- length / 2, - length / 2, z), color),
        VertexFormat(glm::vec3(length / 2, - length / 2, z), color),
        VertexFormat(glm::vec3(length / 2, length / 2, z), color),
        VertexFormat(glm::vec3(- length / 2, length / 2, z), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objects2D::CreateSquare1(
    const std::string& name,
    float length,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(length, 0, 0), color),
        VertexFormat(glm::vec3(length, length, 0), color),
        VertexFormat(glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* objects2D::CreateHexagon(
    const std::string& name,
    glm::vec3 color, 
    float z)
{
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-0.5f, -0.86f, z), color),
        VertexFormat(glm::vec3(0.5f, -0.86f, z), color),
        VertexFormat(glm::vec3(1, 0, z), color),
        VertexFormat(glm::vec3(0.5f, 0.86f, z), color),
        VertexFormat(glm::vec3(-0.5f, 0.86f, z), color),
        VertexFormat(glm::vec3(-1, 0, z), color)
    };

    
    std::vector<unsigned int> indices =
    {
        0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5
    };
    

    Mesh* hexagon = new Mesh(name);
    hexagon->SetDrawMode(GL_TRIANGLE_FAN);
    hexagon->InitFromData(vertices, indices);
	return hexagon;

	
}


Mesh* objects2D::CreateStar(
    const std::string& name,
    glm::vec3 color,
    float z)
{
	std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, z), color),
		VertexFormat(glm::vec3(-0.58f, -0.8f, z), color),
		VertexFormat(glm::vec3(0.58f, -0.8f, z), color),
		VertexFormat(glm::vec3(0.95f, 0.3f, z), color),
		VertexFormat(glm::vec3(0, 1, z), color),
		VertexFormat(glm::vec3(-0.95f, 0.3f, z), color)
	};

    std::vector<unsigned int> indices =
    {
        0, 1, 3,
        0, 2, 4,
        0, 3, 5,
        0, 4, 1,
        0, 5, 2
    };

    Mesh* star = new Mesh(name);
    star->SetDrawMode(GL_TRIANGLES);
    star->InitFromData(vertices, indices);
    return star;

}