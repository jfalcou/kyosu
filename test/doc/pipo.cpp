#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>


struct toto
{
  template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::cayley_dickson Z1>
  requires(!eve::integral_value<Z1>)
    KYOSU_FORCEINLINE constexpr
  auto operator()(Z0 z0, Z1 z1) const noexcept -> kyosu::complexify_t<kyosu::as_cayley_dickson_like_t<kyosu::as_real_type_t<Z0>, Z1>>
  {
    std::cout << "icitte 1" << std::endl;
    return kyosu::complexify_t<kyosu::as_cayley_dickson_like_t<kyosu::as_real_type_t<Z0>, Z1>>(z0+z1);
  }

  template<kyosu::concepts::cayley_dickson_like Z0, kyosu::concepts::real Z1>
  requires(!eve::integral_value<Z1>)
    KYOSU_FORCEINLINE constexpr
  auto operator()(Z0 z0, Z1 z1) const noexcept// -> kyosu::complexify_t<kyosu::as_cayley_dickson_like_t<kyosu::as_real_type_t<Z0>, Z1>>
  {
    std::cout << "icitte 2" << std::endl;
    return kyosu::complexify_t<kyosu::as_cayley_dickson_like_t<kyosu::as_real_type_t<Z0>, Z1>>(z0+z1);
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_scalar_value Z1>
  KYOSU_FORCEINLINE constexpr
  auto operator()(Z0 z0, Z1 ) const noexcept -> kyosu::as_real_type_t<Z0>
  {
    std::cout << "icitte 3" << std::endl;
    return kyosu::abs(z0);
  }

  template<kyosu::concepts::cayley_dickson_like Z0, eve::integral_simd_value Z1>
  KYOSU_FORCEINLINE constexpr
  auto operator()(Z0 z0, Z1 ) const noexcept -> eve::as_wide_as_t<kyosu::as_real_type_t<Z0>, Z1>
  {
    std::cout << "icitte 4" << std::endl;
    using r_t = eve::as_wide_as_t<kyosu::as_real_type_t<Z0>, Z1>;
    return r_t( kyosu::abs(z0));
  }
};

int main()
{
  double r(4.5);
  using wi_t =  eve::wide<unsigned int, eve::fixed<2>>;
  wi_t n{4, 5};
  using c_t =  kyosu::as_cayley_dickson_n_t<2, double>;
  c_t cr{4.0, 5.0};

  toto t;
   std::cout << "toto(cr, cr)" << t(cr, cr) << std::endl;
   std::cout << "toto(r, r)" << t(r, r) << std::endl;
   std::cout << "toto(r, 4)" << t(r, 4) << std::endl;
   std::cout << "toto(r, n)" << t(r, n) << std::endl;
};
