#include "network/pickup_message.h"
#include "core/i_inventory_component.h"
#include "core/actor_event.h"
#include "core/pickup_collision_component.h"
#include "core/item.h"
namespace network {

    PickupMessageSenderSystem::PickupMessageSenderSystem()
        : MessageSenderSystem()
    {
    }

    void PickupMessageSenderSystem::Init()
    {
        MessageSenderSystem::Init();
        mOnPickup= EventServer<engine::PickupEvent>::Get().Subscribe( boost::bind( &PickupMessageSenderSystem::OnPickup, this, _1 ) );
        mOnActorEvent = EventServer<ActorEvent>::Get().Subscribe( boost::bind( &PickupMessageSenderSystem::OnActorEvent, this, _1 ) );
    }

    void PickupMessageSenderSystem::Update(double DeltaTime)
    {
        MessageSenderSystem::Update(DeltaTime);
    }

    void PickupMessageSenderSystem::OnActorEvent(ActorEvent const& Evt)
    {
        if(Evt.mState==ActorEvent::Added)
        {
            Opt<PickupCollisionComponent> pickupCC = Evt.mActor->Get<PickupCollisionComponent>();
            if(!pickupCC.IsValid())
            {
                return;
            }
            std::auto_ptr<SetPickupContentMessage> setPickupMsg(new SetPickupContentMessage);
            setPickupMsg->mActorGUID=Evt.mActor->GetGUID();
            setPickupMsg->mContentId=pickupCC->GetPickupContent();
            setPickupMsg->mItemType=pickupCC->GetItemType();
            mMessageHolder.AddOutgoingMessage(setPickupMsg);
        }
    }

    void PickupMessageSenderSystem::OnPickup(engine::PickupEvent const& Evt)
    {
        std::auto_ptr<PickupMessage> pickupMsg(new PickupMessage);
        pickupMsg->mActorGUID=Evt.mActor->GetGUID();
        pickupMsg->mItemType=Evt.mItemType;
        pickupMsg->mItemId=Evt.mItemId;
        mMessageHolder.AddOutgoingMessage(pickupMsg);
    }

    PickupMessageHandlerSubSystem::PickupMessageHandlerSubSystem()
        : MessageHandlerSubSystem()
    {

    }

    void PickupMessageHandlerSubSystem::Init()
    {

    }

    void PickupMessageHandlerSubSystem::Execute(Message const& message)
    {
        PickupMessage const& msg=static_cast<PickupMessage const&>(message);
        //        L1("executing PlayerController: %d \n",msg.mSenderId );
        Opt<Actor> actor=mScene.GetActor(msg.mActorGUID);
        if (!actor.IsValid())
        {
            L1("cannot find actor with GUID: (pickup) %d \n",msg.mActorGUID );
            return;
        }

        Opt<IInventoryComponent> inventoryC = actor->Get<IInventoryComponent>();
        if (inventoryC.IsValid())
        {
            L2("pickup picked up with itemtype:%d,itemid:%d",msg.mItemType,msg.mItemId);
            inventoryC->DropItemType( msg.mItemType );
            inventoryC->AddItem( msg.mItemId );
            if (msg.mItemType==Item::Weapon)
            {
                inventoryC->SetSelectedWeapon( msg.mItemId );
            }
            else if (msg.mItemType==Item::Normal)
            {
                inventoryC->SetSelectedNormalItem( msg.mItemId );
            }
        }
    }

    SetPickupContentMessageHandlerSubSystem::SetPickupContentMessageHandlerSubSystem()
        : MessageHandlerSubSystem()
    {

    }

    void SetPickupContentMessageHandlerSubSystem::Init()
    {

    }

    void SetPickupContentMessageHandlerSubSystem::Execute(Message const& message)
    {
        SetPickupContentMessage const& msg=static_cast<SetPickupContentMessage const&>(message);
        L1("executing SetPickupContent: %d \n",msg.mSenderId );
        Opt<Actor> actor=mScene.GetActor(msg.mActorGUID);
        if (!actor.IsValid())
        {
            L1("cannot find actor with GUID: (set_pickup_content) %d \n",msg.mActorGUID );
            return;
        }

        Opt<PickupCollisionComponent> pickupCC = actor->Get<PickupCollisionComponent>();
        if(pickupCC.IsValid())
        {
            pickupCC->SetPickupContent(msg.mContentId);
            pickupCC->SetItemType(msg.mItemType);
        }
    }

} // namespace engine
