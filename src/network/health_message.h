#ifndef INCLUDED_NETWORK_HEALTH_H
#define INCLUDED_NETWORK_HEALTH_H

#include "network/message.h"
#include "network/message_handler_sub_system.h"
#include "network/message_sender_system.h"
#include "core/health_changed_event.h"
#include "platform/export.h"

namespace network {

class HealthMessage : public Message
{
    friend class ::boost::serialization::access;
public:
    DEFINE_MESSAGE_BASE( HealthMessage )
    int32_t mActorGUID;
    int32_t mHP;
    int32_t mMaxHP;
    int32_t mMaxHPPercent;
    int32_t mMaxHPFlat;
    HealthMessage()
        : mActorGUID( 0 )
        , mHP( 0 )
        , mMaxHP( 0 )
        , mMaxHPPercent( 0 )
        , mMaxHPFlat( 0 )
    {
    }
    template<class Archive>
    void serialize( Archive& ar, const unsigned int version );
};

template<class Archive>
void HealthMessage::serialize( Archive& ar, const unsigned int version )
{
    ar& boost::serialization::base_object<Message>( *this );
    ar& mActorGUID;
    ar& mHP;
    ar& mMaxHP;
    ar& mMaxHPPercent;
    ar& mMaxHPFlat;
}

class HealthMessageHandlerSubSystem : public PendingMessageHandlerSubSystem<HealthMessage>
{
public:
    DEFINE_SUB_SYSTEM_BASE( HealthMessageHandlerSubSystem )
    HealthMessageHandlerSubSystem();
    virtual void Init();
    virtual void Update( double DeltaTime );
    virtual bool ProcessPending( Message const& message );
};

class HealthMessageSenderSystem : public MessageSenderSystem
{
    AutoReg mOnHealthChanged;
    void OnHealthChanged( core::HealthChangedEvent const& Evt );
public:
    DEFINE_SYSTEM_BASE( HealthMessageSenderSystem )
    HealthMessageSenderSystem();
    virtual void Init();
    virtual void Update( double DeltaTime );
    static std::auto_ptr<HealthMessage> GenerateHealthMessage( Actor& actor );
};
} // namespace network


REAPING2_CLASS_EXPORT_KEY2( network__HealthMessage, network::HealthMessage, "health" );
#endif//INCLUDED_NETWORK_HEALTH_H

// TODO: to main.cpp:
// Eng.AddSystem(AutoId("health_message_sender_system"));
