#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  std::cout << "o       = " << o              << "\n";
  std::cout << "abs(o)  = " << kyosu::abs(o)  << "\n";
  std::cout << "conj(o) = " << kyosu::conj(o) << "\n";
  std::cout << "exp(o)  = " << kyosu::exp(o)  << "\n";
}
