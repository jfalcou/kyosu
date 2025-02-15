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

TTS_CASE_TPL ( "Check hyper 2F1"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-3, 1.0e-8);
  using r_t = kyosu::cayley_dickson<T, 2>;
  r_t I = r_t(0.0, 1.0);
  r_t cinf = kyosu::cinf(eve::as<r_t>());
  TTS_RELATIVE_EQUAL(0, 0, pr);
  if constexpr(sizeof(T) == 8)
  {
  std::cout << cinf << std::endl;
//     {
//       eve::wide z{0.5, 0.5, 0.5, 0.5};
//       eve::wide a{-2.0, 1.0, 2.0, 1.5};
//       eve::wide b{1.0, -2.0, 1.0, 2.0};
//       eve::wide c{-3.5, -3.5, -3.0, -3.0};
//       eve::wide res{1.34285714285714 + 0*I, 1.34285714285714 + 0*I, cinf, cinf};
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
//     {
//       eve::wide z{0.5, 0.5, 0.5, 0.5};
//       eve::wide a{2.0, 1.5, -1.0, 2.0};
//       eve::wide b{1.0, -2.0, -2.0,  1.0};
//       eve::wide c{-3.0, -3.5, -3.0,  3.5};
//       eve::wide res{1.41666666666667 + 0*I, 1.53571428571429 + 0*I, 0.666666666666667 + 0*I, 1.43805509807655 + 0*I};
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
  {
      eve::wide z{-3.0, 30.0, -5.0, 1.04};
      eve::wide a{-2.0, 1.0, 1.0, 1.0};
      eve::wide b{1.0,  2.0,  2.0,  2.0};
      eve::wide c{ 3.5,  3.5,  3.5,  3.5};
      eve::wide res{3.85714 + 0*I, -0.094543453005056519816-0.0128699542349234016572936919*I, -332.644427109329 - 224.988297979129*I, 23.6353087752503 + 25.8503131412842*I};
      using w_t =  eve::wide<r_t, eve::fixed<2>>;
//       auto r00 =  kyosu::hypergeometric(w_t(z.get(0)), kumi::tuple{w_t(a.get(0)), w_t(b.get(0))}, kumi::tuple{w_t(c.get(0))});
//       auto r0 =  kyosu::hypergeometric(z.get(0), kumi::tuple{a.get(0), b.get(0)}, kumi::tuple{c.get(0)});
      auto r1 =  kyosu::hypergeometric(z.get(1), kumi::tuple{a.get(1), b.get(1)}, kumi::tuple{c.get(1)});
      auto r11 =  kyosu::hypergeometric(w_t(z.get(1)), kumi::tuple{w_t(a.get(1)), w_t(b.get(1))}, kumi::tuple{w_t(c.get(1))});
//       auto r2 =  kyosu::hypergeometric(z.get(2), kumi::tuple{a.get(2), b.get(2)}, kumi::tuple{c.get(2)});
//       auto r3 =  kyosu::hypergeometric(z.get(3), kumi::tuple{a.get(3), b.get(3)}, kumi::tuple{c.get(3)});     std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;

//       auto r3 =  kyosu::hypergeometric(z.get(3), kumi::tuple{a.get(3), b.get(3)}, kumi::tuple{c.get(3)});
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << "r3 " << r3 << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;



//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//       std::cout << " ================================================================================================== " << std::endl;
//       std::cout << "r " << r << std::endl;
//       std::cout << " ================================================================================================== " << std::endl;
//       std::cout << " ================================================================================================== " << std::endl;

      std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
      std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
 //      std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << "r00 " << r00 << std::endl;
//       std::cout << "r0 " << r0 << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
      std::cout << "r11 " << r11 << std::endl;
      std::cout << "r1 " << r1 << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << "r2 " << r2 << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << "r3 " << r3 << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
//       std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
      std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
      std::cout << " -------------------------------------------------------------------------------------------------- " << std::endl;
   }


//     {
//       eve::wide z{0.96 + 0*I, 0.96 + 0*I, 0.4-1.2*I, 0.4-2.0*I};
//       eve::wide a{1.0, 1.0, -20.4, -20.4};
//       eve::wide b{2.0,  2.0, -20.4, -12.1};
//       eve::wide c{3.5,  3.5,-20.4,-20.4};
//       eve::wide res{3.25898889914176 + 0*I, 0.784430166457414+ 0*I, -332.644427109329 - 224.988297979129*I, 23.6353087752503 + 25.8503131412842*I };
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
  }
//   else
//   {
//     {
//       eve::wide z{0.5f, 0.5f, 0.5f, 0.5f};
//       eve::wide a{-2.0f, 1.0f, 2.0f, 1.5f};
//       eve::wide b{1.0f, -2.0f, 1.0f, 2.0f};
//       eve::wide c{-3.5f, -3.5f, -3.0f, -3.0f};
//       eve::wide res{1.34285714285714f + 0*I, 1.34285714285714f + 0*I, cinf, cinf};
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
//     {
//       eve::wide z{0.5f, 0.5f, 0.5f, 0.5f};
//       eve::wide a{2.0f, 1.5f, -1.0f, 2.0f};
//       eve::wide b{1.0f, -2.0f, -2.0f,  1.0f};
//       eve::wide c{-3.0f, -3.5f, -3.0f,  3.5f};
//       eve::wide res{1.41666666666667f + 0*I, 1.53571428571429f + 0*I, 0.666666666666667f + 0*I, 1.43805509807655f + 0*I};
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
//     {
//       eve::wide z{-3.0f, 30.0f, -5.0f, 1.04f};
//       eve::wide a{2.0f, 1.0f, 1.0f, 1.0f};
//       eve::wide b{1.0f,  2.0f,  2.0f,  2.0f};
//       eve::wide c{ 3.5f,  3.5f,  3.5f,  3.5f};
//       eve::wide res{3.25898889914176f + 0*I, 0.784430166457414f + 0*I, -332.644427109329f - 224.988297979129f*I, 23.6353087752503f + 25.8503131412842f*I};
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
//     {
//       eve::wide z{0.96f + 0*I, 0.96f + 0*I, 0.4f-1.2f*I, 0.4f-2.0f*I};
//       eve::wide a{1.0f, 1.0f, -20.4f, -20.4f};
//       eve::wide b{2.0f,  2.0f, -20.4f, -12.1f};
//       eve::wide c{3.5f,  3.5f,-20.4f,-20.4f};
//       eve::wide res{3.25898889914176f + 0*I, 0.784430166457414f+ 0*I, -332.644427109329f - 224.988297979129f*I, 23.6353087752503f + 25.8503131412842f*I };
//       auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
//       TTS_RELATIVE_EQUAL(r, res, pr);
//     }
//   }

};
