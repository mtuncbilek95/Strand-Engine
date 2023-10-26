// Copyright (C) 2023 Metehan Tuncbilek - All Rights Reserved
#pragma once

#if defined(__MSC_VERSION__) || defined(_MSC_VER)
#define NODISCARD_INLINE [[nodiscard]] __forceinline
#define NODISCARD_MSG(_Msg) [[nodiscard(_Msg)]]
#elif defined(__GNUC__) || defined(__GNUG__)
#define NODISCARD_INLINE __attribute__((warn_unused_result)) __attribute__((always_inline))
#define _NODISCARD_MSG(_Msg) [[nodiscard(_Msg)]]
#else
#define NODISCARD_INLINE __attribute__((warn_unused_result)) inline
#define _NODISCARD_MSG(_Msg) [[nodiscard(_Msg)]]
#endif

#define NODISCARD NODISCARD_MSG("This function or variable should be used, otherwise it is useless to declare it.")

#define NODISCARD_SMART_PTR_ALLOC                                                                               \
    NODISCARD_MSG("This function constructs an object wrapped by a smart pointer and has no other effects; "    \
                   "it is not useful to call this function and discard the return value.")

#define NODISCARD_SMART_PTR_GET \
    NODISCARD_MSG("This function returns a pointer to an object wrapped by a smart pointer; "                   \
                   "it is not useful to call this function and discard the return value.")

#define NODISCARD_SMART_PTR_GET_CONST \
    NODISCARD_MSG("This function returns a pointer to a const object wrapped by a smart pointer; "              \
                   "it is not useful to call this function and discard the return value.")


namespace Strand_Std
{

template<class T, T value>
struct EXPORT_STRAND_STD IntegralConstant
{
    static constexpr T _Value = value;

    using _ValueType = T;
    using type = IntegralConstant;

    constexpr operator _ValueType() const noexcept { return _Value; }

    NODISCARD constexpr _ValueType operator()() const noexcept { return _Value; }
};

template<bool value> using BoolConstant = IntegralConstant<bool, value>;

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

template<bool test, class T = void>
struct EnableIf {};

template<class T>
struct EnableIf<true, T> { using _Type = T; };

template<bool _Test, class _Ty1, class _Ty2>
struct Conditional
{
    using _Type = _Ty1;
};

template<class _Ty1, class _Ty2>
struct Conditional<false, _Ty1, _Ty2>
{
    using _Type = _Ty2;
};

template<class> INLINE constexpr bool IsArray_V = false;

template<class _Ty, size_t _Nx> INLINE constexpr bool IsArray_V<_Ty[_Nx]> = true;

template<class _Ty> INLINE constexpr bool IsArray_V<_Ty[]> = true;

template<class _Ty>
struct IsArray : BoolConstant<IsArray_V<_Ty>> {};

template<class> INLINE constexpr bool IsBoundedArray_V = false;

template<class _Ty, size_t _Nx> INLINE constexpr bool IsBoundedArray_V<_Ty[_Nx]> = true;

template<class _Ty>
struct IsBoundedArray : BoolConstant<IsBoundedArray_V<_Ty>> {};

template<class> INLINE constexpr bool IsUnboundedArray_V = false;

template<class _Ty> INLINE constexpr bool IsUnboundedArray_V<_Ty[]> = true;

template<class _Ty>
struct IsUnboundedArray : BoolConstant<IsUnboundedArray_V<_Ty>> {};

} // Strand_Std
