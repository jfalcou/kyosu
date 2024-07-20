//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE( "Check as_cayley_dickson_n<N,T> with scalar reals")
{
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int32_t > ), kyosu::complex_t<float>    );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float        > ), kyosu::complex_t<float>    );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t > ), kyosu::complex_t<double>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double       > ), kyosu::complex_t<double>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, std::int32_t > ), kyosu::quaternion_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, float        > ), kyosu::quaternion_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, std::int64_t > ), kyosu::quaternion_t<double>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, double       > ), kyosu::quaternion_t<double>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, std::int32_t > ), kyosu::octonion_t<float>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, float        > ), kyosu::octonion_t<float>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, std::int64_t > ), kyosu::octonion_t<double>  );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, double       > ), kyosu::octonion_t<double>  );
};

TTS_CASE( "Check as_cayley_dickson_n<N,T> with scalar non-reals")
{
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::complex_t<float>  > ), kyosu::complex_t<float>    );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::complex_t<double> > ), kyosu::complex_t<double>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::complex_t<float>  > ), kyosu::quaternion_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::complex_t<double> > ), kyosu::quaternion_t<double>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::complex_t<float>  > ), kyosu::octonion_t<float>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::complex_t<double> > ), kyosu::octonion_t<double>  );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::quaternion_t<float>  > ), kyosu::complex_t<float>    );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::quaternion_t<double> > ), kyosu::complex_t<double>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::quaternion_t<float>  > ), kyosu::quaternion_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::quaternion_t<double> > ), kyosu::quaternion_t<double>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::quaternion_t<float>  > ), kyosu::octonion_t<float>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::quaternion_t<double> > ), kyosu::octonion_t<double>  );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::octonion_t<float>  > ), kyosu::complex_t<float>    );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::octonion_t<double> > ), kyosu::complex_t<double>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::octonion_t<float>  > ), kyosu::quaternion_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::octonion_t<double> > ), kyosu::quaternion_t<double>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::octonion_t<float>  > ), kyosu::octonion_t<float>   );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::octonion_t<double> > ), kyosu::octonion_t<double>  );
};

TTS_CASE( "Check as_cayley_dickson_n<N,Ts...> with mixed scalar")
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , complex_t<float>> ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , int           > ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , std::int64_t  > ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , float         > ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , double        > ), complex_t<float> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<float> , complex_t<float>> ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int            , complex_t<float>> ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t   , complex_t<float>> ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float          , complex_t<float>> ), complex_t<float> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double         , complex_t<float>> ), complex_t<float> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, complex_t<double>>), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, int           > ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, std::int64_t  > ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, float         > ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, double        > ), complex_t<double> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex_t<double>, complex_t<double>> ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int            , complex_t<double>> ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t   , complex_t<double>> ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float          , complex_t<double>> ), complex_t<double> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double         , complex_t<double>> ), complex_t<double> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, complex_t<double>, quaternion_t<double>> ), quaternion_t<double> );
};

TTS_CASE( "Check as_cayley_dickson_n<N,T> on SIMD reals")
{
  using eve::wide;

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<std::int32_t >> ), wide<kyosu::complex_t<float>    >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<float        >> ), wide<kyosu::complex_t<float>    >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<std::int64_t >> ), wide<kyosu::complex_t<double>   >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<double       >> ), wide<kyosu::complex_t<double>   >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<std::int32_t >> ), wide<kyosu::quaternion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<float        >> ), wide<kyosu::quaternion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<std::int64_t >> ), wide<kyosu::quaternion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<double       >> ), wide<kyosu::quaternion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<std::int32_t >> ), wide<kyosu::octonion_t<float>   >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<float        >> ), wide<kyosu::octonion_t<float>   >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<std::int64_t >> ), wide<kyosu::octonion_t<double>  >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<double       >> ), wide<kyosu::octonion_t<double>  >);
};

TTS_CASE( "Check as_cayley_dickson_n<N,T> on SIMD non-reals")
{
  using eve::wide;

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::complex_t<float>     >> ), wide<kyosu::complex_t<float>  >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::complex_t<double>    >> ), wide<kyosu::complex_t<double> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::quaternion_t<float>  >> ), wide<kyosu::complex_t<float>  >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::quaternion_t<double> >> ), wide<kyosu::complex_t<double> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::octonion_t<float>    >> ), wide<kyosu::complex_t<float>  >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::octonion_t<double>   >> ), wide<kyosu::complex_t<double> >);

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::complex_t<float>     >> ), wide<kyosu::quaternion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::complex_t<double>    >> ), wide<kyosu::quaternion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::quaternion_t<float>  >> ), wide<kyosu::quaternion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::quaternion_t<double> >> ), wide<kyosu::quaternion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::octonion_t<float>    >> ), wide<kyosu::quaternion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::octonion_t<double>   >> ), wide<kyosu::quaternion_t<double>>);

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::complex_t<float>     >> ), wide<kyosu::octonion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::complex_t<double>    >> ), wide<kyosu::octonion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::quaternion_t<float>  >> ), wide<kyosu::octonion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::quaternion_t<double> >> ), wide<kyosu::octonion_t<double>>);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::octonion_t<float>    >> ), wide<kyosu::octonion_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::octonion_t<double>   >> ), wide<kyosu::octonion_t<double>>);
};

TTS_CASE( "Check as_cayley_dickson_n<N,Ts...> with mixed SIMD types")
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using eve::wide;

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, wide<complex_t<float>>> ), wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, int           > )        , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, std::int64_t  > )        , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, float         > )        , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, double        > )        , wide<complex_t<float> >);

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<float>>, wide<complex_t<float>>> ), wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int            , wide<complex_t<float>>> )       , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t   , wide<complex_t<float>>> )       , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float          , wide<complex_t<float>>> )       , wide<complex_t<float> >);
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double         , wide<complex_t<float>>> )       , wide<complex_t<float> >);

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, wide<complex_t<double>>>) , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, int           > )         , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, std::int64_t  > )         , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, float         > )         , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, double        > )         , wide<complex_t<double>> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<complex_t<double>>, wide<complex_t<double>>> ), wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int         , wide<complex_t<double>>> )           , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t, wide<complex_t<double>>> )           , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float       , wide<complex_t<double>>> )           , wide<complex_t<double>> );
  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double      , wide<complex_t<double>>> )           , wide<complex_t<double>> );

  TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<complex_t<double>>, quaternion_t<double>> ), wide<quaternion_t<double>> );
};
