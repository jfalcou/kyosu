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

TTS_CASE_TPL( "Check corner cases of erf", kyosu::real_types)
<typename T>(tts::type<T>)
{
  using e_t = T;
  auto tcx = kyosu::complex;
  using c_t = decltype(tcx(e_t(0)));
  using eve::as;
  const int N = 18;
  auto zer = eve::zero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  auto h   = eve::half(as<T>());
  std::array<c_t, N> inputs =
    {
      tcx(zer,zer), //0
      tcx(zer,inf), //1
      tcx(zer,nan), //2
      tcx(one,inf), //3
      tcx(one,nan), //4
      tcx(inf,zer), //5
      tcx(inf,one), //6
      tcx(inf,inf), //7
      tcx(inf,nan), //8
      tcx(nan,zer), //9
      tcx(nan,one), //10
      tcx(nan,nan), //11
      tcx(h, zer ), //12
      tcx(zer, h ), //13
      tcx(e_t(4e-2), one),       //14
      tcx(e_t(4e-2), e_t(1e-3)), //15
      tcx(e_t(-4e-2), one),      //16
      tcx(e_t(-4e-2), e_t(1e-3)) //17
    };

  std::array<c_t, N> results =
    {
      tcx(zer,zer),  //0
      tcx(zer, inf), //1
      tcx(zer,nan),  //2
      tcx(nan, nan), //3
      tcx(nan,nan),  //4
      tcx(one,zer),  //5
      tcx(one,zer),  //6
      tcx(nan, nan), //7
      tcx(nan,nan),  //8
      tcx(nan,zer),  //9
      tcx(nan,nan),  //10
      tcx(nan,nan),  //11
      tcx(e_t(5.204998778130465187e-01), zer),    //12
      tcx(zer, e_t(6.14952094696510909e-01)), //13
      tcx(e_t(1.224939980392529826e-01), e_t(1.645524692691958002e+00)), //14
      tcx(e_t(4.511115120815541862e-02), e_t(1.126575578306994625e-03)), //15
      tcx(e_t(-1.224939980392529826e-01), e_t(1.645524692691958002e+00)),//16
      tcx(e_t(-4.511115120815541862e-02), e_t(1.126575578306994625e-03)) //17
    };
  using kyosu::conj;
  using kyosu::erf;
  for(int i=0; i < N; ++i)
  {
//     if (i < 12)
//       TTS_IEEE_EQUAL(erf(inputs[i]), results[i]) << "i =  " << i << " <- " << inputs[i] << "\n";
//     else
    TTS_RELATIVE_EQUAL(kyosu::erf(inputs[i]), results[i], tts::prec<T>()) << "i =  " << i << "\n";
    TTS_IEEE_EQUAL(kyosu::erf(conj(inputs[i])), conj(erf(inputs[i]))) << "i =  " << i << "\n";
  }
};

