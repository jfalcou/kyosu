//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#include <kyosu/kyosu.hpp>
#include <test.hpp>

TTS_CASE("convert reals to real/complex/quaternion/octonion")
{
  using namespace kyosu;

  float rf_in = 2.5f;
  double rd_out = 2.5;
  double rd_in = 2.5;
  float rf_out = 2.5f;

  complex_t<float> cf_out{2.5};
  complex_t<double> cd_out{2.5};
  quaternion_t<float> qf_out{2.5};
  quaternion_t<double> qd_out{2.5};
  octonion_t<float> of_out{2.5};
  octonion_t<double> od_out{2.5};

  // float
  TTS_EQUAL((convert(rf_in, as(rf_in))), rf_in);
  TTS_EQUAL((convert(rf_in, as(rd_out))), rd_out);
  TTS_EQUAL((convert(rf_in, as(cf_out))), cf_out);
  TTS_EQUAL((convert(rf_in, as(cd_out))), cd_out);
  TTS_EQUAL((convert(rf_in, as(qf_out))), qf_out);
  TTS_EQUAL((convert(rf_in, as(qd_out))), qd_out);
  TTS_EQUAL((convert(rf_in, as(of_out))), of_out);
  TTS_EQUAL((convert(rf_in, as(od_out))), od_out);

  // double
  TTS_EQUAL((convert(rd_in, as(rd_in))), rd_in);
  TTS_EQUAL((convert(rd_in, as(rf_out))), rf_out);
  TTS_EQUAL((convert(rd_in, as(cf_out))), cf_out);
  TTS_EQUAL((convert(rd_in, as(cd_out))), cd_out);
  TTS_EQUAL((convert(rd_in, as(qf_out))), qf_out);
  TTS_EQUAL((convert(rd_in, as(qd_out))), qd_out);
  TTS_EQUAL((convert(rd_in, as(of_out))), of_out);
  TTS_EQUAL((convert(rd_in, as(od_out))), od_out);
};

TTS_CASE("convert wide<reals> to real/complex/quaternion/octonion")
{
  using namespace kyosu;
  auto fill = [](auto i, auto) { return 1 + i; };

  eve::wide<float, eve::fixed<4>> rf_in{fill};
  eve::wide<double, eve::fixed<4>> rd_out{fill};
  eve::wide<double, eve::fixed<4>> rd_in{fill};
  eve::wide<float, eve::fixed<4>> rf_out{fill};

  complex_t<eve::wide<float, eve::fixed<4>>> cf_out{fill};
  complex_t<eve::wide<double, eve::fixed<4>>> cd_out{fill};
  quaternion_t<eve::wide<float, eve::fixed<4>>> qf_out{fill};
  quaternion_t<eve::wide<double, eve::fixed<4>>> qd_out{fill};
  octonion_t<eve::wide<float, eve::fixed<4>>> of_out{fill};
  octonion_t<eve::wide<double, eve::fixed<4>>> od_out{fill};

  // float
  TTS_EQUAL((convert(rf_in, eve::as_element(rf_in))), rf_in);
  TTS_EQUAL((convert(rf_in, eve::as_element(rd_out))), rd_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(cf_out))), cf_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(cd_out))), cd_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(qf_out))), qf_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(qd_out))), qd_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(rf_in, eve::as_element(od_out))), od_out);

  // double
  TTS_EQUAL((convert(rd_in, eve::as_element(rd_in))), rd_in);
  TTS_EQUAL((convert(rd_in, eve::as_element(rf_out))), rf_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(cf_out))), cf_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(cd_out))), cd_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(qf_out))), qf_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(qd_out))), qd_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(rd_in, eve::as_element(od_out))), od_out);
};

