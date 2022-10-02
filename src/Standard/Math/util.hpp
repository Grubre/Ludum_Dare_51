#pragma once
#include "Standard/Math/vector.hpp"
#include <type_traits>

template<std::integral T>
constexpr T to1d(const T width, const T x, const T y)
{
    return width * y + x;
}
template<std::integral T>
constexpr engine::Vec2i to2d(const T width, const T x)
{
    return {x % width, x / width};
}
