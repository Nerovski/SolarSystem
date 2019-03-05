#ifndef Scene_hpp
#define Scene_hpp

#include "../cbs/ObjectManager.h"
#include "../rendering/DrawManager.h"

class IScene {
public:
    IScene();
    
    virtual void CreateScene() = 0;
    
    void PreRun();
    void Run();
    void PostRun();
    
    void Exit();
    
    // DrawManager functions
    void RegisterDrawCall(IDrawable* drawable);
    void UnregisterDrawCall(IDrawable* drawable);
    void RegisterLightSource(ILightSource* light_source);
    void UnregisterLightSource(ILightSource* light_source);
    void RegisterCamera(Camera* camera);
    void UnregisterCamera();
    Camera* MainCamera() const;
    void Skybox(const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& back, const std::string& front);
    void Background(const glm::vec3& background);
    
protected:
    Object* CreateObject(std::string name = "");
    Object* CreateObject(const Object* other, std::string name = "");
    
    float FrameRate() const;
    void FrameRate(unsigned int frame_rate);
    
private:
    ObjectManager m_ObjectManager;
    DrawManager m_DrawManager;
    
    bool m_Running;
    float m_FrameRate;
};

#endif
