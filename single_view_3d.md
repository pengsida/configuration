# https://www2.eecs.berkeley.edu/Pubs/TechRpts/2018/EECS-2018-93.html

## Introduction

Motivation

1. We humans have remarkable ability to perceive 3d from 2d: determine the relative depth of objects; image the 3d shape of objects.
2. It is ill-posed to infer the underlying 3d structure from a single input image: there are infinite possible 3d geometries that can explain a given 2d image.
3. However, the 3d geometries are not equally likely: we humans infer the most likely 3d by relying on the regularities in the world.

Problems

1. The forms of priors leveraged: hand-designed priors; learning from data.
2. Various 3d representations: volumetric representation; compositional structure (we humans reason about the world as being composed of separate objects).
3. Two main tasks: learnt to predict 3d without requiring direct 3d supervision; predict compositional 3d representations.

Actions

1. Allow geometry to act as a bridge between the inferred 3d representations and the available 2d supervision: we known concise geometric equations and thus can enforce our inferences are geometrically consistent with the available 2d training data.
2. Represent complex objects and scenes in terms of the underlying simpler entities.

## Compositional structures for complex scenes

Motivation

There exists hierarchical levels of perception for the world

1. Scene level: indoor scenes have roughly perpendicular walls.
2. Object level: chairs have similar shapes.
3. Local object relationships: chairs are close to tables; monitors are on top of tables.

Problems

1. What is the right representation for object level 3d prediction?
2. How do we represent object-object relationships?
3. How do we predict them from pixels?
4. How to incorporate object-object relationships with object-level module?

Possible solutions

1. Representation for objects: 9DoF pose (scale, translation, rotation) and normalized shape in a canonical frame.
2. Object-object relationships: relative translation, relative scale and relative 2d direction.
3. Incorporating object-object relationships with object-level module: geometric constraints (a linear system of object poses and relative poses)

