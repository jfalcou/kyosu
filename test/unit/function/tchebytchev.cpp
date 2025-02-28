//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <eve/module/polynomial/regular/polynomial.hpp>

#include <kyosu/kyosu.hpp>
#include <test.hpp>


//==================================================================================================
//== tchebytchev tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tchebytchev on wide",
              kyosu::real_types,
              tts::generate(tts::between(-1.0, 1.0))
             )
  <typename T>(T const& a0)
{
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    for( unsigned int n = 0; n < 6; ++n )
    {
      TTS_ULP_EQUAL(eve::tchebytchev(n, a0), kyosu::real(kyosu::tchebytchev(T(n), a0)), 320);
      std::cout << eve::tchebytchev(n, a0) << std::endl;
      std::cout << kyosu::tchebytchev(T(n), a0) << std::endl;
      std::cout << eve::tchebytchev[eve::kind_2](n, a0) << std::endl;
      std::cout << kyosu::tchebytchev[eve::kind_2](T(n), a0) << std::endl;
    }
  }
};

// TTS_CASE_WITH("Check behavior of successor(tchebytchev)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::between(-1.0, 1.0)))
// <typename T>(T const& a0)
// {
//   auto t3 = eve::tchebytchev(3, a0);
//   auto t4 = eve::tchebytchev(4, a0);
//   auto t5 = eve::tchebytchev(5, a0);
//   TTS_ULP_EQUAL(eve::tchebytchev[eve::successor](a0, t4, t3), t5, 64);
//   using eve::kind_2;
//   auto u3 = eve::tchebytchev[kind_2](3, a0);
//   auto u4 = eve::tchebytchev[kind_2](4, a0);
//   auto u5 = eve::tchebytchev[kind_2](5, a0);
//   TTS_ULP_EQUAL(eve::tchebytchev[eve::successor](a0, u4, u3), u5, 300);
// };
// #else
// TTS_CASE("Check return types of tchebytchev")
// {
//   TTS_PASS("SKipping due to no reference available");
// };
// #endif
