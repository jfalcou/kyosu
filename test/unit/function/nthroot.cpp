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
  //primary root
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  T fn(eve::floor(eve::iota(eve::as<T>())/2)+1);
  wi_t n(eve::iota(eve::as<wi_t>())/2+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, n), fn), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, fn), fn), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::real(kyosu::nthroot[kyosu::real_only](r0, fn)), eve::nthroot(r0, fn), tts::prec<T>() );
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, e_t(3)), e_t(3)), kyosu::complex(r0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(r0, 3), e_t(3)), kyosu::complex(r0), tts::prec<T>() );

  //kth root
  //scalar k scalar n
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, e_t(3), e_t(2)), kyosu::nthroot(r0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, e_t(3), 2     ), kyosu::nthroot(r0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, 3,      2     ), kyosu::nthroot(r0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );

  //simd k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, e_t(3), fn), kyosu::nthroot(r0, e_t(3))*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, e_t(3), n ), kyosu::nthroot(r0, e_t(3))*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );

  //scalar k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, fn, e_t(3)), kyosu::nthroot(r0, fn)*kyosu::exp_ipi(e_t(6)/fn), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, n, e_t(3) ), kyosu::nthroot(r0, n)*kyosu::exp_ipi( e_t(6)/fn), tts::prec<T>() );

  //simd k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, fn, fn), kyosu::nthroot(r0, fn), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, n, fn ), kyosu::nthroot(r0, n), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, n, n  ), kyosu::nthroot(r0, n), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(r0, fn, n ), kyosu::nthroot(r0, n), tts::prec<T>() );
};

TTS_CASE_WITH ( "Check kyosu::nthroot over complex"
              , kyosu::simd_real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
<typename T>  (T r0, T i0)
{
  //primary root
  using  e_t = eve::element_type_t<T>;
  using ce_t = kyosu::complex_t<T>;
  auto c0 = kyosu::complex(r0,i0);
  using wi_t =  eve::wide<unsigned int, eve::fixed<T::size()>>;
  T fn(eve::floor(eve::iota(eve::as<T>())/2)+1);
  wi_t n(eve::iota(eve::as<wi_t>())/2+1);
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(c0, n), fn), kyosu::complex(c0), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(c0, fn), fn), kyosu::complex(c0), tts::prec<T>() );
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::pow(kyosu::nthroot(c0, e_t(3)), e_t(3)), kyosu::complex(c0), tts::prec<T>() );

  //kth root
  //scalar k scalar n
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, e_t(3), e_t(2)), kyosu::nthroot(c0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, e_t(3), 2     ), kyosu::nthroot(c0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, 3,      2     ), kyosu::nthroot(c0, e_t(3))*kyosu::exp_ipi(e_t(4)/3), tts::prec<T>() );

  //simd k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, e_t(3), fn), kyosu::nthroot(c0, e_t(3))*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, e_t(3), n ), kyosu::nthroot(c0, e_t(3))*kyosu::exp_ipi(fn*2/3), tts::prec<T>() );

  //scalar k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, fn, e_t(3)), kyosu::nthroot(c0, fn)*kyosu::exp_ipi(e_t(6)/fn), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, n, e_t(3) ), kyosu::nthroot(c0, n)*kyosu::exp_ipi( e_t(6)/fn), tts::prec<T>() );

  //simd k simd n
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, fn, fn), kyosu::nthroot(c0, fn), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, n, fn ), kyosu::nthroot(c0, n), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, n, n  ), kyosu::nthroot(c0, n), tts::prec<T>() );
  TTS_RELATIVE_EQUAL(kyosu::nthroot(c0, fn, n ), kyosu::nthroot(c0, n), tts::prec<T>() );

  auto cond = eve::is_ltz(r0);

  TTS_RELATIVE_EQUAL(kyosu::nthroot[cond][kyosu::real_only](r0, 3),      kyosu::if_else(cond,  eve::nthroot(r0, 3), r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::nthroot[cond][kyosu::real_only](r0, e_t(3)), kyosu::if_else(cond,  eve::nthroot(r0, e_t(3)), r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::nthroot[cond][kyosu::real_only](r0, T(3)), kyosu::if_else(cond,  eve::nthroot(r0, T(3)), r0), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::nthroot[cond](r0, 3), kyosu::if_else(cond,  kyosu::nthroot(r0, 3), ce_t(r0)), tts::prec<T>());
  TTS_RELATIVE_EQUAL(kyosu::nthroot[cond](c0, 3), kyosu::if_else(cond,  kyosu::nthroot(c0, 3), c0), tts::prec<T>());
};
