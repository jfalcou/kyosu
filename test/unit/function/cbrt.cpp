//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::cbrt over real"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10))
              )
  <typename T>  (T v)
{
  auto kr = kyosu::cbrt(v);
  TTS_RELATIVE_EQUAL(kyosu::pow(kr, 3), kyosu::complex(v), tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::cbrt over complex"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
  <typename T> (T r, T i)
{
  auto c = kyosu::complex(r,i);
  auto kc = kyosu::cbrt(c);
  TTS_RELATIVE_EQUAL(kyosu::pow(kc, 3), c, tts::prec<T>());
};

TTS_CASE_WITH ( "Check kyosu::cbrt over real"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T r0)
{
  //primary root
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  using e_t = eve::element_type_t<T>;
  T fn(eve::floor(eve::iota(eve::as<T>())/2)+1);
  wi_t n(eve::iota(eve::as<wi_t>())/2+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::cbrt(r0), 3), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::cbrt(r0), e_t(3)), kyosu::complex(r0), tts::prec<T>() );


  //kth root
  //scalar k
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::cbrt(r0, e_t(2)), kyosu::cbrt(r0)*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::cbrt(r0, 2     ), kyosu::cbrt(r0)*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::cbrt(r0, 2     ), kyosu::cbrt(r0)*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );

  //simd k
  TTS_RELATIVE_EQUAL(kyosu::cbrt(r0, fn), kyosu::cbrt(r0)*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::cbrt(r0, n ), kyosu::cbrt(r0)*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );
  auto cond = eve::is_ltz(r0);

  TTS_RELATIVE_EQUAL(kyosu::cbrt[cond][kyosu::real_only](r0), kyosu::if_else(cond,  eve::cbrt(r0), r0), tts::prec<T>());
 };

TTS_CASE_WITH ( "Check kyosu::cbrt over complex"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>  (T r0, T i0)
{
  auto c0 = kyosu::complex(r0, i0);
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  using e_t = eve::element_type_t<T>;
  T fn(eve::floor(eve::iota(eve::as<T>())/2)+1);
  wi_t n(eve::iota(eve::as<wi_t>())/2+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::cbrt(c0), 3), kyosu::complex(c0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::cbrt(c0), e_t(3)), kyosu::complex(c0), tts::prec<T>() );


  //kth root
  //scalar k
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::cbrt(c0, e_t(2)), kyosu::cbrt(c0)*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::cbrt(c0, 2     ), kyosu::cbrt(c0)*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );

  //simd k
  TTS_RELATIVE_EQUAL(kyosu::cbrt(c0, fn), kyosu::cbrt(c0)*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::cbrt(c0, n ), kyosu::cbrt(c0)*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );

  auto cond = eve::is_ltz(r0);

  TTS_RELATIVE_EQUAL(kyosu::cbrt[cond](c0, 2), kyosu::if_else(cond,   kyosu::cbrt(c0, 2), c0), tts::prec<T>());
};
