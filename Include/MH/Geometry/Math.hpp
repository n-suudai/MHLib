
#pragma once


#include "MH/External/Eigen.hpp"
#include "MH/OS/Types.hpp"


namespace MH {
namespace Geometry {


typedef f32                             Radius;
typedef Eigen::Matrix4f                 Matrix4x4;
typedef Eigen::Matrix3f                 Matrix3x3;
typedef Eigen::Matrix2f                 Matrix2x2;
typedef Eigen::Vector4f                 Vector4;
typedef Eigen::Vector3f                 Vector3;
typedef Eigen::Vector2f                 Vector2;
typedef Eigen::DiagonalMatrix<f32, 3>   Scaling3;
typedef Eigen::DiagonalMatrix<f32, 2>   Scaling2;
typedef Eigen::Affine3f                 Affine3;
typedef Eigen::Affine2f                 Affine2;
typedef Eigen::Translation3f            Translation3;
typedef Eigen::Translation2f            Translation2;
typedef Eigen::Quaternionf              Quaternion;
typedef Eigen::Rotation2Df              Rotation2;


static constexpr f32 PIH            = 1.5707963267948966192313216916398f;
static constexpr f32 PI             = 3.1415926535897932384626433832795f;
static constexpr f32 PI2            = 6.2831853071795864769252867665590f;
static constexpr f32 DIV_PI         = 0.31830988618379067153776752674503f;
static constexpr f32 DIV_PI2        = 0.15915494309189533576888376337251f;
static constexpr f32 F32_EPSILON    = 1.192093e-07f;


template<typename T>
inline T& Lerp(T& out, T const& value1, T const& value2, f32 t)
{
    out = value1 + (value2 - value1) * t;
    return out;
}


inline f32 DegreeToRadian(f32 degree)
{
    return degree * 0.01745329251994329576923690768489f;
}


inline f32 RadianToDegree(f32 radian)
{
    return radian * 57.295779513082320876798154814105f;
}


inline f32 Clamp(f32 value, f32 min, f32 max)
{
    if (value < min) { return min; }
    if (value > max) { return max; }
    return value;
}


inline f32 Min(f32 value1, f32 value2)
{
    return value1 > value2 ? value2 : value1;
}


inline f32 Max(f32 value1, f32 value2)
{
    return value1 < value2 ? value2 : value1;
}


inline f32 Saturate(f32 value)
{
    if (value > 1.0f) { return 1.0f; }
    if (value < 0.0f) { return 0.0f; }
    return value;
}


inline f32 Smoothstep(f32 edge0, f32 edge1, f32 x)
{
    x = Saturate((x - edge0) / (edge1 - edge0));
    return x * x * (3.0f - 2.0f * x);
}


inline bool NearEqual(f32 S1, f32 S2, f32 epsilon = F32_EPSILON)
{
    float Delta = S1 - S2;
    return (fabsf(Delta) <= epsilon);
}


inline f32 Cos(f32 x)
{
    return std::cos(x);
}


inline f32 Sin(f32 x)
{
    return std::sin(x);
}


inline void SinCos(f32* pSin, f32* pCos, f32 value)
{
    assert(pSin);
    assert(pCos);

    // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
    f32 quotient = DIV_PI2 * value;
    if (value >= 0.0f)
    {
        quotient = (f32)((int)(quotient + 0.5f));
    }
    else
    {
        quotient = (f32)((int)(quotient - 0.5f));
    }
    f32 y = value - PI2 * quotient;

    // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
    f32 sign;
    if (y > PIH)
    {
        y = PI - y;
        sign = -1.0f;
    }
    else if (y < -PIH)
    {
        y = -PI - y;
        sign = -1.0f;
    }
    else
    {
        sign = +1.0f;
    }

    f32 y2 = y * y;

    // 11-degree minimax approximation
    *pSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

    // 10-degree minimax approximation
    f32 p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
    *pCos = sign * p;
}


inline void SinCos(f32* pSin, f32* pCos, f32 value, f32 scale)
{
    SinCos(pSin, pCos, value);
    *pSin *= scale;
    *pCos *= scale;
}


inline Matrix4x4& Translate(Matrix4x4& mat, Matrix4x4 const& m, Vector3 const& v)
{
    mat = m;
    mat.col(3) = m.col(0) * v(0) + m.col(1) * v(1) + m.col(2) * v(2) + m.col(3);
    return mat;
}


inline Matrix4x4& Rotate(Matrix4x4& mat, Matrix4x4 const& m, f32 angle, Vector3 const& v)
{
    f32 s, c;
    SinCos(&s, &c, angle);

    Vector3 axis(v.normalized());
    Vector3 temp((1.0f - c) * axis);

    Matrix4x4 Rotate;
    Rotate(0, 0) = c + temp(0) * axis(0);
    Rotate(0, 1) = temp(0) * axis(1) + s * axis(2);
    Rotate(0, 2) = temp(0) * axis(2) - s * axis(1);

    Rotate(1, 0) = temp(1) * axis(0) - s * axis(2);
    Rotate(1, 1) = c + temp(1) * axis(1);
    Rotate(1, 2) = temp(1) * axis(2) + s * axis(0);

    Rotate(2, 0) = temp(2) * axis(0) + s * axis(1);
    Rotate(2, 1) = temp(2) * axis(1) - s * axis(0);
    Rotate(2, 2) = c + temp(2) * axis(2);

    mat.col(0) = m.col(0) * Rotate(0, 0) + m.col(1) * Rotate(0, 1) + m.col(2) * Rotate(0, 2);
    mat.col(1) = m.col(0) * Rotate(1, 0) + m.col(1) * Rotate(1, 1) + m.col(2) * Rotate(1, 2);
    mat.col(2) = m.col(0) * Rotate(2, 0) + m.col(1) * Rotate(2, 1) + m.col(2) * Rotate(2, 2);
    mat.col(3) = m.col(3);
    return mat;
}


inline Matrix4x4& Scale(Matrix4x4& mat, Matrix4x4 const& m, Vector3 const& v)
{
    mat.col(0) = m.col(0) * v(0);
    mat.col(1) = m.col(1) * v(1);
    mat.col(2) = m.col(2) * v(2);
    mat.col(3) = m.col(3);
    return mat;
}


inline Matrix4x4& OrthoLH(Matrix4x4& mat, f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
{
    mat = Matrix4x4::Identity();
    mat(0, 0) = 2.0f / (right - left);
    mat(1, 1) = 2.0f / (top - bottom);
    mat(2, 2) = 2.0f / (zFar - zNear);
    mat(3, 0) = -(right + left) / (right - left);
    mat(3, 1) = -(top + bottom) / (top - bottom);
    mat(3, 2) = -(zFar + zNear) / (zFar - zNear);
    return mat;
}


inline Matrix4x4& OrthoRH(Matrix4x4& mat, f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
{
    mat = Matrix4x4::Identity();
    mat(0, 0) = 2.0f / (right - left);
    mat(1, 1) = 2.0f / (top - bottom);
    mat(2, 2) = -2.0f / (zFar - zNear);
    mat(3, 0) = -(right + left) / (right - left);
    mat(3, 1) = -(top + bottom) / (top - bottom);
    mat(3, 2) = -(zFar + zNear) / (zFar - zNear);
    return mat;
}


inline Matrix4x4& FrustumLH(Matrix4x4& mat, f32 left, f32 right, f32 bottom, f32 top, f32 nearVal, f32 farVal)
{
    mat = Matrix4x4::Zero();
    mat(0, 0) = (2.0f * nearVal) / (right - left);
    mat(1, 1) = (2.0f * nearVal) / (top - bottom);
    mat(2, 0) = (right + left) / (right - left);
    mat(2, 1) = (top + bottom) / (top - bottom);
    mat(2, 2) = (farVal + nearVal) / (farVal - nearVal);
    mat(2, 3) = 1.0f;
    mat(3, 2) = -(2.0f * farVal * nearVal) / (farVal - nearVal);
    return mat;
}


inline Matrix4x4& FrustumRH(Matrix4x4& mat, f32 left, f32 right, f32 bottom, f32 top, f32 nearVal, f32 farVal)
{
    mat = Matrix4x4::Zero();
    mat(0, 0) = (2.0f * nearVal) / (right - left);
    mat(1, 1) = (2.0f * nearVal) / (top - bottom);
    mat(2, 0) = (right + left) / (right - left);
    mat(2, 1) = (top + bottom) / (top - bottom);
    mat(2, 2) = -(farVal + nearVal) / (farVal - nearVal);
    mat(2, 3) = -1.0f;
    mat(3, 2) = -(2.0f * farVal * nearVal) / (farVal - nearVal);
    return mat;
}


inline Matrix4x4& PerspectiveFovLH(Matrix4x4& mat, f32 fov, f32 width, f32 height, f32 zNear, f32 zFar)
{
    assert(width > 0.0f);
    assert(height > 0.0f);
    assert(fov > 0.0f);

    f32 s, c;
    SinCos(&s, &c, 0.5f * fov);
    f32 const h = c / s;
    f32 const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

    mat = Matrix4x4::Zero();
    mat(0, 0) = w;
    mat(1, 1) = h;
    mat(2, 2) = (zFar + zNear) / (zFar - zNear);
    mat(2, 3) = 1.0f;
    mat(3, 2) = -(2.0f * zFar * zNear) / (zFar - zNear);
    return mat;
}


inline Matrix4x4& PerspectiveFovRH(Matrix4x4& mat, f32 fov, f32 width, f32 height, f32 zNear, f32 zFar)
{
    assert(width > 0.0f);
    assert(height > 0.0f);
    assert(fov > 0.0f);

    f32 s, c;
    SinCos(&s, &c, 0.5f * fov);
    f32 const h = c / s;
    f32 const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

    mat = Matrix4x4::Zero();
    mat(0, 0) = w;
    mat(1, 1) = h;
    mat(2, 2) = -(zFar + zNear) / (zFar - zNear);
    mat(2, 3) = -1.0f;
    mat(3, 2) = -(2.0f * zFar * zNear) / (zFar - zNear);
    return mat;
}


inline Matrix4x4& LookAtLH(Matrix4x4& mat, Vector3 const& eye, Vector3 const& center, Vector3 const& up)
{
    Vector3 const f((center - eye).normalized());
    Vector3 const s(up.cross(f).normalized());
    Vector3 const u(f.cross(s));

    mat = Matrix4x4::Identity();
    mat(0, 0) = s.x();
    mat(1, 0) = s.y();
    mat(2, 0) = s.z();
    mat(0, 1) = u.x();
    mat(1, 1) = u.y();
    mat(2, 1) = u.z();
    mat(0, 2) = f.x();
    mat(1, 2) = f.y();
    mat(2, 2) = f.z();
    mat(3, 0) = -s.dot(eye);
    mat(3, 1) = -u.dot(eye);
    mat(3, 2) = -f.dot(eye);
    return mat;
}


inline Matrix4x4& LookAtRH(Matrix4x4& mat, Vector3 const& eye, Vector3 const& center, Vector3 const& up)
{
    Vector3 const f((center - eye).normalized());
    Vector3 const s(f.cross(up).normalized());
    Vector3 const u(s.cross(f));

    mat = Matrix4x4::Identity();
    mat(0, 0) = s.x();
    mat(1, 0) = s.y();
    mat(2, 0) = s.z();
    mat(0, 1) = u.x();
    mat(1, 1) = u.y();
    mat(2, 1) = u.z();
    mat(0, 2) = -f.x();
    mat(1, 2) = -f.y();
    mat(2, 2) = -f.z();
    mat(3, 0) = -s.dot(eye);
    mat(3, 1) = -u.dot(eye);
    mat(3, 2) = f.dot(eye);
    return mat;
}


} // namespace Geometry
} // namespace MH

