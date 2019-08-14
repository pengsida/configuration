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

