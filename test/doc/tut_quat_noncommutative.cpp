#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using q_t = kyosu::quaternion_t<double>;

  auto i = kyosu::i(kyosu::as<q_t>());
  auto j = kyosu::j(kyosu::as<q_t>());

  std::cout << "i * j = " << i * j << "\n";
  std::cout << "j * i = " << j * i << "\n";

  auto a = q_t(1., 2., 3., 4.);
  auto b = q_t(0., 1., 0., 1.);
  std::cout << "a * b = " << a * b << "\n";
  std::cout << "b * a = " << b * a << "\n";
}
