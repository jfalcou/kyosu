//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <kyosu/types/impl/detail/bessel_utils2.hpp>

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_jn
  //===-------------------------------------------------------------------------------------------
  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_jn>, N nn, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      if ( is_eqz(nn) )
      {
        return cyl_bessel_j0(z);
      }
      else if (nn == 1)
      {
        return cyl_bessel_j1(z);
      }
      else if ( nn == -1 )
      {
        return -cyl_bessel_j1(z);
      }
      else
      {
        using e_t = as_real_type_t<Z>;
        using u_t = eve::underlying_type_t<e_t>;
        auto n = u_t(eve::abs(nn));
        auto az = kyosu::abs(z);

        auto forward = [n](auto z){
          auto b0 = cyl_bessel_j0(z);
          auto b1 = cyl_bessel_j1(z);
          Z bn;
          auto rz = rec(z);
          for ( int k=1; k<n; ++k)
          {
            bn = 2*k*b1*rz-b0;
            b0 = b1;
            b1 = bn;
          }
          real(bn) = eve::if_else(is_pure(z), eve::zero, real(bn));
          return bn;
        };

        auto backward = [az, n](auto z){
          auto m1 = ini_for_br_1(az, e_t(200));
          auto m2 = ini_for_br_2(n, az, e_t(15));
          auto m = eve::if_else( m1 >= n && eve::is_not_nan(m2), m2, m1);
          auto cf2 = Z(0);
          auto cf1 = complex(eve::sqrtsmallestposval(eve::as< e_t>()));
          Z cf(cf2);
          Z bn(cf);
          auto k = m;
          auto kgez = eve::is_gez(k);
          while (eve::any(kgez))
          {
            cf  = kyosu::if_else(kgez,  2*inc(k)*cf1*rec(z)-cf2, cf);
            bn  = kyosu::if_else ( k == n, cf, bn);
            cf2 = kyosu::if_else(kgez, cf1, cf2);
            cf1 = kyosu::if_else(kgez, cf, cf1);
            k = dec(k);
            kgez = eve::is_gez(k);
          }
          auto j0 = cyl_bessel_j0(z);
          auto j1 = cyl_bessel_j1(z);
          bn *= eve::if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

          return bn;
        };

        auto srz = eve::signnz(real(z));
        z *= srz;

        auto r = kyosu::if_else(is_eqz(az), Z(0), eve::nan(eve::as(az)));
        auto notdone = kyosu::is_nan(r);
        if( eve::any(notdone) )
        {
          notdone = next_interval(forward, notdone, 4*n < az, r, z);
          if( eve::any(notdone) )
          {
            last_interval(backward, notdone, r, z);
          }
        }
        auto sgnaltern = [n](auto x){return eve::if_else(eve::is_ltz(x), eve::one, eve::sign_alternate(n));};
        r = sgnaltern(srz)*sgnaltern(n)*r;
        return nn < 0 ? r*eve::sign_alternate(u_t(nn)) : r;
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_jn, nn, z);
    }
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j0>, Z z) noexcept
  {
    return sinc(z);
  }

  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto rz = rec(z);
      return if_else(kyosu::abs(z) < eve::eps(eve::as(real(z)))
                    , eve::zero
                    , (sinc(z)-cos(z))*rz
                    );
    }
    else
    {
      return cayley_extend(sph_bessel_j0, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::sph_bessel_jn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using u_t = eve::underlying_type_t<Z>;
      auto bd = [z](int n){
        auto st = eve::abs(eve::sin(eve::abs(arg(z))));
        auto r  = kyosu::abs(z);
        auto m = eve::maximum(eve::ceil((u_t(1.83)+u_t(4.1)*eve::pow(st, u_t(0.33)))*
                                        eve::pow(r, (u_t(0.91)-u_t(0.43)*eve::pow(st, u_t(0.36))))+9*(1-eve::sqrt(st))));
        auto nn = (eve::any(is_real(z))) ? n+5 : n;
        return eve::max(nn, int(inc(m)));
      };

      auto j0 = kyosu::sph_bessel_j0(z);
      if (n == 0) return j0;
      auto j1 = kyosu::sph_bessel_j1(z);
      if (n == 1) return j1;

      auto rz = kyosu::rec(z);
      auto nn = bd(n);
      Z jnext(kyosu::complex(u_t(0)));
      Z j(kyosu::complex(eve::sqrtsmallestposval(eve::as<u_t>())));
      auto init = j;
      auto jcur = jnext;
      auto res = j;
      for(int i=nn-1; i > 0 ; --i)
      {
        jcur = (2*i+1)*rz*j-jnext;
        if(i == n) res = j;
        jnext = j;
        j = jcur;
      }
      auto j0ltj1 = kyosu::abs(j0) <= kyosu::abs(j1);
      auto scalej0 = (j0/jcur);
      auto scalej1 = (j1/jnext);
      res *= if_else(j0ltj1, scalej0, scalej1);
      return if_else(is_eqz(z), eve::zero, res);
    }
    else
    {
      return cayley_extend_rev(sph_bessel_jn, n, z);
    }
  }

}
