#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using s_t = kyosu::as_cayley_dickson_n_t<16, double>;
  s_t s{};
  kyosu::get<0>(s) = 1.;
  kyosu::get<9>(s) = 2.;

  std::cout << "s       = " << s              << "\n";
  std::cout << "get<9>  = " << kyosu::get<9>(s) << "\n";
  std::cout << "abs(s)  = " << kyosu::abs(s)  << "\n";
  std::cout << "exp(s)  = " << kyosu::exp(s)  << "\n";
}
