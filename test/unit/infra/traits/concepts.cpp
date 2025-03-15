//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE( "Check kyosu::concepts::cayley_dickson_like behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT    ( kyosu::concepts::cayley_dickson_like<int>          );
  TTS_EXPECT    ( kyosu::concepts::cayley_dickson_like<float>        );
  TTS_EXPECT    ( kyosu::concepts::cayley_dickson_like<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson_like<wide<int >>   );
  TTS_EXPECT    ( kyosu::concepts::cayley_dickson_like<wide<float >> );
  TTS_EXPECT    ( kyosu::concepts::cayley_dickson_like<wide<double>> );

  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<float , 2>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<float , 4>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<float , 8>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<float ,16>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<double , 2>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<double , 4>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<double , 8>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<cayley_dickson<double ,16>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson_like<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::cayley_dickson behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<int>          );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<float>        );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::cayley_dickson<wide<double>> );

  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<float , 2>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<float , 4>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<float , 8>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<float ,16>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<double , 2>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<double , 4>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<double , 8>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<cayley_dickson<double ,16>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT((kyosu::concepts::cayley_dickson<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::scalar_cayley_dickson behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<int>          );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<float>        );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_cayley_dickson<wide<double>> );

  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<float , 2>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<float , 4>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<float , 8>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<float ,16>>));

  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<double , 2>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<double , 4>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<double , 8>>));
  TTS_EXPECT((kyosu::concepts::scalar_cayley_dickson<cayley_dickson<double ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_cayley_dickson<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::real behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT    ( kyosu::concepts::real<int>          );
  TTS_EXPECT    ( kyosu::concepts::real<float>        );
  TTS_EXPECT    ( kyosu::concepts::real<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::real<wide<int >>   );
  TTS_EXPECT    ( kyosu::concepts::real<wide<float >> );
  TTS_EXPECT    ( kyosu::concepts::real<wide<double>> );

  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<float , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<float , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<float , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<float ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<double , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<double , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<double , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<cayley_dickson<double ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::real<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::scalar_real behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT    ( kyosu::concepts::scalar_real<int>          );
  TTS_EXPECT    ( kyosu::concepts::scalar_real<float>        );
  TTS_EXPECT    ( kyosu::concepts::scalar_real<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_real<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_real<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::scalar_real<wide<double>> );

  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<float , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<float , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<float , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<float ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<double , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<double , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<double , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<cayley_dickson<double ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::scalar_real<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::complex behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT_NOT( kyosu::concepts::complex<int>          );
  TTS_EXPECT_NOT( kyosu::concepts::complex<float>        );
  TTS_EXPECT_NOT( kyosu::concepts::complex<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::complex<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::complex<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::complex<wide<double>> );

  TTS_EXPECT    ((kyosu::concepts::complex<cayley_dickson<float , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<float , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<float , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<float ,16>>));

  TTS_EXPECT    ((kyosu::concepts::complex<cayley_dickson<double , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<double , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<double , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<cayley_dickson<double ,16>>));

  TTS_EXPECT    ((kyosu::concepts::complex<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT    ((kyosu::concepts::complex<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::complex<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::quaternion behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT_NOT( kyosu::concepts::quaternion<int>          );
  TTS_EXPECT_NOT( kyosu::concepts::quaternion<float>        );
  TTS_EXPECT_NOT( kyosu::concepts::quaternion<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::quaternion<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::quaternion<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::quaternion<wide<double>> );

  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<float , 2>>));
  TTS_EXPECT    ((kyosu::concepts::quaternion<cayley_dickson<float , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<float , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<float ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<double , 2>>));
  TTS_EXPECT    ((kyosu::concepts::quaternion<cayley_dickson<double , 4>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<double , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<cayley_dickson<double ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT    ((kyosu::concepts::quaternion<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT    ((kyosu::concepts::quaternion<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::quaternion<wide<cayley_dickson<double ,16>>>));
};

TTS_CASE( "Check kyosu::concepts::octonion behavior")
{
  using eve::wide;
  using kyosu::cayley_dickson;

  TTS_EXPECT_NOT( kyosu::concepts::octonion<int>          );
  TTS_EXPECT_NOT( kyosu::concepts::octonion<float>        );
  TTS_EXPECT_NOT( kyosu::concepts::octonion<double>       );
  TTS_EXPECT_NOT( kyosu::concepts::octonion<wide<int >>   );
  TTS_EXPECT_NOT( kyosu::concepts::octonion<wide<float >> );
  TTS_EXPECT_NOT( kyosu::concepts::octonion<wide<double>> );

  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<float , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<float , 4>>));
  TTS_EXPECT    ((kyosu::concepts::octonion<cayley_dickson<float , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<float ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<double , 2>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<double , 4>>));
  TTS_EXPECT    ((kyosu::concepts::octonion<cayley_dickson<double , 8>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<cayley_dickson<double ,16>>));

  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<float , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<float , 4>>>));
  TTS_EXPECT    ((kyosu::concepts::octonion<wide<cayley_dickson<float , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<float ,16>>>));

  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<double , 2>>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<double , 4>>>));
  TTS_EXPECT    ((kyosu::concepts::octonion<wide<cayley_dickson<double , 8>>>));
  TTS_EXPECT_NOT((kyosu::concepts::octonion<wide<cayley_dickson<double ,16>>>));
};