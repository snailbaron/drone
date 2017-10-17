#pragma once

#include <ostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <cassert>

template <class T>
struct Vector {
    T x;
    T y;

    Vector() : x{}, y{} {}
    Vector(T x, T y) : x(std::move(x)), y(std::move(y)) {}

    Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector& operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector& operator*=(const T& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector& operator/=(const T& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    T length() const
    {
        return std::sqrt(x * x + y * y);
    }

    bool isZero() const
    {
        return x == 0 && y == 0;
    }

    void setLength(const T& newLength)
    {
        auto currentLength = length();
        if (currentLength == 0) {
            return;
        }

        auto ratio = newLength / currentLength;
        x *= ratio;
        y *= ratio;
    }

    void normalize()
    {
        setLength(1);
    }

    void capLength(const T& maxLength)
    {
        assert(maxLength >= 0);

        if (length() > maxLength) {
            setLength(maxLength);
        }
    }

    void decreaseBy(const T& value)
    {
        if (!isZero()) {
            setLength(std::max<T>(0, length() - value));
        }
    }

    void rotate(const T& angle)
    {
        double xx = cos(angle) * x - sin(angle) * y;
        double yy = sin(angle) * x + cos(angle) * y;

        x = xx;
        y = yy;
    }

    T angle() const
    {
        return atan2(x, y);
    }

    static T angle(const Vector& left, const Vector& right)
    {
        return math::angleRadianDiff(left.angle(), right.angle());
    }

    template <class Target>
    Vector<Target> cast() const
    {
        return {static_cast<Target>(x), static_cast<Target>(y)};
    }
};

template <class T>
Vector<T> operator-(const Vector<T>& vector)
{
    return {-vector.x, -vector.y};
}

template <class T>
Vector<T> operator+(Vector<T> left, const Vector<T>& right)
{
    left += right;
    return left;
}

template <class T>
Vector<T> operator-(Vector<T> left, const Vector<T>& right)
{
    left -= right;
    return left;
}

template <class T>
Vector<T> operator*(Vector<T> vector, const T& scalar)
{
    vector *= scalar;
    return vector;
}

template <class T>
Vector<T> operator*(const T& scalar, Vector<T> vector)
{
    vector *= scalar;
    return vector;
}

template <class T>
Vector<T> operator/(Vector<T> vector, const T& scalar)
{
    vector /= scalar;
    return vector;
}

template <class T>
bool operator<(const Vector<T>& left, const Vector<T>& right)
{
    return std::tie(left.x, left.y) < std::tie(right.x, right.y);
}

template <class T>
bool operator>(const Vector<T>& left, const Vector<T>& right)
{
    return right < left;
}

template <class T>
bool operator<=(const Vector<T>& left, const Vector<T>& right)
{
    return !(right < left);
}

template <class T>
bool operator>=(const Vector<T>& left, const Vector<T>& right)
{
    return !(right > left);
}

template <class T>
bool operator==(const Vector<T>& left, const Vector<T>& right)
{
    return left.x == right.x && left.y == right.y;
}

template <class T>
bool operator!=(const Vector<T>& left, const Vector<T>& right)
{
    return !(left == right);
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& vector)
{
    stream << "[" << vector.x << ", " << vector.y << "]";
    return stream;
};