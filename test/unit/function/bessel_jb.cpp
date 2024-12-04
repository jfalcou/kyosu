//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

// TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j"
//               , kyosu::scalar_real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
//   <typename T>(T )
// {
//   if constexpr(sizeof(T) == 8)
//   {
//     std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00
//         , -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01
//         , 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00
//         , 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
//     std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00
//         , 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00
//         , -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00
//         , -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

//     constexpr int N = 0;
//     T v1 = 1.0/3;
//     auto n = int(v1);
//     using vc_t = std::array<T, 16>;
//     using a_t = std::array<vc_t, N+1>;
//     a_t reresi_03{
//       vc_t{2.8090373106452773e+02, 1.7536493250871054e+01, -3.3400462158788272e+01, -2.3524142528283910e+01
//           , -9.3274540332656208e+00, -1.9656734427524503e+00, 4.3413771695853465e-01, 7.4917804310983560e-01
//           , 5.8501480583737409e-01, 1.0213243250718731e+00, 1.3227852389571668e+00, 1.9818890844578396e-01
//           , -6.0472153767481238e+00, -2.3374276615174153e+01, -5.1769656721627001e+01, -5.2626473557055462e+01
//           }

//     };
//     a_t imresi_03{
//       vc_t{-2.6513665958745401e+02, 1.5122859663021515e+02, -5.0648785179729913e+01, 7.0192828558358924e+00
//           , 4.0222943595848140e+00, -3.8995769510156886e+00, 1.9902620949926999e+00, -7.5756275269309670e-01
//           , 0.0000000000000000e+00, -1.1158707376004939e-01, 1.3330326497253218e+00, -4.1355677304829221e+00
//           , 7.6943469735731851e+00, -4.6838788665148172e+00, -2.8742293351241671e+01, 1.3952363114976131e+02
//           }
//     };

//     std::vector<kyosu::complex_t<T>> is_03(N+2), mis_03(N+1);
//     for (int k = 0; k < 16; ++k)
//     {
//       auto c = kyosu::complex(re[k], im[k]);
//       auto jl = kyosu::cyl_bessel_j(v1, c, std::span(is_03));
//       auto mjl = kyosu::bessel_j(v1, c, std::span(mis_03));
//       TTS_RELATIVE_EQUAL(mjl, jl, 1.e-2);
//       auto vv = T(N+1.0/3);
//       for (n = 0; n <= N; ++n)
//       {
//         auto refi_03=  kyosu::complex_t<T>(reresi_03[n][k], imresi_03[n][k]);
//         TTS_RELATIVE_EQUAL(refi_03, is_03[n], 1.e-2);
//         TTS_RELATIVE_EQUAL(refi_03,  kyosu::cyl_bessel_j(vv, c), 1.e-2);
//         if (n < N) TTS_RELATIVE_EQUAL(mis_03[n], is_03[n], 1.e-2);
//       }
//     }
//   }
// };


// TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j"
//               , kyosu::scalar_real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
//   <typename T>(T )
// {
//   if constexpr(sizeof(T) == 8)
//   {
//     std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00
//         , -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01
//         , 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00
//         , 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
//     std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00
//         , 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00
//         , -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00
//         , -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};

//     constexpr int N = 0;
//     T v1 = -1.0/3;
//     auto n = int(v1);
//     using vc_t = std::array<T, 16>;
//     using a_t = std::array<vc_t, N+1>;
//     a_t reresi_03{
//       vc_t{-8.9163143837610050e+01, -1.2219942089268812e+02, -6.0563369116851803e+01, -1.7842181975937766e+01
//           , -1.1860080210885884e+00, 2.3789187887624883e+00, 1.9232059348460351e+00, 1.1368224659946016e+00
//           , 1.3432948699326057e+00, 5.5139655214064687e-01, -4.8990051277299940e-01, -3.4926635951494012e+00
//           , -9.6925116789155155e+00, -1.5745152038061331e+01, -9.9352493046059109e-01, 9.4517830645215696e+01
//           }
//     };
//     a_t imresi_03{
//       vc_t{-3.7583808427575212e+02, 9.0801181249849066e+01, 3.6018913915299962e+00, -1.6864299541716473e+01
//           , 1.0089846321224439e+01, -3.6425542565379301e+00, 5.6128150602785309e-01, 4.7851915025080155e-01
//           , 0.0000000000000000e+00, -7.8534132361994757e-01, 1.7555311861860581e+00, -2.2254640329062294e+00
//           , -1.3912074018251386e+00, 1.7899970399493917e+01, -5.9204417397002132e+01, 1.1533747474469016e+02
//           }
//     };

