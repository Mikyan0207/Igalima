//
// Created by Mikyan on 13/02/2021.
//

#ifndef IGALIMA_OPENGL_COMPONENT_H
#define IGALIMA_OPENGL_COMPONENT_H

#include <cstdint>

// Everything is public so we don't need to use a class..
struct Component
{
    Component() = default;
    Component(const Component&) = default;
    Component(Component&&) noexcept = default;
    virtual ~Component() = default;

    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) noexcept = default;

    // virtual functions are not really optimized, but for now I don't care.
    virtual void Initialize();
    virtual void Destroy();

    uint32_t Id;
};

#endif //IGALIMA_OPENGL_COMPONENT_H
