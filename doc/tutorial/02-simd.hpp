#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-simd SIMD support
//!
//! **KYOSU** is built on [EVE](https://github.com/jfalcou/eve), and every function accepts an
//! `eve::wide` where it accepts a scalar. An `eve::wide<T>` is a SIMD register of `T`, on which
//! the arithmetic is the arithmetic of a scalar. `kyosu/kyosu.hpp` includes EVE, so `eve::wide`
//! and the constants of EVE need no header of their own. Nothing of SIMD programming is assumed
//! below.
//!
//! @note Everything about SIMD programming, the registers, the masks, the algorithms, and the
//! architectures, is in the [EVE documentation](https://jfalcou.github.io/eve/) and its
//! [tutorials](https://jfalcou.github.io/eve/intro-01.html).
//!
//! # Registers of reals
//!
//! `eve::wide<double>` holds as many `double` as a register of the target machine: two on x86-64
//! with SSE2, four with AVX, eight with AVX-512. The width is a property of the target, selected
//! at compile time, and the source never names it.
//!
//! A register is built from a function of two arguments, the lane index and the width, called
//! once per lane: below, a [lambda](https://en.cppreference.com/w/cpp/language/lambda) puts
//! \f$-1 + i\f$ in lane \f$i\f$, and the width goes unused. The arithmetic and the functions
//! apply to every lane:
//!
//! @godbolt{doc/tut_simd_wide.cpp}
//!
//! `eve::wide<double>::size()` is the number of `double` in the register. The square root of a
//! register of reals is a register of complex numbers, since any lane may be negative, and
//! `kyosu::real_only` selects the real function on every lane.
//!
//! # Registers of complex numbers
//!
//! `eve::wide<kyosu::complex_t<double>>` is a register of complex numbers, built by
//! `kyosu::complex` from two registers of reals, and every function applies to all its lanes:
//!
//! @godbolt{doc/tut_simd_complex.cpp}
//!
//! The source differs from the scalar case by the type of the components alone. There is no
//! separate SIMD interface and no `#ifdef` on the architecture.
//!
//! @note `auto z = kyosu::complex(re, im);` builds the same register with its type deduced from
//! the components, and is the form to prefer.
//!
//! # Generic code
//!
//! A [function template](https://en.cppreference.com/w/cpp/language/function_template) accepts
//! scalars and registers with the same body:
//!
//! @godbolt{doc/tut_simd_generic.cpp}
//!
//! The template is instantiated once per argument type, scalar or wide, and no code is written
//! per width.
//!
//! <div class="section_buttons">
//!
//! | Previous                              |                            Next |
//! |:--------------------------------------|--------------------------------:|
//! | [Complex numbers](@ref tutorial-complex) | [Quaternions](@ref tutorial-quaternion) |
//!
//! </div>
