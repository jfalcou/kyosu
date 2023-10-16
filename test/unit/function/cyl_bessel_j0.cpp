//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::scalar_real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  using e_t = eve::element_type_t<T>;
  if constexpr(sizeof(e_t) == 8)
  {
    std::cout.precision(17);
    std::array<T, 10> re{ e_t(-9.8403264736233908e+01), e_t(8.6287324687322851e+01), e_t(2.8677183208357349e+01), e_t(7.5642931882481321e+01), e_t(9.6351793077594323e+01)
        , e_t(-7.8716695947540288e+01), e_t(-5.0019457963533974e+01), e_t(5.9030075032843811e+01), e_t(-7.5596124248257235e+00), e_t(8.5810875418338028e+01)};

    std::array<T, 10> im{ e_t(-1.9271037994246587e+01), e_t(7.9043790847200569e+01), e_t(-3.0599555605285602e+01), e_t(-7.1720588923445590e+01), e_t(-6.1110206702938363e+01)
        , e_t(9.0167523214068439e+01), e_t(-7.0131934820406244e+01), e_t(-9.3405497312943496e+01), e_t(8.3431692318213322e+01), e_t(-4.1557438097347173e+01)};

    std::array<T, 10> reres{e_t(-8.8414975251226071e+06), e_t(-3.9177291392384149e+32), e_t(-1.2012865579185671e+12), e_t(5.4246749994831845e+29), e_t(-3.8201314596721725e+23)
        , e_t(-5.1783207689008547e+37), e_t(1.0487044863432896e+29), e_t(-8.2091088236413212e+38), e_t(2.4924320903438798e+34), e_t(-4.1577568667728512e+16)};
    std::array<T, 10> imres{e_t(2.9689225084136692e+06), e_t(6.8130876628410661e+32), e_t(-2.9179495183191563e+10), e_t(-8.8752530111744507e+28), e_t(1.2946830695756804e+25)
        , e_t(9.5653949361454081e+36), e_t(6.5259614844547437e+28), e_t(1.1301644890532119e+39), e_t(7.0530420820017420e+34), e_t(-1.8907103618909208e+16)};
    for(int i=0; i < 10; ++i)
    {
      auto c = kyosu::complex(re[i], im[i]);
      auto res = kyosu::complex(reres[i], imres[i]);
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(c), res, 1.0e-4) << i <<  " <- " << c << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(re[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(re[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
      TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(im[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(im[i], e_t(0.0)))), 1.0e-4)<< re[i] << '\n';
    }
  }
  std::cout.precision(17);
  std::array<T, 8> re{2.175102683907268e+00, 3.007738475083643e-01, 3.571791197760752e+00, 1.916834892035037e+00, 2.309329011574615e+00, 1.116302757926106e+00, 3.454188251414261e+00, 2.504516854443353e+00};
  std::array<T, 8> im{  3.008362577802520e+00, 3.733804275914350e+00, 2.988312632706299e+00, 4.411110052057489e+00, 3.055249958745497e+00, 2.508994160634028e+00, 3.100976745146938e-01, 3.854880352108083e+00};

  std::array<T, 8> reres{-1.1271605877499498e+00, 8.6819450415271469e+00, -3.7342482747514563e+00, -1.9594143015933545e+00, -1.6842573645694947e+00, 1.9975730077018730e+00, -3.9366090510718693e-01, -5.2795374955460659e+00};
  std::array<T, 8> imres{-4.1516002202378823e+00, -2.2772457219968798e+00, -1.0734738341492034e-01, -1.5246293957752114e+01, -4.0999678002136202e+00, -2.3878228304877860e+00, -4.8664505025944993e-02, -7.2799291393660077e+00};
  for(int i=0; i < 8; ++i)
  {
    auto c = kyosu::complex(re[i], im[i]);
    auto res = kyosu::complex(reres[i], imres[i]);
    double tol = (sizeof(e_t) == 4) ? 1.e-3 :1.e-7;
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(c), res, tol) << i <<  " <- " << c << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(re[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(re[i], e_t(0.0)))), tol)<< re[i] << '\n';
    TTS_RELATIVE_EQUAL(kyosu::cyl_bessel_j0(im[i]), kyosu::real(kyosu::cyl_bessel_j0(kyosu::complex(im[i], e_t(0.0)))), tol)<< re[i] << '\n';
  }
};
