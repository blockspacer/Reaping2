#include "platform/i_platform.h"
#include "network/soldier_properties_message.h"
#include "core/buffs/i_buff_holder_component.h"
#include "core/buffs/buff_factory.h"
#include "core/buffs/move_speed_buff.h"
#include "core/buffs/max_health_buff.h"
#include "engine/buffs_engine/max_health_buff_sub_system.h"
#include "core/i_health_component.h"
#include "health_message.h"
#include "core/buffs/accuracy_buff.h"
#include "core/i_accuracy_component.h"
#include "engine/buffs_engine/accuracy_buff_sub_system.h"
#include "accuracy_message.h"

namespace network {

SoldierPropertiesMessageSenderSystem::SoldierPropertiesMessageSenderSystem()
    : MessageSenderSystem()
{
    mOnSoldierCreatedEvent=EventServer<engine::SoldierCreatedEvent>::Get().Subscribe( boost::bind( &SoldierPropertiesMessageSenderSystem::OnSoldierCreatedEvent, this, _1 ) );
    mOnSoldierPropertiesReady= EventServer<engine::SoldierPropertiesReadyEvent>::Get().Subscribe( boost::bind( &SoldierPropertiesMessageSenderSystem::OnSoldierPropertiesReady, this, _1 ) );

}

void SoldierPropertiesMessageSenderSystem::OnSoldierCreatedEvent(engine::SoldierCreatedEvent const& Evt)
{
    if(mProgramState.mMode==ProgramState::Server)
    {
        Opt<IBuffHolderComponent> buffHolderC = Evt.mActor->Get<IBuffHolderComponent>();
        if(buffHolderC.IsValid())
        {
            mMessageHolder.AddOutgoingMessage(network::HealthMessageSenderSystem::GenerateHealthMessage(*Evt.mActor));
            mMessageHolder.AddOutgoingMessage(network::AccuracyMessageSenderSystem::GenerateAccuracyMessage(*Evt.mActor));
        }

    }
}

void SoldierPropertiesMessageSenderSystem::Init()
{
    MessageSenderSystem::Init();
}


void SoldierPropertiesMessageSenderSystem::Update(double DeltaTime)
{
    MessageSenderSystem::Update(DeltaTime);
}

void SoldierPropertiesMessageSenderSystem::OnSoldierPropertiesReady(engine::SoldierPropertiesReadyEvent const& Evt)
{
    if (mProgramState.mMode!=ProgramState::Server)
    {
        std::auto_ptr<SoldierPropertiesMessage> soldierPorpertiesMessage(new SoldierPropertiesMessage);
        soldierPorpertiesMessage->mSoldierProperties=mProgramState.mSoldierProperties;
        mMessageHolder.AddOutgoingMessage(soldierPorpertiesMessage);
    }
}

SoldierPropertiesMessageHandlerSubSystem::SoldierPropertiesMessageHandlerSubSystem()
    : MessageHandlerSubSystem()
{
}


void SoldierPropertiesMessageHandlerSubSystem::Init()
{
}

void SoldierPropertiesMessageHandlerSubSystem::Execute(Message const& message)
{
    SoldierPropertiesMessage const& msg=static_cast<SoldierPropertiesMessage const&>(message);
    L1("executing soldierProperties from id: %d \n",msg.mSenderId );
    L2("got revive message: senderId:%d\n",msg.mSenderId);

    Opt<core::ClientData> clientData(mProgramState.FindClientDataByClientId(msg.mSenderId));
    if (!clientData.IsValid())
    {
        L1("cannot find clientdata for for properties: senderId: %d\n",msg.mSenderId);
        return;
    }

    clientData->mSoldierProperties=msg.mSoldierProperties;
    L1("**** Client: %s properties arrived. Ready to fight!!! **** from id: %d \n", clientData->mClientName.c_str(),msg.mSenderId );
    L1("   MoveSpeed:%d\n   Health:%d\n   Accuracy:%d\n", msg.mSoldierProperties.mMoveSpeed, msg.mSoldierProperties.mHealth, msg.mSoldierProperties.mAccuracy );

}


} // namespace network
