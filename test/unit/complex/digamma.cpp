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

TTS_CASE_TPL( "Check log_abs_gamma", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  using z_t = kyosu::complex_t<T>;
  auto tcx = [](auto r,  auto i){return kyosu::to_complex(T(r), T(i)); };
  z_t one = tcx(1, 0);
  z_t zer = tcx(0, 0);
  z_t two = tcx(2, 0);
  z_t three = tcx(3, 0);
  z_t naninf = tcx(eve::nan(eve::as<e_t>()), eve::inf(eve::as<e_t>()));
  TTS_IEEE_EQUAL( kyosu::digamma(zer), naninf);
  TTS_IEEE_EQUAL( kyosu::digamma(-zer),naninf);
  TTS_RELATIVE_EQUAL( kyosu::real(kyosu::digamma(one)), e_t(-0.577215664901532860606512090082402431042159335939923598805767234), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::real(kyosu::digamma(two)), e_t(0.4227843350984671393934879099175975689578406640600764011942327651), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::real(kyosu::digamma(three)), e_t(0.9227843350984671393934879099175975689578406640600764011942327651), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::real(kyosu::digamma(tcx(-3.5, 0))), e_t(1.3888709263595289015114046193821968137592213477205182739052536985), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::real(kyosu::digamma(tcx(-3.75, 0))), e_t(-1.692388598311330343154465211031748512432179503643307206720214624), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::digamma(tcx(1, 1))    , tcx(9.4650320622476947e-02, 1.076674047468581174e+00), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::digamma(tcx(-1, 1))   , tcx(0.594650320622477, 2.576674047468582), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::digamma(tcx(1, -1))   , tcx(9.4650320622476947e-02, -1.076674047468581174e+00), 1.0e-4);
  TTS_RELATIVE_EQUAL( kyosu::digamma(tcx(-1, -1))  , tcx(0.594650320622477, -2.576674047468582), 1.0e-4);;
};
