//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>


TTS_CASE_WITH ( "Check kyosu::bessel_j"
              , kyosu::real_types
              , tts::generate(tts::randoms(0,10),
                              tts::randoms(0,10)
                             )
              )
<typename T>(T a0, T a1)
{
  using u_t = eve::underlying_type_t<T>;
  auto c =  kyosu::complex(a0, a1);
  using c_t = decltype(c);

  auto N = 10;
  auto v0 = u_t(1.0/3.0);
  auto vN = v0+N;
  v0 = vN-N;
  using kyosu::cyl_bessel_j;
  using kyosu::bessel_j;
  using eve::cylindrical;

  std::array<c_t, 3 > Jv3, Jv3b;

  auto pr = tts::prec<u_t>(1.0e-2, 1.0e-5);
  std::cout << (eve::frac(vN) == v0) << std::endl;
  auto vJv3  = bessel_j(vN, c, std::span(Jv3));
  auto vJv3b = cyl_bessel_j(vN, c, std::span(Jv3b));
  if constexpr(sizeof(eve::element_type_t<T>) == 8)
  {
    std::cout << "c                    "<< std::hexfloat << c << std::endl;
    std::cout << "Jv3[0]               "<< Jv3[0] << std::endl;
    std::cout << "Jv3b[0]              "<< Jv3b[0] << std::endl;
    std::cout << "bessel_j(v0, c)      "<< bessel_j(v0, c) << std::endl;
    std::cout << "bessel_j(vN, c)      "<< bessel_j(vN, c) << std::endl;
    std::cout << "bessel_j(vN, c, jv3) "<< bessel_j(vN, c, std::span(Jv3)) << std::endl;
    std::cout << "bessel_j(vN, c, jv3b)"<< bessel_j(vN, c, std::span(Jv3b)) << std::endl;
  }
  TTS_RELATIVE_EQUAL(vJv3b, vJv3, pr);
};
