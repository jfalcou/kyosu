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

//   //===-------------------------------------------------------------------------------------------
//   //  cyl_bessel_j0
//   //===-------------------------------------------------------------------------------------------
//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_j0>, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       using e_t = as_real_t<Z>;
//       using u_t = eve::underlying_type_t<e_t>;
//       auto saz = kyosu::sqr_abs(z);

//       auto ascending_series_cyl_j0 = [](auto z)
//         {
// //          std::cout << "ascending z " << z << std::endl;
//           // Ascending Series from G. N. Watson 'A treatise on the
//           //  theory of Bessel functions', 2ed, Cambridge, 1996,
//           //  Chapter II, equation (3); or from Equation 9.1.12 of
//           //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
//           //  Functions'.
//           // good for abs(z) < 12
//           std::cout << "ascending" << std::endl;
//           auto eps = eve::eps(eve::as<e_t>());
//           auto j0 = complex(eve::one((eve::as<e_t>())));
//           auto sm = j0;
//           auto test = sqr_abs(sm) >= eps*sqr_abs(j0);
//           auto  m(eve::one(eve::as<e_t>()));
//           auto z2 = - sqr(z);
//           while(eve::any(test))
//           {
//             sm *= z2*e_t(0.25)/sqr(m);
//             j0 = if_else(test, j0+sm, j0);
//             test = sqr_abs(sm) >= eps*sqr_abs(j0);
//             m = inc(m);
//           }
//           return j0;
//         };

//       auto semiconvergent_series_cyl_j0 = [saz](auto z)
//         {
// //          std::cout << "semi z " << z << std::endl;
//           auto bound_compute = [saz]()
//           {
// //            std::cout << "saz " << saz << std::endl;
//             auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
//             bds = eve::if_else(saz < 35*35, e_t(12), bds);
//             bds = eve::if_else(saz < 12*12, e_t(0),  bds);
//             std::cout << "bds " << bds << std::endl;
//             return bds;
//           };

//           // DLMF 10.17.1 Hankel expansion tabulated p[i] = a[2i],  q[i] = a{2i°1]
//           std::array<u_t, 14> p{1.0000000000000000e+00, 7.0312500000000000e-02, 1.1215209960937500e-01, 5.7250142097473145e-01,
//               6.0740420012734830e+00, 1.1001714026924674e+02, 3.0380905109223841e+03, 1.1883842625678323e+05, 6.2529514934347952e+06,
//               4.2593921650476676e+08, 3.6468400807065552e+10,3.8335346613939438e+12, 4.8540146868528994e+14, 7.2868573493776544e+16};

//           std::array<u_t, 14> q{-1.2500000000000000e-01, -7.3242187500000000e-02, -2.2710800170898438e-01, -1.7277275025844574e+00,
//               -2.4380529699556064e+01, -5.5133589612202059e+02, -1.8257755474293172e+04, -8.3285930401628907e+05, -5.0069589531988911e+07,
//               -3.8362551802304325e+09, -3.6490108188498328e+11, -4.2189715702840953e+13, -5.8272446315669060e+15, -9.4762880992601062e+17};

//           // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
//           //  treatise on Bessel functions and their applications to
//           //  physics, 1895.
//           //
//           std::cout << "semi" << std::endl;
//           if constexpr(eve::scalar_value<e_t>)
//           {
// //            std::cout << "icitte" << std::endl;
//             auto Pm = complex(u_t(p[0]));
//             auto Qm = complex(u_t(q[0]));
//             auto rz = rec(z);
//             auto rz2 = sqr(rz);
//             auto P = Pm;
//             auto Q = Qm;
//             size_t bds = bound_compute();
//             for ( size_t m=1; m<=bds; m++ )
//             {
//               Pm *= -Pm*p[m]*rz2;
//               Qm *= -Qm*q[m]*rz2;
//  //              Pm = -Pm*Pm*p[m]*rz2;
// //               Qm = -Pm*Qm*q[m]*rz2;

