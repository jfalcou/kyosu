#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{ eve::wide xd{0.5, -1.5, 0.1, -1.0};
  eve::wide n{0.0, 1.0, 2.0, 3.0};

 auto I = kyosu::complex(0.0, 1.0);
  std::cout << "tricomi(2.0, 1, 1.5)                    "<< kyosu::tricomi(2.0, 1, 1.5)        << std::endl;
  std::cout << "tricomi(2.0, 1, I)                      "<< kyosu::tricomi(2.0, 1, I)          << std::endl;
  std::cout << "tricomi(xd, n, I)                       "<< kyosu::tricomi(xd, n, I)           << std::endl;
  std::cout << "tricomi[n >= 2.0](xd, n, I)             "<< kyosu::tricomi[n >= 2.0](xd, n, I)  << std::endl;
  std::cout << "tricomi[eve::ignore_last(2)](xd, n, I)  "<< kyosu::tricomi[eve::ignore_last(2)](xd, n, I) << std::endl;

 return 0;
}
