#include <eve/wide.hpp>
#include <kyosu/kyosu.hpp>
#include <iostream>


struct toto
{

  template<typename Z0,typename Z1>
  struct result  : eve::as_wide_as<Z0,Z1>
  {};

  template<kyosu::concepts::cayley_dickson Z0, kyosu::concepts::cayley_dickson Z1>
  struct result<Z0,Z1> : kyosu::as_cayley_dickson_like<Z0, Z1>
  {};

  template<kyosu::concepts::real Z0, kyosu::concepts::cayley_dickson Z1>
  struct result<Z0,Z1> : eve::as_wide_as<Z1,Z0>
  {};

  template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson_like Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 z1) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    return that_t(z0+z1);
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_simd_value Z1>
  KYOSU_FORCEINLINE constexpr
  typename result<Z0,Z1>::type operator()(Z0 z0, Z1 ) const noexcept
  {
    using that_t = typename result<Z0,Z1>::type;
    return that_t(z0);
  }
};

int main()
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

};
