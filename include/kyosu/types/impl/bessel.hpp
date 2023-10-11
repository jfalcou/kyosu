//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <kyosu/details/cayleyify.hpp>


//////////////////////////////////////////////////////////////////////////////////////////////////
//! This simd implementation of the cylindrical jn functions is inspired from
//! The codes and routines were developed and are updated by
//! <a href="https://www.researchgate.net/profile/Jhonas-de-Sarro">Jhonas O. de Sarro</a> ([@jodesarro]( https://github.com/jodesarro )).
//!
//! We repruce here the copyrith notice
//!
//!MIT License
//!
//!Copyright (c) 2021 Jhonas Olivati de Sarro
//!
//!Permission is hereby granted, free of charge, to any person obtaining a copy
//!of this software and associated documentation files (the "Software"), to deal
//!in the Software without restriction, including without limitation the rights
//!to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//!copies of the Software, and to permit persons to whom the Software is
//!furnished to do so, subject to the following conditions:
//!
//!The above copyright notice and this permission notice shall be included in all
//!copies or substantial portions of the Software.
//!
//!THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//!AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//!LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//!OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//!SOFTWARE.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////

namespace kyosu::_
{

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j0
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j0 = [](auto z)
      {
        // Ascending Series from G. N. Watson 'A treatise on the
        //  theory of Bessel functions', 2ed, Cambridge, 1996,
        //  Chapter II, equation (3); or from Equation 9.1.12 of
        //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
        //  Functions'.
        // good for abs(z) < 12
        auto eps = eve::eps(eve::as<e_t>());
        auto j0 = complex(eve::one((eve::as<e_t>())));
        auto sm = j0;
        auto test = sqr_abs(sm) >= eps*sqr_abs(j0);
        auto  m(eve::one(eve::as<e_t>()));
        auto z2 = - sqr(z);
        while(eve::any(test))
        {
          sm *= z2*e_t(0.25)/sqr(m);
          j0 += sm;
          test = sqr_abs(sm) >= eps*sqr_abs(j0);
          m = inc(m);
        }
        return j0;
      };

      auto semiconvergent_series_cyl_j0 = [saz](auto z)
      {
        auto bound_compute = [saz]()
        {
          auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
          bds = eve::if_else(saz < 35*35, e_t(12), bds);
          return bds;
        };
        // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
        //  treatise on Bessel functions and their applications to
        //  physics, 1895.
        auto Pm = complex(eve::one((eve::as<e_t>())));
        auto Qm = rec(8*z);
        auto P = Pm;
        auto Q = Qm;
        auto bds = bound_compute();
        auto m = eve::one((eve::as<e_t>()));
        auto  bound_not_reached = m <= bds;
        auto z2 = sqr(z);
        while (eve::any(bound_not_reached))
        {
          auto twom = m+m;
          auto fourm = twom+twom;
          auto pim = sqr((fourm-3)*(fourm-1))/((twom-1)*128*m);
          Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
          auto xim =  sqr((fourm-1)*(fourm+1))/((twom+1)*128*m);
          Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);

          P += Pm;
          Q += Qm;
          m = inc(m);
          bound_not_reached = m <= bds;
        }
        auto [s, c] = kyosu::sincos(z);
        return (c*(P-Q) + s*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
      };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto notdone = eve::true_(eve::as(saz));
      auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j0, notdone, saz <= as_real_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j0, notdone, r, z);
        }
      }
      return r;
    }
    else
    {
      return cayley_extend(cyl_bessel_j0, z);
    }
  }

  //===-------------------------------------------------------------------------------------------
  //  cyl_bessel_j1
  //===-------------------------------------------------------------------------------------------
  template<typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_j1>, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      using e_t = as_real_t<Z>;
      auto saz = kyosu::sqr_abs(z);

      auto ascending_series_cyl_j1 = [](auto z){
        // Ascending Series from G. N. Watson 'A treatise on the
        //  theory of Bessel functions', 2ed, Cambridge, 1996,
        //  Chapter II, equation (3); or from Equation 9.1.12 of
        //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
        //  Functions'.
        // good for abs(z) < 12
        auto eps = eve::eps(eve::as<e_t>());
        auto j1 = complex(eve::one((eve::as<e_t>())));
        auto sm = j1;
        auto test = sqr_abs(sm) >= eps*sqr_abs(j1);
        auto  m(eve::one(eve::as<e_t>()));
        auto z2 = - sqr(z);
        while(eve::any(test))
        {
          sm *= z2*e_t(0.25)/(m*inc(m));
          j1 += sm;
          test = sqr_abs(sm) >= eps*sqr_abs(j1);
          m = inc(m);
        }
        return j1*eve::half(eve::as<e_t>())*z;
      };

      auto semiconvergent_series_cyl_j1 = [saz](auto z)
        {
          auto bound_compute = [saz]()
          {
            auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
            bds = eve::if_else(saz < 35*35, e_t(12), bds);
            return bds;
          };
          // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
          //  treatise on Bessel functions and their applications to
          //  physics, 1895.
          auto Pm = complex(eve::one((eve::as<e_t>())));
          auto Qm = -e_t(0.375)*rec(z); //-8*rec(3*z);
          auto P = Pm;
          auto Q = Qm;
          auto bds = bound_compute();
          auto m = eve::one((eve::as<e_t>()));
          auto  bound_not_reached = m <= bds;
          auto z2 = sqr(z);
          while (eve::any(bound_not_reached))
          {
            auto twom = m+m;
            auto fourm = twom+twom;
            auto pim = (4-sqr(fourm-3))*(4-sqr(fourm-1))/((twom-1)*128*m);
            Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
            auto xim =  (sqr(fourm-1)-4)*(sqr(fourm+1)-4)/((twom+1)*128*m);
            Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
            P += Pm;
            Q += Qm;
            m = inc(m);
            bound_not_reached = m <= bds;
          }
          auto [s, c] = kyosu::sincos(z);
          return (s*(P-Q)-c*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
      };

      auto rzneg = eve::is_ltz(real(z));
      z = if_else(rzneg, -z, z);

      auto notdone = eve::true_(eve::as(saz));
      auto r = kyosu::if_else(is_eqz(saz), Z(0), eve::nan(eve::as(saz)));
      if( eve::any(notdone) )
      {
        notdone = next_interval(ascending_series_cyl_j1, notdone, saz <= as_real_t<Z>(144), r, z);
        if( eve::any(notdone) )
        {
          last_interval(semiconvergent_series_cyl_j1, notdone, r, z);
        }
      }
      return if_else(rzneg, -r, r);
    }
    else
    {
      return cayley_extend(cyl_bessel_j1, z);
    }
  }

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
        using e_t = as_real_t<Z>;
        using u_t = eve::underlying_type_t<e_t>;
        auto n = u_t(nn);
        auto an = eve::abs(n);
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
          return bn;
        };

        auto minus_log10_cyl_j_at_infinity = []( auto n, auto az ) {
          // Auxiliary function to calculate -log( Jn(x->INF) ).
          return e_t(0.5)*eve::log10(e_t(6.28)*n) - n*eve::log10(e_t(1.36)*az/n);
        };

        auto ini_for_br_1 = [minus_log10_cyl_j_at_infinity](auto az, auto mg)
        {
          // Starting point for backward recurrence
          //  for when |Jn(x)|~10e-mg
          //  using the secant method.
          auto n0 = inc(eve::nearest( e_t(1.1)*az));
          auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - mg;
          auto n1 = n0 + 5;
          auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - mg;
          auto nn = n1 - (n1 - n0)/oneminus(f0/f1);
          auto f = minus_log10_cyl_j_at_infinity(nn, az) - mg;
          auto test = eve::abs(nn - n1) > 1;
          while ( eve::any(test) )
          {
            n0 = n1;
            f0 = f1;
            n1 = nn;
            f1 = f;
            nn = eve::if_else(test, n1 - (n1 - n0)/oneminus(f0/f1), nn);
            f = minus_log10_cyl_j_at_infinity(nn, az) - mg;
            test =  eve::abs(nn - n1) > 1;
          }
          return eve::trunc(nn);
        };

        auto ini_for_br_2 = [minus_log10_cyl_j_at_infinity](auto n, auto az, auto sd){
          // Starting point for backward recurrence
          //  for when Jn(x) has sd significant digits
          //  using the secant method.
          auto hmp = eve::half(eve::as<e_t>())*sd;
          auto ejn = minus_log10_cyl_j_at_infinity(n, az);
          auto t = ejn <= hmp;
          auto obj = eve::if_else(t, sd, hmp+ejn);
          auto n0  = eve::if_else(t, eve::nearest(e_t(1.1)*az), n);
          auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - obj;
          auto n1 = n0 + 5;
          auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - obj;
          auto nn = n1 - (n1-n0)/oneminus(f0/f1);
          auto f = minus_log10_cyl_j_at_infinity(nn, az) - obj;
          auto test = eve::abs(nn - n1) >= 1;
          while ( eve::any(test))
          {
            n0 = n1;
            f0 = f1;
            n1 = nn;
            f1 = f;
            nn = eve::if_else(test, n1 - (n1-n0)/(oneminus(f0/f1)), nn);
            f = minus_log10_cyl_j_at_infinity(nn, az) - obj;
            test = eve::abs(nn - n1) >= 1;
          }
          return eve::trunc(nn + 10);
        };

        auto backward = [az, n, ini_for_br_1, ini_for_br_2](auto z){
          auto m = ini_for_br_1(az, e_t(200));
          m = eve::if_else ( m >= n, ini_for_br_2(n, az, e_t(15)), m);
          auto cf2 = Z(0);
          auto cf1 = Z(eve::sqrtsmallestposval(eve::as< e_t>())); //std::complex<T>(1.0e-100, T(0));
          Z cf(cf2);
          Z bn(cf);
          auto k = m;
          auto kgez = eve::is_gez(k);
          while (eve::any(kgez))
          {
            cf = eve::if_else(kgez,  2*inc(k)*cf1*rec(z)-cf2, cf);
            bn = eve::if_else ( k == n, cf, bn);
            cf2 = cf1;
            cf1 = cf;
            k = dec(k);
            kgez = eve::is_gez(k);
          }
          auto j0 = cyl_bessel_j0(z);
          auto j1 = cyl_bessel_j1(z);
          bn *= eve::if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

          return bn;
        };

        auto srz = eve::sign(real(z));
        z *= srz;

        auto notdone = eve::true_(eve::as(az));
        auto r = kyosu::if_else(is_eqz(az), Z(0), eve::nan(eve::as(az)));
        if( eve::any(notdone) )
        {
          notdone = next_interval(forward, notdone, 8*n < az, r, z);
          if( eve::any(notdone) )
          {
            last_interval(backward, notdone, r, z);
          }
        }
        auto sgnaltern = [n](auto x){return eve::if_else(eve::is_ltz(x), eve::one, eve::sign_alternate(n));};
        return sgnaltern(srz)*sgnaltern(n)*r;
      }
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_jn, nn, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_in>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto iton = [](N n){
        if (n%4 == 0) return Z(1);
        else if (n%4 == 1) return Z(0, 1);
        else if (n%4 == 2) return Z(-1);
        else return  Z(0, -1);
      };
      return iton(n)*cyl_bessel_jn(n,Z(-imag(z), real(z)));
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_in, n, z);
    }
  }

  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_yn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto iton = [](N n){
        if (n%4 == 0) return Z(1);
        else if (n%4 == 1) return Z(0, 1);
        else if (n%4 == 2) return Z(-1);
        else return  Z(0, -1);
      };
      using e_t = eve::underlying_type_t<as_real_t<Z>>;
      auto [s, c] = sinpicospi(e_t(n));
      return (cyl_bessel_jn(n,x)*c-cyl_bessel_jn(-n, x))/s;
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_yn, n, z);
    }
  }


  template<eve::integral_scalar_value N, typename Z>
  auto dispatch(eve::tag_of<kyosu::cyl_bessel_kn>, N n, Z z) noexcept
  {
    if constexpr(concepts::complex<Z> )
    {
      auto iton = [](N n){
        if (n%4 == 0) return Z(1);
        else if (n%4 == 1) return Z(0, 1);
        else if (n%4 == 2) return Z(-1);
        else return  Z(0, -1);
      };
      using e_t = eve::underlying_type_t<as_real_t<Z>>;
      auto s = eve::cscpi(e_t(n));
      return  pio_2(eve::as<e_t>())*(cyl_bessel_in(-n, x)-cyl_bessel_in(n,x))*s;
    }
    else
    {
      return cayley_extend_rev(cyl_bessel_kn, n, z);
    }
  }
}

// SUBROUTINE cbesy(z, fnu, kode, n, cy, nz, ierr)

// ! N.B. Argument CWRK has been removed.

// !***BEGIN PROLOGUE  CBESY
// !***DATE WRITTEN   830501   (YYMMDD)
// !***REVISION DATE  890801, 930101  (YYMMDD)
// !***CATEGORY NO.  B5K
// !***KEYWORDS  Y-BESSEL FUNCTION,BESSEL FUNCTION OF COMPLEX ARGUMENT,
// !             BESSEL FUNCTION OF SECOND KIND
// !***AUTHOR  AMOS, DONALD E., SANDIA NATIONAL LABORATORIES
// !***PURPOSE  TO COMPUTE THE Y-BESSEL FUNCTION OF A COMPLEX ARGUMENT
// !***DESCRIPTION

// !   ON KODE=1, CBESY COMPUTES AN N MEMBER SEQUENCE OF COMPLEX
// !   BESSEL FUNCTIONS CY(I)=Y(FNU+I-1,Z) FOR REAL (dp), NONNEGATIVE
// !   ORDERS FNU+I-1, I=1,...,N AND COMPLEX Z IN THE CUT PLANE
// !   -PI < ARG(Z) <= PI.
// !   ON KODE=2, CBESY RETURNS THE SCALED FUNCTIONS

// !   CY(I)=EXP(-ABS(Y))*Y(FNU+I-1,Z)   I = 1,...,N , Y=AIMAG(Z)

// !   WHICH REMOVE THE EXPONENTIAL GROWTH IN BOTH THE UPPER AND
// !   LOWER HALF PLANES FOR Z TO INFINITY. DEFINITIONS AND NOTATION
// !   ARE FOUND IN THE NBS HANDBOOK OF MATHEMATICAL FUNCTIONS (REF. 1).

// !   INPUT
// !     Z      - Z=CMPLX(X,Y), Z.NE.CMPLX(0.,0.),-PI < ARG(Z) <= PI
// !     FNU    - ORDER OF INITIAL Y FUNCTION, FNU >= 0.0_dp
// !     KODE   - A PARAMETER TO INDICATE THE SCALING OPTION
// !              KODE= 1  RETURNS
// !                       CY(I)=Y(FNU+I-1,Z), I=1,...,N
// !                  = 2  RETURNS
// !                       CY(I)=Y(FNU+I-1,Z)*EXP(-ABS(Y)), I=1,...,N
// !                       WHERE Y=AIMAG(Z)
// !     N      - NUMBER OF MEMBERS OF THE SEQUENCE, N >= 1
// !     CWRK   - A COMPLEX WORK VECTOR OF DIMENSION AT LEAST N

// !   OUTPUT
// !     CY     - A COMPLEX VECTOR WHOSE FIRST N COMPONENTS CONTAIN
// !              VALUES FOR THE SEQUENCE
// !              CY(I)=Y(FNU+I-1,Z)  OR
// !              CY(I)=Y(FNU+I-1,Z)*EXP(-ABS(Y))  I=1,...,N
// !              DEPENDING ON KODE.
// !     NZ     - NZ=0 , A NORMAL RETURN
// !              NZ > 0 , NZ COMPONENTS OF CY SET TO ZERO DUE TO
// !              UNDERFLOW (GENERALLY ON KODE=2)
// !     IERR   - ERROR FLAG
// !              IERR=0, NORMAL RETURN - COMPUTATION COMPLETED
// !              IERR=1, INPUT ERROR   - NO COMPUTATION
// !              IERR=2, OVERFLOW      - NO COMPUTATION, FNU+N-1 IS
// !                      TOO LARGE OR ABS(Z) IS TOO SMALL OR BOTH
// !              IERR=3, ABS(Z) OR FNU+N-1 LARGE - COMPUTATION DONE
// !                      BUT LOSSES OF SIGNIFICANCE BY ARGUMENT REDUCTION
// !                      PRODUCE LESS THAN HALF OF MACHINE ACCURACY
// !              IERR=4, ABS(Z) OR FNU+N-1 TOO LARGE - NO COMPUTATION
// !                      BECAUSE OF COMPLETE LOSSES OF SIGNIFICANCE
// !                      BY ARGUMENT REDUCTION
// !              IERR=5, ERROR              - NO COMPUTATION,
// !                      ALGORITHM TERMINATION CONDITION NOT MET

// !***LONG DESCRIPTION

// !   THE COMPUTATION IS CARRIED OUT IN TERMS OF THE I(FNU,Z) AND
// !   K(FNU,Z) BESSEL FUNCTIONS IN THE RIGHT HALF PLANE BY

// !       Y(FNU,Z) = I*CC*I(FNU,ARG) - (2/PI)*CONJG(CC)*K(FNU,ARG)

// !       Y(FNU,Z) = CONJG(Y(FNU,CONJG(Z)))

// !   FOR AIMAG(Z) >= 0 AND AIMAG(Z) < 0 RESPECTIVELY, WHERE
// !   CC=EXP(I*PI*FNU/2), ARG=Z*EXP(-I*PI/2) AND I**2=-1.

// !   FOR NEGATIVE ORDERS,THE FORMULA

// !       Y(-FNU,Z) = Y(FNU,Z)*COS(PI*FNU) + J(FNU,Z)*SIN(PI*FNU)

// !   CAN BE USED.  HOWEVER,FOR LARGE ORDERS CLOSE TO HALF ODD INTEGERS THE
// !   FUNCTION CHANGES RADICALLY.  WHEN FNU IS A LARGE POSITIVE HALF ODD INTEGER,
// !   THE MAGNITUDE OF Y(-FNU,Z) = J(FNU,Z)*SIN(PI*FNU) IS A LARGE NEGATIVE
// !   POWER OF TEN.  BUT WHEN FNU IS NOT A HALF ODD INTEGER, Y(FNU,Z) DOMINATES
// !   IN MAGNITUDE WITH A LARGE POSITIVE POWER OF TEN AND THE MOST THAT THE
// !   SECOND TERM CAN BE REDUCED IS BY UNIT ROUNDOFF FROM THE COEFFICIENT.
// !   THUS, WIDE CHANGES CAN OCCUR WITHIN UNIT ROUNDOFF OF A LARGE HALF
// !   ODD INTEGER.  HERE, LARGE MEANS FNU > ABS(Z).

// !   IN MOST COMPLEX VARIABLE COMPUTATION, ONE MUST EVALUATE ELEMENTARY
// !   FUNCTIONS.  WHEN THE MAGNITUDE OF Z OR FNU+N-1 IS LARGE, LOSSES OF
// !   SIGNIFICANCE BY ARGUMENT REDUCTION OCCUR.  CONSEQUENTLY, IF EITHER ONE
// !   EXCEEDS U1=SQRT(0.5/UR), THEN LOSSES EXCEEDING HALF PRECISION ARE LIKELY
// !   AND AN ERROR FLAG IERR=3 IS TRIGGERED WHERE UR = EPSILON(0.0_dp) = UNIT
// !   ROUNDOFF.  ALSO IF EITHER IS LARGER THAN U2=0.5/UR, THEN ALL SIGNIFICANCE
// !   IS LOST AND IERR=4.  IN ORDER TO USE THE INT FUNCTION, ARGUMENTS MUST BE
// !   FURTHER RESTRICTED NOT TO EXCEED THE LARGEST MACHINE INTEGER, U3 = HUGE(0).
// !   THUS, THE MAGNITUDE OF Z AND FNU+N-1 IS RESTRICTED BY MIN(U2,U3).
// !   ON 32 BIT MACHINES, U1,U2, AND U3 ARE APPROXIMATELY 2.0E+3, 4.2E+6, 2.1E+9
// !   IN SINGLE PRECISION ARITHMETIC AND 1.3E+8, 1.8D+16, 2.1E+9 IN DOUBLE
// !   PRECISION ARITHMETIC RESPECTIVELY. THIS MAKES U2 AND U3 LIMITING IN
// !   THEIR RESPECTIVE ARITHMETICS.  THIS MEANS THAT ONE CAN EXPECT TO RETAIN,
// !   IN THE WORST CASES ON 32 BIT MACHINES, NO DIGITS IN SINGLE AND ONLY
// !   7 DIGITS IN DOUBLE PRECISION ARITHMETIC.
// !   SIMILAR CONSIDERATIONS HOLD FOR OTHER MACHINES.

// !   THE APPROXIMATE RELATIVE ERROR IN THE MAGNITUDE OF A COMPLEX BESSEL
// !   FUNCTION CAN BE EXPRESSED BY P*10**S WHERE P = MAX(UNIT ROUNDOFF,1.0E-18)
// !   IS THE NOMINAL PRECISION AND 10**S REPRESENTS THE INCREASE IN ERROR DUE TO
// !   ARGUMENT REDUCTION IN THE ELEMENTARY FUNCTIONS.  HERE, S =
// !   MAX(1,ABS(LOG10(ABS(Z))), ABS(LOG10(FNU))) APPROXIMATELY (I.E. S =
// !   MAX(1,ABS(EXPONENT OF ABS(Z),ABS(EXPONENT OF FNU)) ).
// !   HOWEVER, THE PHASE ANGLE MAY HAVE ONLY ABSOLUTE ACCURACY.  THIS IS MOST
// !   LIKELY TO OCCUR WHEN ONE COMPONENT (IN ABSOLUTE VALUE) IS LARGER THAN THE
// !   OTHER BY SEVERAL ORDERS OF MAGNITUDE.  IF ONE COMPONENT IS 10**K LARGER
// !   THAN THE OTHER, THEN ONE CAN EXPECT ONLY MAX(ABS(LOG10(P))-K, 0)
// !   SIGNIFICANT DIGITS; OR, STATED ANOTHER WAY, WHEN K EXCEEDS THE EXPONENT
// !   OF P, NO SIGNIFICANT DIGITS REMAIN IN THE SMALLER COMPONENT.
// !   HOWEVER, THE PHASE ANGLE RETAINS ABSOLUTE ACCURACY BECAUSE, IN COMPLEX
// !   ARITHMETIC WITH PRECISION P, THE SMALLER COMPONENT WILL NOT (AS A RULE)
// !   DECREASE BELOW P TIMES THE MAGNITUDE OF THE LARGER COMPONENT.  IN THESE
// !   EXTREME CASES, THE PRINCIPAL PHASE ANGLE IS ON THE ORDER OF +P, -P,
// !   PI/2-P, OR -PI/2+P.

// !***REFERENCES  HANDBOOK OF MATHEMATICAL FUNCTIONS BY M. ABRAMOWITZ AND
// !        I. A. STEGUN, NBS AMS SERIES 55, U.S. DEPT. OF COMMERCE, 1955.

// !      COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT
// !        BY D. E. AMOS, SAND83-0083, MAY 1983.

// !      COMPUTATION OF BESSEL FUNCTIONS OF COMPLEX ARGUMENT
// !        AND LARGE ORDER BY D. E. AMOS, SAND83-0643, MAY 1983

// !      A SUBROUTINE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX ARGUMENT
// !        AND NONNEGATIVE ORDER BY D. E. AMOS, SAND85-1018, MAY 1985

// !      A PORTABLE PACKAGE FOR BESSEL FUNCTIONS OF A COMPLEX ARGUMENT
// !        AND NONNEGATIVE ORDER BY D. E. AMOS, ACM TRANS. MATH. SOFTWARE,
// !        VOL. 12, NO. 3, SEPTEMBER 1986, PP 265-273.

// !***ROUTINES CALLED  CBESI,CBESK,I1MACH,R1MACH
// !***END PROLOGUE  CBESY

// COMPLEX (dp), INTENT(IN)   :: z
// REAL (dp), INTENT(IN)      :: fnu
// INTEGER, INTENT(IN)        :: kode
// INTEGER, INTENT(IN)        :: n
// COMPLEX (dp), INTENT(OUT)  :: cy(n)
// INTEGER, INTENT(OUT)       :: nz
// INTEGER, INTENT(OUT)       :: ierr

// COMPLEX (dp)  :: ci, csgn, cspn, cwrk(n), ex, zu, zv, zz, zn
// REAL (dp)     :: arg, elim, ey, r1, r2, tay, xx, yy, ascle, rtol,  &
//                  atol, tol, aa, bb, ffnu, rhpi, r1m5
// INTEGER       :: i, ifnu, k, k1, k2, nz1, nz2, i4
// COMPLEX (dp), PARAMETER  :: cip(4) = (/ (1.0_dp, 0.0_dp), (0.0_dp, 1.0_dp),  &
//                                         (-1.0_dp, 0.0_dp), (0.0_dp, -1.0_dp) /)
// REAL (dp), PARAMETER     :: hpi = 1.57079632679489662_dp

// !***FIRST EXECUTABLE STATEMENT  CBESY
// xx = REAL(z, KIND=dp)
// yy = AIMAG(z)
// ierr = 0
// nz = 0
// IF (xx == 0.0_dp .AND. yy == 0.0_dp) ierr = 1
// IF (fnu < 0.0_dp) ierr = 1
// IF (kode < 1 .OR. kode > 2) ierr = 1
// IF (n < 1) ierr = 1
// IF (ierr /= 0) RETURN
// ci = CMPLX(0.0_dp, 1.0_dp, KIND=dp)
// zz = z
// IF (yy < 0.0_dp) zz = CONJG(z)
// zn = -ci * zz
// CALL cbesi(zn, fnu, kode, n, cy, nz1, ierr)
// IF (ierr == 0 .OR. ierr == 3) THEN
//   CALL cbesk(zn, fnu, kode, n, cwrk, nz2, ierr)
//   IF (ierr == 0 .OR. ierr == 3) THEN
//     nz = MIN(nz1, nz2)
//     ifnu = fnu
//     ffnu = fnu - ifnu
//     arg = hpi * ffnu
//     csgn = CMPLX(COS(arg), SIN(arg), KIND=dp)
//     i4 = MOD(ifnu, 4) + 1
//     csgn = csgn * cip(i4)
//     rhpi = 1.0_dp / hpi
//     cspn = CONJG(csgn) * rhpi
//     csgn = csgn * ci
//     IF (kode /= 2) THEN
//       DO  i = 1, n
//         cy(i) = csgn * cy(i) - cspn * cwrk(i)
//         csgn = ci * csgn
//         cspn = -ci * cspn
//       END DO
//       IF (yy < 0.0_dp) cy(1:n) = CONJG(cy(1:n))
//       RETURN
//     END IF

//     r1 = COS(xx)
//     r2 = SIN(xx)
//     ex = CMPLX(r1, r2, KIND=dp)
//     tol = MAX(EPSILON(0.0_dp), 1.0D-18)
//     k1 = MINEXPONENT(0.0_dp)
//     k2 = MAXEXPONENT(0.0_dp)
//     k = MIN(ABS(k1),ABS(k2))
//     r1m5 = LOG10( REAL( RADIX(0.0_dp), KIND=dp) )
// !-----------------------------------------------------------------------
// !     ELIM IS THE APPROXIMATE EXPONENTIAL UNDER- AND OVERFLOW LIMIT
// !-----------------------------------------------------------------------
//     elim = 2.303_dp * (k*r1m5 - 3.0_dp)
//     ey = 0.0_dp
//     tay = ABS(yy+yy)
//     IF (tay < elim) ey = EXP(-tay)
//     cspn = ex * ey * cspn
//     nz = 0
//     rtol = 1.0_dp / tol
//     ascle = TINY(0.0_dp) * rtol * 1.0E+3
//     DO  i = 1, n
// !----------------------------------------------------------------------
// !       CY(I) = CSGN*CY(I)-CSPN*CWRK(I): PRODUCTS ARE COMPUTED IN
// !       SCALED MODE IF CY(I) OR CWRK(I) ARE CLOSE TO UNDERFLOW TO
// !       PREVENT UNDERFLOW IN AN INTERMEDIATE COMPUTATION.
// !----------------------------------------------------------------------
//       zv = cwrk(i)
//       aa = REAL(zv, KIND=dp)
//       bb = AIMAG(zv)
//       atol = 1.0_dp
//       IF (MAX(ABS(aa),ABS(bb)) <= ascle) THEN
//         zv = zv * rtol
//         atol = tol
//       END IF
//       zv = zv * cspn
//       zv = zv * atol
//       zu = cy(i)
//       aa = REAL(zu, KIND=dp)
//       bb = AIMAG(zu)
//       atol = 1.0_dp
//       IF (MAX(ABS(aa),ABS(bb)) <= ascle) THEN
//         zu = zu * rtol
//         atol = tol
//       END IF
//       zu = zu * csgn
//       zu = zu * atol
//       cy(i) = zu - zv
//       IF (yy < 0.0_dp) cy(i) = CONJG(cy(i))
//       IF (cy(i) == CMPLX(0.0_dp, 0.0_dp, KIND=dp) .AND. ey == 0.0_dp) nz = nz + 1
//       csgn = ci * csgn
//       cspn = -ci * cspn
//     END DO
//     RETURN
//   END IF
// END IF
// nz = 0
// RETURN
// END SUBROUTINE cbesy
