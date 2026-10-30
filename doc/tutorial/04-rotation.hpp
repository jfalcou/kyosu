#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-rotation Rotations
//!
//! A unit quaternion [represents a rotation](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation) of the
//! three-dimensional space, and is the standard
//! representation of rotations in graphics, robotics, and aerospace.
//!
//! # Constructors
//!
//! The rotation of angle \f$\theta\f$ about the unit axis \f$u\f$ is the quaternion
//! \f$q = \cos\frac{\theta}{2} + \sin\frac{\theta}{2}\,(u_x i + u_y j + u_z k)\f$, which
//! `kyosu::from_angle_axis` builds from \f$\theta\f$ and \f$u\f$:
//!
//! @htmlinclude[block] rotation.svg
//!
//! A quaternion can be built from an angle and an axis, from Euler angles with their axes, from
//! a modulus, an argument, and a unit pure quaternion, or from the spherical and cylindrical
//! coordinates of the four-dimensional space:
//!
//! @godbolt{doc/tut_quat_constructors.cpp}
//!
//! # Comparison with Euler angles
//!
//! Three angles around three axes represent a rotation with two defects. The first is
//! [gimbal lock](https://en.wikipedia.org/wiki/Gimbal_lock): at some orientations two of the three axes align, and a direction of motion is no
//! longer reached by varying the angles. The second concerns interpolation: a linear
//! interpolation of the three angles is not the shortest path between the two rotations, and
//! has neither a fixed axis nor a constant angular speed. A unit quaternion has neither defect:
//! it covers every orientation without a singularity, it composes by multiplication, and two of
//! them interpolate along the shortest arc.
//!
//! # Rotating a vector
//!
//! The rotation sends a vector \f$v\f$ to \f$v' = q v q^{-1}\f$, which `kyosu::rotate_vec`
//! computes. The angle of `kyosu::from_angle_axis` is in radians. `kyosu::rotate_vec` takes the
//! vector as an array of three reals passed as a
//! [`std::span`](https://en.cppreference.com/w/cpp/container/span), and returns the rotated
//! vector as a `std::array`:
//!
//! @godbolt{doc/tut_rot_apply.cpp}
//!
//! A positive angle turns counterclockwise about the axis, by the right-hand rule: the quarter
//! turn about \f$z\f$ sends \f$x\f$ to \f$y\f$.
//!
//! @note `kyosu::from_angle_axis` normalizes the axis, and `kyosu::rotate_vec` the quaternion,
//! so that neither argument has to be of unit length. @ref tutorial-options "The option"
//! `kyosu::assume_unitary` skips the normalization on an argument already of unit length.
//!
//! # Composition
//!
//! The rotation \f$p\f$ followed by \f$q\f$ is the product \f$qp\f$, in that order, since the
//! product does not commute. A rotation composed backward is the usual effect of a product
//! written in the wrong order, or of one division taken for the other:
//!
//! @godbolt{doc/tut_rot_compose.cpp}
//!
//! # Interpolation
//!
//! `kyosu::slerp`, the [spherical linear interpolation](https://en.wikipedia.org/wiki/Slerp),
//! interpolates between two orientations along the shortest arc at constant angular speed, which
//! is the interpolation an animation or a trajectory requires. Since \f$q\f$ and \f$-q\f$ are
//! the [same rotation](https://en.wikipedia.org/wiki/3D_rotation_group#Connection_between_SO%283%29_and_SU%282%29),
//! the sign of the second operand is chosen so that the arc is the short one:
//!
//! @godbolt{doc/tut_rot_slerp.cpp}
//!
//! # Conversions
//!
//! A rotation converts to and from a rotation matrix, with kyosu::to_rotation_matrix and
//! kyosu::from_rotation_matrix, Euler angles with their axes, with kyosu::to_euler and
//! kyosu::from_euler, and an angle and an axis, with kyosu::to_angle_axis and
//! kyosu::from_angle_axis. The matrix is a `std::array` of three rows. The angle and the axis,
//! and the three Euler angles, are returned as a `kumi::tuple`, read by a
//! [structured binding](https://en.cppreference.com/w/cpp/language/structured_binding):
//!
//! @godbolt{doc/tut_rot_convert.cpp}
//!
//! The Euler angles are in radians. The three axes that follow them are listed in the order of
//! the three rotations, the first angle going with the first axis, and each is one of
//! `kyosu::X_`, `kyosu::Y_`, and `kyosu::Z_`, two consecutive axes being distinct. Each rotation
//! is about the axis as moved by the rotations before it, which is the
//! [intrinsic](https://en.wikipedia.org/wiki/Euler_angles#Definition_by_intrinsic_rotations) reading of the angles. The
//! option `kyosu::extrinsic` reads them about the
//! [fixed axes](https://en.wikipedia.org/wiki/Euler_angles#Definition_by_extrinsic_rotations) instead, and
//! `kyosu::radpi` takes them as multiples of \f$\pi\f$.
//!
//! A round trip through a matrix or a triple of angles may return \f$-q\f$ in place of \f$q\f$.
//!
//! <div class="section_buttons">
//!
//! | Previous | Next |
//! |:---------|-----:|
//! | [Octonions and higher algebras](@ref tutorial-beyond) | [Options](@ref tutorial-options) |
//!
//! </div>
