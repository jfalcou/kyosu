#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using q_t = kyosu::quaternion_t<double>;
  auto c = kyosu::complex_t<double>(1., 2.);
  auto q = q_t(1., 2., 3., 4.);
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  // Dimensions mix freely: the result takes the largest one.
  std::cout << "c + q = " << c + q << "\n";
  std::cout << "q * o = " << q * o << "\n";

  // The constants behave as the algebra says they should, and it is not commutative.
  auto i = kyosu::i(kyosu::as<q_t>());
  auto j = kyosu::j(kyosu::as<q_t>());
  std::cout << "i * j = " << i * j << "\n";
  std::cout << "j * i = " << j * i << "\n";

  // Which is why a left-division of its own is needed.
  std::cout << "q / c      = " << q / c            << "\n";
  std::cout << "ldiv(c, q) = " << kyosu::ldiv(c, q) << "\n";
}
