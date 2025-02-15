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

TTS_CASE_TPL ( "Check hyper 1F1"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-2, 1.0e-7);
  using r_t = kyosu::cayley_dickson<T, 2>;
  r_t I = r_t(0.0, 1.0);
  r_t res[] = {r_t(1.0, 0.0),
               r_t(-0.1269693745281, 0),
               r_t(0.07950472902909, 0.0),
               kyosu::cinf(eve::as<r_t>()),
               r_t(2.68, 0.0),
               r_t(0.07950472902909934, 0.0),
               r_t(-136.227503222143526977, 41.13766180660205530874),
               r_t(1.08556626293120142, -0.9298264679463321554100)
  };
  int i = 0;
  r_t r =  kyosu::hypergeometric(r_t(0.0), kumi::tuple{r_t(-20.4)}, kumi::tuple{r_t(2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.4), kumi::tuple{r_t(-20.4)}, kumi::tuple{r_t(2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(2.4), kumi::tuple{r_t(-20.4)}, kumi::tuple{r_t(2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(2.4), kumi::tuple{r_t(-20.4)}, kumi::tuple{r_t(-2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(2.4), kumi::tuple{r_t(-2)}, kumi::tuple{r_t(-4.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(2.4), kumi::tuple{r_t(-20.4)}, kumi::tuple{r_t(2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.5+20.4*I), kumi::tuple{r_t(-2.4)}, kumi::tuple{r_t(2.0)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);
  r =  kyosu::hypergeometric(r_t(0.5+20.4*I), kumi::tuple{r_t(-2.4+I)}, kumi::tuple{r_t(2.0+5.0*I)});
  TTS_RELATIVE_EQUAL(r, res[i++], pr);

};
