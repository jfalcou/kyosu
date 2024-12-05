#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <array>

int main()
{

  std::array<double, 16> a{1, 2, 3, 4, 5,  6, 7,  8, 11, 21, 31, 41, 51,  61, 71, 81};
  std::cout << "reverse_horner(a[0],a[1],a[2],a[3], a[4]) " << kyosu::reverse_horner(a[0],a[1],a[2],a[3], a[4]) << std::endl;

  auto x = kyosu::quaternion(a[0],a[1],a[2],a[3]);
  auto q1= kyosu::quaternion(a[4],a[5],a[6],a[7]);
  auto q2= kyosu::quaternion(a[8],a[9],a[10],a[11]);
  auto q3= kyosu::quaternion(a[12],a[13],a[14],a[15]);
  std::cout << "reverse_horner(x, q1, q2, q3) " << kyosu::reverse_horner(x, q1, q2, q3) << std::endl;
  auto x1= kyosu::complex(a[1],a[6]);
  auto c1= kyosu::complex(a[4],a[3]);
  auto c2= kyosu::complex(a[8],a[9]);
  auto c3= kyosu::complex(a[1],a[2]);
  std::cout << "reverse_horner(x, q1, c2, a[2]) " << kyosu::reverse_horner(x, q1, c2, a[12]) << std::endl;
  std::cout << "reverse_horner(x, c1, c2, c3) " << kyosu::reverse_horner(x, c1, c2, c3) << std::endl;
  std::cout << "reverse_horner(x1, c1, c2, c3) " << kyosu::reverse_horner(x1, c1, c2, c3) << std::endl;
  auto o1= kyosu::cayley_dickson(a[4],a[5],a[6],a[7], a[8],a[9],a[10],a[11]);
  auto o2= kyosu::cayley_dickson(a[0],a[1],a[2],a[3], a[8],a[9],a[10],a[11]);
  auto o3= kyosu::cayley_dickson(a[12],a[13],a[14],a[15],a[4],a[5],a[6],a[7]);
  std::cout << "reverse_horner(x, o1, c2, a[2]) " << kyosu::reverse_horner(x, o1, c2, a[2]) << std::endl;
  std::cout << "reverse_horner(x, o1, o2, o3) " << kyosu::reverse_horner(x, o1, o2, o3) << std::endl;
};
