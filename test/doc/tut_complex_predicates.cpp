#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto z = kyosu::complex_t<double>(3., 4.);
  auto w = kyosu::complex_t<double>(3., 0.);

  std::cout << std::boolalpha;
  std::cout << "z == w        : " << (z == w)              << "\n";
  std::cout << "is_real(w)    : " << kyosu::is_real(w)     << "\n";
  std::cout << "is_pure(z)    : " << kyosu::is_pure(z)     << "\n";
  std::cout << "is_finite(z)  : " << kyosu::is_finite(z)   << "\n";
}
