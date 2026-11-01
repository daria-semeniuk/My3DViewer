#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#include "Vertex.h"

class OpenglRenderSystem
{
public:
    void init();
    void clearDisplay(float r, float g, float b);
    void setViewport(double x, double y, double width, double height);

    void renderTriangleSoup(const std::vector<Vertex>& vertices);
    void renderLines(const std::vector<Vertex>& vertices);

    void setupLight(uint32_t index, glm::vec3 position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is);
    void turnLight(uint32_t index, bool enable);

    void setWorldMatrix(const glm::mat4& matrix)      { m_worldMatrix = matrix; }
    void setViewMatrix(const glm::mat4& matrix)       { m_viewMatrix = matrix; }
    void setProjectionMatrix(const glm::mat4& matrix) { m_projMatrix = matrix; }

    const glm::mat4& getWorldMatrix() const      { return m_worldMatrix; }
    const glm::mat4& getViewMatrix() const       { return m_viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return m_projMatrix; }

private:
    // primitive — GL_TRIANGLES або GL_LINES (unsigned int, щоб не тягнути glad у заголовок)
    void renderData(const std::vector<Vertex>& vertices, unsigned int primitive);

    static constexpr uint32_t kMaxLights = 8;

    glm::mat4 m_worldMatrix{1.0f};
    glm::mat4 m_viewMatrix{1.0f};
    glm::mat4 m_projMatrix{1.0f};

    std::array<glm::vec3, kMaxLights> m_lightPositions{};
    std::array<bool, kMaxLights>      m_lightConfigured{};
};
