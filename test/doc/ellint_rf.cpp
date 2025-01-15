#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout<< std::setprecision(16) << std::endl;
  auto r =  kyosu::ellint_rf(kyosu::complex(1.0), kyosu::complex(2.0), kyosu::complex(0.0));
  auto rf=  eve::ellint_rf(1.0, 2.0, 0.0);
  std::cout<< " kyosu::ellint_rf(kyosu::complex(1.0), kyosu::complex(2.0), kyosu::complex(0.0));" << r << std::endl;
  std::cout<< " eve::ellint_rf(1.0, 2.0, 0.0)                                                   " << rf<< std::endl;
   r =  kyosu::ellint_rf(kyosu::complex(0.0, 1.0), kyosu::complex(0.0, -1.0), kyosu::complex(0.0));
   rf=  eve::ellint_rf(0.5     , 1.0      , 0.0);
  auto rr = kyosu::ellint_rf(kyosu::complex(0.5), kyosu::complex(1.0), kyosu::complex(0.0));
  std::cout<< " r " << r << std::endl;
  std::cout<< " rr "<< rr << std::endl;
  std::cout<< " rf " << rf << std::endl;
  r =  kyosu::ellint_rf(kyosu::complex(-1.0, 1.0), kyosu::complex(0.0, 1.0), kyosu::complex(0.0));
  std::cout<< " r " << r << std::endl;

  return 0;
}
