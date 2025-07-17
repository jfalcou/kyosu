#include <eve/wide.hpp>
#include <kyosu/kyosu.hpp>
#include <iostream>
#include <test.hpp>


struct toto
{

  template<typename Z0,typename Z1>
  struct result
  {
    using type =  decltype(kyosu::real(kyosu::pow(kyosu::abs(Z0()), Z1())));
  };

  template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson Z1>
  struct result<Z0,Z1>
  {
    using type =  decltype((kyosu::pow(kyosu::abs(Z0()), Z1())));
  };

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_value Z1>
  struct result<Z0,Z1>
  {
    using r_t = decltype(eve::convert(Z1(), eve::as(eve::element_type_t<kyosu::as_real_type_t<Z0>>())));
    using type =  decltype(kyosu::real(kyosu::pow(kyosu::abs(Z0()), r_t())));
  };

  //===========================================================

  template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 z1) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    std::cout << " ==== 1  " << std::endl;
    return that_t(kyosu::pow(kyosu::abs(z0),z1));
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::floating_value Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 z1) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    std::cout << " ==== 1  " << std::endl;
    return that_t(kyosu::real(kyosu::pow(kyosu::abs(z0),z1)));
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_scalar_value Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 z1) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    std::cout << " ==== 2  " << std::endl;
    auto cz1 =  Z0(z1);
    return that_t(kyosu::real(kyosu::pow(kyosu::abs(z0),cz1)));
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_simd_value Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 z1) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    std::cout << " ==== 2  " << std::endl;
    auto cz1 =  eve::convert(z1, eve::as(eve::element_type_t<kyosu::as_real_type_t<Z0>>()));
    return that_t(kyosu::real(kyosu::pow(kyosu::abs(z0),cz1)));
  }
};

TTS_CASE_WITH ( "Check kyosu::abs over real"
              , kyosu::real_types
              , tts::generate(tts::randoms(-10,10))
              )
<typename T>(T )
{
  if constexpr(sizeof(T) == 8)
  {
    double r(4.5);
    using wi_t =  eve::wide<unsigned int, eve::fixed<2>>;
    wi_t n{4,5};
    kyosu::as_cayley_dickson_n_t<2, double> cr{4.,5.};

    toto t;
    std::cout << "\ncomplex results"<< "\n";
    std::cout << "cr,cr: " << t(cr,cr) << "\n";
    std::cout << "r,cr: " << t( r,cr) << "\n";

    std::cout << "\nreal results"<< "\n";
    std::cout << "cr,n: " << t(cr, n) << "\n";
    std::cout << "cr,4: " << t(cr, 4) << "\n";
    std::cout << "cr,r: " << t(cr, r) << "\n";
    std::cout << "r,r: " << t( r, r) << "\n";
    std::cout << "r,4: " << t( r, 4) << "\n";
    std::cout << "r,n: " << t( r, n) << "\n";


    using w_t = eve::wide<double, eve::fixed<2>>;
    kyosu::as_cayley_dickson_n_t<2, w_t> cwr{cr};
    w_t wr(4.5);

    std::cout << "\ncomplex results"<< "\n";
    std::cout << "cwr,cwr: " << t(cwr,cwr) << "\n";
    std::cout << "wr,cwr: " << t( wr,cwr) << "\n";

    std::cout << "\nreal results"<< "\n";
    std::cout << "wrc,wr: " << t(cwr, wr) << "\n";
    std::cout << "cwr,n: " << t(cwr, n) << "\n";
    std::cout << "cwr,4: " << t(cwr, 4) << "\n";
    std::cout << "wr,wr: " << t( wr, wr) << "\n";
    std::cout << "wr,4: " << t( wr, 4) << "\n";
    std::cout << "wr,n: " << t( wr, n) << "\n";

  }
};
