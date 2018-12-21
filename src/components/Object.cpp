#include "Object.h"
#include "IComponent.h"
#include "../scenes/Scene.h"

Object::Object(std::string name)
    : m_Name(name)
    , m_Position(glm::vec3(0.0f))
    , m_Rotation(glm::vec3(0.0f))
    , m_Scale(glm::vec3(1.0f)) {
}

Object::~Object() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->m_Object = nullptr;
    }
}

void Object::Initialize() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Initialize();
    }
}

void Object::Update() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Update();
    }
}

void Object::Destroy() {
    for (auto it = m_Components.begin(); it != m_Components.end(); it++) {
        (*it)->Destroy();
    }
}

void Object::AddComponent(IComponent *component) {
    if (std::find(m_Components.begin(), m_Components.end(), component) == m_Components.end()) {
        m_Components.push_back(component);
        component->m_Object = this;
    }
}

void Object::RemoveComponent(IComponent *component) {
    auto it = std::find(m_Components.begin(), m_Components.end(), component);
    
    if (it != m_Components.end()) {
        int index = (int)std::distance(m_Components.begin(), it);
        m_Components.erase(m_Components.begin() + index);
        component->m_Object = nullptr;
    }
}

void Object::RegisterUpdateCall(IComponent *component) {
    if (std::find(m_Components.begin(), m_Components.end(), component) != m_Components.end()) {
        if (std::find(m_UpdateCalls.begin(), m_UpdateCalls.end(), component) == m_UpdateCalls.end()) {
            m_UpdateCalls.push_back(component);
        }
    }
}

void Object::UnregisterUpdateCall(IComponent *component) {
    auto it = std::find(m_UpdateCalls.begin(), m_UpdateCalls.end(), component);
    
    if (it != m_UpdateCalls.end()) {
        int index = (int)std::distance(m_UpdateCalls.begin(), it);
        m_UpdateCalls.erase(m_UpdateCalls.begin() + index);
    }
}

void Object::Position(const glm::vec3& position) {
    m_Position = position;
    
    UpdateModel();
}

void Object::Rotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    
    UpdateModel();
}

void Object::Scale(const glm::vec3& scale) {
    m_Scale = scale;
    
    UpdateModel();
}

void Object::UpdateModel() {
    m_Model = glm::translate(glm::mat4(), m_Position);
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Model = glm::scale(m_Model, m_Scale);
}