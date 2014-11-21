#include "health_component.h"
#include "i_position_component.h"
#include "platform/auto_id.h"
#include "platform/event.h"
#include "core/damage_taken_event.h"
#include "i_core.h"

using platform::AutoId;
using platform::EventServer;

HealthComponent::HealthComponent()
    : mHP( 1 )
    , mAlive( true )
    , mTimeOfDeath( 0 )
    , mActor( NULL )
    , mNeedDelete( false )
{
}

void HealthComponent::Update( double Seconds )
{
    if ( IsAlive() )
    {
        return;
    }
    BOOST_ASSERT( mActor );
    mAlive = false;
    mActor->SetCC( CollisionClass::No_Collision );
    mActor->AddAction( AutoId( "death" ) );
    if ( mTimeOfDeath <= 0.0 )
    {
        mTimeOfDeath=glfwGetTime();
    }
}

int32_t const& HealthComponent::GetHP() const
{
    return mHP;
}

void HealthComponent::SetHP( int32_t Hp )
{
    if (IsAlive())
    {
        if (mHP>Hp)
        {
            Opt<IPositionComponent> positionC = mActor->Get<IPositionComponent>();
            if(positionC.IsValid())
            {
                EventServer<core::DamageTakenEvent>::Get().SendEvent( core::DamageTakenEvent( positionC->GetX(), positionC->GetY() ) );
            }
        }
        mHP = Hp;
        mAlive = mHP > 0;
    }
}

bool HealthComponent::IsAlive() const
{
    return mAlive;
}

double HealthComponent::GetTimeOfDeath() const
{
    return mTimeOfDeath;
}

void HealthComponent::SetActor( Actor* Obj )
{
    mActor=Obj;
}

bool HealthComponent::NeedDelete() const
{
    return mNeedDelete;
}
