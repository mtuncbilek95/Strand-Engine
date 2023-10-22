// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#include <DirectXMath.h>

/*
 * When the time comes, there will be a custom library.
 */

namespace Strand
{

using namespace DirectX;

using Vector2f = DirectX::XMFLOAT2;
using Vector3f = DirectX::XMFLOAT3;
using Vector4f = DirectX::XMFLOAT4;

using Vector2i = DirectX::XMINT2;
using Vector3i = DirectX::XMINT3;
using Vector4i = DirectX::XMINT4;

using Vector2u = DirectX::XMUINT2;
using Vector3u = DirectX::XMUINT3;
using Vector4u = DirectX::XMUINT4;

using Matrix3x3f = DirectX::XMFLOAT3X3;
using Matrix4x4f = DirectX::XMMATRIX;
using Quaternionf = DirectX::XMFLOAT4;

constexpr float Pi = 3.14159265358979323846f;
constexpr float FloatMax = FLT_MAX;
constexpr float FloatMin = FLT_MIN;

constexpr float Epsilon = 0.00001f;

constexpr float ToRadians(float degrees)
{
    return degrees * (Pi / 180.0f);
}

constexpr float ToDegrees(float radians)
{
    return radians * (180.0f / Pi);
}

constexpr float Clamp(float value, float min, float max)
{
    return value < min ? min : value > max ? max : value;
}

constexpr float Lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

constexpr float InverseLerp(float a, float b, float value)
{
    return (value - a) / (b - a);
}

constexpr float SmoothStep(float a, float b, float t)
{
    float x = Clamp(InverseLerp(a, b, t), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

constexpr float SmoothStep2(float a, float b, float t)
{
    float x = Clamp(InverseLerp(a, b, t), 0.0f, 1.0f);
    return x * x * x * (x * (x * 6 - 15) + 10);
}

constexpr float SmoothStep3(float a, float b, float t)
{
    float x = Clamp(InverseLerp(a, b, t), 0.0f, 1.0f);
    return x * x * x * x * (x * (x * (x * -20 + 70) - 84) + 35);
}

constexpr float SmoothStep4(float a, float b, float t)
{
    float x = Clamp(InverseLerp(a, b, t), 0.0f, 1.0f);
    return x * x * x * x * x * (x * (x * (x * (x * 70 - 315) + 540) - 420) + 126);
}

constexpr Matrix4x4f TransposeMatrix(const Matrix4x4f matrix)
{
    return XMMatrixTranspose(matrix);
}

constexpr Matrix4x4f InverseMatrix(const Matrix4x4f matrix)
{
    return XMMatrixInverse(nullptr, matrix);
}

Matrix4x4f IdentityMatrix()
{
    return XMMatrixIdentity();
}

Matrix4x4f TranslationMatrix(const Vector3f& translation)
{
    return XMMatrixTranslation(translation.x, translation.y, translation.z);
}

Matrix4x4f RotationMatrix(const Vector3f& rotation)
{
    return XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
}

Matrix4x4f ScaleMatrix(const Vector3f& scale)
{
    return XMMatrixScaling(scale.x, scale.y, scale.z);
}

Matrix4x4f LookAtMatrix(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
{
    return XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

Matrix4x4f PerspectiveMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    return XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
}

Matrix4x4f OrthographicMatrix(float width, float height, float nearPlane, float farPlane)
{
    return XMMatrixOrthographicLH(width, height, nearPlane, farPlane);
}

Matrix4x4f OrthographicMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    return XMMatrixOrthographicOffCenterLH(left, right, bottom, top, nearPlane, farPlane);
}

Matrix4x4f operator*(const Matrix4x4f& lhs, const Matrix4x4f& rhs)
{
    return XMMatrixMultiply(lhs, rhs);
}

Vector3f operator*(const Vector3f& lhs, const Matrix4x4f& rhs)
{
    Vector4f result;
    XMStoreFloat4(&result, XMVector3Transform(XMLoadFloat3(&lhs), rhs));
    return {result.x, result.y, result.z};
}

Vector4f operator*(const Vector4f& lhs, const Matrix4x4f& rhs)
{
    Vector4f result;
    XMStoreFloat4(&result, XMVector4Transform(XMLoadFloat4(&lhs), rhs));
    return result;
}

Vector3f operator*(const Matrix4x4f& lhs, const Vector3f& rhs)
{
    Vector4f result;
    XMStoreFloat4(&result, XMVector3Transform(XMLoadFloat3(&rhs), lhs));
    return {result.x, result.y, result.z};
}

Vector4f operator*(const Matrix4x4f& lhs, const Vector4f& rhs)
{
    Vector4f result;
    XMStoreFloat4(&result, XMVector4Transform(XMLoadFloat4(&rhs), lhs));
    return result;
}

} // Strand
