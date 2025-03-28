//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::is_not_fnan over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
  (auto data)
{
  TTS_EQUAL(kyosu::is_not_fnan(data), eve::is_not_nan(data));
};

TTS_CASE_WITH ( "Check kyosu::is_not_fnan over complex"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10), tts::randoms(-10,10))
              )
  (auto r, auto i)
{
  using T = kyosu::complex_t<decltype(r)>;
  TTS_EQUAL(kyosu::is_not_fnan(kyosu::complex(r,i)), eve::is_not_nan(r) || eve::is_not_nan(i));
  auto z(kyosu::nan(eve::as<T>()));
  std::cout << "z " << z << std::endl;
  TTS_EQUAL(kyosu::is_not_fnan(z), eve::true_(eve::as(r)));
  auto zz = kyosu::complex (eve::nan(eve::as(r)), eve::nan(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_fnan(zz), eve::false_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_fnan over quaternion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              )
              )
  <typename T>(T r, T i, T j, T k)
{
  using type = kyosu::quaternion_t<T>;
  auto z(kyosu::fnan(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_fnan(type(r,i,j,k)), eve::is_not_nan(r) || eve::is_not_nan(i) || eve::is_not_nan(j) || eve::is_not_nan(k));
  TTS_EQUAL(kyosu::is_not_fnan(z), eve::false_(eve::as(r)));
  type zz(kyosu::nan(eve::as<T>()));
  TTS_EQUAL(kyosu::is_not_fnan(zz), eve::true_(eve::as(r)));
};

TTS_CASE_WITH ( "Check kyosu::is_not_fnan over octonion"
              , kyosu::real_types
              , tts::generate ( tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)
                              , tts::randoms(-10,10), tts::randoms(-10,10)                              )
              )
  <typename T>(T r, T i, T j, T k, T l, T li, T lj, T lk)
{
  using type = kyosu::octonion_t<T>;
  auto z(kyosu::fnan(eve::as(r)));
  TTS_EQUAL(kyosu::is_not_fnan(type(r,i,j,k,l,li,lj,lk)), eve::is_not_nan(r) || eve::is_not_nan(i) || eve::is_not_nan(j) || eve::is_not_nan(k)
            || eve::is_not_nan(l) || eve::is_not_nan(li) || eve::is_not_nan(lj) || eve::is_not_nan(lk) );
  TTS_EQUAL(kyosu::is_not_fnan(z), eve::false_(eve::as(r)));
  type zz(eve::zero(eve::as<T>()), eve::nan(eve::as<T>()), eve::nan(eve::as<T>()), eve::nan(eve::as<T>()));
  TTS_EQUAL(kyosu::is_not_fnan(zz), eve::true_(eve::as(r)));
};
