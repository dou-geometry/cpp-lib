# Dou-geometry's Field-oriented RK4

## Overview
The `rk4.*` series under this directory are specifically designed to work for Dou-geometry's Existence-Field dynamics. By implying the [prerequisites](#Prerequisites) below, we could enable some extensive usage, such as [possible to feed only coordinates as argument](#InputTypes)

### Prerequisites
1. Initial Conditions:
   - Position (optional)
   - Velocity (**requires**)
2. Acceleration is determined by the field function and object's current velocity

## Arguments

- `d::dyn::mono` or `d::coord`

## Function Declaration
