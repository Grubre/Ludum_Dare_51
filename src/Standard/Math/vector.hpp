#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

namespace engine
{
    template<typename T>
    class Vec2
    {
        public:
            T x;
            T y;
            
            constexpr Vec2() : x(0), y(0) {}
            explicit Vec2(sf::Vector2<T> vec) : x(vec.x), y(vec.y) {}
            constexpr Vec2(T x, T y) : x(x), y(y) {}

            constexpr T dot(const Vec2<T> &rhs) const {
                return x*rhs.x + y*rhs.y;
            }

            constexpr T length_sq() const {
                return x*x + y*y;
            }

            constexpr float length() const {
                return std::sqrt(length_sq());
            }

            constexpr Vec2<float> norm() const {
                float len = length();
                return Vec2<float>(x/len,y/len);
            }

            constexpr Vec2<T> perpendicular() const  {
                return {-y,x};
            }

            constexpr Vec2<float> interpolate(float scalar) const {
                return (*this) * scalar;
            }

            //konwersje
            constexpr explicit operator sf::Vector2<T>() const {
                return {x, y};
            }
    };

    using Vec2i = Vec2<int>;
    using Vec2u = Vec2<unsigned int>;
    using Vec2d = Vec2<double>;
    using Vec2f = Vec2<float>;

    //unarny minus
    template<typename T> 
    Vec2<T> operator-(const Vec2<T> &rhs) {
        return Vec2(-rhs.x,-rhs.y);
    }

    //dodawanie
    template<typename T> 
    Vec2<T> operator+(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return Vec2(lhs.x + rhs.x,lhs.y + rhs.y);
    }

    template<typename T> 
    Vec2<T>& operator+=(Vec2<T> &lhs, const Vec2<T> &rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    //odejmowanie
    template<typename T> 
    Vec2<T> operator-(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return Vec2(lhs.x - rhs.x,lhs.y - rhs.y);
    }

    template<typename T> 
    Vec2<T>& operator-=(Vec2<T> &lhs, const Vec2<T> &rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    //mno??enie przez skalar
    template<typename T> 
    Vec2<T> operator*(T lhs, const Vec2<T> &rhs) {
        return Vec2(lhs * rhs.x,lhs * rhs.y);
    }

    template<typename T> 
    Vec2<T> operator*(const Vec2<T> &lhs, T rhs) {
        return Vec2(lhs.x * rhs,lhs.y * rhs);
    }
    
    template<typename T> 
    Vec2<T>& operator*=(Vec2<T> &lhs, const T rhs) {
        lhs.x *= rhs;
        lhs.y *= rhs;
        return lhs;
    }

    //dzielenie przez skalar
    template<typename T> 
    Vec2<T> operator/(const Vec2<T> &lhs, T rhs) {
        return Vec2(lhs.x / rhs,lhs.y / rhs);
    }
    
    template<typename T> 
    Vec2<T>& operator/=(Vec2<T> &lhs, const T rhs) {
        lhs.x /= rhs;
        lhs.y /= rhs;
        return lhs;
    }   

    //por??wnywanie
    template<typename T> 
    Vec2<T> operator==(const Vec2<T> &lhs, const Vec2<T> &rhs) {
        return rhs.x == lhs.x && rhs.y == lhs.y;
    }

    //wypisanie 
    template<typename T> 
    std::ostream& operator<< (std::ostream& out, const Vec2<T> &vec)
    {
        return out << vec.x << " " << vec.y;
    }
}
