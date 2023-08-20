//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL( "Check complex::div", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using c_t   = kyosu::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;
  using eve::div;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return 2*T(1+i); };
  auto fill   = [](auto i, auto) { return c_t(T(1+i),2*T(1+i)); };

  c_t   z_s1(T{1}, T{3}), z_s2(T{2}, T{-2});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex / complex
  TTS_EQUAL(div(z_s1  , z_s2  ) , (c_t{-0.5,1}));

  // complex / real / real / complex
  TTS_EQUAL(div(z_s1   , 1     ) , (c_t{1.   , 3. }));
  TTS_EQUAL(div(z_s1   , 2.    ) , (c_t{0.5  , 1.5}));
  TTS_EQUAL(div(z_s1   , 3.f   ) , (c_t{1./3 , 1. }));

  TTS_EQUAL(div(1      , z_s2  ) , (c_t{0.25 , 0.25 }));
  TTS_EQUAL(div(2.     , z_s2  ) , (c_t{0.5  , 0.5  }));
  TTS_EQUAL(div(4.f    , z_s2  ) , (c_t{1    , 1    }));

  // complex / wide real / wide real / complex
  TTS_RELATIVE_EQUAL(div(z_s1   , rv    ) , (wc_t{[&](auto i, auto){ return z_s1 / rv.get(i);}}), 1e-6);
  TTS_RELATIVE_EQUAL(div(rv     , z_s1  ) , (wc_t{[&](auto i, auto){ return rv.get(i) / z_s1;}}), 1e-6);

  // complex / wide complex / wide complex / complex
  TTS_RELATIVE_EQUAL(div(z_s1,  z_v1) , (wc_t{[&](auto i, auto){ return z_s1 / z_v1.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1,  z_s1) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / z_s1;}}), 1e-4);

  // wide complex / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / z_v2.get(i));}}), 1e-4);

  // wide complex / real / real / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 1     );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 2.    );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 3.f   );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(1      , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(1       / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(2.     , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(2.      / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(3.f    , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(3.f     / z_v1.get(i));}}), 1e-4);

  // wide complex / wide real / wide real / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / rv.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(rv     , z_v1  ) , (wc_t{[&](auto i, auto){ return rv.get(i)   / z_v1.get(i);}}), 1e-4);
};

TTS_CASE_TPL( "Check complex::operator/", kyosu::scalar_real_types)
<typename T>(tts::type<T>)
{
  using c_t   = kyosu::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return 2*T(1+i); };
  auto fill   = [](auto i, auto) { return c_t(T(1+i),2*T(1+i)); };

  c_t   z_s1(T{1}, T{3}), z_s2(T{2}, T{-2});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex / complex
  TTS_EQUAL((z_s1 /z_s2  ) , (c_t{-0.5,1}));

  // complex / real / real / complex
  TTS_EQUAL((z_s1 / 1     ) , (c_t{1.   , 3. }));
  TTS_EQUAL((z_s1 / 2.    ) , (c_t{0.5  , 1.5}));
  TTS_EQUAL((z_s1 / 3.f   ) , (c_t{1./3 , 1. }));

  TTS_EQUAL((1   / z_s2  ) , (c_t{0.25 , 0.25 }));
  TTS_EQUAL((2.  / z_s2  ) , (c_t{0.5  , 0.5  }));
  TTS_EQUAL((4.f / z_s2  ) , (c_t{1    , 1    }));

  // complex / wide real / wide real / complex
  TTS_RELATIVE_EQUAL((z_s1 / rv    ) , (wc_t{[&](auto i, auto){ return z_s1 / rv.get(i);}}), 1e-6);
  TTS_RELATIVE_EQUAL((rv   / z_s1  ) , (wc_t{[&](auto i, auto){ return rv.get(i) / z_s1;}}), 1e-6);

  // complex / wide complex / wide complex / complex
  TTS_RELATIVE_EQUAL((z_s1 / z_v1) , (wc_t{[&](auto i, auto){ return z_s1 / z_v1.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL((z_v1 / z_s1) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / z_s1;}}), 1e-4);

  // wide complex / wide complex
  TTS_RELATIVE_EQUAL((z_v1 / z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / z_v2.get(i));}}), 1e-4);

  // wide complex / real / real / wide complex
  TTS_RELATIVE_EQUAL((z_v1 / 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 1     );}}), 1e-4);
  TTS_RELATIVE_EQUAL((z_v1 / 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 2.    );}}), 1e-4);
  TTS_RELATIVE_EQUAL((z_v1 / 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 3.f   );}}), 1e-4);
  TTS_RELATIVE_EQUAL((1    / z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(1       / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL((2.   / z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(2.      / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL((3.f  / z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(3.f     / z_v1.get(i));}}), 1e-4);

  // wide complex / wide real / wide real / wide complex
  TTS_RELATIVE_EQUAL((z_v1 / rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / rv.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL((rv   / z_v1  ) , (wc_t{[&](auto i, auto){ return rv.get(i)   / z_v1.get(i);}}), 1e-4);
};
