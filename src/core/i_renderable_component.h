#ifndef INCLUDED_CORE_I_RENDERABLE_COMPONENT_H
#define INCLUDED_CORE_I_RENDERABLE_COMPONENT_H
#include "core/component.h"
#include "core/renderable_layer.h"
#include "platform/export.h"

class IRenderableComponent : public Component
{
public:
    DEFINE_COMPONENT_BASE( IRenderableComponent )
    virtual RenderableLayer::Type const& GetLayer()const = 0;
    virtual void SetLayer( RenderableLayer::Type Lay ) = 0;
    virtual int32_t const& GetZOrder()const = 0;
    virtual void SetZOrder( int32_t ZOrder ) = 0;
protected:
    friend class ComponentFactory;
public:
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize( Archive& ar, const unsigned int version );
};

template<class Archive>
void IRenderableComponent::serialize( Archive& ar, const unsigned int version )
{
    //NOTE: generated archive for this class
    ar& boost::serialization::base_object<Component>( *this );
}


REAPING2_CLASS_EXPORT_KEY2( IRenderableComponent, IRenderableComponent, "i_renderable_component" );
#endif//INCLUDED_CORE_I_RENDERABLE_COMPONENT_H