//               P += Pm;
//               Q += Qm;
//             }
//             Q*= rec(z);
//             auto [s, c] = kyosu::sincos(z);
//             e_t isqtpi(5.641895835477563e-01);
//             auto r = isqtpi*(c*(P+Q) + s*(P-Q))/(kyosu::sqrt(z)); ;
//             return r;
//           }
//           else
//           {
//             //            std::cout << "latte" << std::endl;
//             auto zero = complex(u_t(0));
//             auto Pm = complex(e_t(p[0]));
//             auto Qm = complex(e_t(q[0]));
//             auto rz = rec(z);
//             auto rz2 = sqr(rz);
//             auto P = Pm;
//             auto Q = Qm;
//             auto bds = bound_compute();
//             //           std::cout << "bds " << bds << std::endl;
//             size_t im = 1;
//             auto  bound_not_reached = u_t(im) <= bds;
//             while (eve::any(bound_not_reached))
//             {
//               std::cout << "im " << im << std::endl;
//               Pm *= kyosu::if_else(bound_not_reached, -Pm*p[im]*rz2, zero);
//               Qm *= kyosu::if_else(bound_not_reached, -Qm*q[im]*rz2, zero);
//               P += Pm;
//               Q += Qm;
//               im = inc(im);
//               bound_not_reached = u_t(im) <= bds;
//             }
//             Q *= rec(z);
//             auto [s, c] = kyosu::sincos(z);
//             e_t isqtpi(5.641895835477563e-01);
//             auto r = isqtpi*(c*(P+Q) + s*(P-Q))/(kyosu::sqrt(z)); ;
//             return r;
//           };
//         };

//       auto rzneg = eve::is_ltz(real(z));
//       z = if_else(rzneg, -z, z);

//       auto r = kyosu::if_else(is_eqz(saz), Z(1), eve::nan(eve::as(saz)));
//       auto notdone = kyosu::is_nan(r);

//       if( eve::any(notdone) )
//       {
//         notdone = next_interval(ascending_series_cyl_j0, notdone, saz <= as_real_t<Z>(144), r, z);
//         if( eve::any(notdone) )
//         {
//           last_interval(semiconvergent_series_cyl_j0, notdone, r, z);
//         }
//       }
//       return r;
//     }
//     else
//     {
//       return cayley_extend(cyl_bessel_j0, z);
//     }
//   }

//   //===-------------------------------------------------------------------------------------------
//   //  cyl_bessel_j1
//   //===-------------------------------------------------------------------------------------------
//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_j1>, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       using e_t = as_real_t<Z>;
//       using u_t = eve::underlying_type_t<e_t>;
//       auto saz = kyosu::sqr_abs(z);

//       auto ascending_series_cyl_j1 = [](auto z){
//         // Ascending Series from G. N. Watson 'A treatise on the
//         //  theory of Bessel functions', 2ed, Cambridge, 1996,
//         //  Chapter II, equation (3); or from Equation 9.1.12 of
//         //  M. Abramowitz, I. A. Stegun 'Handbook of Mathematical
//         //  Functions'.
//         // good for abs(z) < 12
//         auto eps = eve::eps(eve::as<e_t>());
//         auto j1 = complex(eve::one((eve::as<e_t>())));
//         auto sm = j1;
//         auto test = sqr_abs(sm) >= eps*sqr_abs(j1);
//         auto  m(eve::one(eve::as<e_t>()));
//         auto z2o_4 = - sqr(z)*e_t(0.25);
//         while(eve::any(test))
//         {
//           sm *= z2o_4/(m*inc(m));
//           j1 += sm;
//           test = sqr_abs(sm) >= eps*sqr_abs(j1);
//           m = inc(m);
//         }
//         return j1*eve::half(eve::as<e_t>())*z;
//       };

//       auto semiconvergent_series_cyl_j1 = [saz](auto z)
//         {
//           auto bound_compute = [saz]()
//           {
//             auto bds = eve::if_else(saz < 50*50, e_t(10), e_t(8));
//             bds = eve::if_else(saz < 35*35, e_t(12), bds);
//             return bds;
//           };
//           // Stokes Semiconvergent Series from A. Gray, G. B. Mathews 'A
//           //  treatise on Bessel functions and their applications to
//           //  physics, 1895.
//           if constexpr(false && eve::scalar_value<e_t>)
//           {

