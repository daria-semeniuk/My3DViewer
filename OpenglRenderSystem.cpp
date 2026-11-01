#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "OpenglRenderSystem.h"

namespace
{
    GLenum GetLight(uint32_t index)
    {
        return static_cast<GLenum>(GL_LIGHT0 + index); // GL_LIGHT0 ... GL_LIGHT7
    }
}

void OpenglRenderSystem::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_NORMALIZE);

    // Щоб glColor3f впливав на матеріал при увімкненому освітленні
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void OpenglRenderSystem::clearDisplay(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRenderSystem::setViewport(double x, double y, double width, double height)
{
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y),
               static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void OpenglRenderSystem::renderTriangleSoup(const std::vector<Vertex>& vertices)
{
    renderData(vertices, GL_TRIANGLES);
}

void OpenglRenderSystem::renderLines(const std::vector<Vertex>& vertices)
{
    renderData(vertices, GL_LINES);
}

void OpenglRenderSystem::renderData(const std::vector<Vertex>& vertices, unsigned int primitive)
{
    // Проєкція
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(m_projMatrix));

    // Матриця виду — у ній задаємо позиції світла, щоб вони були у світових координатах
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(m_viewMatrix));
    for (uint32_t i = 0; i < kMaxLights; ++i)
    {
        if (!m_lightConfigured[i])
            continue;
        const glm::vec4 pos(m_lightPositions[i], 1.0f);
        glLightfv(GetLight(i), GL_POSITION, glm::value_ptr(pos));
    }

    // Model * View
    const glm::mat4 modelView = m_viewMatrix * m_worldMatrix;
    glLoadMatrixf(glm::value_ptr(modelView));

    glBegin(primitive);
    for (const Vertex& v : vertices)
    {
        glNormal3f(v.normal.x, v.normal.y, v.normal.z);
        glColor3f(v.color.r, v.color.g, v.color.b);
        glVertex3f(v.position.x, v.position.y, v.position.z);
    }
    glEnd();
}

void OpenglRenderSystem::setupLight(uint32_t index, glm::vec3 position,
                                    glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
    if (index >= kMaxLights)
        return;

    const glm::vec4 ambient(Ia, 1.0f);
    const glm::vec4 diffuse(Id, 1.0f);
    const glm::vec4 specular(Is, 1.0f);

    glLightfv(GetLight(index), GL_AMBIENT,  glm::value_ptr(ambient));
    glLightfv(GetLight(index), GL_DIFFUSE,  glm::value_ptr(diffuse));
    glLightfv(GetLight(index), GL_SPECULAR, glm::value_ptr(specular));

    // Позицію виставимо під час рендеру (в renderData), коли вже відома матриця виду
    m_lightPositions[index]  = position;
    m_lightConfigured[index] = true;

    if (!glIsEnabled(GL_LIGHTING))
        glEnable(GL_LIGHTING);
}

void OpenglRenderSystem::turnLight(uint32_t index, bool enable)
{
    if (index >= kMaxLights)
        return;

    if (enable)
        glEnable(GetLight(index));
    else
        glDisable(GetLight(index));
}
