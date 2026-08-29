#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  // Past dimension 8 the type is named by its dimension.
  using s_t = kyosu::as_cayley_dickson_n_t<16, double>;
  s_t s{};
  kyosu::get<0>(s) = 1.;
  kyosu::get<9>(s) = 2.;

  std::cout << "octonion  : " << o             << "\n";
  std::cout << "sedenion  : " << s             << "\n";
  std::cout << "abs(o)    = " << kyosu::abs(o) << "\n";
  std::cout << "exp(s)    = " << kyosu::exp(s) << "\n";
}
