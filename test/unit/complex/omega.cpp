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

TTS_CASE_WITH("Check kyosu::omega over real", kyosu::simd_real_types, tts::randoms(-10, 10), tts::randoms(-10, 10))
<typename T>(T const& a0, T const& a1)
{
  TTS_RELATIVE_EQUAL(kyosu::omega(a0), kyosu::complex(eve::omega(a0)), tts::prec<T>()) << a0 << '\n';
  TTS_RELATIVE_EQUAL(kyosu::omega(5.8148731e-15), kyosu::complex(eve::omega(5.8148731e-15)), tts::prec<T>())
    << a0 << '\n';

  auto x = kyosu::complex(a0, a1);
  auto o = kyosu::omega(x);
  TTS_RELATIVE_EQUAL(kyosu::log(o) + o, x, tts::prec<T>());
};

TTS_CASE_TPL("Check peculiar values", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  int const N = 18;
  std::array<c_t, N> inputs = {
    tcx(eve::zero(as<e_t>()), eve::zero(as<e_t>())),      // 0*
    tcx(eve::minf(as<e_t>()), eve::zero(as<e_t>())),      // 1*
    tcx(eve::inf(as<e_t>()), eve::zero(as<e_t>())),       // 2*
    tcx(eve::nan(as<e_t>()), eve::zero(as<e_t>())),       // 3*
    tcx(eve::zero(as<e_t>()), eve::inf(as<e_t>())),       // 4*
    tcx(eve::inf(as<e_t>()), eve::inf(as<e_t>())),        // 5*
    tcx(eve::minf(as<e_t>()), eve::inf(as<e_t>())),       // 6*
    tcx(1 + eve::euler(as<e_t>()), eve::zero(as<e_t>())), // 7*
    tcx(eve::zero(as<e_t>()), eve::pi(as<e_t>())),        // 8*
    tcx(eve::mone(as<e_t>()), eve::pi(as<e_t>())),        // 9*
    tcx(eve::mone(as<e_t>()), -eve::pi(as<e_t>())),       // 10*
    tcx(-2 + eve::log_2(as<e_t>()), -eve::pi(as<e_t>())), // 11*
    tcx(-2 + eve::log_2(as<e_t>()), eve::pi(as<e_t>())),  // 12*
    tcx(eve::one(as<e_t>()), eve::one(as<e_t>())),        // 13*
    tcx(eve::zero(as<e_t>()), 1 + eve::pio_2(as<e_t>())), // 14*
    tcx(e_t(-10.0), 3 * eve::pio_4(as<e_t>())),           // 15*
    tcx(e_t(-1.06), e_t(3.1618)),                         // 16*
    tcx(e_t(-1.06), e_t(-3.1416)),                        // 17*
  };
  std::array<c_t, N> expected = {
    tcx(eve::omega(eve::zero(as<e_t>()))),                            // 0*
    tcx(eve::zero(as<e_t>()), eve::zero(as<e_t>())),                  // 1*
    tcx(eve::inf(as<e_t>()), eve::zero(as<e_t>())),                   // 2*
    tcx(eve::nan(as<e_t>()), eve::nan(as<e_t>())),                    // 3*
    tcx(eve::zero(as<e_t>()), eve::inf(as<e_t>())),                   // 4*
    tcx(eve::inf(as<e_t>()), eve::inf(as<e_t>())),                    // 5*
    tcx(eve::minf(as<e_t>()), eve::inf(as<e_t>())),                   // 6*
    tcx(eve::euler(as<e_t>()), eve::zero(as<e_t>())),                 // 7*
    tcx(e_t(-0.3181315052047641353), e_t(1.337235701430689408901)),   // 8
    tcx(eve::mone(as<e_t>()), eve::zero(as<e_t>())),                  // 9*
    tcx(eve::mone(as<e_t>()), eve::zero(as<e_t>())),                  // 10*
    tcx(e_t(-0.406375739959959907)),                                  // 11*
    tcx(e_t(-2)),                                                     // 12*
    tcx(e_t(0.937208208373369753), e_t(0.50542131601315120396215)),   // 13*
    tcx(eve::zero(as<e_t>()), eve::one(as<e_t>())),                   // 14*
    tcx(e_t(-0.00003210259810118209), e_t(0.0000321046594533210201)), // 15*
    tcx(e_t(-1.392216875578e+00), e_t(7.156772220838e-02)),           // 16*
    tcx(e_t(-1.387512771358e+00), e_t(-2.630426333236e-05)),          // 17*
  };

  for (int i = 0; i < N; ++i)
  {
    TTS_RELATIVE_EQUAL(kyosu::omega(inputs[i]), expected[i], tts::prec<T>()) << i << " < - " << inputs[i] << '\n';
  }

  e_t r0(sizeof(e_t) == 4 ? 64 : 512);
  e_t recr0(eve::rec(r0));
  for (e_t r = recr0; r < r0; r *= e_t(2))
  {
    for (int i = -32; i < 32; ++i)
    {
      auto xx = r * kyosu::exp_ipi(i / e_t(16));
      auto o = kyosu::omega(xx);
      TTS_RELATIVE_EQUAL(kyosu::log(o) + o, xx, tts::prec<T>()) << o << '\n';
    }
  }
};
