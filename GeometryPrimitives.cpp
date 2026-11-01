#include "GeometryPrimitives.h"

#include <utility>

namespace
{
    // Додає один трикутник. Нормаль рахується через векторний добуток,
    // а порядок вершин автоматично перевертається, якщо нормаль дивиться всередину фігури.
    void addTriangle(std::vector<Vertex>& out,
                     glm::vec3 a, glm::vec3 b, glm::vec3 c,
                     const glm::vec3& color, const glm::vec3& shapeCenter)
    {
        glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        const glm::vec3 faceCenter = (a + b + c) / 3.0f;

        if (glm::dot(normal, faceCenter - shapeCenter) < 0.0f)
        {
            std::swap(b, c);
            normal = -normal;
        }

        out.push_back({a, normal, color});
        out.push_back({b, normal, color});
        out.push_back({c, normal, color});
    }
}

namespace GeometryPrimitives
{
    std::vector<Vertex> createCubeVertices()
    {
        std::vector<Vertex> cubeVertices;

        const glm::vec3 positions[] = {
            {-0.5f, -0.5f, -0.5f}, // 0
            { 0.5f, -0.5f, -0.5f}, // 1
            { 0.5f,  0.5f, -0.5f}, // 2
            {-0.5f,  0.5f, -0.5f}, // 3
            {-0.5f, -0.5f,  0.5f}, // 4
            { 0.5f, -0.5f,  0.5f}, // 5
            { 0.5f,  0.5f,  0.5f}, // 6
            {-0.5f,  0.5f,  0.5f}  // 7
        };

        const glm::vec3 normals[] = {
            { 0.0f,  0.0f, -1.0f}, // Front
            { 0.0f,  0.0f,  1.0f}, // Back
            {-1.0f,  0.0f,  0.0f}, // Left
            { 1.0f,  0.0f,  0.0f}, // Right
            { 0.0f, -1.0f,  0.0f}, // Bottom
            { 0.0f,  1.0f,  0.0f}  // Top
        };

        const glm::vec3 colors[] = {
            {1.0f, 0.0f, 0.0f}, // Red
            {0.0f, 1.0f, 0.0f}, // Green
            {0.0f, 0.0f, 1.0f}, // Blue
            {1.0f, 1.0f, 0.0f}, // Yellow
            {1.0f, 0.0f, 1.0f}, // Magenta
            {0.0f, 1.0f, 1.0f}  // Cyan
        };

        const unsigned int indices[] = {
            0, 1, 2, 2, 3, 0, // Front
            4, 5, 6, 6, 7, 4, // Back
            0, 3, 7, 7, 4, 0, // Left
            1, 5, 6, 6, 2, 1, // Right
            0, 1, 5, 5, 4, 0, // Bottom
            3, 2, 6, 6, 7, 3  // Top
        };

        cubeVertices.reserve(36);
        for (int i = 0; i < 36; i++)
        {
            const unsigned int index = indices[i];
            const int face = i / 6;

            Vertex vertex;
            vertex.position = positions[index];
            vertex.normal   = normals[face];
            vertex.color    = colors[face];
            cubeVertices.push_back(vertex);
        }

        return cubeVertices;
    }

    // Чотирикутна піраміда: квадратна основа (2 трикутники) + 4 бічні грані = 6 трикутників, 18 вершин
    std::vector<Vertex> createPyramidVertices()
    {
        std::vector<Vertex> pyramidVertices;
        pyramidVertices.reserve(18);

        const glm::vec3 base[4] = {
            {-0.5f, -0.5f, -0.5f},
            { 0.5f, -0.5f, -0.5f},
            { 0.5f, -0.5f,  0.5f},
            {-0.5f, -0.5f,  0.5f}
        };
        const glm::vec3 apex{0.0f, 0.5f, 0.0f};
        const glm::vec3 center{0.0f, -0.25f, 0.0f}; // точка всередині піраміди

        const glm::vec3 baseColor{1.0f, 0.0f, 1.0f}; // Magenta
        const glm::vec3 sideColors[4] = {
            {1.0f, 0.0f, 0.0f}, // Red
            {0.0f, 1.0f, 0.0f}, // Green
            {0.0f, 0.0f, 1.0f}, // Blue
            {1.0f, 1.0f, 0.0f}  // Yellow
        };

        // Основа
        addTriangle(pyramidVertices, base[0], base[1], base[2], baseColor, center);
        addTriangle(pyramidVertices, base[0], base[2], base[3], baseColor, center);

        // Бічні грані
        for (int i = 0; i < 4; ++i)
            addTriangle(pyramidVertices, base[i], base[(i + 1) % 4], apex, sideColors[i], center);

        return pyramidVertices;
    }
}
