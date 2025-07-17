//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::nthroot over real"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r0)
{
  using el_t =  eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, T(5)), kyosu::complex(eve::nthroot(r0, 5)), tts::prec<T>());
  auto sr = r0.get(0);
//   std::cout << kyosu::nthroot(sr, el_t(5))<< std::endl;
//   std::cout << kyosu::complex(eve::nthroot(r0, el_t(5)))<< std::endl;
  std::cout <<sr << " 5 -> " << eve::nthroot(sr, el_t(5)) << std::endl;
   std::cout <<sr << " 5 -> " << kyosu::nthroot(sr, el_t(5)) << std::endl;
 std::cout <<sr << " 4 -> " << eve::nthroot(sr, el_t(4)) << std::endl;
   std::cout <<sr << " 4 -> " << kyosu::nthroot(sr, el_t(4)) << std::endl;
   TTS_RELATIVE_EQUAL(kyosu::nthroot(sr, el_t(5)),  eve::sign(sr)*kyosu::pow(eve::sign(sr)*sr, el_t(0.2)) , tts::prec<el_t>()) << "sr " << sr << '\n';
  TTS_RELATIVE_EQUAL(kyosu::nthroot(sr, el_t(4)),  kyosu::pow(sr, el_t(0.25)), tts::prec<el_t>());

//   using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
//   wi_t n(4); //eve::iota(eve::as<wi_t>())+1);
//   T    fn(4); //eve::iota(eve::as<T>())+1);
//   std::cout << "n  " << n << std::endl;
//   std::cout << "fn " << fn << std::endl;
//  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, n), kyosu::complex(eve::pow(r0, eve::rec(fn))), tts::prec<T>() );
//   TTS_RELATIVE_EQUAL(kyosu::nthroot(kyosu::complex(r0),fn), kyosu::complex(eve::pow(r0, eve::rec(fn))), tts::prec<T>() );
//   TTS_IEEE_EQUAL(kyosu::nthroot(r0, fn), kyosu::nthroot(r0, n));
};

// TTS_CASE_WITH ( "Check kyosu::nthroot over complex"
//               , kyosu::real_types
//               , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10)
//                              ,tts::randoms(-10,10), tts::randoms(-10,10)
//                              )
//               )
// (auto r0, auto i0, auto r1, auto i1)
// {
//   using T =  decltype(r0);
//   auto c0 = kyosu::complex(r0,i0);
//   auto c1 = kyosu::complex(r1,i1);
//   TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, c1), kyosu::pow(kyosu::abs(c0), c1), tts::prec<T>());
// //  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, c1), kyosu::pow(kyosu::abs(r0), c1), tts::prec<T>());
// //  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, r1), eve::pow(kyosu::abs(c0), r1), 2e-4);
// };

// TTS_CASE_WITH ( "Check kyosu::nthroot over quaternion"
//               , kyosu::real_types
//               , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               , tts::randoms(-10,10), tts::randoms(-10,10)
//                               )
//               )
// <typename T>(T r0, T i0, T j0, T k0, T r1, T i1, T j1, T k1)
// {
//   using type = kyosu::quaternion_t<T>;
//   auto q0 = type(r0,i0,j0,k0);
//   auto q1 = type(r1,i1,j1,k1);
//   TTS_RELATIVE_EQUAL(kyosu::nthroot(q0, q1), kyosu::pow(kyosu::abs(q0), q1), tts::prec<T>());
// //   TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, q1), kyosu::pow(kyosu::abs(r0), q1), tts::prec<T>());
// //   TTS_RELATIVE_EQUAL(kyosu::nthroot(q0, r1), eve::pow(kyosu::abs(q0), r1), 2e-4);
// };
