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

#include <kyosu/types/impl/detail/besselj0.hpp>
#include <kyosu/types/impl/detail/besselj1.hpp>
#include <kyosu/types/impl/detail/besseljn.hpp>
#include <kyosu/types/impl/detail/besseli0.hpp>
#include <kyosu/types/impl/detail/besseli1.hpp>
#include <kyosu/types/impl/detail/besselin.hpp>
#include <kyosu/types/impl/detail/bessely0.hpp>


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
  //  cyl_bessel_y0
  //===-------------------------------------------------------------------------------------------
//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_y0>, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       using e_t = as_real_t<Z>;
//       using u_t = eve::underlying_type_t<Z>;
//       auto saz = kyosu::sqr_abs(z);

//       auto ascending_series_cyl_y0 = [](auto z) {
// //          std::cout << "ascending z " << z << std::endl;
//         // Ascending Series from G. N. Watson 'A treatise on the
//         //  theory of Bessel functions', 2ed, Cambridge, 1996,
//         //  Chapter II, equation (3); or from Equation 9.1.12 of
//         //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
//         //  Functions'.
//         // good for abs(z) < 12
//         using u_t = eve::underlying_type_t<Z>;
//         auto g =eve::egamma(eve::as<u_t>());// u_t(0.5772156649015328606);
//         auto twoopi= eve::two_o_pi(eve::as<u_t>());
//         auto eps = eve::eps(eve::as<u_t>());

//         auto hk(eve::zero(eve::as<u_t>()));
//         auto z2o_4 = sqr(z*e_t(0.5));
//         auto n(eve::one(eve::as<u_t>()));
//         auto sgn(eve::one(eve::as<u_t>()));
//         auto t = complex(eve::one ((eve::as<e_t>())));
//         auto s = complex(eve::zero((eve::as<e_t>())));
//         auto ds= complex(eve::zero((eve::as<e_t>())));
//         auto test = sqr_abs(ds) >= eps*sqr_abs(s);

//         while(eve::any(test))
//         {
// //             std::cout << "sgn " << sgn << std::endl;
// //             std::cout << "nn  " << eve::sqr(n)<< std::endl;
// //             std::cout << "z2o_4 " << z2o_4 << std::endl;
// //             std::cout << "n     " << n     << std::endl;
//           auto recn = rec(n);
//           hk += recn;
//           t *= z2o_4*sqr(recn);
//           ds = hk*t;
//           auto dssgn = sgn*ds;
// //            std::cout << "dssgn     " << dssgn  << std::endl;
//           s = if_else(test, s+dssgn, s);
// //            std::cout  << " s " << s << std::endl;
//           test = sqr_abs(ds) >= sqr(eps)*sqr_abs(s);
//           n = inc(n);
//           sgn = -sgn;
//         }
//         return ((kyosu::log(z*eve::half(eve::as<u_t>()))+g)*kyosu::cyl_bessel_j0(z)+s)*twoopi;
//       };

//       auto semiconvergent_series_cyl_y0 = [saz](auto z) {
//         std::cout << "semi z " << z << std::endl;
//         auto bound_compute = [saz]()
//         {
// //            std::cout << "saz " << saz << std::endl;
//           auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
//           bds = eve::if_else(saz < 35*35, e_t(12), bds);
//           bds = eve::if_else(saz < 12*12, e_t(1),  bds);
//           std::cout << "bds " << bds << std::endl;
//           return bds;
//         };

//         // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
//         //  treatise on Bessel functions and their applications to
//         //  physics, 1895.
// //         auto Pm = complex(eve::one((eve::as<e_t>())));
// //         auto Qm = rec(8*z);
//         auto P = complex(eve::one((eve::as<e_t>())));
//         auto Q = u_t(0.375)/z;
//         auto bds = bound_compute();
//         auto m = eve::one((eve::as<e_t>()));

