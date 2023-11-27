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
#include <kyosu/details/cayleyify.hpp>
#include <complex>
//======================================================================================================================
//! Up to now bessel functions of integer orders are only implemented here for scalar integral orders
//!
//! cylindical functions
//!
//!  * \f$J_n\f$ many foloow the design of Jhonas Olivati de Sarro, with adaptations to simd cases.
//!    Its copyrigth notice is reproduced at the end of this file
//!  * \f$I_n\f$ are obtained from \f$J_n\f$ by various connections  formulas that can be found in DLMF.
//!  * \f$Y_0\f$ is obtained using the formula \f$Y_0(z) = \frac2\pi\left[\log(z/2)+\gamma)\right] J_0(z) - \frac4\pi\sum_{k = 1}_\infty (-1)^k \frac{J_{2k}}k \f$.
//!  * \f$Y_n\f$ is then obtained by backward recurrence from the \f$(J_i(z))_{i \le n}\f$ and  \f$Y_0\f$
//!  * \f$H_n^{(1)}\f$ is \f$J_n+ i Y_n\f$
//!  * \f$H_n^{(2)}\f$ is \f$J_n- i Y_n\f$
//!  * \f$K_n\f$ is computed from \f$H_n^{(1)}\f$ and \f$H_n^{(2)}\f$ with DLMF 10.27.8
//!
//! spherical functions
//!
//! As in DMLF we restrict to non-negative order
//!
//! The computation scheme of \f$j_n\f$, \f$y_n\f$, \f$h_n^{(1)}\f$ and  \f$h_n^{(2)}\f$ follows the article of Liang-Wu Kai
//! (On the computation of spherical Bessel functions of complex arguments,
//! Comput. Phys. Commun., 182 (3) (2011), pp. 663-668)).
//! \f$k_n\f$ is computed from f$h_n^{(1)}\f$ using DLMF 10.47.13
//!  * \f$i_n^{(1)}\f$ and \f$i_n^{(2)}\f$ are given by 10.47.12


#include <kyosu/types/impl/detail/bessel_utils.hpp>

// bessels of integral order
#include <kyosu/types/impl/detail/bessel_j.hpp>
#include <kyosu/types/impl/detail/bessel_i.hpp>
#include <kyosu/types/impl/detail/bessel_y.hpp>
#include <kyosu/types/impl/detail/bessel_h.hpp>
#include <kyosu/types/impl/detail/bessel_k.hpp>
#include <kyosu/types/impl/detail/bessel_jy.hpp>
// bessels of floating (real) order
#include <kyosu/types/impl/detail/bessel_jyr.hpp>
#include <kyosu/types/impl/detail/bessel_jr.hpp>
#include <kyosu/types/impl/detail/bessel_yr.hpp>

//================================================================================
// MIT License

// Copyright (c) 2021 Jhonas Olivati de Sarro

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//================================================================================
