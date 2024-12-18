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
//! Up to now complex bessel functions are only implemented for scalar orders (integral or floating)
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
//! Contrarily to DMLF we do not restrict the implementation to non-negative integral orders
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
//! Contrarily to DMLF we do not restrict the implementation to non-negative integral orders
//! Non-integral and negative orders are computed via their relation to cylindrical
//!
//!======================================================================================================================
//!
//!  Rationale of the interface
//!
//!  the functions are all named bessel_x x designing the chosen bessel function(s) i.e. j, i, h, k.
//!   * the options `cylindrical` and `spherical` are always available.
//!   * the options `kind_1` and `kind_2` are also available for some functions : i.e.
//!  no option means  `cylindrical` and `kind_1`
//!
//!  The choice not to make order an simd parameter is driven by two causes
//!
//!    * The complexity involved in the merging of test on order and on evaluation arguments preclude the
//!      SIMD expected performances
//!    * many bessel functions of arithmetic range order (with step one) can be computed with almost no additionnal cost
//!      provided that the returned value is complex (scalar or simd). So for each possible call another is provided
//!      allowing additionnal output parameters, the rule being that if bessel_x(n, z, output) is called:
//!
//!        * the caller must provide output as a std::span of kyosu::complex allocated to receive N values
//!           values.
//!        * These values will be the same as the result of calling :
//!          `for (int i = 0; i < min(N, ceil(abs(n)+1));  ++i) output[i] = bessel_x(n0+sgn*i, z)`
//!          where n0 is the fractionnal part of n and sgn is the sign of n.
//!          However,  even if N is less than  ceil(abs(n)+1) the function will return the order n value at z.
//!
//!    * Moreover jy and ik functions can be computed together and two ouput parameters can be used
//!
//!======================================================================================================================
//!
//!  @warning although float and double versions for the underlying type are available, it is common
//!  to obtain poor precision with float based computations.
//!======================================================================================================================


#include <kyosu/details/bessel/bessel_utils.hpp>
// These files only contain implementation details and do not contain any function
// belonging to the user interface
//
// bessels of integral order
#include <kyosu/details/bessel/besseln/cb_jyn.hpp>
#include <kyosu/details/bessel/besseln/sb_jyn.hpp>
#include <kyosu/details/bessel/besseln/cb_hn.hpp>
#include <kyosu/details/bessel/besseln/sb_hn.hpp>
#include <kyosu/details/bessel/besseln/cb_ikn.hpp>
#include <kyosu/details/bessel/besseln/sb_ikn.hpp>
// bessels of floating (real) order
#include <kyosu/details/bessel/besselr/cb_jyr.hpp>
#include <kyosu/details/bessel/besselr/cb_hr.hpp>
#include <kyosu/details/bessel/besselr/cb_ikr.hpp>
#include <kyosu/details/bessel/besselr/sb_jyr.hpp>
#include <kyosu/details/bessel/besselr/sb_hr.hpp>
#include <kyosu/details/bessel/besselr/sb_ikr.hpp>
// airy functions
#include <kyosu/details/bessel/besselr/airy.hpp>
