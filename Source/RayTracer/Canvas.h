#pragma once
#include "Color.h"
#include <vector>


class Canvas
{
public:
    Canvas(int width, int height, const class Renderer& renderer);
    ~Canvas();

    void Update();
    void Clear(const color4_t& color);
    void DrawPoint(const glm::ivec2& point, const color4_t& color);

    //<return const reference of m_size> GetSize() const { return m_size; }
        glm::vec2 GetSize() const { return m_size; }
    //<allow Renderer to access Canvas private data>
        friend class Renderer;
private:
    //<SDL Texture pointer(forward declaration)> m_texture<default to nullptr>;
    //<vector of rgba_t> m_buffer;
    struct SDL_Texture* m_texture = nullptr;
    std::vector<rgba_t> m_buffer;
    //<glm integer vector2> m_size<default to 0>;
    glm::ivec2 m_size{ 0 };
};