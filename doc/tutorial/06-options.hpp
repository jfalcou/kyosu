#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-options Options
//!
//! Some functions have different behaviors depending on the context:
//!
//! - `kyosu::sqrt` may return \f$i\f$ or a NaN on \f$-1\f$,
//! - `kyosu::to_euler` may return its angles in radians or in multiples of \f$\pi\f$,
//! - `kyosu::log` may evaluate with full accuracy, or by a faster formula with less precision,
//! - `kyosu::rotate_vec` assumes its quaternion is not normalized, but it may be.
//!
//! A specific function for each behavior would dilute the API, so **KYOSU** reuses the
//! [option](https://jfalcou.github.io/eve/design_rationale.html#rationale-decorator) mechanism of
//! EVE:
//!
//! @code
//! kyosu::sqrt[kyosu::real_only](-1.0)
//! @endcode
//!
//! Options, which modify the semantics of a function, are passed in square brackets after its
//! name. `kyosu::sqrt[kyosu::real_only]` is a new
//! [callable](https://en.cppreference.com/w/cpp/named_req/Callable), which is then applied to the
//! arguments.
//!
//! Options compose, as in `kyosu::to_euler[kyosu::extrinsic][kyosu::radpi]`. A function of its
//! own for that combination, `to_euler_extrinsic_radpi`, would be obscure in the API.
//!
//! # raw
//!
//! By default a function is accurate over its whole domain and handles the edges of that domain.
//! `kyosu::raw` selects the fastest formula instead, with two effects:
//!
//! - less accuracy on ordinary input,
//! - no handling of the edges.
//!
//! Below, `kyosu::log` and `kyosu::log[kyosu::raw]` are applied to an ordinary value and to the
//! origin, where the default returns an imaginary part and the option a NaN:
//!
//! @godbolt{doc/tut_opt_raw.cpp}
//!
//! `kyosu::raw` is for an inner loop whose cost has been measured, not a default.
//!
//! # radpi
//!
//! By default, angles are in radians. An angle such as \f$\pi/2\f$ is then an
//! [irrational](https://en.wikipedia.org/wiki/Proof_that_%CF%80_is_irrational) number, which no
//! floating point number represents exactly, so `pi/2` already carries a rounding error.
//! `kyosu::radpi` reads and returns angles as multiples of \f$\pi\f$ instead, with two effects:
//!
//! - `0.5` stands for \f$\pi/2\f$ exactly,
//! - the result carries no rounding error of \f$\pi\f$.
//!
//! Below, `kyosu::sin` is applied to a half turn and to a million half turns, where the sine is
//! zero, in radians and with the option:
//!
//! @godbolt{doc/tut_opt_radpi.cpp}
//!
//! # real_only
//!
//! By default, a real argument outside the real domain of a function gives a complex result.
//! `kyosu::real_only` selects the real function instead, with two effects:
//!
//! - the result is a real,
//! - an argument outside the real domain gives a NaN.
//!
//! Below, `kyosu::acosh` and `kyosu::asin` are applied to arguments outside their real domains,
//! with and without the option:
//!
//! @godbolt{doc/tut_opt_real_only.cpp}
//!
//! # assume_unitary
//!
//! By default, `kyosu::from_angle_axis` and `kyosu::rotate_vec` normalize their argument, since a
//! rotation is a unit quaternion. `kyosu::assume_unitary` skips that normalization on an argument
//! known to be of unit length, with two effects:
//!
//! - `kyosu::from_angle_axis` uses its axis as given,
//! - `kyosu::rotate_vec` uses its quaternion as given.
//!
//! Below, `kyosu::rotate_vec` is applied to a unit quaternion, with and without the option:
//!
//! @godbolt{doc/tut_opt_assume_unitary.cpp}
//!
//! @warning The option is not checked: on an argument that is not of unit length, the result is
//! wrong.
//!
//! <div class="section_buttons">
//!
//! | Previous |
//! |:---------|
//! | [Rotations](@ref tutorial-rotation) |
//!
//! </div>
