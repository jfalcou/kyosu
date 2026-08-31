#include <iostream>
#include <kyosu/kyosu.hpp>

using s_t = kyosu::as_cayley_dickson_n_t<16, double>;
template<int N> s_t e() { s_t z{}; kyosu::get<N>(z) = 1.; return z; }

int main()
{
  auto a = e<3>() + e<10>();
  auto b = e<6>() - e<15>();

  std::cout << "|a|    = " << kyosu::abs(a)   << "\n";
  std::cout << "|b|    = " << kyosu::abs(b)   << "\n";
  std::cout << "|a*b|  = " << kyosu::abs(a*b) << "\n";

  // The product destroys the operands, and no division brings them back.
  std::cout << "|ldiv(b, a*b)| = " << kyosu::abs(kyosu::ldiv(b, a*b))
            << "   but |a| = "     << kyosu::abs(a) << "\n";
}