//             std::array<u_t, 14> p{1.0000000000000000e+00, -1.1718750000000000e-01, -1.4419555664062500e-01, -6.7659258842468262e-01,
//                 -6.8839142681099474e+00, -1.2159789187653587e+02, -3.3022722944808525e+03, -1.2764127264617461e+05, -6.6563677188176867e+06,
//                 -4.5027860030503923e+08, -3.8338575207427895e+10, -4.0118385991331973e+12, -5.0605685033147256e+14, -7.5726164611179552e+16};

//             std::array<u_t, 14> q{3.7500000000000000e-01, 1.0253906250000000e-01, 2.7757644653320312e-01, 1.9935317337512970e+00,
//                 2.7248827311268542e+01, 6.0384407670507017e+02, 1.9718375912236628e+04, 8.9029787670706783e+05, 5.3104110109685220e+07,
//                 4.0436203251077538e+09, 3.8270113465986060e+11,4.4064814178522781e+13, 6.0650913512226980e+15, 9.8338838765906790e+17};
// //             std::array<u_t, 14> p{1.0000000000000000e+00, 1.1718750000000000e-01, -1.4419555664062500e-01, 6.7659258842468262e-01,
// //                 -6.8839142681099474e+00, 1.2159789187653587e+02, -3.3022722944808525e+03, 1.2764127264617461e+05, -6.6563677188176867e+06,
// //                 4.5027860030503923e+08, -3.8338575207427887e+10, 4.0118385991331968e+12, -5.0605685033147250e+14, 7.5726164611179552e+16};
// //             std::array<u_t, 14> q{-3.7500000000000000e-01, 1.0253906250000000e-01, -2.7757644653320312e-01, 1.9935317337512970e+00,
// //                 -2.7248827311268542e+01, 6.0384407670507028e+02, -1.9718375912236632e+04, 8.9029787670706806e+05, -5.3104110109685242e+07,
// //                 4.0436203251077561e+09, -3.8270113465986078e+11, 4.4064814178522805e+13, -6.0650913512227020e+15, +9.8338838765906842e+17};

//             auto Pm = complex(u_t(p[0]));
//             auto Qm = complex(u_t(q[0]));
//             auto rz = rec(z);
//             auto rz2 = sqr(rz);
//             auto P = Pm;
//             auto Q = Qm;
//             size_t bds = bound_compute();
//             for ( size_t m=1; m<=bds; m++ )
//             {
//                Pm *= -Pm*p[m]*rz2;
//                Qm *= -Qm*q[m]*rz2;
//                P+= Pm;
//                Q+= Qm;
// //               P += p[m]*rz2;
// //               Q += q[m]*rz2;
// //              std::cout << "m " << m << " -> " << Pm <<  " --- " << Qm/z << std::endl;
//             }
//             Q *= rz;
//             auto pio4 = eve::pio_4(eve::as<u_t>());
//             auto [s, c] = kyosu::sincos(z+pio4);
//             e_t isqtpi(5.641895835477563e-01);
// //            auto r = isqtpi*(c*(P+Q) + s*(P-Q))/(kyosu::sqrt(z));
// //            auto r = isqtpi*(s*(P-Q) + c*(P+Q))/(kyosu::sqrt(z)); ;
//             auto r = isqtpi*(s*P+c*Q)*rz;
//             return r;
//           }
//           else
//           {
//             auto Pm = complex(eve::one((eve::as<e_t>())));
//             auto Qm = -e_t(0.375)*rec(z);
//             auto P = Pm;
//             auto Q = Qm;
//             auto bds = bound_compute();
//             auto m = eve::one((eve::as<e_t>()));
//             auto  bound_not_reached = m <= bds;
//             auto PPm = Pm;
//             auto QQm = -3*Pm/8;
//             auto z2 = sqr(z);
//             while (eve::any(bound_not_reached))
//             {
//               auto twom = m+m;
//               auto fourm = twom+twom;
//               auto pim = (4-sqr(fourm-3))*(4-sqr(fourm-1))/((twom-1)*128*m);
//               PPm = -PPm*pim;
// //              std::cout << m << "  -> " << std::scientific << PPm << std::endl;
//               Pm = kyosu::if_else(bound_not_reached, -Pm*pim/z2, Pm);
//               auto xim =  (sqr(fourm-1)-4)*(sqr(fourm+1)-4)/((twom+1)*128*m);
//               QQm = -QQm*xim;
// //              std::cout << m << "  -> " << std::scientific << QQm << std::endl;
//               Qm = kyosu::if_else(bound_not_reached, -Qm*xim/z2, Qm);
//               P += Pm;
//               Q += Qm;
// //              std::cout << "m " << int(m) << " -> " << Pm <<  " --- " << Qm << std::endl;
//               m = inc(m);
//               bound_not_reached = m <= bds;
//             }
//             auto [s, c] = kyosu::sincos(z);
//             return (s*(P-Q)-c*(P+Q))/kyosu::sqrt(z*eve::pi(eve::as<e_t>()));
//           }
//         };

