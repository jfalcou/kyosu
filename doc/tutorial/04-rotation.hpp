#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-rotation Rotations
//!
//! A unit quaternion
//! [represents a rotation](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation) of the
//! three-dimensional space.
//!
//! # Constructors
//!
//! The rotation of angle \f$\theta\f$ about the unit axis \f$u\f$ is the quaternion
//! \f$q = \cos\frac{\theta}{2} + \sin\frac{\theta}{2}\,(u_x i + u_y j + u_z k)\f$, which
//! `kyosu::from_angle_axis` builds from \f$\theta\f$ and \f$u\f$:
//!
//! @htmlinclude[block] rotation.svg
//!
//! A quaternion is built from one of the following:
//!
//! - an angle and an axis,
//! - Euler angles and their axes,
//! - a modulus, an argument, and a unit pure quaternion,
//! - the spherical or the cylindrical coordinates of the four-dimensional space.
//!
//! @godbolt{doc/tut_quat_constructors.cpp}
//!
//! # Comparison with Euler angles
//!
//! Three angles about three axes represent a rotation with two defects:
//!
//! - [gimbal lock](https://en.wikipedia.org/wiki/Gimbal_lock): when two of the three axes align,
//!   varying the angles no longer reaches every direction of motion,
//! - interpolation: a linear interpolation of the three angles is in general not the shortest
//!   path between two rotations, and has neither a fixed axis nor a constant angular speed.
//!
//! Unit quaternions cover every orientation without a singularity, and `kyosu::slerp` interpolates
//! between two of them along the shortest arc. Two rotations compose by the product of their quaternions.
//!
//! # Rotating a vector
//!
//! The rotation sends a vector \f$v\f$, taken as the pure quaternion \f$v_x i + v_y j + v_z k\f$,
//! to \f$v' = q v q^{-1}\f$, which `kyosu::rotate_vec` computes. The angle of `kyosu::from_angle_axis` is in radians, or a multiple of \f$\pi\f$ with
//! the option `kyosu::radpi`. `kyosu::from_angle_axis` takes the axis, and `kyosu::rotate_vec` the
//! vector, as an array of three reals passed as a
//! [`std::span`](https://en.cppreference.com/w/cpp/container/span). `kyosu::rotate_vec` returns the
//! rotated vector as a `std::array`:
//!
//! @godbolt{doc/tut_rot_apply.cpp}
//!
//! The quarter turn about \f$z\f$ sends \f$x\f$ to \f$y\f$: a positive angle turns counterclockwise
//! about the axis, by the right-hand rule. The first component of the result prints as
//! \f$2.22045 \cdot 10^{-16}\f$ in place of \f$0\f$, a rounding error of the computation in
//! `double`.
//!
//! @note `kyosu::from_angle_axis` normalizes the axis, and `kyosu::rotate_vec` also normalizes the
//! quaternion, so neither argument has to be of unit length. The @ref tutorial-options "option"
//! `kyosu::assume_unitary` skips the normalization when the argument is already of unit length.
//!
//! # Composition
//!
//! The rotation \f$p\f$ followed by \f$q\f$ is the product \f$qp\f$, in that order, since the
//! product does not commute:
//!
//! @godbolt{doc/tut_rot_compose.cpp}
//!
//! The quarter turn \f$p\f$ about \f$z\f$ followed by the quarter turn \f$q\f$ about \f$y\f$ sends
//! \f$x\f$ to \f$y\f$, while the product in the other order, \f$pq\f$, sends \f$x\f$ to \f$-z\f$.
//!
//! @warning A product written in the wrong order, or one division taken for the other, composes
//! the rotations backward.
//!
//! # Interpolation
//!
//! `kyosu::slerp`, the [spherical linear interpolation](https://en.wikipedia.org/wiki/Slerp),
//! interpolates between two orientations along the shortest arc at constant angular speed.
//! `kyosu::slerp` normalizes its two operands. Since \f$q\f$ and \f$-q\f$ are the
//! [same rotation](https://en.wikipedia.org/wiki/3D_rotation_group#Connection_between_SO%283%29_and_SU%282%29),
//! it negates the second operand when their dot product is negative, so that the arc is the short
//! one:
//!
//! @godbolt{doc/tut_rot_slerp.cpp}
//!
//! From the identity to the quarter turn about \f$z\f$, the steps of \f$t = 0.25\f$ turn \f$x\f$ by
//! \f$22.5\f$ degrees each, from \f$x\f$ to \f$y\f$.
//!
//! # Conversions
//!
//! A rotation converts to and from three other forms:
//!
//! - a rotation matrix, with kyosu::to_rotation_matrix and kyosu::from_rotation_matrix,
//! - Euler angles with their axes, with kyosu::to_euler and kyosu::from_euler,
//! - an angle and an axis, with kyosu::to_angle_axis and kyosu::from_angle_axis.
//!
//! The matrix is a `std::array` of three rows. The angle and the axis, and the three Euler angles,
//! are returned as a `kumi::tuple`, read by a
//! [structured binding](https://en.cppreference.com/w/cpp/language/structured_binding):
//!
//! @godbolt{doc/tut_rot_convert.cpp}
//!
//! kyosu::to_angle_axis gives back the angle \f$\pi/3\f$ and the axis \f$z\f$, and the round
//! trips through the Euler angles and through the matrix give back \f$q\f$.
//!
//! The Euler angles follow these conventions:
//!
//! - the angles are in radians, or in multiples of \f$\pi\f$ with the option `kyosu::radpi`,
//! - the three axes follow the angles in the order of the rotations, the first angle going with
//!   the first axis,
//! - each axis is one of `kyosu::X_`, `kyosu::Y_`, and `kyosu::Z_`, and two consecutive axes are
//!   distinct,
//! - by default each rotation is about the axis as moved by the rotations before it, the
//!   [intrinsic](https://en.wikipedia.org/wiki/Euler_angles#Definition_by_intrinsic_rotations)
//!   convention,
//! - with the option `kyosu::extrinsic`, each rotation is about a
//!   [fixed axis](https://en.wikipedia.org/wiki/Euler_angles#Definition_by_extrinsic_rotations).
//!
//! A round trip through a matrix or a triple of angles may return \f$-q\f$ in place of \f$q\f$.
//!
//! <div class="section_buttons">
//!
//! | Previous                                              |                             Next |
//! |:------------------------------------------------------|---------------------------------:|
//! | [Octonions and higher algebras](@ref tutorial-beyond) | [Options](@ref tutorial-options) |
//!
//! </div>
