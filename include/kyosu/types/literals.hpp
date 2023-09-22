//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu
{
  inline namespace literals
  {
    inline constexpr kyosu::complex_t<double> operator""_i(long double d) noexcept
    {
      return kyosu::complex_t<double> {0.0, static_cast<double>(d)};
    }

    inline constexpr kyosu::complex_t<double> operator""_i(unsigned long long d) noexcept
    {
      return kyosu::complex_t<double> {0.0, static_cast<double>(d)};
    }

    inline constexpr kyosu::complex_t<float> operator""_if(long double d) noexcept
    {
      return kyosu::complex_t<float> {0.0f, static_cast<float>(d)};
    }

    inline constexpr kyosu::complex_t<float> operator""_if(unsigned long long  d) noexcept
    {
      return kyosu::complex_t<float> {0.0f, static_cast<float>(d)};
    }

    inline constexpr kyosu::quaternion_t<double> operator""_j(long double d) noexcept
    {
      return kyosu::quaternion_t<double> {0.0, 0.0, static_cast<double>(d), 0.0};
    }

    inline constexpr kyosu::quaternion_t<double> operator""_j(unsigned long long d) noexcept
    {
      return kyosu::quaternion_t<double> {0.0, 0.0, static_cast<double>(d), 0.0};
    }

    inline constexpr kyosu::quaternion_t<float> operator""_jf(long double d) noexcept
    {
      return kyosu::quaternion_t<float> {0.0f, 0.0, static_cast<float>(d), 0.0};
    }

    inline constexpr kyosu::quaternion_t<float> operator""_jf(unsigned long long  d) noexcept
    {
      return kyosu::quaternion_t<float> {0.0f, 0.0, static_cast<float>(d), 0.0};
    }

    inline constexpr kyosu::quaternion_t<double> operator""_k(long double d) noexcept
    {
      return kyosu::quaternion_t<double> {0.0, 0.0, 0.0, static_cast<double>(d)};
    }

    inline constexpr kyosu::quaternion_t<double> operator""_k(unsigned long long d) noexcept
    {
      return kyosu::quaternion_t<double> {0.0, 0.0, 0.0, static_cast<double>(d)};
    }

    inline constexpr kyosu::quaternion_t<float> operator""_kf(long double d) noexcept
    {
      return kyosu::quaternion_t<float> {0.0f, 0., 0.00, static_cast<float>(d)};
    }

    inline constexpr kyosu::quaternion_t<float> operator""_kf(unsigned long long  d) noexcept
    {
      return kyosu::quaternion_t<float> {0.0f, 0., 0.00, static_cast<float>(d)};
    }
  }
}
