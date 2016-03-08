#ifndef INCLUDED_ENGINE_CONTROLLERS_TARGET_PLAYER_CONTROLLER_SUB_SYSTEM_H
#define INCLUDED_ENGINE_CONTROLLERS_TARGET_PLAYER_CONTROLLER_SUB_SYSTEM_H

#include "core/scene.h"
#include "engine/sub_system.h"
#include "core/program_state.h"
#include "core/i_target_holder_component.h"

namespace engine {

class TargetPlayerControllerSubSystem : public SubSystem
{
public:
    DEFINE_SUB_SYSTEM_BASE( TargetPlayerControllerSubSystem )
    TargetPlayerControllerSubSystem();
    virtual void Init();
    virtual void Update( Actor& actor, double DeltaTime );

    static double GetRotationDiffRadians( Actor const& actor, Actor const& target );

    void UpdateTarget( Opt<ITargetHolderComponent> targetHolderC );

private:
    Scene& mScene;
    core::ProgramState& mProgramState;
};

} // namespace engine

#endif//INCLUDED_ENGINE_CONTROLLERS_TARGET_PLAYER_CONTROLLER_SUB_SYSTEM_H