//       auto rzneg = eve::is_ltz(real(z));
//       z = if_else(rzneg, -z, z);

//       auto notdone = eve::true_(eve::as(saz));
//       auto r = kyosu::if_else(is_eqz(saz), Z(0), eve::nan(eve::as(saz)));
//       if( eve::any(notdone) )
//       {
//         notdone = next_interval(ascending_series_cyl_j1, notdone, saz <= as_real_t<Z>(144), r, z);
//         if( eve::any(notdone) )
//         {
//           last_interval(semiconvergent_series_cyl_j1, notdone, r, z);
//         }
//       }
//       return if_else(rzneg, -r, r);
//     }
//     else
//     {
//       return cayley_extend(cyl_bessel_j1, z);
//     }
//   }

//   template<eve::integral_scalar_value N, typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_jn>, N nn, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       if ( is_eqz(nn) )
//       {
//         return cyl_bessel_j0(z);
//       }
//       else if (nn == 1)
//       {
//         return cyl_bessel_j1(z);
//       }
//       else if ( nn == -1 )
//       {
//         return -cyl_bessel_j1(z);
//       }
//       else
//       {
//         using e_t = as_real_t<Z>;
//         using u_t = eve::underlying_type_t<e_t>;
//         auto n = u_t(nn);
//         auto an = eve::abs(n);
//         auto az = kyosu::abs(z);

//         auto forward = [n](auto z){
//           auto b0 = cyl_bessel_j0(z);
//           auto b1 = cyl_bessel_j1(z);
//           Z bn;
//           auto rz = rec(z);
//           for ( int k=1; k<n; ++k)
//           {
//             bn = 2*k*b1*rz-b0;
//             b0 = b1;
//             b1 = bn;
//           }
//           return bn;
//         };

//         auto minus_log10_cyl_j_at_infinity = []( auto n, auto az ) {
//           // Auxiliary function to calculate -log( Jn(x->INF) ).
//           return e_t(0.5)*eve::log10(e_t(6.28)*n) - n*eve::log10(e_t(1.36)*az/n);
//         };

//         auto ini_for_br_1 = [minus_log10_cyl_j_at_infinity](auto az, auto mg)
//         {
//           // Starting point for backward recurrence
//           //  for when |Jn(x)|~10e-mg
//           //  using the secant method.
//           auto n0 = inc(eve::nearest( e_t(1.1)*az));
//           auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - mg;
//           auto n1 = n0 + 5;
//           auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - mg;
//           auto nn = n1 - (n1 - n0)/oneminus(f0/f1);
//           auto f = minus_log10_cyl_j_at_infinity(nn, az) - mg;
//           auto test = eve::abs(nn - n1) > 1;
//           while ( eve::any(test) )
//           {
//             n0 = n1;
//             f0 = f1;
//             n1 = nn;
//             f1 = f;
//             nn = eve::if_else(test, n1 - (n1 - n0)/oneminus(f0/f1), nn);
//             f =  eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - mg, f);
//             test =  eve::abs(nn - n1) > 1;
//           }
//           return eve::trunc(nn);
//         };

