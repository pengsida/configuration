# Convex hull

## Definition

Input: a set of points.
Output: the polygon that passes through some points encloses all the points and has the convexity.

## Algorithms

### Brute force

1. Given a set of points, we connect two of them every time and check if the remaining points locate at the same side of this line.
2. The method to check if p3 (x3, y3) is at the right side or left of p1p2. Simply use the formula: x1y2 + x3y1 + x2y3 - x3y2 - x2y1 - x1y3. If the formula is positive, p3 is at the left side of p1p2, otherwise the right side.

### Divide and conquer

1. The point with the smallest abscissa and the point with the biggest abscissa are points of the convex hull.
2. Then we connect these two points and find the points farthest away from this line at each side. The distance of a point to a line is given by the same formula: |x1y2 + x3y1 + x2y3 - x3y2 - x2y1 - x1y3|.

### Jarvis's algorithm

1. The point with the smallest ordinate is a point of the convex hull, and we set it as the first point.
2. In the clockwise or counter-clockwise orientation, we find a point that form the smallest angle with previous line. For the second point, its previous line is the horizontal line passing through the first point.

