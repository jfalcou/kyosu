//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <kyosu/kyosu.hpp>

TTS_CASE_WITH("Check behavior of to_polar on wide",
              kyosu::real_types,
              tts::randoms(-1.0, +1.0),
              tts::randoms(-1.0, +1.0),
              tts::randoms(-1.0, +1.0),
              tts::randoms(-1.0, +1.0)

)
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3){{auto q = kyosu::quaternion(a0, a1, a2, a3);
auto [r, t, iz] = kyosu::to_polar(q);
auto q1 = kyosu::from_polar(r, t, iz);
TTS_RELATIVE_EQUAL(q, q1, tts::prec<T>());
}
{
  auto c = kyosu::complex(a0, a1);
  auto [r1, t1] = kyosu::to_polar(c);
  auto c1 = kyosu::from_polar(r1, t1);
  TTS_RELATIVE_EQUAL(c, c1, tts::prec<T>());
}
{
  auto [r1, t1] = kyosu::to_polar(a0);
  auto c1 = kyosu::from_polar(r1, t1);
  TTS_RELATIVE_EQUAL(kyosu::complex(a0), c1, tts::prec<T>());
}
}
;

TTS_CASE_WITH("Check that the radpi option reaches both sides of the trip",
              kyosu::real_types,
              tts::randoms(-1.0, +1.0),
              tts::randoms(-1.0, +1.0))
<typename T>(T const& a0, T const& a1)
{
  auto c = kyosu::complex(a0, a1);
  auto [r, t] = kyosu::to_polar[kyosu::radpi](c);

  TTS_RELATIVE_EQUAL(kyosu::from_polar[kyosu::radpi](r, t), c, tts::prec<T>());
};

//======================================================================================================================
//== These return another type than their argument, so a conditional has nothing to return
//======================================================================================================================
TTS_CASE("Check that kyosu::to_polar and kyosu::from_polar reject a conditional")
{
  [[maybe_unused]] kyosu::complex_t<double> const c{3., 4.};
  [[maybe_unused]] double const r{1.};
  [[maybe_unused]] bool const m{false};

  TTS_EXPECT_NOT_COMPILES(c, m, { kyosu::to_polar[m](c); });
  TTS_EXPECT_NOT_COMPILES(r, m, { kyosu::from_polar[m](r, r); });
};
