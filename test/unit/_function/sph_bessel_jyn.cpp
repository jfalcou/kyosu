//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::sph_bessel_jn over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    std::array<T, 16> re{-5.2999999999999998e+00, -4.5999999999999996e+00, -3.8999999999999999e+00, -3.2000000000000002e+00, -2.5000000000000000e+00, -1.7999999999999998e+00, -1.1000000000000005e+00, -4.0000000000000036e-01, 2.9999999999999982e-01, 1.0000000000000000e+00, 1.7000000000000002e+00, 2.3999999999999995e+00, 3.0999999999999988e+00, 3.7999999999999998e+00, 4.4999999999999991e+00, 5.2000000000000002e+00};
    std::array<T, 16> im{8.0000000000000000e+00, -7.0000000000000000e+00, 6.0000000000000000e+00, -5.0000000000000000e+00, 4.0000000000000000e+00, -3.0000000000000000e+00, 2.0000000000000000e+00, -1.0000000000000000e+00, -0.0000000000000000e+00, 1.0000000000000000e+00, -2.0000000000000000e+00, 3.0000000000000000e+00, -4.0000000000000000e+00, 5.0000000000000000e+00, -6.0000000000000000e+00, 7.0000000000000000e+00};
    for(size_t i=0; i < re.size(); ++i)
    {
      using z_t =  kyosu::complex_t<T>;
      auto c = kyosu::complex(re[i], im[i]);
      int n = 6;
      std::vector<z_t> sjs(n+1), sys(n+1), sjsb(n+1), sysb(n+1) ;
      kyosu::sph_bessel_jn(n, c, sjsb);
      kyosu::sph_bessel_yn(n, c, sysb);

      kyosu::sph_bessel_jyn(n, c, sjs, sys);
      for(int k=0; k <= n; ++k)
      {
        TTS_RELATIVE_EQUAL(sjsb[k], sjs[k], 1.0e-7) << k <<  " <- " << c << '\n';
        TTS_RELATIVE_EQUAL(sysb[k], sys[k], 1.0e-7) << k <<  " <- " << c << '\n';
        TTS_RELATIVE_EQUAL(kyosu::sph_bessel_jn(k, c), sjs[k], 1.0e-7) << k <<  " <- " << c << '\n';
        TTS_RELATIVE_EQUAL(kyosu::sph_bessel_yn(k, c), sys[k], 1.0e-7) << k <<  " <- " << c << '\n';
      }
    }
  }
};