//         auto rz2 = rec(sqr(z));
//         if constexpr(eve::scalar_value<e_t>)
//         {
//           //A1
//           std::array<u_t, 12> p{1.0000000000000000e+00, 1.1718750000000000e-01, -1.4419555664062500e-01, 6.7659258842468262e-01,
//               -6.8839142681099474e+00, 1.2159789187653587e+02, -3.3022722944808525e+03, 1.2764127264617461e+05, -6.6563677188176867e+06,
//               4.5027860030503923e+08, -3.8338575207427887e+10, 4.0118385991331968e+12}; //, -5.0605685033147250e+14, 7.5726164611179552e+16 };
//           //B1
//           std::array<u_t, 12> q{3.7500000000000000e-01, -1.0253906250000000e-01, 2.7757644653320312e-01, -1.9935317337512970e+00,
//               2.7248827311268542e+01, -6.0384407670507028e+02, 1.9718375912236632e+04, -8.9029787670706806e+05, 5.3104110109685242e+07,
//               -4.0436203251077561e+09, 3.8270113465986078e+11, -4.4064814178522805e+13}; //, 6.0650913512227020e+15, -9.8338838765906842e+17 };
//           auto zz = complex(eve::one((eve::as<e_t>())));;
//           for ( int m=1; m<bds; ++m )
//           {

//             P += p[m]*pow(z, -2*m);
//             Q += q[m]*pow(z, -2*m-1);
//             //           zz   *= rz2;
//           }
// //          Q*= rec(z);
// //          auto [s, c] = kyosu::sincos(z);
//           auto t2 = z-u_t(0.75)*eve::pi(eve::as<u_t>());
//           auto [s, c] = kyosu::sincos(t2);
//           e_t sqtpio2(1.253314137315500);
// //          isqtpi = e_t isqtpi(5.641895835477563e-01);
//           auto r = sqtpio2*(c*P-s*Q)/(kyosu::sqrt(z)*sqtpio2);
//  //auto r = (c*(Q-P) + s*(P+Q))/(kyosu::sqrt(z)*sqtpio2);
//           return r;
// //           auto log2mg = u_t(0.1159315156584124488107);
//           //     auto r = sqtpio2*(c*Q-s*P)/kyosu::sqrt(z);
// //          return (eve::log_2(eve::as<u_t>())-eve::egamma(eve::as<u_t>()))*cyl_bessel_j0(z)+ r;
// //          return log2mg*cyl_bessel_j0(z)+r;
//         }
//         else
//         {
//           return z;
// //           auto  bound_not_reached = m <= bds;
// //           while (eve::any(bound_not_reached))
// //           {
// //             auto twom = m+m;
// //             auto fourm = twom+twom;
// //             auto pim = sqr((fourm-3)*(fourm-1))/((twom-1)*128*m);
// //             Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
// //             auto xim =  sqr((fourm-1)*(fourm+1))/((twom+1)*128*m);
// //             Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
// //             P = kyosu::if_else(bound_not_reached, P+Pm, P);
// //             Q = kyosu::if_else(bound_not_reached, Q+Qm, Q);
// //             m = inc(m);
// //             bound_not_reached = m <= bds;
// //           }
// //           auto [s, c] = kyosu::sincos(z);
// // //          e_t sqtpio2(1.253314137315500);
// //           e_t sqtpi(1.772453850905516);
// //           auto r = sqtpi*(c*(Q-P) + s*(P+Q))/kyosu::sqrt(z);
// //           return (eve::log_2(eve::as<u_t>()-eve::egamma(eve::as<u_t>())))*cyl_bessel_j0(z)+r;
//         };
//       };

//       auto rzneg = eve::is_ltz(real(z));
//       z = if_else(rzneg, -z, z);

//       auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
//       auto notdone = kyosu::is_nan(r);

//       if( eve::any(notdone) )
//       {
//         notdone = next_interval(ascending_series_cyl_y0, notdone, saz <= as_real_t<Z>(144), r, z);
//         if( eve::any(notdone) )
//         {
//           last_interval(semiconvergent_series_cyl_y0, notdone, r, z);
//         }
//       }
//       return r;
//     }
//     else
//     {
//       return cayley_extend(cyl_bessel_y0, z);
//     }
//   }

}
