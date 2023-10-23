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

} // Strand
