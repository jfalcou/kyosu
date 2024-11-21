//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>
#include <complex>

TTS_CASE_TPL( "Check corner cases of erfi", kyosu::real_types)
  <typename T>(tts::type<T>)
{
  using e_t = T;
  using c_t = decltype(kyosu::complex(e_t(0)));
  using eve::as;
  const int N = 11;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto half= eve::half(as<T>());
  auto tcx = [](auto r, auto i){return kyosu::complex(T(r), T(i));};

  std::array<c_t, N> inputs =
    {
      tcx(one,one),   //0
      tcx(half,one),  //1
      tcx(10, 10),    //2
      tcx(65, zer),   //3*
      tcx(0.01, one), //4
      tcx(1.0e-4, 2), //5
      tcx(0.785398163397448, zer), //6
      tcx(inf,zer),   //7
      tcx(nan,nan),   //8
      tcx(one, 0 ),   //9
      tcx(half, 0)    //10
    };

  std::array<c_t, N> results =
    {
      tcx(1.90453469237835e-01, 1.31615128169795e+00), //0
      tcx(1.87973467223383e-01, 9.50709728318957e-01), //1
      tcx(-1.09876846081940e-02, 9.61649374272475e-01), //2
      tcx(inf,                  0.00000000000000e+00), //3
      tcx(4.15093659812155e-03, 8.42742304391298e-01), //4
      tcx(2.06669848718624e-06, 9.95322265432292e-01), //5
      tcx(1.10778360148748e+00, 0.00000000000000e+00), //6
      tcx(inf,                  0.00000000000000e+00), //7
      tcx(nan,                  nan                 ), //8
      tcx(1.65042575879754e+00, 0.00000000000000e+00), //9
      tcx(6.14952094696511e-01, 0.00000000000000e+00)  //10
    };

  using kyosu::erfi;
  using kyosu::conj;
  for(int i=0; i < N; ++i)
  {
    TTS_RELATIVE_EQUAL(kyosu::erfi(inputs[i]), results[i], tts::prec<T>()) << "i " << i << " -> " << inputs[i] <<"\n";
  }
};

TTS_CASE_WITH( "Check behavior of erfi on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-1.0, 1.0)
                            , tts::randoms(-1.0, 1.0))
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = kyosu::complex(a0, a1);
  auto ez = kyosu::erfi(z);
  for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
  {
    TTS_RELATIVE_EQUAL(ez.get(i), kyosu::erfi(z.get(i)), tts::prec<T>());
  }
};
