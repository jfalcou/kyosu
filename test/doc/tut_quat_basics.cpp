#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);

  std::cout << "q          = " << q                  << "\n";
  std::cout << "abs(q)     = " << kyosu::abs(q)      << "\n";
  std::cout << "conj(q)    = " << kyosu::conj(q)     << "\n";
  std::cout << "rec(q)     = " << kyosu::rec(q)      << "\n";
  std::cout << "pure(q)    = " << kyosu::pure(q)     << "\n";
  std::cout << "exp(q)     = " << kyosu::exp(q)      << "\n";
  std::cout << "sqrt(q)    = " << kyosu::sqrt(q)     << "\n";
}
