#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::align;
  auto norm = [](auto& v) {
    auto n = eve::hypot(v[0], v[1], v[2]);
    for (int i = 0; i <= 2; ++i) v[i] /= n;
  };

  std::array<double, 3> v0{-1.0, 5.0, 4.0};
  std::array<double, 3> v1{1.5, 2.0, -3.0};
  norm(v0);
  norm(v1);
  auto q = kyosu::align(std::span(v0), std::span(v1));
  std::cout << " v0                " << v0[0] << ", " << v0[1] << ",  " << v0[2] << "\n";
  std::cout << " v1                " << v1[0] << ", " << v1[1] << ",  " << v1[2] << "\n";
  std::cout << " q                 " << q << std::endl;
  auto rv = kyosu::rotate_vec(q, std::span(v0));
  std::cout << " rotate_vec(q, v0) " << rv[0] << ", " << rv[1] << ",  " << rv[2] << "\n";

  return 0;
}
