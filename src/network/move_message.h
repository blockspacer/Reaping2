#ifndef INCLUDED_NETWORK_MOVE_MESSAGE_H
#define INCLUDED_NETWORK_MOVE_MESSAGE_H

#include "network/message.h"
#include "platform/export.h"
namespace network {

class MoveMessage: public Message
{
    friend class ::boost::serialization::access;
public:
    DEFINE_MESSAGE_BASE( MoveMessage )
    int32_t mActorGUID;
    int32_t mHeadingModifier;
    int32_t mSpeed;
    int32_t mPercent;
    int32_t mFlat;
    bool mMoving;
    bool mRooted;

    MoveMessage()
        : mActorGUID( 0 )
        , mHeadingModifier( 0 )
        , mSpeed( 0 )
        , mPercent( 0 )
        , mFlat( 0 )
        , mMoving( false )
        , mRooted( false )
    {
    }
    template<class Archive>
    void serialize( Archive& ar, const unsigned int version );
    bool operator==( MoveMessage const& other );
};

template<class Archive>
void MoveMessage::serialize( Archive& ar, const unsigned int version )
{
    ar& boost::serialization::base_object<Message>( *this );
    ar& mActorGUID;
    ar& mHeadingModifier;
    ar& mSpeed;
    ar& mPercent;
    ar& mFlat;
    ar& mMoving;
    ar& mRooted;
}

} // namespace network

REAPING2_CLASS_EXPORT_KEY2( network__MoveMessage, network::MoveMessage, "move" );
#endif//INCLUDED_NETWORK_MOVE_MESSAGE_H
