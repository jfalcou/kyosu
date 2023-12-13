//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

namespace kyosu::_
{
  /////////////////////////////////
  // contains implementations of
  // airy_ai
  // airy_bi
  // airy
  /////////////////////////////////
  // utilities
  // zet
  // ai
  // bi
  // aibi
  /////////////////////////////////
  // implementation is done using j and y functions

  //===-------------------------------------------------------------------------------------------
  // zet
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto zet(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
     auto sqz = sqrt(z);
//    auto zeta = 2*sqz*z/3;
     auto zeta = (pow(z, u_t(1.5))*2)/3;
    return kumi::tuple{sqz/eve::sqrt_3(as(z)), zeta};
  }

  //===-------------------------------------------------------------------------------------------
  // ai
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto ai(Z z) noexcept
  {

    using u_t = eve::underlying_type_t<Z>;
    auto [sqzo3, zeta] = zet(z);
    auto r = eve::inv_pi(as(z))*sqzo3*cyl_bessel_k(eve::third(as<u_t>()), zeta);
    return r;
//    return if_else(eve::is_ltz(arg(z)), -r, r);
//     return sqzo3*(cyl_bessel_i(eve::third(as<u_t>()), zeta)
//                   +cyl_bessel_i(-eve::third(as<u_t>()), zeta));
  }

  //===-------------------------------------------------------------------------------------------
  // bi
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto bi(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto [sqzo3, zeta] = zet(z);
//     std::cout << "z" << z << " sqzo3 "<< sqzo3 << " zeta "<< zeta << std::endl;
//     std::cout << "third " << eve::third(as<u_t>())  << std::endl;
//     std::cout << "cyl_bessel_i(eve::third(as<u_t>()), zeta) " << cyl_bessel_i(eve::third(as<u_t>()), zeta) << std::endl;
//     std::cout << "cyl_bessel_i(-eve::third(as<u_t>()), zeta) " << cyl_bessel_i(-eve::third(as<u_t>()), zeta) << std::endl;
    return sqzo3*(cyl_bessel_i(-eve::third(as<u_t>()), zeta)
                  -cyl_bessel_i(eve::third(as<u_t>()), zeta));
  }

  //===-------------------------------------------------------------------------------------------
  // aibi
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto aibi(Z z) noexcept
  {
    using u_t = eve::underlying_type_t<Z>;
    auto [sqzo3, zeta] = zet(z);
    auto ip = cyl_bessel_i(eve::third(as<u_t>()), zeta);
    auto im = cyl_bessel_i(-eve::third(as<u_t>()), zeta);

    return kumi::tuple{ invpi(as<u_t>())*sqzo3*(im-ip),  sqzo3*(ip+im)};
  }

  //===-------------------------------------------------------------------------------------------
  //  airy_ai
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::airy_ai>, Z z) noexcept
  {
    if constexpr(kyosu::concepts::complex<Z> )
    {
      return ai(z);
    }
    else
    {
      return cayley_extend(airy_ai, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  airy_bi
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::airy_bi>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return bi(z);
    }
    else
    {
      return cayley_extend(airy_bi, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  airy
  //===-------------------------------------------------------------------------------------------
  template<typename Z> KYOSU_FORCEINLINE
  auto dispatch(eve::tag_of<kyosu::airy>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      return aibi(z);
    }
    else
    {
      return cayley_extend2(airy, z);
    }
  }
}
