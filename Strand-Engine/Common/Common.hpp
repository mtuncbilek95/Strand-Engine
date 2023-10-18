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
#include <memory>

template<typename T>
using ArrayList = std::vector<T>;
template<typename T, size_t N>
using Array = std::array<T, N>;
using String = std::string;
template<typename T>
using OwnedHeap = std::unique_ptr<T>;
template<typename T>
using SharedHeap = std::shared_ptr<T>;
template<typename T>
using WeakHeap = std::weak_ptr<T>;
template<typename T>
using Ref = std::reference_wrapper<T>;

#pragma endregion "STL Includes"

#pragma region "DirectX includes"

#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace DirectX;

template<typename T>
using DXHEAP = Microsoft::WRL::ComPtr<T>;

#pragma endregion "DirectX includes"

// @brief This macro is used to define the engine API
#define STRAND_API __declspec(dllexport)

#define FloatMax 3.402823466e+38f
