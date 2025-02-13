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
  r_t I = r_t(0.0, 1.0);
  r_t res[] = {r_t(1.0, 0.0), r_t(2.9804751679668771e-05, 0), r_t(-7.8075602538993698e09, -2.051570308163214752e09)};
  int i = 0;
  r_t r =  kyosu::hypergeometric(r_t(0.0), kumi::tuple{r_t(3.0)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.4), kumi::tuple{r_t(-20.4)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.4+3.0*I), kumi::tuple{r_t(-20.4)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
};
