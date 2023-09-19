//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_TPL( "Check acos lilits", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using z_t = kyosu::as_complex_t<T>;
  auto tcx = [](auto r,  auto i){return kyosu::to_complex(T(r), T(i)); };
  z_t inf(eve::inf(eve::as<e_t>()), 0);
  z_t nan(eve::nan(eve::as<e_t>()), eve::nan(eve::as<e_t>()));
  z_t one = tcx(1, 0);
  z_t zer = tcx(0, 0);
  z_t two = tcx(2, 0);
  z_t three = tcx(3, 0);
  TTS_IEEE_EQUAL( kyosu::tgamma(zer), inf );
  TTS_IEEE_EQUAL( kyosu::tgamma(-zer), -inf);
  TTS_EQUAL( kyosu::tgamma(one), one );
  TTS_EQUAL( kyosu::tgamma(two), one);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(three), two, 1);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx( 3.5, 0)), tcx(3.323350970447843, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(-3.5, 0)), tcx(0.270088205852269, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(3.75, 0)), tcx(4.422988410460251, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(-3.75, 0)), tcx(0.267866128861417, 0), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(4, 0))   , tcx(6, 0)                , 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(1, 1))   , tcx( 0.498015668118356, -0.154949828301811), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(-1,1))   , tcx(-0.17153291990827267, +0.326482748210083), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(1, -1))  , tcx( 0.498015668118356, +0.154949828301811), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(-1,-1))  , tcx(-0.17153291990827267, -0.326482748210083), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(1, -2))  , tcx(0.1519040026700361, -0.01980488016185498), 1.0e-5);
  TTS_RELATIVE_EQUAL( kyosu::tgamma(tcx(-1,-2))  , tcx(-0.0323612885501927257,  -0.0112294242346326173504), 1.0e-5);
  TTS_IEEE_EQUAL( kyosu::tgamma(tcx(-1,0))   , tcx(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>())));
  TTS_RELATIVE_EQUAL( kyosu::tgamma(kyosu::to_complex(eve::half(eve::as<e_t>()))),  kyosu::to_complex(eve::tgamma(eve::half(eve::as<e_t>()))), 1.0e-5);
};
