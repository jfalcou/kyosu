//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
namespace kyosu::_
{

  /////////////////////////////////
  // contains implementations of
  // sph_bessel_i0
  // sph_bessel_i1
  // sph_bessel_k0
  // sph_bessel_k1
  // sph_bessel_ikn
  /////////////////////////////////
  // utilities
  // sb_i1_0
  // sb_i1_1
  // sb_i2_0
  // sb_i2_1
  // sb_k0
  // sb_k1
  // sb_ikn
  ////////////////////////////////

  template<typename T, eve::integral_scalar_value N>
  auto riton(N n){
    n = n & N(3);
    if (n == 0) return complex(eve::one(eve::as<T>()));
    else if (n == 1) return  complex(eve::zero(eve::as<T>()), eve::mone(eve::as<T>()));
    else if (n == 2) return complex(eve::mone(eve::as<T>()));
    else return complex(eve::zero(eve::as<T>()), eve::one(eve::as<T>()));
  };

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_i1_0(Z z) noexcept
  {
    return sinhc(z);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_i1_1(Z z) noexcept
  {
    auto [sh, ch] = sinhcosh(z);
    auto rz = rec(z);
    return fnma(sh, rz, ch)*rz;
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_i2n(N n, Z z) noexcept
  {
    using e_t = as_real_type_t<Z>;
    return riton<e_t>(n+1)*sph_bessel_yn(n,muli(z));
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_i2n(N n, Z z, R & sis) noexcept
  {
    using e_t = as_real_type_t<Z>;
    return riton<e_t>(n+1)*sph_bessel_yn(n,muli(z), sis);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_i2_0(Z z) noexcept
  {
    return cosh(z)/z;
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto sb_i2_1(Z z) noexcept
  {
    auto [sh, ch] = sinhcosh(z);
    auto rz = rec(z);
    return eve::fnma(ch, rz, sh)*rz;
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto sb_i1n(N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_type_t<Z>;
      return riton<e_t>(n)*sph_bessel_jn(n,muli(z));
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_i1n(N n, Z z, R & sys) noexcept
  {
    EVE_ASSERT(N(size(sys)) > n, "not enough room in sys");
    using e_t = as_real_type_t<Z>;
    return riton<e_t>(n)*sph_bessel_yn(n,muli(z), sys);
  }

  //===-------------------------------------------------------------------------------------------
  //  sb_kn
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto sb_kn(int n, Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto iton = [](int n){
      if (n%4 == 0) return complex(eve::one(eve::as<u_t>()));
      else if (n%4 == 1) return  complex(eve::zero(eve::as<u_t>()), eve::one(eve::as<u_t>()));
      else if (n%4 == 2) return complex(eve::mone(eve::as<u_t>()));
      else return complex(eve::zero(eve::as<u_t>()), eve::mone(eve::as<u_t>()));
    };
    return -eve::pio_2(eve::as<u_t>())*iton(n)*sph_bessel_h1n(n, complex(-imag(z), real(z)));
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto sb_kn(N n, Z z, R& sks) noexcept
  {
    EVE_ASSERT(N(size(sks)) > n, "not enough room in sks");
    using u_t = eve::underlying_type_t<Z>;
    auto iton = [](int n){
      if (n%4 == 0) return complex(eve::one(eve::as<u_t>()));
      else if (n%4 == 1) return  complex(eve::zero(eve::as<u_t>()), eve::one(eve::as<u_t>()));
      else if (n%4 == 2) return complex(eve::mone(eve::as<u_t>()));
      else return complex(eve::zero(eve::as<u_t>()), eve::mone(eve::as<u_t>()));
    };
    return -eve::pio_2(eve::as<u_t>())*iton(n)*sph_bessel_h1n(n, complex(-imag(z), real(z)), sks);
  }

  template<typename Z, typename R1, typename R2> KYOSU_FORCEINLINE
  auto sb_ikn(int n, Z z, R1& sis, R2& sks) noexcept
  {
    EVE_ASSERT(N(size(sis)) > n, "not enough room in sis");
    EVE_ASSERT(N(size(sks)) > n, "not enough room in sks");
    sb_i1n(n, z, sis);
    sb_kn(n, z, sks);
    return kumi::tuple{sis[n], sks[n]};
  }

  //===-------------------------------------------------------------------------------------------
  //  sb_k0
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto sb_k0(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    return eve::pio_2(eve::as<u_t>())*exp(-z)/z;
  }

  //===-------------------------------------------------------------------------------------------
  //  sb_k1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto sb_k1(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto rz = rec(z);
    return  eve::pio_2(eve::as<u_t>())*exp(-z)*fma(rz, rz, rz);
  }

  ////////////////////////////////////////////////////////////
  // end utilities
  ////////////////////////////////////////////////////////////

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i2_0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i2_0(z);
    }
    else
    {
      return cakley_extend(sph_bessel_i2_0, z);
    }
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i2_1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i2_1(z);
    }
    else
    {
      return cakley_extend(sph_bessel_i2_1, z);
    }
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i1_0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i1_0(z);
    }
    else
    {
      return cayley_extend(sph_bessel_i1_0, z);
    }
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i1_1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i1_1(z);
    }
    else
    {
      return cayley_extend(sph_bessel_i1_1, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i1n>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i1n(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_i1n, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i1n>, N n, Z z, R& sis) noexcept
  {
    return sb_i1n(n, z, sis);
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i2n>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_i2n(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_i2n, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_i2n>, N n, Z z, R& sis) noexcept
  {
    return sb_i2n(n, z, sis);
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_k0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
     return sb_k0(z);
    }
    else
    {
      return cayley_extend(sph_bessel_k0, z);
    }
  }

  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_k1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_k1(z);
    }
    else
    {
      return cayley_extend(sph_bessel_k1, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_kn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return sb_kn(n, z);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_kn, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z, typename R> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_kn>, N n, Z z, R& sks) noexcept
  {
    return sb_kn(n, z, sks);
  }

  template<eve::integral_scalar_value N, typename Z, typename R1,  typename R2> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::sph_bessel_ikn>, N n, Z z, R1& sis, R2& sks) noexcept
  {
      return sb_ikn(n, z, sis, sks);
  }
}
