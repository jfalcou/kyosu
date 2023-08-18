//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL( "Check complex::add", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using c_t   = kyosu::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;
  using eve::add;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill   = [](auto i, auto) { return kyosu::complex<T>(T(1+i),T(1)/(1+i)); };

  c_t   z_s1(T{1.234}, T{5.678}), z_s2(T{2.468}, T{1.357});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex + complex
  TTS_EQUAL(add(z_s1   , z_s2  ) , (c_t{3.702,7.035}));

  // complex + real / real + complex
  TTS_EQUAL(add(z_s1   , 1     ) , (c_t{2.234,5.678}));
  TTS_EQUAL(add(z_s1   , 2.    ) , (c_t{3.234,5.678}));
  TTS_EQUAL(add(z_s1   , 3.f   ) , (c_t{4.234,5.678}));

  TTS_EQUAL(add(1      , z_s1  ) , (c_t{2.234,5.678}));
  TTS_EQUAL(add(2.     , z_s1  ) , (c_t{3.234,5.678}));
  TTS_EQUAL(add(3.f    , z_s1  ) , (c_t{4.234,5.678}));

  // complex + wide real / wide real + complex
  TTS_EQUAL(add(z_s1   , rv    ) , (wc_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));
  TTS_EQUAL(add(rv     , z_s1  ) , (wc_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));

  // complex + wide complex / wide complex + complex
  TTS_EQUAL(add(z_s1 , z_v1) , (wc_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));
  TTS_EQUAL(add(z_v1 , z_s1) , (wc_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));

  // wide complex + wide complex
  TTS_EQUAL(add(z_v1   , z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + z_v2.get(i));}}));

  // wide complex + real / real + wide complex
  TTS_EQUAL(add(z_v1   , 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL(add(z_v1   , 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL(add(z_v1   , 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 3.f        );}}));
  TTS_EQUAL(add(1      , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL(add(2.     , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL(add(3.f    , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 3.f        );}}));

  // wide complex + wide real / wide real + wide complex
  TTS_EQUAL(add(z_v1   , rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
  TTS_EQUAL(add(rv     , z_v1  ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
};

TTS_CASE_TPL( "Check complex::operator+ ", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using c_t   = kyosu::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill   = [](auto i, auto) { return kyosu::complex<T>(T(1+i),T(1)/(1+i)); };

  c_t   z_s1(T{1.234}, T{5.678}), z_s2(T{2.468}, T{1.357});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex + complex
  TTS_EQUAL((z_s1   + z_s2  ) , (c_t{3.702,7.035}));

  // complex + real / real + complex
  TTS_EQUAL((z_s1   + 1     ) , (c_t{2.234,5.678}));
  TTS_EQUAL((z_s1   + 2.    ) , (c_t{3.234,5.678}));
  TTS_EQUAL((z_s1   + 3.f   ) , (c_t{4.234,5.678}));

  TTS_EQUAL((1      + z_s1  ) , (c_t{2.234,5.678}));
  TTS_EQUAL((2.     + z_s1  ) , (c_t{3.234,5.678}));
  TTS_EQUAL((3.f    + z_s1  ) , (c_t{4.234,5.678}));

  // complex + wide real / wide real + complex
  TTS_EQUAL((z_s1   + rv    ) , (wc_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));
  TTS_EQUAL((rv     + z_s1  ) , (wc_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));

  // complex + wide complex / wide complex + complex
  TTS_EQUAL((z_s1 + z_v1) , (wc_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));
  TTS_EQUAL((z_v1 + z_s1) , (wc_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));

  // wide complex + wide complex
  TTS_EQUAL((z_v1   + z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + z_v2.get(i));}}));

  // wide complex + real / real + wide complex
  TTS_EQUAL((z_v1   + 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL((z_v1   + 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL((z_v1   + 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 3.f        );}}));
  TTS_EQUAL((1      + z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL((2.     + z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL((3.f    + z_v1  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) + 3.f        );}}));

  // wide complex + wide real / wide real + wide complex
  TTS_EQUAL((z_v1   + rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
  TTS_EQUAL((rv     + z_v1  ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
};
