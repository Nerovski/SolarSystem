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
    
    DrawManager& DrawManager() { return m_DrawManager; }
    
protected:
    Object* CreateObject(std::string name = "");
    
    float FrameRateLimit() const;
    void FrameRateLimit(unsigned int frame_rate);
    
private:
    ObjectManager m_ObjectManager;
    class DrawManager m_DrawManager;
    
    bool m_Running;
    float m_FrameRateLimit;
};

#endif
