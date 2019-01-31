#ifndef ThirdPersonController_h
#define ThirdPersonController_h

#include "IComponent.h"

#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#include <glm/gtx/rotate_vector.hpp>

class ThirdPersonController : public IComponent {
public:
    ThirdPersonController(class Object* target = nullptr, float radius = 0.0f, glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), float mouse_sensitivity = 0.1f);
    
    void Update() override;
    
    void Target(class Object* target) { m_Target = &target->Transform(); }
    void Radius(float radius) { m_Radius = radius; }
    
    class Object* line;
    
private:
    Transform* m_Target;
    float m_Radius;
    float m_MouseSensitivity;
    
    glm::vec3 m_Front;
    glm::vec3 m_RotationAxis;
    float m_XRotation;
    float m_YRotation;
    
    glm::quat m_RotationBeetwen(const glm::vec3& start, const glm::vec3& dest);
};

#endif
