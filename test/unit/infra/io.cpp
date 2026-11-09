//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <sstream>
#include <string>
#include <test.hpp>

TTS_CASE("Check the labels of the octonion basis in the stream output")
{
  using o_t = kyosu::octonion_t<double>;
  auto print = [](o_t const& z) {
    std::ostringstream s;
    s << z;
    return s.str();
  };

  TTS_EQUAL(print(o_t(1., 2., 3., 4., 5., 6., 7., 8.)), std::string("1 + 2i + 3j + 4k + 5l + 6il + 7jl + 8kl "));
};
