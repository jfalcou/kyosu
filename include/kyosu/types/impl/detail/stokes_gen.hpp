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

  // These routines are not used
  // They have served to generate the p and q polynomials of
  // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
  //  treatise on Bessel functions and their applications to
  //  physics, 1895.
  // They can serve if we implement bessel for more accurate type in the future


  template < size_t N, typename T>
  auto stokes_gen0() noexcept
  {
    // once p and tabulated and given  the adapted value of n. considering p and q as
    // the coefficients of two polynomial in ascending power order. For large z (abs(z) > 12, real(z) > 0)
    // P(z) = p(rec(z*z)) and Q(z) = q(rec(z*z))/z
    // J0(z) = (c*(P-Q) + s*(P+Q))/(kyosu::sqrt(z*pi));
    // s = sin(z) and c = cos(z)
    std::array<T, N> p, q;
    auto p[0] = complex(eve::one((eve::as<T>())));
    auto q[0] = p[0]/8;
    for ( size_t m=1; m<N; ++m )
    {
      T pim = T(4*m-3)*T(4*m-3)*T(4*m-1)*T(4*m-1) / ( T(2*m-1)*T(128*m) );
      p[m] = -p[m-1]*pim;
      T xim = T(4*m-1)*T(4*m-1)*T(4*m+1)*T(4*m+1) / ( T(2*m+1)*T(128*m) );
      q[m] = -q[m-1]*xim;
    }
    return std::pair{p, q};
  }

  template < size_t N, typename T>
  auto stokes_gen1() noexcept
  {
    // once p and tabulated and  given the adapted value of n. considering p and q as
    // the coefficients of two polynomial in ascending power order. For large z (abs(z) > 12, real(z) > 0)
    // P(z) = p(rec(z*z)) and Q(z) = q(rec(z*z))/z
    // J1(z) = (s*(P-Q) - c*(P+Q))/(kyosu::sqrt(z*pi));
    // s = sin(z) and c = cos(z)
    std::array<T, N> p, q;
    auto p[0] = complex(eve::one((eve::as<T>())));
    auto q[0] = -3*p[0]/8;
    for ( size_t m=1; m<N; ++m )
    {
      auto twom = m+m;
      auto fourm = twom+twom;
      T pim = (4-sqr(fourm-3))*(4-sqr(fourm-1))/((twom-1)*128*m);
      p[m] = -p[m-1]*pim;
      T xim =  (sqr(fourm-1)-4)*(sqr(fourm+1)-4)/((twom+1)*128*m);
      q[m] = -q[m-1]*xim;
    }
    return std::pair{p, q};
  }
}
