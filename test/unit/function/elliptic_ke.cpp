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

TTS_CASE_TPL ( "Check jacobi_elliptic over complex"
             , kyosu::scalar_real_types
             )
  <typename T>(tts::type<T>)
{
  auto pr = tts::prec<T>(4.0e-2, 1.0e-8);
  using c_t = kyosu::complex_t<T>;
  using a_t  = std::array<T, 7 >;
//   if constexpr(sizeof(T) == 8)
//   {
  constexpr auto nan = eve::nan(eve::as<T>());
    a_t phi= {0.000000000000000e+00, 1.346396851538483e+00, 2.692793703076966e+00, 4.039190554615448e+00, 5.385587406153931e+00, 6.731984257692414e+00, 8.078381109230897e+00, };
    a_t m= {0.000000000000000e+00, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01, };
    a_t ree = {nan,   1.545486188403233e+02,  -2.240669689136373e+01,   1.731898389351810e+01,   8.395951912807700e-01,    5.720419655812918e+00,   5.779502973552437e+00};
    a_t ime = {nan,   3.654685952505582e+01,   5.340773457856197e+01,   1.218092118477447e+01,   3.853460993937446e+00,    1.539669180714825e+00,                       0.0};
    a_t ref = {0.0,   6.150211481292479e-03,   3.403816928620261e+00,   3.637799767891663e+00,   7.539639717553287e+00,   8.632555723502625e+00,  1.262536872229223e+01};
    a_t imf = {nan,   2.410171764691075e+00,   2.081529547642794e+00,   1.886274604714848e+00,   1.685592709331894e+00, 1.157716506821809e+00,                       0.0};
    for(int i=0; i <= 6; ++i)
    {
      c_t z(phi[i], phi[6-i]);
      auto [f, e] = kyosu::elliptic_fe(z, eve::sqrt(m[i]));
      std::cout << std::setprecision(15) << "i " << i << " z " << z << " m " << m[i] << " f " << f << " e " << e << std::endl;
      TTS_RELATIVE_EQUAL(f, kyosu::complex(ref[i], imf[i]), pr);
      TTS_RELATIVE_EQUAL(e, kyosu::complex(ree[i], ime[i]), pr);
    }
//  }
}; ;
