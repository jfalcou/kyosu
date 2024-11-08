//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <eve/module/bessel.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <complex>
//!======================================================================================================================
//! Up to now bessel functions  are only implemented here for scalar orders
//!
//!======================================================================================================================
//!
//! Integral orders
//!
//! cylindical functions
//!
//!  * \f$J_n\f$ globally follows the design of Jhonas Olivati de Sarro.
//!  * \f$I_n\f$ are obtained from \f$J_n\f$ by various connections  formulas that can be found in DLMF.
//!  * \f$Y_0\f$ is obtained using the formula
//!    \f$Y_0(z) = \frac2\pi\left[\log(z/2)+\gamma)\right] J_0(z) - \frac4\pi\sum_{k = 1}_\infty (-1)^k \frac{J_{2k}}k \f$.
//!  * \f$Y_n\f$ is then obtained by backward recurrence from the \f$(J_i(z))_{i \le n}\f$ and  \f$Y_0\f$
//!  * \f$H_n^{(1)}\f$ is \f$J_n+ i Y_n\f$
//!  * \f$H_n^{(2)}\f$ is \f$J_n- i Y_n\f$
//!  * \f$K_n\f$ is computed from \f$H_n^{(1)}\f$ and \f$H_n^{(2)}\f$ with DLMF 10.27.8 simplified for the integral case
//!
//! spherical functions
//!
//! As in DMLF we restrict the implementation to non-negative integral orders
//!
//! The computation scheme of \f$j_n\f$, \f$y_n\f$, \f$h_n^{(1)}\f$ and  \f$h_n^{(2)}\f$
//! follows the article of Liang-Wu Kai (On the computation of spherical Bessel functions of complex arguments,
//! Comput. Phys. Commun., 182 (3) (2011), pp. 663-668)).
//! \f$k_n\f$ is computed from f$h_n^{(1)}\f$ using DLMF 10.47.13
//! \f$i_n^{(1)}\f$ and \f$i_n^{(2)}\f$ are given by DLMF 10.47.12
//!
//!======================================================================================================================
//!
//! floating real orders
//!
//! cylindical functions
//!
//! If the order is a flint (i.e. v == trunc(v)) the integral implementation is called
//!
//!  * The case where \f$\vu\f$ is in \f$\]0, 1\[\f$ or in \f$\]1, 2\[\f$ are  treated apart
//!    by forward recursion if \f$|z|\f$ is less  than twelve or Hankel expansion (DLMF 10.17.3 and 10.17.4)
//!    in the other case.
//!  * \f$J_\vu\f$ and \f$Y_\vu\f$ for  \f$\vu \gt 1 \f$ are computed from \f$J_{\vu_0}\f$,
//!    \f$Y_{\vu_0}\f$, \f$J_{\vu_0+1}\f$ and \f$Y_{\vu_0+1}\f$ (where \f$\vu_0\f$ is the  fractionnal part
//!    of \f$\vu\f$). Forward or backward recursion is used for f$J_\vu\f$ and using wronskian relation for
//!    \f$Y_\vu\f$ as proposed  in  "Computation of special functions" by S. Zhang and J. Jin, (5.5.11 and 5.5.12)
//!  * \f$H_\vu^{(1)}\f$ is \f$J_\vu+ i Y_\vu\f$
//!  * \f$H_\vu^{(2)}\f$ is \f$J_\vu- i Y_\vu\f$
//!  * \f$I_\vu\f$ are obtained from \f$J_\vu\f$ by  DLMF 10.27.6 using conjugation if phase is positive.
//!  * \f$K_\vu\f$ is computed from \f$H_\vu^{(1)}\f$ and \f$H_\vu^{(2)}\f$ with DLMF 10.27.8
//!
//! spherical functions
//!
//!  Following DLMF 10.47 spherical functions are only implemented for integral non negative orders.
//!
//!======================================================================================================================
//!
//!  Rationale of the interface
//!
//!  the functions are all named [cyl, sph]_bessel_xxx xxx designing the chosen bessel function(s).
//!  The choice not to make order an simd parameter is driven by two causes
//!
//!    * The complexity involved in the merging of test on order and on evaluation arguments preclude the
//!      SIMD expected performances
//!    * many bessel functions of arithmetic range order (with step one) can be computed with almost no additionnal cost
//!      provided that the returned value is complex (scalar or simd). So for each possible call another is provided
//!      allowing additionnal output parameters, the rule being that if aaa_bessel_xxx(n, z, output) is called:
//!
//!        * the caller must provide output as a random access range of kyosu::complex allocated to receive
//!          N = int(trunc(abs(n)+1)) values.
//!        * These values will be the same as the result of calling :
//!          `for (int i = 0; i <= N;  ++i) output[i] = aaa_bessel_xxx(n0+sgn*i, z)`
//!          where n0 is the fractionnal part of n and sgn is the sign of n.
//!
//!    * Moreover jy and ik functions can be computed together and two ouput parameters can be used
//!
//!  values of xxx
//!
//!   * one parameter
//!      j0 j1 i0 i1 y0 y1 k0 k1 h10 h11 h20 h21 only admit the z parameter which can be any cayley-dickson type
//!   * two parameters or three parameters
//!      * jn in yn kn h1n h2n  the first one is the integer order, the second  z which can be any cayley-dickson type
//!      * j  i  y  k  h1  h2   the first one is the floating order, the second  z which can be any cayley-dickson type
//!      * if present the third parameter will be the output parameter as described above and z must be floating or complex
//!   * two parameters or four parameters
//!      * jyn  ikn h12n the first one is the integer order, the second  z which can be any cayley-dickson type
//!      * jy   ik  h12 the first one is the floating order, the second  z which can be any cayley-dickson type
//!      * if present the third and fourth parameter will be the output parameters as described above
//!        and z must be floating or complex

#include <kyosu/types/impl/detail/bessel_utils.hpp>

// bessels of integral order
#include <kyosu/types/impl/bessel/cb_jyn.hpp>
#include <kyosu/types/impl/bessel/sb_jyn.hpp>
// #include <kyosu/types/impl/bessel/cb_hn.hpp>
// #include <kyosu/types/impl/bessel/sb_hn.hpp>
// #include <kyosu/types/impl/bessel/cb_ikn.hpp>
// #include <kyosu/types/impl/bessel/sb_ikn.hpp>
// // bessels of floating (real) order
// #include <kyosu/types/impl/besselr/cb_jyr.hpp>
// #include <kyosu/types/impl/besselr/cb_h.hpp>
// #include <kyosu/types/impl/besselr/cb_ikr.hpp>
// // airy functions
// #include <kyosu/types/impl/besselr/airy.hpp>
