//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cyl_bessel_j"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    auto N = 5;
    auto v1 = 1.0/3.0;
    std::vector<kyosu::complex_t<T>> is_03(N+1);
    std::vector<kyosu::complex_t<T>> is_03b(N+1);
    auto c = kyosu::complex(-5.3, 8.0);
    auto v2 = v1+N;
    kyosu::cyl_bessel_j(v2, c, std::span(is_03));
    kyosu::bessel_j(v2, c, std::span(is_03b));

    for (int n = 0; n <= N; ++n)
    {
//         auto refi_03=  kyosu::complex_t<T>(reresi_03[n][k], imresi_03[n][k]);
//        TTS_RELATIVE_EQUAL(refi_03, is_03[n], 1.e-2) << "n " << n  << " k " << k  << " c "<< c << " arg(c) "<< kyosu::arg(kyosu::conj(c)) << " < 1.57" << '\n';
//        TTS_RELATIVE_EQUAL(refi_03, is_03b[n], 1.e-2) << "n " << n  << " k " << k  << " c "<< c << " arg(c) "<< kyosu::arg(kyosu::conj(c)) << " < 1.57" << '\n';
      auto vv = n+v1;
      TTS_RELATIVE_EQUAL(is_03[n],  kyosu::cyl_bessel_j(vv, c), 1.e-2) << "vv " << vv << " n " << n  << " c "<< c <<'\n';
      TTS_RELATIVE_EQUAL(is_03b[n],  kyosu::bessel_j(vv, c), 1.e-2) << "vv " << vv << " n " << n  << " c "<< c <<'\n';
      std::cout << n <<  " -> " << is_03b[n] << std::endl;
    }
  }
};
