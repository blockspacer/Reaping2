#ifndef INCLUDED_ENGINE_CONTROLLERS_RANDOM_CONTROLLER_SUB_SYSTEM_H
#define INCLUDED_ENGINE_CONTROLLERS_RANDOM_CONTROLLER_SUB_SYSTEM_H

#include "core/scene.h"
#include "engine/sub_system.h"
#include "core/program_state.h"

namespace engine {

class RandomControllerSubSystem : public SubSystem
{
public:
    DEFINE_SUB_SYSTEM_BASE( RandomControllerSubSystem )
    RandomControllerSubSystem();
    virtual void Init();
    virtual void Update( Actor& actor, double DeltaTime );
private:
    Scene& mScene;
    core::ProgramState& mProgramState;
};

} // namespace engine

#endif//INCLUDED_ENGINE_CONTROLLERS_RANDOM_CONTROLLER_SUB_SYSTEM_H
