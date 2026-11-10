#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-simd SIMD support
//!
//! **KYOSU** is built on [EVE](https://github.com/jfalcou/eve), and every function accepts an
//! `eve::wide` where it accepts a scalar. An `eve::wide<T>` is a SIMD register of `T`, whose
//! operators apply to every lane as they apply to a scalar. `kyosu/kyosu.hpp` also includes EVE, so `eve::wide`
//! and the constants of EVE need no header of their own.
//!
//! @note The [EVE documentation](https://jfalcou.github.io/eve/) and its
//! [tutorials](https://jfalcou.github.io/eve/intro-01.html) cover SIMD programming: the registers,
//! the masks, the algorithms, and the architectures.
//!
//! # Registers of reals
//!
//! `eve::wide<double>` holds as many `double` as a register of the target machine:
//!
//! - two on x86-64 with SSE2,
//! - four with AVX,
//! - eight with AVX-512.
//!
//! The width is selected at compile time from the target, and the source never names it.
//!
//! A register is built from a function of two arguments, the lane index and the width, called once
//! per lane. Below, a [lambda](https://en.cppreference.com/w/cpp/language/lambda) puts
//! \f$-1 + k\f$ in lane \f$k\f$ and leaves the width unused:
//!
//! @godbolt{doc/tut_simd_wide.cpp}
//!
//! `eve::wide<double>::size()` is the number of `double` in the register. The square root of a
//! register of reals is a register of complex numbers, since a lane may be negative. With
//! `kyosu::real_only`, the result is a register of reals.
//!
//! # Registers of complex numbers
//!
//! `eve::wide<kyosu::complex_t<double>>` is a register of complex numbers. `kyosu::complex` builds
//! it from two registers of reals, and the functions are applied to all its lanes:
//!
//! @godbolt{doc/tut_simd_complex.cpp}
//!
//! The source differs from the scalar case only by the type of the components.
//!
//! @note `auto z = kyosu::complex(re, im);` builds the same register while deducing its type from
//! the components, and is the preferred form.
//!
//! # Generic code
//!
//! A [function template](https://en.cppreference.com/w/cpp/language/function_template) accepts
//! scalars and registers with the same body:
//!
//! @godbolt{doc/tut_simd_generic.cpp}
//!
//! `energy` returns a `double` when given a complex number, and an `eve::wide<double>` when given
//! a register of complex numbers. The template is instantiated once for each argument type, and no
//! code is written per width.
//!
//! <div class="section_buttons">
//!
//! | Previous                                 |                                    Next |
//! |:-----------------------------------------|----------------------------------------:|
//! | [Complex numbers](@ref tutorial-complex) | [Quaternions](@ref tutorial-quaternion) |
//!
//! </div>
