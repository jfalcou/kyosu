#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using s_t = kyosu::as_cayley_dickson_n_t<32, double>;
  s_t z{};
  kyosu::get<0>(z) = 0.5;
  kyosu::get<7>(z) = 0.25;

  // A single element generates an associative subalgebra, on which these are defined.
  std::cout << "exp(log(z)) = " << kyosu::exp(kyosu::log(z)) << "\n";
  std::cout << "z           = " << z                         << "\n";
  std::cout << "sqrt(z)^2   = " << kyosu::sqr(kyosu::sqrt(z)) << "\n";
}
