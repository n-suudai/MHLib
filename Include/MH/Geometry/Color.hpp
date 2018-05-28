
#pragma once


#include "MH/OS/Types.hpp"
#include "MH/Geometry/Math.hpp"


namespace MH {
namespace Geometry {


class Color : Vector4
{
public:
    inline Color()
        : Vector4()
    {}

    inline Color(Scalar r, Scalar g, Scalar b, Scalar a = Scalar(1))
    {
        (*this) << r, g, b, a;
    }

    inline Color(u8 r, u8 g, u8 b, u8 a = 0xFF)
    {
        (*this) <<
            Scalar(r) / Scalar(0xFF),
            Scalar(g) / Scalar(0xFF),
            Scalar(b) / Scalar(0xFF),
            Scalar(a) / Scalar(0xFF);
    }

    inline Color(u32 color)
        : Color(
            static_cast<u8>(color),
            static_cast<u8>(color >> 8),
            static_cast<u8>(color >> 16),
            static_cast<u8>(color >> 24)
            )
    {}

    inline Color(const Vector4& color)
    {
        (*this) = color;
    }

    inline Color(const Vector3& color, Scalar a = Scalar(1))
    {
        (*this) << color.x(), color.y(), color.z(), a;
    }

    inline u32 GetPacked() const
    {
        return static_cast<u32>(
            static_cast<u32>(Saturate(a()) * 0xFF) << 24 |
            static_cast<u32>(Saturate(b()) * 0xFF) << 16 |
            static_cast<u32>(Saturate(g()) * 0xFF) << 8 |
            static_cast<u32>(Saturate(r()) * 0xFF)
            );
    }

    inline Color ToHSVColor(const Color& rgbColor)
    {
        Color hsv = rgbColor;
        Scalar min = Min(Min(rgbColor.r, rgbColor.g), rgbColor.b);
        Scalar max = Max(Max(rgbColor.r, rgbColor.g), rgbColor.b);
        Scalar Delta = max - min;

        hsv.v() = max;

        if (max != static_cast<Scalar>(0))
        {
            hsv.s() = Delta / hsv.v();
            Scalar h = static_cast<Scalar>(0);

            if (rgbColor.r() == max)
                // between yellow & magenta
                h = static_cast<Scalar>(0) + Scalar(60) * (rgbColor.g() - rgbColor.b()) / Delta;
            else if (rgbColor.g() == max)
                // between cyan & yellow
                h = static_cast<Scalar>(120) + Scalar(60) * (rgbColor.b() - rgbColor.r()) / Delta;
            else
                // between magenta & cyan
                h = static_cast<Scalar>(240) + Scalar(60) * (rgbColor.r() - rgbColor.g()) / Delta;

            if (h < Scalar(0))
                hsv.h() = h + Scalar(360);
            else
                hsv.h() = h;
        }
        else
        {
            // If r = g = b = 0 then s = 0, h is undefined
            hsv.s() = static_cast<Scalar>(0);
            hsv.h() = static_cast<Scalar>(0);
        }

        return hsv;
    }

    inline Color ToRGBColor(const Color& hsvColor)
    {
        Color hsv = hsvColor;
        Color rgbColor;

        if (hsv.y == static_cast<Scalar>(0))
        {
            // achromatic (grey)
            rgbColor = Color(hsv.v());
        }
        else
        {
            Scalar sector = floor(hsv.h() * (Scalar(1) / Scalar(60)));
            Scalar frac = (hsv.h() * (Scalar(1) / Scalar(60))) - sector;
            // factorial part of h
            Scalar o = hsv.v() * (Scalar(1) - hsv.s());
            Scalar p = hsv.v() * (Scalar(1) - hsv.s() * frac);
            Scalar q = hsv.v() * (Scalar(1) - hsv.s() * (Scalar(1) - frac));

            switch (int(sector))
            {
            default:
            case 0:
                rgbColor.r() = hsv.v();
                rgbColor.g() = q;
                rgbColor.b() = o;
                break;
            case 1:
                rgbColor.r() = p;
                rgbColor.g() = hsv.v();
                rgbColor.b() = o;
                break;
            case 2:
                rgbColor.r() = o;
                rgbColor.g() = hsv.v();
                rgbColor.b() = q;
                break;
            case 3:
                rgbColor.r() = o;
                rgbColor.g() = p;
                rgbColor.b() = hsv.v();
                break;
            case 4:
                rgbColor.r() = q;
                rgbColor.g() = o;
                rgbColor.b() = hsv.v();
                break;
            case 5:
                rgbColor.r() = hsv.v();
                rgbColor.g() = o;
                rgbColor.b() = p;
                break;
            }
        }
        return rgbColor;
    }

    inline Scalar& r() { return (*this)[0]; }
    inline const Scalar& r() const { return (*this)[0]; }

    inline Scalar& g() { return (*this)[1]; }
    inline const Scalar& g() const { return (*this)[1]; }

    inline Scalar& b() { return (*this)[2]; }
    inline const Scalar& b() const { return (*this)[2]; }

    inline Scalar& h() { return (*this)[0]; }
    inline const Scalar& h() const { return (*this)[0]; }

    inline Scalar& s() { return (*this)[1]; }
    inline const Scalar& s() const { return (*this)[1]; }

    inline Scalar& v() { return (*this)[2]; }
    inline const Scalar& v() const { return (*this)[2]; }

    inline Scalar& a() { return (*this)[3]; }
    inline const Scalar& a() const { return (*this)[3]; }
};


} // namespace Geometry
} // namespace MH

