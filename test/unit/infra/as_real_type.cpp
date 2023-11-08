//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_TPL( "Check as_real_type_t behavior on real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_TYPE_IS(kyosu::as_real_type_t<T>, T);
};

TTS_CASE_TPL( "Check as_real_type_t behavior on non-real types", kyosu::real_types)
<typename T>(tts::type<T>)
{
  TTS_TYPE_IS(kyosu::as_real_type_t<kyosu::complex_t<T>>    , T);
  TTS_TYPE_IS(kyosu::as_real_type_t<kyosu::quaternion_t<T>> , T);
  TTS_TYPE_IS(kyosu::as_real_type_t<kyosu::octonion_t<T>>   , T);
};
