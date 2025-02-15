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
   {
      eve::wide z{0.5, 0.5, 0.5, 0.5};
      eve::wide a{-2.0, 1.0, 2.0, 1.5};
      eve::wide b{1.0, -2.0, 1.0, 2.0};
      eve::wide c{-3.5, -3.5, -3.0, -3.0};
      eve::wide res{1.34285714285714 + 0*I, 1.34285714285714 + 0*I, cinf, cinf};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }
    {
      eve::wide z{0.5, 0.5, 0.5, 0.5};
      eve::wide a{2.0, 1.5, -1.0, 2.0};
      eve::wide b{1.0, -2.0, -2.0,  1.0};
      eve::wide c{-3.0, -3.5, -3.0,  3.5};
      eve::wide res{1.41666666666667 + 0*I, 1.53571428571429 + 0*I, 0.666666666666667 + 0*I, 1.43805509807655 + 0*I};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }
    {
      eve::wide z{-3.0, 30.0, -5.0, 1.04};
      eve::wide a{-2.0, 1.0, 1.0, 1.0};
      eve::wide b{1.0,  2.0,  2.0,  2.0};
      eve::wide c{ 3.5,  3.5,  3.5,  3.5};
      eve::wide res{3.8571428571428571 + 0*I,
          -0.094543453005056519816-0.0128699542349234016572936919*I,
          0.2924304510986073277883+0*I,
          4.26012617974385730373092 -2.136130533701953350*I};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }


    {
      eve::wide z{0.96 + 0*I, -0.5 + 0*I, 0.4-1.2*I, 0.4-2.0*I};
      eve::wide a{1.0,         1.0,       -20.4,     -20.4};
      eve::wide b{2.0,         2.0,       -20.4,     -12.1};
      eve::wide c{3.5,         3.5,       -20.4,     -20.4};
      eve::wide res{3.25898889914176 + 0*I,
          0.784430166457414+ 0*I,
          -332.644427109329 - 224.988297979129*I,
          -7202.950681649458 + 1670.99237074548870*I };
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }

    {
      eve::wide z{0.96 + 2*I,  -0.5 + 4*I,     1.2*I,        -2.0*I};
      eve::wide a{1.0+0.0*I,      1+1.0*I,     0.4+0.0*I,     1.2*I};
      eve::wide b{-2.5+0.0*I,   2.0+2.0*I,     -20.4+I,      -12.1*I};

      eve::wide c{-43.5+0.0*I,  3.5+0.0*I,     -2.4+0.0*I, -2.4+0.0*I};
      eve::wide res{1.1172786872818116653 -0.01890970717512781*I,
                    0.08945210258112101 -0.160349515471060001*I,
                    205698.58578614875114764 +3338237.860363822376580*I,
                    -7.9608516398905606382595 -13.660975125299382850*I };
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);


//       auto r0 =  kyosu::hypergeometric(z.get(0), kumi::tuple{a.get(0), b.get(0)}, kumi::tuple{c.get(0)});
//       TTS_RELATIVE_EQUAL(r0, res.get(0), pr);
//       auto r1 =  kyosu::hypergeometric(z.get(1), kumi::tuple{a.get(1), b.get(1)}, kumi::tuple{c.get(1)});
//       TTS_RELATIVE_EQUAL(r1, res.get(1), pr);
//       auto r2 =  kyosu::hypergeometric(z.get(2), kumi::tuple{a.get(2), b.get(2)}, kumi::tuple{c.get(2)});
//       TTS_RELATIVE_EQUAL(r2, res.get(2), pr);
//       auto r3 =  kyosu::hypergeometric(z.get(3), kumi::tuple{a.get(3), b.get(3)}, kumi::tuple{c.get(3)});
//       TTS_RELATIVE_EQUAL(r3, res.get(3), pr);
     }

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
