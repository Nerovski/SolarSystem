#ifndef Line_h
#define Line_h

#include "../rendering/IDrawable.h"

class Line : public IDrawable {
public:
    Line(glm::vec3 start, glm::vec3 end, glm::vec3 color, float width = 1.0f);
    ~Line();
    
    void Draw(const ShaderProgram& shader) const override;
    
    const glm::vec3& Start() const { return m_Start; }
    
    const glm::vec3& End() const { return m_End; }
    
    const glm::vec3& Color() const { return m_Color; }
    void Color(const glm::vec3 color) { m_Color = color; }
    
    float Width() const { return m_Width; }
    void Width(float width) { m_Width = width; }
    
private:
    glm::vec3 m_Start;
    glm::vec3 m_End;
    glm::vec3 m_Color;
    float m_Width;
    
    unsigned int m_VAO;
    unsigned int m_VBO;
};

#endif
