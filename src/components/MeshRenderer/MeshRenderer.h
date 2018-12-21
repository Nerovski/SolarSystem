#ifndef Model_h
#define Model_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image/stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "Mesh.h"
#include "../IComponent.h"
#include "../../rendering/ShaderProgram.h"
#include "../../rendering/IDrawable.h"
#include "../../utilities/DrawManager.h"
#include "../../scenes/Scene.h"

class MeshRenderer : public IComponent, public IDrawable {
public:
    MeshRenderer(char *path, ShaderType type);
    ~MeshRenderer();
    
    void Initialize() override;
    void Destroy() override {}
    
    void Draw(const ShaderProgram &shader) override;
    
    const std::vector<Mesh>& Meshes() const { return m_Meshes; }
    const std::vector<Texture>& TexturesLoaded() const { return m_TexturesLoaded; }
    const std::string& Directory() const { return m_Directory; }
    
private:
    std::vector<Mesh> m_Meshes;
    std::vector<Texture> m_TexturesLoaded;
    std::string m_Directory;
    
    void LoadModel(std::string path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif
