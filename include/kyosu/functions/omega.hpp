//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>
#include <kyosu/functions/to_complex.hpp>
#include <kyosu/functions/exp2.hpp>
#include <kyosu/functions/deta.hpp>
#include <iomanip>
namespace kyosu
{
  template<typename Options>
  struct omega_t : eve::elementwise_callable<omega_t, Options>
  {
    template<concepts::cayley_dickson_like Z>
    KYOSU_FORCEINLINE constexpr complexify_t<Z> operator()(Z const& z) const noexcept
    {
      if constexpr(concepts::real<Z>)
        return (*this)(complex(z));
      else
        return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(omega_t, omega_);
};
//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var omega
//!   @brief Computes the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log
//!   x+x\f$
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto omega(complex_like auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto omega[conditional_expr auto c](complex_like auto x) noexcept; // 2
//!      constexpr auto omega[logical_value auto m](complex_like auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [complex_like](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Wright \f$\omega\f$ function is returned
//!        (the inverse function of \f$ x \rightarrow \log x+x\f$) is returned.
//!        is the input is a real value a complex value is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!     ω can be used as an alias.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Wright omega function](https://en.wikipedia.org/wiki/Wright_omega_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/omega.cpp}
//================================================================================================
  inline constexpr auto omega = eve::functor<omega_t>;
  inline constexpr auto ω = eve::functor<omega_t>;
//================================================================================================
//! @}
//======================================================================================================================
}

// This implementation is adapted from
// Algorithm 917: Complex Double-Precision Evaluation of the Wright ~ Function
// Authors: Piers W. Lawrence, Robert M. Corless, David J. JeffreyAuthors Info & Claims
// ACM Transactions on Mathematical Software (TOMS), Volume 38, Issue 3

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto omega_(KYOSU_DELAY(), O const&, Z zz) noexcept
  {

//     if constexpr(concepts::real<Z> )
//     {
//       return complex(eve::omega(zz));
//     }
//     else
    if constexpr(concepts::complex<Z> )
    {
      using u_t = eve::underlying_type_t<Z>;
      auto [x, y] = zz;
      auto e = kyosu::zero(kyosu::as(zz));
      auto r = kyosu::zero(kyosu::as(zz));
      auto pi = eve::pi(kyosu::as(x));
      auto pio2 = eve::pio_2(kyosu::as(x));
      auto ipi  = kyosu::muli(pi);
      auto I = kyosu::i(kyosu::as(zz));
      auto s =  kyosu::one(kyosu::as(x));
      auto singular = (x == eve::mone(eve::as(x))) && (eve::abs(y)==pi);
      auto notdone = is_not_infinite(zz) && is_not_nan(zz) && !singular;
      auto notalreadydone = notdone;
      // //std::cout << "zz = " << zz << std::endl;
      // //std::cout << "singular " << singular << std::endl;
      // //std::cout << "notdone " << notdone << std::endl;
      auto w = kyosu::fnan(kyosu::as(zz));

      // //std::cout << "w avant 0 = " << w << std::endl;
      // Signed zeros between branches
      auto inftest = (eve::is_minf(x) && (-pi < y) && (y<= pi));
      w = if_else(inftest, sign(pio2-y)*zero(eve::as(y)), w);

      // //std::cout << "w avant 1 = " << w << std::endl;
      w += kyosu::muli(eve::bitofsign(y));

      // //std::cout << "w avant 2 = " << w << std::endl;
      auto ympi = y-pi;
      auto yppi = y+pi;
      auto near = u_t(0.1e-1);
      w = if_else(eve::is_pinf(x) || eve::is_infinite(y), zz, w);
      w = if_else(singular, kyosu::mone(kyosu::as(zz)), w);
      constexpr u_t half =  eve::half(eve::as<u_t>());
      constexpr u_t third = eve::third(eve::as<u_t>());
      constexpr u_t thotw = 3*half;
      constexpr u_t inv36(1.0/36.0);
      constexpr u_t inv270(1.0/270.0);
      constexpr u_t inv4320(1.0/4320.0);

      // //std::cout << "w avant 3 = " << w << std::endl;

      if( eve::any(notdone) )
      {
        /* Choose approximation based on region */
        /**********************************/
        /* Region 1: upper branch point   */
        /* Series about z=-1+Pi*I         */
        /**********************************/
        auto br_1 = [&](auto z){ // ((-2.0<x && x<=1.0 && 1.0<y && y< 2.0*pi))
          std::cout << "in br_1" << std::endl;
          auto pz=/*kyosu::conj*/(kyosu::sqrt(kyosu::conj(2*(z+1-ipi))));
          //std::cout << "pz "<< pz << std::endl;
          auto r = -1.0+(I+(third+(-inv36*I+(inv270+inv4320*I*pz)*pz)*pz)*pz)*pz;
          //std::cout << "br_1 r "<< r << std::endl;
          return r;
        };
        /**********************************/
        /* Region 2: lower branch point   */
        /* Series about z=-1-Pi*I         */
        /**********************************/
        auto br_2 = [&](auto z){// ((-2.0<x && x<=1.0 && -2.0*pi<y && y<-1.0))
          std::cout << "in br_2" << std::endl;
          auto pz=/*conj*/(kyosu::sqrt(conj(2*(z+1.0+ipi))));
          //std::cout << "pz "<< pz << std::endl;
          return -1.0+(-I+(third+(inv36*I+(inv270-inv4320*I*pz)*pz)*pz)*pz)*pz;
        };
        /*********************************/
        /* Region 3: between branch cuts */
        /* Series: About -infinity       */
        /*********************************/
        auto br_3 = [&](auto z){ // (x <= -2.0 && -pi < y && y <= pi)
          std::cout << "in br_3" << std::endl;
          auto pz=kyosu::exp(z);
          return (1+(-1+(thotw+(u_t(-8.0/3.0)+u_t(125.0/24.0)*pz)*pz)*pz)*pz)*pz;
        };
        /**********************/
        /* Region 4: Mushroom */
        /* Series about z=1   */
        /**********************/
        auto br_4 = [&](auto z){ // (((-2.0 < x) && (x<=1.0) && (-1.0 <= y) && (y <= 1.0))
          //    || ((-2.0 < x) && (x-0.1e1)*(x-0.1e1)+y*y<=pi*pi))
          std::cout << "in br_4" << std::endl;
          auto pz=kyosu::dec(z);
          std::cout << "pz" << pz << std::endl;
          auto res = half+half*z+(u_t(1.0/16.0)+(u_t(-1.0/192.0)+(u_t(-1.0/3072.0)+u_t(13.0/61440.0)*pz)*pz)*pz)*pz*pz;
          std::cout << "res " << res << std::endl;
          return res;
        };
        /*************************/
        /* Region 5: Top wing    */
        /* Negative log series   */
        /*************************/
        auto br_5 = [&](auto z){ // (x<=-0.105e1 && pi<y && y-pi<=-0.75e0*(x+0.1e1))
          //std::cout << "in br_5" << std::endl;
          auto t=z-ipi;
          auto pz=kyosu::log(-t);
          return ((1+(-thotw+third*pz)*pz)*pz+((-1+half*pz)*pz+(pz+(-pz+t)*t)*t)*t)/(t*t*t);
        };
        /***************************/
        /* Region 6: Bottom wing   */
        /* Negative log series     */
        /***************************/
        auto br_6 = [&](auto z){// (x<=-0.105e1 && 0.75e0*(x+0.1e1)< y+pi && y+pi<=0.0e0)
          //std::cout << "in br_6" << std::endl;
          auto  t=z+ipi;
          auto pz=kyosu::log(-t);
          return ((1+(-thotw+third*pz)*pz)*pz+((-1+half*pz)*pz+(pz+(-pz+t)*t)*t)*t)/(t*t*t);
        };
        /************************************/
        /* Region 7: Everywhere else        */
        /* Series solution about infinity   */
        /************************************/
        auto br_7 = [&](auto z){// else
           //std::cout << "in br_7" << std::endl;
         auto pz=kyosu::log(z);
          return ((1+(-thotw+third*pz)*pz)*pz+((-1+half*pz)*pz+(pz+(-pz+z)*z)*z)*z)/(z*z*z);
        };

        auto t1 = ((-2<x && x<=1 && 1<y && y< 2*pi));
        notdone = next_interval(br_1, notdone, t1, w, zz);
        if( eve::any(notdone) )
        {
          auto t2 = ((-2<x && x<=1 && -2*pi<y && y<-1));
          notdone = next_interval(br_2, notdone, t2, w, zz);
          if( eve::any(notdone) )
          {
            auto t3 =(x <= -2 && -pi < y && y <= pi);
            notdone = next_interval(br_3, notdone, t3, w, zz);
            if( eve::any(notdone) )
            {
              auto t4 =((-2 < x) && (x<=1) && (-1 <= y) && (y <= 1));
              notdone = next_interval(br_4, notdone, t4, w, zz);
              if( eve::any(notdone) )
              {
                auto t5 = (x<=-0.105e1 && pi<y && y-pi<=u_t(-0.75)*(x+1));
                notdone = next_interval(br_5, notdone, t5, w, zz);
                if( eve::any(notdone) )
                {
                  auto t6 = (x<=u_t(-0.105e1) && u_t(0.75)*(x+1)< y+pi && y+pi<=0);
                  notdone = next_interval(br_6, notdone, t6, w, zz);
                  if( eve::any(notdone) )
                  {
                    notdone = last_interval(br_7, notdone, w, zz);
                  }
                }
              }
            }
          }
        }
      }

      std::cout << "w avant regul = " << w << std::endl;
      /**********************************/
      /* Regularize if near branch cuts */
      /**********************************/
      // //std::cout << "dans regul " <<  std::endl;
      auto regul = [&](auto z, auto test){
        auto pid = eve::pi[lower](eve::as(x));
        auto piu = eve::pi[upper](eve::as(x));

        s = if_else(test, -s,  s);
        std::cout << "dans regul s = " << s << std::endl;
        auto regulm = [&](auto test1){
          //std::cout << "test1 " << test1 << std::endl;
          /* Recompute ympi with directed rounding */
          auto nympi = eve::sub[upper](y,pid);
          //std::cout << std::setprecision(15) << "nympi " << nympi << std::endl;
          nympi = eve::if_else(eve::is_lez(ympi), eve::sub[lower](y,pi), ympi);
          auto res = complex(x, kyosu::if_else(test1, nympi, ympi));
          //std::cout << std::setprecision(15) << "z " << res << std::endl;
          return res;
        };
        auto regulp = [&](auto test2){
          /* Recompute yppi with directed rounding */
          auto nyppi = eve::add[upper](y,piu);
          nyppi = eve::if_else(eve::is_lez(yppi), eve::add[lower](y,pi), yppi);
          return complex(x, kyosu::if_else(test2, nyppi, yppi));
        };
        auto test1 = eve::abs(ympi) <= near;
        //std::cout << " eve::abs(ympi) <= near = " << test1 << std::endl;

        return if_else(test, if_else(test1, regulm(test1), regulp(!test1)), z);
      };

      auto test = notalreadydone && (x <= -0.1e1 + near && (eve::abs(ympi) <= near || eve::abs(yppi) <= near));
      std::cout << "test = " << test << std::endl;
      auto regulzz = regul(zz, test);
      //std::cout << "regulzz = " << regulzz << std::endl;
      if (eve::any(test))
      {
        //std::cout << "icitte " << notalreadydone << " test " << test << std::endl;
        zz = if_else(notalreadydone, if_else(test, regulzz, zz), zz);
      }
      std::cout << "apres regul zz = " << zz << std::endl;
      std::cout << "apres regul w = " << w << std::endl;

      const auto TWOITERTOL = eps(as(x));

      /*****************/
      /* Iteration one */
      /*****************/
  // //std::cout << "not done apres regul = " << notdone << std::endl;
      if(eve::any(notalreadydone))
      {
        std::cout << "iter1" << std::endl;
        auto w1=s*w;
        r=zz-s*w1-kyosu::log(w1);
        auto wp1=s*w1+1;
        e=r/wp1*(2*wp1*(wp1+u_t(2.0/3.0)*r)-r)/(2*wp1*(wp1+u_t(2.0/3.0)*r)-2*r);
        w1=w1*(1+e);
        w = if_else(notalreadydone, w1, w);
        std::cout << "apres iter1 w = " << w << std::endl;

        /*****************/
        /* Iteration two */
        /*****************/
        if(eve::any(notalreadydone && (kyosu::abs((2*w*w-8*w-1)*eve::pow(kyosu::abs(r),4)) >= TWOITERTOL*72*eve::pow(kyosu::abs(wp1),6) )))
        {
          std::cout << "iter2 " << std::endl;
          r=zz-s*w-kyosu::log(w);
          wp1=s*w+1;
          e=r/wp1*(2.0*wp1*(wp1+u_t(2.0/3.0)*r)-r)/(2*wp1*(wp1+u_t(2.0/3.0)*r)-2*r);
          w=if_else(notalreadydone, w*(1+e), w);
          std::cout << "apres iter2 w = " << w << std::endl;
        }
      }
      std::cout << "apres iter2 s = " <<  s<< std::endl;
     std::cout << "apres iter2 s*w = " <<  s*w<< std::endl;
      return s*w;

    }
    else return kyosu::_::cayley_extend(kyosu::omega, zz);
  }
}
