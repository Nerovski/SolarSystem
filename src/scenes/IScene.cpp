#include "IScene.h"

#include "../rendering/IDrawable.h"
#include "../rendering/ILightSource.h"
#include "../utilities/Time.h"
#include "../utilities/Input.h"
#include "../utilities/Window.h"

IScene::IScene() {
    m_Running = true;
    m_FrameRate = 0.0f;
}

void IScene::PreRun() {
    m_Running = true;
    
    m_DrawManager.Initialize();
    m_ObjectManager.InitializeObjects();
}

void IScene::Run() {
    g_Time.Initialize();
    
    while (m_Running && !glfwWindowShouldClose(g_Window)) {
        do {
            g_Time.Hold();
            glfwPollEvents();
        } while (g_Time.DeltaTime() < m_FrameRate);
        
        g_Time.Update();
        g_Input.Update(g_Window);
        
        m_ObjectManager.UpdateObjects();
        m_DrawManager.CallDraws();
    }
}

void IScene::PostRun() {
    m_ObjectManager.DestroyObjects();
}

void IScene::Exit() {
    m_Running = false;
}

Object* IScene::CreateObject(std::string name) {
    return m_ObjectManager.CreateObject(*this, name);
}

Object* IScene::CreateObject(const Object *other, std::string name) {
    return m_ObjectManager.CreateObject(other, name);
}

float IScene::FrameRate() const {
    return 1.0f / m_FrameRate;
}

void IScene::FrameRate(unsigned int frame_rate) {
    m_FrameRate = frame_rate != 0 ? 1.0f / (float)frame_rate : 0.0f;
}
