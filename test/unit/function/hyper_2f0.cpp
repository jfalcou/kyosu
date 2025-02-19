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

TTS_CASE_TPL ( "Check hyper 2F0"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
  using r_t = kyosu::cayley_dickson<T, 2>;
  r_t r;
  r_t res[] = {r_t(1.0, 0.0),
               r_t(0.548563416668060, 0.377068308602826), //eve::nan(eve::as<T>()), 0),
               r_t(0.52, 0.0),
               r_t(169, 0.0),
               r_t(121, 0.0),
               r_t(1.04166637647907, 8.34584913683906e-8)};
  int i = 0;
  r =  kyosu::hypergeometric(r_t(0.0), kumi::tuple{r_t(-2.0), r_t(1.0)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(10.0), kumi::tuple{r_t(1.5), r_t(0.2)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.4), kumi::tuple{r_t(-2.0), r_t(1.0)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(4.0), kumi::tuple{r_t(-2.0), r_t(3.0)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(4.0), kumi::tuple{r_t(-2.0), -r_t(3.0)}, kumi::tuple{});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
};