//     std::vector<kyosu::complex_t<T>> is_03(N+2), mis_03(N+1);
//     for (int k = 0; k < 16; ++k)
//     {
//       auto c = kyosu::complex(re[k], im[k]);
//       auto jl = kyosu::cyl_bessel_j(v1, c, std::span(is_03));
//       auto mjl = kyosu::bessel_j(v1, c, std::span(mis_03));
//       TTS_RELATIVE_EQUAL(mjl, jl, 1.e-2);
//       auto vv = -T(N+1.0/3);
//       for (n = 0; n <= N; ++n)
//       {
//          auto refi_03=  kyosu::complex_t<T>(reresi_03[n][k], imresi_03[n][k]);
//         TTS_RELATIVE_EQUAL(refi_03, is_03[n], 1.e-2) << "n " << n  << " k " << k  << " c "<< c << " arg(c) "<< kyosu::arg(kyosu::conj(c)) << " < 1.57" << '\n';
//         TTS_RELATIVE_EQUAL(refi_03,  kyosu::cyl_bessel_j(vv, c), 1.e-2);
//         if (n < N) TTS_RELATIVE_EQUAL(mis_03[n], is_03[n], 1.e-2);
//       }
//     }
//   }
// };

// TTS_CASE_WITH ( "Check kyosu::sph_bessel_jn over real"
//               , kyosu::scalar_real_types
//               , tts::generate(tts::randoms(-10,10))
//               )
// <typename T>(T )
// {
//   if constexpr(sizeof(T) == 8)
//   {
//     std::array<T, 8> re{-3.5864413497599945e-01, 1.8305506745510136e+00, 4.8145177703097399e+00, 4.7301901125586436e+00, -4.3947566261794710e+00, 1.0212518380533187e+00, -4.1514744061148807e+00, 1.2766581423615309e-01};
//     std::array<T, 8> im{-1.4900727734412866e+00, 4.3733972760463349e+00, 6.3220189518343628e-01, 5.1967694618977767e-01, 6.2761895523580580e-01, 3.8772322566505766e+00, -4.6074082935612806e+00, -4.4849065338089478e+00};
//     std::array<T, 8> reres{2.6695000315635153e-02, -2.2215759788276843e+00, 2.5805202705605512e-01, 2.5337598654371535e-01, -2.6051834312740757e-01, -1.1816979617769454e+00, -3.2042363997219185e+00, -3.3242357291991742e-01};
//     std::array<T, 8> imres{2.7709520397028151e-02, 9.1259760936216550e-01, -1.9344122386863866e-02, -1.1252144284238647e-02, 8.5011995341820815e-03, -5.1276579958119139e-01, -2.1027562948226137e+00, 2.3711156404785037e+00};
//     for(int i=0; i < 8; ++i)
//     {
//       auto c = kyosu::complex(re[i], im[i]);
//       auto res = kyosu::complex(reres[i], imres[i]);
//       TTS_RELATIVE_EQUAL(kyosu::sph_bessel_jn(3, c), res, tts::prec<T>()) << i <<  " <- " << c << '\n';
//       TTS_RELATIVE_EQUAL(kyosu::sph_bessel_jn(3, c), kyosu::bessel_j[eve::spherical](3, c), tts::prec<T>());
//     }
//   }
// };


// TTS_CASE_WITH ( "Check kyosu::sph_bessel_jn over real"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10),
//                               tts::randoms(-10,10)
//                              )
//               )
// <typename T>(T a0, T a1)
// {
//   if constexpr(sizeof(eve::underlying_type_t<T>) == 8)
//   {
//     using u_t = eve::underlying_type_t<T>;
//     auto c =  kyosu::complex(a0, a1);
//     auto cb=  kyosu::conj(c);
//     auto cm=  -c;
//     auto cr=  kyosu::complex(a0);
//     auto ci=  kyosu::complex(T(0), a1);
//     auto zer =   kyosu::complex(T(0), T(0));
//     auto one =   kyosu::complex(T(1), T(0));
// //    auto fac = kyosu::sqrt(eve::pio_2(eve::as(kyosu::real(c)))*kyosu::rec(c));

//     using kyosu::sph_bessel_jn;

//     for(int i=0; i < 10 ; ++i)
//     {
// //      auto v = i+1.0/3.0; eve::third(eve::as(kyosu::real(c)));
//       auto jnc = sph_bessel_jn(i, c);
//       TTS_IEEE_EQUAL(jnc, eve::sign_alternate(u_t(i))*sph_bessel_jn(i, cm)) << "c " << c << "\n";
//       TTS_IEEE_EQUAL(jnc, kyosu::conj(sph_bessel_jn(i, cb)));
//       TTS_IEEE_EQUAL(jnc, kyosu::bessel_j[eve::spherical](i, c));
// //      TTS_IEEE_EQUAL(kyosu::bessel_j[eve::spherical](v, c), kyosu::bessel_j(v+0.5, c)*fac);
// //       std::cout << kyosu::bessel_j[eve::spherical](v, c) << std::endl;
// //       std::cout << kyosu::bessel_j(v+0.5, c)*fac << std::endl;
//       TTS_EXPECT(eve::all(kyosu::is_real(cr)));
//       TTS_EXPECT(eve::all(kyosu::is_pure(ci)));
//       TTS_IEEE_EQUAL(sph_bessel_jn(i, zer), i ? zer : one) << i << '\n';
//     }
//   }
// };


