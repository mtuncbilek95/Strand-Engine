// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#pragma region "STL Includes"

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <array>
#include <fstream>

#pragma endregion "STL Includes"

#pragma region "DirectX includes"

#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <psapi.h>

using namespace DirectX;

template<typename T>
using DXHEAP = Microsoft::WRL::ComPtr<T>;

#pragma endregion "DirectX includes"

// @brief This macro is used to define the engine API
#define STRAND_API __declspec(dllexport)

#define FloatMax 3.402823466e+38f
