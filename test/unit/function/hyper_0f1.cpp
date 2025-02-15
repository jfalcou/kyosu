//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <iomanip>
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <eve/wide.hpp>
#include <iostream>

TTS_CASE_TPL ( "Check hyper 1F0"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
  using r_t = kyosu::cayley_dickson<T, 2>;
  r_t res[] = {r_t(1.0, 0.0),
               r_t(0.8227512861083565818, 0),
               kyosu::cinf(eve::as<r_t>()),
               r_t(6.822479299281938112227, 0.0),
               r_t(3.825376991857549983, -1.9848051342921483)
  };
  int i = 0;
  r_t r =  kyosu::hypergeometric(T(0.0), kumi::tuple{}, kumi::tuple{T(-20.4)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(T(4.0), kumi::tuple{}, kumi::tuple{T(-20.4)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(T(0.4), kumi::tuple{}, kumi::tuple{T(-3.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(T(4.0), kumi::tuple{}, kumi::tuple{T(1.5)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(-2.4, 1.0), kumi::tuple{}, kumi::tuple{T(-2.3)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
};
