#include "simple_room1.h"
#include "core/i_position_component.h"
#include "platform/settings.h"

namespace map {

SimpleRoom1::SimpleRoom1( int32_t Id )
    : IRoom( Id )
    , mActorFactory( ActorFactory::Get() )
{
    mRoomDesc.SetCellCount( 1 );
    mRoomDesc.SetCellSize( Settings::Get().GetInt( "generator.cell_size", 1000 ) );
    mRoomDesc.GetCell( 0, 0 ).SetEntrances( { EntranceType::Top, EntranceType::Right, EntranceType::Bottom, EntranceType::Left } );
    mRoomDesc.GetCell( 0, 0 ).SetFilled( true );
    mRoomDesc.SetPlainProperties( { RoomProperty::Start, RoomProperty::End } );
    mRoomDesc.SetRoom( this );
}

void SimpleRoom1::Generate( RoomDesc& roomDesc, glm::vec2 pos, bool editor /*= false*/ )
{
    int cellCount = mRoomDesc.GetCellSize() / 100;
    for (int i = 0; i < cellCount*cellCount; ++i)
    {
        auto& cell = roomDesc.GetCell( glm::vec2( 0, 0 ) );
        if (i < cellCount && !cell.HasEntrance( EntranceType::Bottom )
            || i >= (cellCount - 1)*cellCount && !cell.HasEntrance( EntranceType::Top )
            || i%cellCount == 0 && !cell.HasEntrance( EntranceType::Left )
            || i%cellCount == cellCount - 1 && !cell.HasEntrance( EntranceType::Right ))
        {
            std::auto_ptr<Actor> wall = mActorFactory( AutoId( "wall_small" ) );
            Opt<IPositionComponent> positionC = wall->Get<IPositionComponent>();
            positionC->SetX( i%cellCount*100.0 + pos.x );
            positionC->SetY( i / cellCount*100.0 + pos.y );
            roomDesc.mPlacedActorGUIDs.push_back( wall->GetGUID() );
            mScene.AddActor( wall.release() );
        }
    }
    if (roomDesc.HasProperty( RoomProperty::Start ))
    {
        PlaceSoldierSpawnPoint( roomDesc, pos + glm::vec2( cellCount / 2 * 100, cellCount / 2 * 100 ) );
    }
    if (roomDesc.HasProperty( RoomProperty::End ))
    {
        PlaceLevelEndPoint( roomDesc, pos + glm::vec2( cellCount / 2 * 100, cellCount / 2 * 100 ) );
    }
}

} // namespace map