//         auto ini_for_br_2 = [minus_log10_cyl_j_at_infinity](auto n, auto az, auto sd){
//           // Starting point for backward recurrence
//           //  for when Jn(x) has sd significant digits
//           //  using the secant method.
//           auto hmp = eve::half(eve::as<e_t>())*sd;
//           auto ejn = minus_log10_cyl_j_at_infinity(n, az);
//           auto t = ejn <= hmp;
//           auto obj = eve::if_else(t, sd, hmp+ejn);
//           auto n0  = eve::if_else(t, eve::nearest(e_t(1.1)*az), n);
//           auto f0 = minus_log10_cyl_j_at_infinity(n0, az) - obj;
//           auto n1 = n0 + 5;
//           auto f1 = minus_log10_cyl_j_at_infinity(n1, az) - obj;
//           auto nn = n1 - (n1-n0)/oneminus(f0/f1);
//           auto f = minus_log10_cyl_j_at_infinity(nn, az) - obj;
//           auto test = eve::abs(nn - n1) >= 1;
//           while ( eve::any(test))
//           {
//             n0 = n1;
//             f0 = f1;
//             n1 = nn;
//             f1 = f;
//             nn = eve::if_else(test, n1 - (n1-n0)/(oneminus(f0/f1)), nn);
//             f  = eve::if_else(test, minus_log10_cyl_j_at_infinity(nn, az) - obj, f);
//             test = eve::abs(nn - n1) >= 1;
//           }
//           return eve::trunc(nn + 10);
//         };

//         auto backward = [az, n, ini_for_br_1, ini_for_br_2](auto z){
//           auto m = ini_for_br_1(az, e_t(200));
//           m = eve::if_else ( m >= n, ini_for_br_2(n, az, e_t(15)), m);
//           auto cf2 = Z(0);
//           auto cf1 = complex(eve::sqrtsmallestposval(eve::as< e_t>()));
//           Z cf(cf2);
//           Z bn(cf);
//           auto k = m;
//           auto kgez = eve::is_gez(k);
//           while (eve::any(kgez))
//           {
//             cf  = kyosu::if_else(kgez,  2*inc(k)*cf1*rec(z)-cf2, cf);
//             bn  = kyosu::if_else ( k == n, cf, bn);
//             cf2 = kyosu::if_else(kgez, cf1, cf2);
//             cf1 = kyosu::if_else(kgez, cf, cf1);
//             k = dec(k);
//             kgez = eve::is_gez(k);
//           }
//           auto j0 = cyl_bessel_j0(z);
//           auto j1 = cyl_bessel_j1(z);
//           bn *= eve::if_else ( sqr_abs(j0) > sqr_abs(j1), j0/cf, j1/cf2);

//           return bn;
//         };

//         auto srz = eve::signnz(real(z));
//         z *= srz;

//         auto r = kyosu::if_else(is_eqz(az), Z(0), eve::nan(eve::as(az)));
//         auto notdone = kyosu::is_nan(r);
//         if( eve::any(notdone) )
//         {
//           notdone = next_interval(forward, notdone, 8*n < az, r, z);
//           if( eve::any(notdone) )
//           {
//             last_interval(backward, notdone, r, z);
//           }
//         }
//         auto sgnaltern = [n](auto x){return eve::if_else(eve::is_ltz(x), eve::one, eve::sign_alternate(n));};
//         return sgnaltern(srz)*sgnaltern(n)*r;
//       }
//     }
//     else
//     {
//       return cayley_extend_rev(cyl_bessel_jn, nn, z);
//     }
//   }

//   template<eve::integral_scalar_value N, typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_in>, N n, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       using e_t = as_real_t<Z>;
//       auto miton = [](N n){
//         if (n%4 == 0) return complex(eve::one(eve::as<e_t>()));
//         else if (n%4 == 1) return  complex(eve::zero(eve::as<e_t>()), eve::mone(eve::as<e_t>()));
//         else if (n%4 == 2) return complex(eve::mone(eve::as<e_t>()));
//         else return complex(eve::zero(eve::as<e_t>()), eve::one(eve::as<e_t>()));
//       };
//       return miton(n)*cyl_bessel_jn(n,complex(-ipart(z), real(z)));
//     }
//     else
//     {
//       return cayley_extend_rev(cyl_bessel_in, n, z);
//     }
//   }


//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_i0>, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       return cyl_bessel_in(0, z);
//     }
//     else
//     {
//       return cayley_extend(cyl_bessel_i0, z);
//     }
//   }

//   template<typename Z>
//   auto dispatch(eve::tag_of<kyosu::cyl_bessel_i1>, Z z) noexcept
//   {
//     if constexpr(concepts::complex<Z> )
//     {
//       return cyl_bessel_in(1, z);
//     }
//     else
//     {
//       return cayley_extend(cyl_bessel_i1, z);
//     }
//   }

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
