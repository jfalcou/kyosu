#include <kyosu/kyosu.hpp>

int main()
{
  using r_t = eve::wide<double, eve::fixed<4>>;
  using z_t = eve::wide<kyosu::complex_t<double>, eve::fixed<4>>;

  r_t a0(0.570496, 0.588969, 9.2607, 9.97403);
  r_t a1(1.52101, 7.67699, 0.317079 , 4.23027);
  r_t a2{9.2607, 9.97403, 9.2607, 9.97403};
  r_t a3{0.317079 , 4.23027, 0.317079 , 4.23027};

  z_t a(a0, a1);
  z_t b(a2, a3);

  std::cout << "a  " << a << std::endl;
  std::cout << "b  " << b << std::endl;

  auto rf =  [](auto z0){
    return  kyosu::tgamma(z0);
  };
  auto aa2 =  rf(a+z_t(-2));
  std::cout << "aa2 " << aa2 << std::endl;
  auto bb2 =  rf(b+ z_t(-2));
  std::cout << "bb2 " << bb2 << std::endl;
}