TTS_CASE_TPL( "Check corner cases of erf", kyosu::scalar_real_types)
  <typename T>(tts::type<T>)
{
  using e_t = T;
  using c_t = decltype(kyosu::complex(e_t(0)));
  using eve::as;
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto tcx = [](auto r, auto i){return kyosu::complex(T(r), T(i));};
  constexpr int NTST = 41;
  std::array<c_t, NTST> z = {
    tcx(1,2), //0
    tcx(-1,2), //1
    tcx(1,-2), //2
    tcx(-1,-2), //3
    tcx(9,-28), //4
    tcx(21,-33), //5
    tcx(1e3,1e3), //6
    tcx(-3001,-1000), //7
    tcx(1e20, -1e19),//8
    tcx(5.1e-3, 1e-8), //9
    tcx(-4.9e-3, 4.95e-3), //10
    tcx(4.9e-3, 0.5), //11
    tcx(4.9e-4, -0.5e1), //12
    tcx(-4.9e-5, -0.5e2),//13
    tcx(5.1e-3, 0.5),//14
    tcx(5.1e-4, -0.5e1),//15
    tcx(-5.1e-5, -0.5e2),//16
    tcx(1e-6,2e-6),//17
    tcx(0,2e-6),//18
    tcx(0,2),//19
    tcx(0,20),//20
    tcx(0,200),//21
    tcx(inf,0),//22
    tcx(-inf,0),//23
    tcx(0,inf),//24
    tcx(0,-inf),//25
    tcx(inf,inf),//26
    tcx(inf,-inf),//27
    tcx(nan,nan),//28
    tcx(nan,0),//29
    tcx(0,nan),//30
    tcx(nan,inf),//31
    tcx(inf,nan),//32
    tcx(1e-3,nan),//33
    tcx(7e-2,7e-2),//34
    tcx(7e-2,-7e-4),//35
    tcx(-9e-2,7e-4),//36
    tcx(-9e-2,9e-2),//37
    tcx(-7e-4,9e-2),  //38
    tcx(7e-2,0.9e-2), //39
    tcx(7e-2,1.1e-2) //40
  };
  std::array<c_t, NTST> w = { // erf(z[i]), evaluated with Maple
    tcx(-0.5366435657785650339917955593141927494421,
        -5.049143703447034669543036958614140565553), //0
    tcx(0.5366435657785650339917955593141927494421,
        -5.049143703447034669543036958614140565553), //1
    tcx(-0.5366435657785650339917955593141927494421,
        5.049143703447034669543036958614140565553), //2
    tcx(0.5366435657785650339917955593141927494421,
        5.049143703447034669543036958614140565553), //3
    tcx(0.3359473673830576996788000505817956637777e304,
        -0.1999896139679880888755589794455069208455e304), //4
    tcx(0.3584459971462946066523939204836760283645e278,
        0.3818954885257184373734213077678011282505e280), //5
    tcx(0.9996020422657148639102150147542224526887,
        0.00002801044116908227889681753993542916894856), //6
    tcx(-1, 0),//7
    tcx(1, 0),//8
    tcx(0.005754683859034800134412990541076554934877,
        0.1128349818335058741511924929801267822634e-7),//9
    tcx(-0.005529149142341821193633460286828381876955,
        0.005585388387864706679609092447916333443570),//10
    tcx(0.007099365669981359632319829148438283865814,
        0.6149347012854211635026981277569074001219),//11
    tcx(0.3981176338702323417718189922039863062440e8,
        -0.8298176341665249121085423917575122140650e10),//12
    tcx(-inf,
        -inf), //13
    tcx(0.007389128308257135427153919483147229573895,
        0.6149332524601658796226417164791221815139),
    tcx(0.4143671923267934479245651547534414976991e8,
        -0.8298168216818314211557046346850921446950e10),
    tcx(-inf,
        -inf),
    tcx(0.1128379167099649964175513742247082845155e-5,
        0.2256758334191777400570377193451519478895e-5),
    tcx(0,
        0.2256758334194034158904576117253481476197e-5),
    tcx(0,
        18.56480241457555259870429191324101719886),
    tcx(0,
        0.1474797539628786202447733153131835124599e173),
    tcx(0,
        inf),
    tcx(1,0),
    tcx(-1,0),
    tcx(0,inf),
    tcx(0,-inf),
    tcx(nan,nan),
    tcx(nan,nan),
    tcx(nan,nan),
    tcx(nan,0),
    tcx(0,nan),
    tcx(nan,nan),
    tcx(nan,nan),
    tcx(nan,nan),
    tcx(0.07924380404615782687930591956705225541145,
        0.07872776218046681145537914954027729115247),
    tcx(0.07885775828512276968931773651224684454495,
        -0.0007860046704118224342390725280161272277506),
    tcx(-0.1012806432747198859687963080684978759881,
        0.0007834934747022035607566216654982820299469),
    tcx(-0.1020998418798097910247132140051062512527,
        0.1010030778892310851309082083238896270340),
    tcx(-0.0007962891763147907785684591823889484764272,
        0.1018289385936278171741809237435404896152),
    tcx(0.07886408666470478681566329888615410479530,
        0.01010604288780868961492224347707949372245),
    tcx(0.07886723099940260286824654364807981336591,
        0.01235199327873258197931147306290916629654)
  };
  using kyosu::erf;
  using kyosu::conj;
  double ulps = 2000;
  for(int i=0; i < NTST; ++i)
  {
    auto [er, ei] = erf(z[i]);
    auto [wr, wi] = w[i];

    TTS_ULP_EQUAL(er, wr, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erf(z[i]) <<  " -> " <<w[i] <<"\n";
    TTS_ULP_EQUAL(ei, wi, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erf(z[i]) <<  " -> " <<w[i] <<'\n';

    auto [mer, mei] = erf(-z[i]);
    TTS_ULP_EQUAL(mer, -wr, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erf(z[i]) <<  " -> " <<w[i] <<"\n";
    TTS_ULP_EQUAL(mei, -wi, ulps) << "i " << i << " -> " << z[i] <<  " -> " <<erf(z[i]) <<  " -> " <<w[i] <<'\n';
  }
};

TTS_CASE_WITH( "Check behavior of erf on wide"
             , kyosu::simd_real_types
             , tts::generate( tts::randoms(-1.0, 1.0)
                            , tts::randoms(-1.0, 1.0))
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = kyosu::complex(a0, a1);
  auto ez = kyosu::erf(z);
  for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
  {
    TTS_RELATIVE_EQUAL(ez.get(i), kyosu::erf(z.get(i)), tts::prec<T>());
  }
};
