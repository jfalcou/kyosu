//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

// TTS_CASE( "Check as_cayley_dickson_n<N,T> with scalar reals")
// {
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int32_t > ), kyosu::complex<float>    );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float        > ), kyosu::complex<float>    );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t > ), kyosu::complex<double>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double       > ), kyosu::complex<double>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, std::int32_t > ), kyosu::quaternion<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, float        > ), kyosu::quaternion<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, std::int64_t > ), kyosu::quaternion<double>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, double       > ), kyosu::quaternion<double>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, std::int32_t > ), kyosu::octonion<float>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, float        > ), kyosu::octonion<float>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, std::int64_t > ), kyosu::octonion<double>  );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, double       > ), kyosu::octonion<double>  );
// };

// TTS_CASE( "Check as_cayley_dickson_n<N,T> with scalar non-reals")
// {
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::complex<float>  > ), kyosu::complex<float>    );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::complex<double> > ), kyosu::complex<double>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::complex<float>  > ), kyosu::quaternion<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::complex<double> > ), kyosu::quaternion<double>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::complex<float>  > ), kyosu::octonion<float>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::complex<double> > ), kyosu::octonion<double>  );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::quaternion<float>  > ), kyosu::complex<float>    );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::quaternion<double> > ), kyosu::complex<double>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::quaternion<float>  > ), kyosu::quaternion<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::quaternion<double> > ), kyosu::quaternion<double>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::quaternion<float>  > ), kyosu::octonion<float>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::quaternion<double> > ), kyosu::octonion<double>  );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::octonion<float>  > ), kyosu::complex<float>    );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, kyosu::octonion<double> > ), kyosu::complex<double>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::octonion<float>  > ), kyosu::quaternion<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, kyosu::octonion<double> > ), kyosu::quaternion<double>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::octonion<float>  > ), kyosu::octonion<float>   );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, kyosu::octonion<double> > ), kyosu::octonion<double>  );
// };

// TTS_CASE( "Check as_cayley_dickson_n<N,Ts...> with mixed scalar")
// {
//   using kyosu::complex;
//   using kyosu::quaternion;
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , complex<float>> ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , int           > ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , std::int64_t  > ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , float         > ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , double        > ), complex<float> );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<float> , complex<float>> ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int            , complex<float>> ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t   , complex<float>> ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float          , complex<float>> ), complex<float> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double         , complex<float>> ), complex<float> );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, complex<double>>), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, int           > ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, std::int64_t  > ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, float         > ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, double        > ), complex<double> );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, complex<double>, complex<double>> ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, int            , complex<double>> ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, std::int64_t   , complex<double>> ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, float          , complex<double>> ), complex<double> );
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, double         , complex<double>> ), complex<double> );

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, complex<double>, quaternion<double>> ), quaternion<double> );
// };

// TTS_CASE( "Check as_cayley_dickson_n<N,T> on SIMD reals")
// {
//   using eve::wide;

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<std::int32_t >> ), wide<kyosu::complex<float>    >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<float        >> ), wide<kyosu::complex<float>    >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<std::int64_t >> ), wide<kyosu::complex<double>   >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<double       >> ), wide<kyosu::complex<double>   >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<std::int32_t >> ), wide<kyosu::quaternion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<float        >> ), wide<kyosu::quaternion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<std::int64_t >> ), wide<kyosu::quaternion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<double       >> ), wide<kyosu::quaternion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<std::int32_t >> ), wide<kyosu::octonion<float>   >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<float        >> ), wide<kyosu::octonion<float>   >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<std::int64_t >> ), wide<kyosu::octonion<double>  >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<double       >> ), wide<kyosu::octonion<double>  >);
// };

// TTS_CASE( "Check as_cayley_dickson_n<N,T> on SIMD non-reals")
// {
//   using eve::wide;

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::complex<float>     >> ), wide<kyosu::complex<float>  >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::complex<double>    >> ), wide<kyosu::complex<double> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::quaternion<float>  >> ), wide<kyosu::complex<float>  >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::quaternion<double> >> ), wide<kyosu::complex<double> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::octonion<float>    >> ), wide<kyosu::complex<float>  >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<2, wide<kyosu::octonion<double>   >> ), wide<kyosu::complex<double> >);

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::complex<float>     >> ), wide<kyosu::quaternion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::complex<double>    >> ), wide<kyosu::quaternion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::quaternion<float>  >> ), wide<kyosu::quaternion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::quaternion<double> >> ), wide<kyosu::quaternion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::octonion<float>    >> ), wide<kyosu::quaternion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<4, wide<kyosu::octonion<double>   >> ), wide<kyosu::quaternion<double>>);

//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::complex<float>     >> ), wide<kyosu::octonion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::complex<double>    >> ), wide<kyosu::octonion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::quaternion<float>  >> ), wide<kyosu::octonion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::quaternion<double> >> ), wide<kyosu::octonion<double>>);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::octonion<float>    >> ), wide<kyosu::octonion<float> >);
//   TTS_TYPE_IS((kyosu::as_cayley_dickson_n_t<8, wide<kyosu::octonion<double>   >> ), wide<kyosu::octonion<double>>);
// };
