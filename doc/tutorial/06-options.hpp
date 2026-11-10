#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-options Options
//!
//! Some functions have several behaviors:
//!
//! - `kyosu::sqrt` may return \f$i\f$ or NaN on \f$-1\f$,
//! - `kyosu::to_euler` may return its angles in radians or in multiples of \f$\pi\f$,
//! - `kyosu::log` may evaluate with full accuracy, or by a faster and less precise formula,
//! - `kyosu::rotate_vec` normalizes its quaternion, or may take it as already normalized.
//!
//! A function of its own for each behavior would multiply the names of the API, so **KYOSU** reuses
//! the [option](https://jfalcou.github.io/eve/design_rationale.html#rationale-decorator) mechanism
//! of EVE:
//!
//! @godbolt{doc/tut_opt_call.cpp}
//!
//! An option, which modifies the semantics of a function, is passed in square brackets after its
//! name. `kyosu::sqrt[kyosu::real_only]` is a new
//! [callable](https://en.cppreference.com/w/cpp/named_req/Callable), which is then applied to the
//! arguments.
//!
//! Options compose, as in `kyosu::to_euler[kyosu::extrinsic][kyosu::radpi]`.
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
//! origin:
//!
//! @godbolt{doc/tut_opt_raw.cpp}
//!
//! With the option, the imaginary part loses accuracy on \f$3 + 4i\f$, and turns into a NaN at the
//! origin.
//!
//! # radpi
//!
//! By default, angles are in radians. In radians, \f$\pi/2\f$ is an
//! [irrational](https://en.wikipedia.org/wiki/Proof_that_%CF%80_is_irrational) number. No floating
//! point number represents it exactly, so `pi/2` already carries a rounding error.
//! `kyosu::radpi` reads and returns angles as multiples of \f$\pi\f$ instead, with two effects:
//!
//! - `0.5` stands for \f$\pi/2\f$ exactly,
//! - the result carries no rounding error of \f$\pi\f$.
//!
//! Below, `kyosu::sin` is applied to a half turn and to a million half turns, in radians and with
//! the option:
//!
//! @godbolt{doc/tut_opt_radpi.cpp}
//!
//! The sine of both angles is zero. In radians, the result is the rounding error of \f$\pi\f$
//! carried through the sine, and it grows with the angle.
//!
//! # real_only
//!
//! By default, a real argument outside the real domain of a function gives a complex result.
//! `kyosu::real_only` selects the real function instead, with two effects:
//!
//! - the result is a real,
//! - an argument outside the real domain gives NaN.
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
//! On a unit quaternion, the two calls agree.
//!
//! @warning The option is not checked: on an argument that is not of unit length, the result is
//! wrong.
//!
//! <div class="section_buttons">
//!
//! | Previous                            |
//! |:------------------------------------|
//! | [Rotations](@ref tutorial-rotation) |
//!
//! </div>
