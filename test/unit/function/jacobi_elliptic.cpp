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
  a_t phi= {0.000000000000000e+00, 1.346396851538483e+00, 2.692793703076966e+00, 4.039190554615448e+00, 5.385587406153931e+00, 6.731984257692414e+00, 8.078381109230897e+00, };
  a_t m= {0.000000000000000e+00, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01, };
  a_t rsn = {0.000000000000000e+00, 2.433149110823434e+00, 1.283941137443174e+00, -4.345523719909591e-01, -1.146031599989070e+00, -1.188244631240457e+00, -9.388455774794550e-01};
  a_t isn = {1.612004689955156e+03, 2.812489928480895e-01, -9.070417680308518e-01, -1.747485822956206e-01, 1.124636778394672e-01, 5.567227280212359e-02, 0.000000000000000e+00};
  a_t rcn = {1.612005000127921e+03, -3.080155826452643e-01, 1.120246188909950e+00, 9.211391985456892e-01, 2.183526381145390e-01, 1.021647932356633e-01, 3.443384696011595e-01};
  a_t icn = {-0.000000000000000e+00, 2.221708171357144e+00, 1.039582415796653e+00, -8.243858372166833e-02, 5.902696196755409e-01, 6.475056344849072e-01, 0.000000000000000e+00};
  a_t rdn = {1.000000000000000e+00, -4.592122381685098e-01, -9.426829656030340e-01, -9.660706784861853e-01, -5.256883155283983e-01, 2.102487586797839e-01, 4.944569734110357e-01};
  a_t idn = {-0.000000000000000e+00, 2.128865416496776e-01, -3.529707325786163e-01, 3.368760217314167e-02, -1.401014086514837e-01, 2.247415316214260e-01, 0.000000000000000e+00};

  for(int i=0; i < 7; ++i)
  {
    c_t z(phi[i], phi[6-i]);
    auto [sn, cn, dn] = kyosu::jacobi_elliptic(z, eve::sqrt(m[i]));
    TTS_RELATIVE_EQUAL(sn, kyosu::complex(rsn[i], isn[i]), pr);
    TTS_RELATIVE_EQUAL(cn, kyosu::complex(rcn[i], icn[i]), pr);
    TTS_RELATIVE_EQUAL(dn, kyosu::complex(rdn[i], idn[i]), pr);
  }
};
