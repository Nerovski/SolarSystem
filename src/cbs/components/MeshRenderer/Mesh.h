#ifndef Mesh_h
#define Mesh_h

#include "../../../rendering/ShaderProgram.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

// TODO to new files
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int ID;
    std::string Type;
    std::string Path;
};

class Mesh {
    friend class MeshRenderer;
    
public:
    Mesh(const std::vector<Vertex> &verticies, const std::vector<unsigned int> &indicies, const std::vector<Texture> &textures);
    //Mesh(Mesh &other) = delete; 
    ~Mesh();
    
    void Draw(const ShaderProgram &shader) const;
    
    const std::vector<Vertex>& Vertices() const { return m_Vertices; }
    const std::vector<unsigned int>& Indicies() const { return m_Indices; }
    const std::vector<Texture>& Textures() const { return m_Textures; }
    
private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
    
    void SetupMesh();
};

#endif