TTS_CASE_WITH ( "Check kyosu::bessel_j"
              , kyosu::real_types
              , tts::generate(tts::randoms(0,10),
                              tts::randoms(0,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto c =  kyosu::complex(a0, a1);
  std::cout << std::hexfloat << c << std::endl;
  using c_t = decltype(c);
//  auto fac = kyosu::sqrt(eve::pio_2(eve::as(u_t()))*kyosu::rec(c));
  auto N = 10;
  auto v0 = u_t(1.0/3.0);
  auto vN = v0+N;
  using kyosu::sph_bessel_jn;
  using kyosu::cyl_bessel_jn;
  using kyosu::cyl_bessel_j;
  using kyosu::bessel_j;
  using eve::spherical;
  using eve::cylindrical;

  std::array<c_t, 10> J10, j10;
  std::array<c_t, 3 > J3, j3;
  std::array<c_t, 10> Jv10, jv10;
  std::array<c_t, 3 > Jv3, jv3;

  auto pr = tts::prec<u_t>(1.0e-2, 1.0e-5);
  auto vJ10 = bessel_j(10, c, std::span(J10));
  auto vJ3  = bessel_j(10, c, std::span(J3));
  auto vj10 = bessel_j[spherical](10, c, std::span(j10));
  auto vj3  = bessel_j[spherical](10, c, std::span(j3));

  auto vJv10 = bessel_j(vN, c, std::span(Jv10));
  auto vJv3  = bessel_j(vN, c, std::span(Jv3));
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    std::cout << "Jv3[0]          "<< Jv3[0] << std::endl;
    std::cout << "bessel_j(v0, c) "<< bessel_j(v0, c) << std::endl;
  }
  auto vjv10 = bessel_j[spherical](vN, c, std::span(jv10));
  auto vjv3  = bessel_j[spherical](vN, c, std::span(jv3));

  TTS_RELATIVE_EQUAL(vJ10, vJ3, pr);
  TTS_RELATIVE_EQUAL(vj10, vj3, pr);
  TTS_RELATIVE_EQUAL(vJv10, vJv3, pr);
  TTS_RELATIVE_EQUAL(vjv10, vjv3, pr);
  auto vi = v0;
  for(int i=0; i < 2 ; ++i, vi+=1 )
  {
    std::cout << i << " ========================================= " << std::endl;
//     auto jn = sph_bessel_jn(i, c);
//     auto Jn = cyl_bessel_jn(i, c);
//     auto Jv = cyl_bessel_j(vi, c);
//     auto jv = kyosu::bessel_j(vi+0.5, c)*fac;
//     TTS_RELATIVE_EQUAL(bessel_j[spherical](i, c), jn, pr);
//     TTS_RELATIVE_EQUAL(bessel_j[spherical](vi, c), jv, pr);
//     TTS_RELATIVE_EQUAL(bessel_j[cylindrical](i, c), Jn, pr);
//     TTS_RELATIVE_EQUAL(bessel_j[cylindrical](vi, c), Jv, pr);
//     if (i < 3) TTS_RELATIVE_EQUAL(bessel_j[cylindrical](i, c), J3[i], pr);
//     TTS_RELATIVE_EQUAL(bessel_j[cylindrical](i, c), J10[i], pr) << i << '\n';
//     if (i < 3) TTS_RELATIVE_EQUAL(bessel_j[spherical](i, c), j3[i], pr);
//     TTS_RELATIVE_EQUAL(bessel_j[spherical](i, c), j10[i], pr) << i << '\n';
    if constexpr(sizeof(eve::element_type_t<T>) == 8)
      if (i < 3) TTS_RELATIVE_EQUAL(bessel_j[cylindrical](vi, c), Jv3[i], pr) << "vi " << vi << " i " << i << '\n';
//      TTS_RELATIVE_EQUAL(bessel_j[cylindrical](vi, c), Jv10[i], pr) << "vi " << vi << " i "<< i << '\n' <<  " c " << c << '\n';
//    if (i < 3) TTS_RELATIVE_EQUAL(bessel_j[spherical](v, c), jv3[i], pr) << "vi " << vi << " i " << i << '\n';;
    //   TTS_RELATIVE_EQUAL(bessel_j[spherical](v, c), jv10[i], pr) << "vi " << vi << " i "<< i << '\n';
  }
};
