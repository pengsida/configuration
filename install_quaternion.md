# https://www.essentialmath.com/GDC2013/GDC13_quaternions_final.pdf

## Application

1. Used to rotate vectors.
2. Excellent for interpolation.

## Euler's rotation theorem

1. Axis and angle represents any 3D rotation.
2. Axis: a line of points that don't change.
3. Angle: the amount of rotation.
4. Alternative expression: vector along axis plus angle.
5. Given a 3D rotation matrix, the eigenvector corresponding to the eigenvalue 1 is the axis of rotation.

## Division algebra

1. All numbers other than zero have a multiplicative inverse.
2. For any rotation, we want to be able to undo it.
3. So rotation must not be a division algebra.

## Quaternion rotation

1. (w, x, y, z)
2. w = cost(theta / 2)
3. (x, y, z) = sin(theta / 2) * axis
4. (w, x, y, z) are all scalar values, which are linear, while (axis, theta) are all radian, which are non-linear (periodic).
5. (x, y, z) indicates a signed axis, and w indicates the length of the axis.


