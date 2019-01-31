#ifndef Manager_h
#define Manager_h

#include "IComponent.h"
#include "FirstPersonController.h"
#include "ThirdPersonController.h"

#include "../../utilities/Time.h"
#include "../../utilities/Input.h"

#include <array>

class Manager : public IComponent {
public:
    Manager(std::array<class Object *, 9> planets, std::array<float, 9> radiuses, FirstPersonController* fpc, ThirdPersonController* tpc);
    
    void Initialize() override;
    void Update() override;
    
private:
    // Controllers
    FirstPersonController* m_FPC;
    ThirdPersonController* m_TPC;
    
    // Time
    bool m_Paused;
    unsigned int m_TimeMultiplayersIndex;
    std::array<int, 5> m_TimeMultiplayers;
    
    std::array<class Object*, 9> m_Planets;
    std::array<float, 9> m_Radiuses;
};

#endif