TTS_CASE("convert complex to complex/quaternion/octonion")
{
  using namespace kyosu;

  complex_t<float> cf_in{2.5};
  complex_t<double> cd_in{2.5};
  quaternion_t<float> qf_out{2.5};
  quaternion_t<double> qd_out{2.5};
  octonion_t<float> of_out{2.5};
  octonion_t<double> od_out{2.5};

  // No conversion to real
  TTS_EXPECT_NOT_COMPILES(cf_in, { convert(cf_in, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(cd_in, { convert(cd_in, as<double>{}); });

  // float
  TTS_EQUAL((convert(cf_in, as(cf_in))), cf_in);
  TTS_EQUAL((convert(cf_in, as(cd_in))), cd_in);
  TTS_EQUAL((convert(cf_in, as(qf_out))), qf_out);
  TTS_EQUAL((convert(cf_in, as(qd_out))), qd_out);
  TTS_EQUAL((convert(cf_in, as(of_out))), of_out);
  TTS_EQUAL((convert(cf_in, as(od_out))), od_out);

  // double
  TTS_EQUAL((convert(cd_in, as(cf_in))), cf_in);
  TTS_EQUAL((convert(cd_in, as(cd_in))), cd_in);
  TTS_EQUAL((convert(cd_in, as(qf_out))), qf_out);
  TTS_EQUAL((convert(cd_in, as(qd_out))), qd_out);
  TTS_EQUAL((convert(cd_in, as(of_out))), of_out);
  TTS_EQUAL((convert(cd_in, as(od_out))), od_out);
};

TTS_CASE("convert wide<complex> to complex/quaternion/octonion")
{
  using namespace kyosu;
  auto fill = [](auto i, auto) { return 1 + i; };

  complex_t<eve::wide<float, eve::fixed<4>>> cf_in{fill};
  complex_t<eve::wide<double, eve::fixed<4>>> cd_in{fill};
  quaternion_t<eve::wide<float, eve::fixed<4>>> qf_out{fill};
  quaternion_t<eve::wide<double, eve::fixed<4>>> qd_out{fill};
  octonion_t<eve::wide<float, eve::fixed<4>>> of_out{fill};
  octonion_t<eve::wide<double, eve::fixed<4>>> od_out{fill};

  // No conversion to real
  TTS_EXPECT_NOT_COMPILES(cf_in, { convert(cf_in, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(cd_in, { convert(cd_in, as<double>{}); });

  // float
  TTS_EQUAL((convert(cf_in, eve::as_element(cf_in))), cf_in);
  TTS_EQUAL((convert(cf_in, eve::as_element(cd_in))), cd_in);
  TTS_EQUAL((convert(cf_in, eve::as_element(qf_out))), qf_out);
  TTS_EQUAL((convert(cf_in, eve::as_element(qd_out))), qd_out);
  TTS_EQUAL((convert(cf_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(cf_in, eve::as_element(od_out))), od_out);

  // double
  TTS_EQUAL((convert(cd_in, eve::as_element(cf_in))), cf_in);
  TTS_EQUAL((convert(cd_in, eve::as_element(cd_in))), cd_in);
  TTS_EQUAL((convert(cd_in, eve::as_element(qf_out))), qf_out);
  TTS_EQUAL((convert(cd_in, eve::as_element(qd_out))), qd_out);
  TTS_EQUAL((convert(cd_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(cd_in, eve::as_element(od_out))), od_out);
};

TTS_CASE("convert quaternion to quaternion/octonion")
{
  using namespace kyosu;

  quaternion_t<float> qf_in{2.5};
  quaternion_t<double> qd_in{2.5};
  octonion_t<float> of_out{2.5};
  octonion_t<double> od_out{2.5};

  // No conversion to real/complex
  TTS_EXPECT_NOT_COMPILES(qf_in, { convert(qf_in, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(qd_in, { convert(qd_in, as<double>{}); });
  TTS_EXPECT_NOT_COMPILES(qf_in, { convert(qf_in, as<complex_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(qd_in, { convert(qd_in, as<complex_t<double>>{}); });

  // float
  TTS_EQUAL((convert(qf_in, as(qf_in))), qf_in);
  TTS_EQUAL((convert(qf_in, as(qd_in))), qd_in);
  TTS_EQUAL((convert(qf_in, as(of_out))), of_out);
  TTS_EQUAL((convert(qf_in, as(od_out))), od_out);

  // double
  TTS_EQUAL((convert(qd_in, as(qf_in))), qf_in);
  TTS_EQUAL((convert(qd_in, as(qd_in))), qd_in);
  TTS_EQUAL((convert(qd_in, as(of_out))), of_out);
  TTS_EQUAL((convert(qd_in, as(od_out))), od_out);
};

TTS_CASE("convert wide<quaternion> to quaternion/octonion")
{
  using namespace kyosu;
  auto fill = [](auto i, auto) { return 1 + i; };

  quaternion_t<eve::wide<float, eve::fixed<4>>> qf_in{fill};
  quaternion_t<eve::wide<double, eve::fixed<4>>> qd_in{fill};
  octonion_t<eve::wide<float, eve::fixed<4>>> of_out{fill};
  octonion_t<eve::wide<double, eve::fixed<4>>> od_out{fill};

  // No conversion to real
  TTS_EXPECT_NOT_COMPILES(qf_in, { convert(qf_in, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(qd_in, { convert(qd_in, as<double>{}); });
  TTS_EXPECT_NOT_COMPILES(qf_in, { convert(qf_in, as<complex_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(qd_in, { convert(qd_in, as<complex_t<double>>{}); });

  // float
  TTS_EQUAL((convert(qf_in, eve::as_element(qf_in))), qf_in);
  TTS_EQUAL((convert(qf_in, eve::as_element(qd_in))), qd_in);
  TTS_EQUAL((convert(qf_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(qf_in, eve::as_element(od_out))), od_out);

  // double
  TTS_EQUAL((convert(qd_in, eve::as_element(qf_in))), qf_in);
  TTS_EQUAL((convert(qd_in, eve::as_element(qd_in))), qd_in);
  TTS_EQUAL((convert(qd_in, eve::as_element(of_out))), of_out);
  TTS_EQUAL((convert(qd_in, eve::as_element(od_out))), od_out);
};

TTS_CASE("convert octonion to octonion")
{
  using namespace kyosu;

  octonion_t<float> of{2.5};
  octonion_t<double> od{2.5};

  // No conversion to real/complex
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<double>{}); });
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<complex_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<complex_t<double>>{}); });
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<quaternion_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<quaternion_t<double>>{}); });

  // float
  TTS_EQUAL((convert(of, as(of))), of);
  TTS_EQUAL((convert(of, as(od))), od);

  // double
  TTS_EQUAL((convert(od, as(of))), of);
  TTS_EQUAL((convert(od, as(od))), od);
};

TTS_CASE("convert wide<octonion> to octonion")
{
  using namespace kyosu;
  auto fill = [](auto i, auto) { return 1 + i; };

  octonion_t<eve::wide<float, eve::fixed<4>>> of{fill};
  octonion_t<eve::wide<double, eve::fixed<4>>> od{fill};

  // No conversion to real
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<float>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<double>{}); });
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<complex_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<complex_t<double>>{}); });
  TTS_EXPECT_NOT_COMPILES(of, { convert(of, as<quaternion_t<float>>{}); });
  TTS_EXPECT_NOT_COMPILES(od, { convert(od, as<quaternion_t<double>>{}); });

  // float
  TTS_EQUAL((convert(of, eve::as_element(of))), of);
  TTS_EQUAL((convert(of, eve::as_element(od))), od);
  TTS_EQUAL((convert(of, eve::as_element(of))), of);
  TTS_EQUAL((convert(of, eve::as_element(od))), od);

  // double
  TTS_EQUAL((convert(od, eve::as_element(of))), of);
  TTS_EQUAL((convert(od, eve::as_element(od))), od);
  TTS_EQUAL((convert(od, eve::as_element(of))), of);
  TTS_EQUAL((convert(od, eve::as_element(od))), od);
};
