#include "FirstPersonController.h"

FirstPersonController::FirstPersonController(float movement_speed_fast, float movement_speed_slow, float mouse_sensivity, float yaw, float pitch, glm::vec3 world_up)
    : m_MovementSpeedFast(movement_speed_fast)
    , m_MovementSpeedSlow(movement_speed_slow)
    , m_MouseSensivity(mouse_sensivity)
    , m_Yaw(yaw)
    , m_Pitch(pitch)
    , m_WorldUp(world_up) {
}

void FirstPersonController::Initialize() {
    m_LastMousePos = g_Input.MousePosition();
}

void FirstPersonController::Update() {
    float dt = g_Time.DeltaTime();
    
    // Keyboard
    if (g_Input.GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
        m_CurrentMovementSpeed = m_MovementSpeedFast;
    } else {
        m_CurrentMovementSpeed = m_MovementSpeedSlow;
    }
    
    if (g_Input.GetKeyState(GLFW_KEY_W) || g_Input.GetKeyState(GLFW_KEY_UP)) {
        Object().Move(m_Front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_S) || g_Input.GetKeyState(GLFW_KEY_DOWN)) {
        Object().Move(-m_Front * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_A) || g_Input.GetKeyState(GLFW_KEY_LEFT)) {
        Object().Move(-m_Right * m_CurrentMovementSpeed * dt);
    }
    if (g_Input.GetKeyState(GLFW_KEY_D) || g_Input.GetKeyState(GLFW_KEY_RIGHT)) {
        Object().Move(m_Right * m_CurrentMovementSpeed * dt);
    }
    
    // Mouse
    float x_offset = (g_Input.MousePosition().x - m_LastMousePos.x) * m_MouseSensivity;
    float y_offset = (m_LastMousePos.y - g_Input.MousePosition().y) * m_MouseSensivity;
    m_LastMousePos = g_Input.MousePosition();
    
    m_Yaw = m_Yaw + x_offset;
    m_Pitch = m_Pitch + y_offset;
    
    if (m_Pitch > 89.0f) {
        m_Pitch = 89.0f;
    } else if (m_Pitch < -89.0f) {
        m_Pitch = -89.0f;
    }
    
    float x_rotation = glm::radians(m_Pitch);
    float y_rotation = -glm::radians(m_Yaw);
    
    Object().Rotation(glm::vec3(x_rotation, y_rotation, 0.0f));
    
    m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Front = glm::rotate(m_Front, x_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
    m_Front = glm::rotate(m_Front, y_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
}
