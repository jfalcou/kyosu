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
//== legendre tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of legendre on wide",
              kyosu::real_types,
              tts::generate(tts::between(-1.0, 1.0))
             )
  <typename T>(T const& a0)
{
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    for( unsigned int n = 0; n < 6; ++n )
    {
      TTS_ULP_EQUAL(eve::legendre(n, a0), kyosu::real(kyosu::legendre(T(n), a0)), 1000);
      std::cout << eve::legendre(n, a0) << std::endl;
      std::cout << kyosu::legendre(T(n), a0) << std::endl;
//       std::cout << eve::legendre[eve::q_kind](n, a0) << std::endl;
//       std::cout << kyosu::legendre[eve::q_kind](T(n), a0) << std::endl;
//        std::cout << kyosu::legendre[eve::q_kind](3.0, 4.0) << std::endl;
//        std::cout <<   eve::legendre[eve::q_kind](3.0, 4.0) << std::endl;
        std::cout <<  kyosu::hypergeometric(kyosu::rec(kyosu::sqr(4.0)), kumi::tuple{3.0, 3.5}, kumi::tuple{4.5});
    }
  }
};

// TTS_CASE_WITH("Check behavior of successor(legendre)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::between(-1.0, 1.0)))
// <typename T>(T const& a0)
// {
//   auto t3 = eve::legendre(3, a0);
//   auto t4 = eve::legendre(4, a0);
//   auto t5 = eve::legendre(5, a0);
//   TTS_ULP_EQUAL(eve::legendre[eve::successor](a0, t4, t3), t5, 64);
//   using eve::kind_2;
//   auto u3 = eve::legendre[kind_2](3, a0);
//   auto u4 = eve::legendre[kind_2](4, a0);
//   auto u5 = eve::legendre[kind_2](5, a0);
//   TTS_ULP_EQUAL(eve::legendre[eve::successor](a0, u4, u3), u5, 300);
// };
// #else
// TTS_CASE("Check return types of legendre")
// {
//   TTS_PASS("SKipping due to no reference available");
// };
// #endif
