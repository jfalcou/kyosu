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
  r_t  nan = kyosu::nan(eve::as<r_t>());
  if constexpr(sizeof(T) == 8)
  {
    {
      eve::wide z{0.5, 0.5, 0.5, 0.5};
      eve::wide a{-2.0, 1.0, 2.0, 1.5};
      eve::wide b{1.0, -2.0, 1.0, 2.0};
      eve::wide c{-3.5, -3.5, -3.0, -3.0};
      eve::wide res{1.34285714285714 + 0*I, 1.34285714285714 + 0*I, nan, nan};
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
    }

    {
      auto hf = 0.5;
      eve::wide z{ 19.0, 25.0, 21.5, 10000.0, 0.5, -1.5, 0.1, -1.0};
      eve::wide n{ 4.0, 5.0, 6.0, 7.0, 0.0, 1.0, 2.0, 3.0};
      eve::wide a(n*hf);
      eve::wide b{(n+1)*hf};
      eve::wide c{n*hf+1.5};
      auto zz = -kyosu::rec(z*z);
      auto r =  kyosu::hypergeometric(zz, kumi::tuple{a, b}, kumi::tuple{c});
      for(int i=0; i < eve::cardinal_v<decltype(z)> ; ++i)
      {
        auto rr = kyosu::hypergeometric(zz.get(i), kumi::tuple{a.get(i), b.get(i)}, kumi::tuple{c.get(i)});
        TTS_RELATIVE_EQUAL(r.get(i), rr, pr) << "i" << i << "\n";
      }
    }
  }
  else
  {
    {
      eve::wide z{0.5f, 0.5f, 0.5f, 0.5f};
      eve::wide a{-2.0f, 1.0f, 2.0f, 1.5f};
      eve::wide b{1.0f, -2.0f, 1.0f, 2.0f};
      eve::wide c{-3.5f, -3.5f, -3.0f, -3.0f};
      eve::wide res{1.34285714285714f + 0*I, 1.34285714285714f + 0*I, nan, nan};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }
    {
      eve::wide z{0.5f, 0.5f, 0.5f, 0.5f};
      eve::wide a{2.0f, 1.5f, -1.0f, 2.0f};
      eve::wide b{1.0f, -2.0f, -2.0f,  1.0f};
      eve::wide c{-3.0f, -3.5f, -3.0f,  3.5f};
      eve::wide res{1.41666666666667f + 0*I, 1.53571428571429f + 0*I, 0.666666666666667f + 0*I, 1.43805509807655f + 0*I};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }
    {
      eve::wide z{-3.0f, 30.0f, -5.0f, 1.04f};
      eve::wide a{-2.0f, 1.0f, 1.0f, 1.0f};
      eve::wide b{1.0f,  2.0f,  2.0f,  2.0f};
      eve::wide c{ 3.5f,  3.5f,  3.5f,  3.5f};
      eve::wide res{3.8571428571428571f + 0*I,
          -0.094543453005056519816f-0.0128699542349234016572936919f*I,
          0.2924304510986073277883f+0*I,
          4.26012617974385730373092f -2.136130533701953350f*I};
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }
   {
      eve::wide z{0.96f + 0*I, -0.5f + 0*I, 0.4f-1.2f*I, 0.4f-2.0f*I};
      eve::wide a{1.0f,         1.0f,       -20.4f,     -20.4f};
      eve::wide b{2.0f,         2.0f,       -20.4f,     -12.1f};
      eve::wide c{3.5f,         3.5f,       -20.4f,     -20.4f};
      eve::wide res{3.25898889914176f + 0*I,
          0.784430166457414f+ 0*I,
          -332.644427109329f - 224.988297979129f*I,
          -7202.950681649458f + 1670.99237074548870f*I };
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }

    {
      eve::wide z{0.96f + 2*I,  -0.5f + 4*I,     1.2f*I,        -2.0f*I};
      eve::wide a{1.0f+0.0f*I,      1+1.0f*I,     0.4f+0.0*I,     1.2f*I};
      eve::wide b{-2.5f+0.0*I,   2.0f+2.0f*I,     -20.4+I,      -12.1f*I};

      eve::wide c{43.5f+0.0f*I,  3.5f+0.0f*I,     -2.4f+0.0f*I, -2.4f+0.0f*I};
      eve::wide res{0.9390912752f - 0.107445335799431f*I,
                    0.08945210258112101f -0.160349515471060001f*I,
                    205698.58578614875114764f +3338237.860363822376580f*I,
                    -7.9608516398905606382595f -13.660975125299382850f*I };
      auto r =  kyosu::hypergeometric(z, kumi::tuple{a, b}, kumi::tuple{c});
      TTS_RELATIVE_EQUAL(r, res, pr);
    }

    {
      auto hf = 0.5f;
      eve::wide z{ 19.0f, 25.0f, 21.5f, 10000.0f, 0.5f, -1.5f, 0.1f, -1.0f};
      eve::wide n{ 4.0f, 5.0f, 6.0f, 7.0f, 0.0f, 1.0f, 2.0f, 3.0f};
      eve::wide a(n*hf);
      eve::wide b{(n+1)*hf};
      eve::wide c{n*hf+1.5f};
      auto zz = -kyosu::rec(z*z);
      auto r =  kyosu::hypergeometric(zz, kumi::tuple{a, b}, kumi::tuple{c});
      for(int i=0; i < eve::cardinal_v<decltype(z)> ; ++i)
      {
        auto rr = kyosu::hypergeometric(zz.get(i), kumi::tuple{a.get(i), b.get(i)}, kumi::tuple{c.get(i)});
        TTS_RELATIVE_EQUAL(r.get(i), rr, pr) << "i" << i << "\n";
      }
    }

  }
};
