# ようこそ、ドー幾何学のC++ライブラリ

## ライセンス License

Throughout the whole project, we'll be licensing under GPL v3, a strong-copyleft license.

## Installation

First download the tarball of branch [`gnu-prod-env`](https://github.com/dou-geometry/cpp-lib/tree/gnu-prod-env) at [https://www.github.com/dou-geometry/cpp-lib/tarball/rk4-dev](https://www.github.com/dou-geometry/cpp-lib/tarball/rk4-dev), then run the command `./configure && make`.

Or you could download any branch's tarball by `https://www.github.com/dou-geometry/cpp-lib/tarball/<branch>` then run `./setupAutotools.sh` follow by `./configure && make`. But notice not all branch's state is guarantee to be run-able.

## プログラム Programs

- `bin/JROFI`
- `bin/CMF`

# ブランチ Branch

- [`main`](https://github.com/dou-geometry/cpp-lib/tree/main)：gnu++20 code, using quadruple-precision floating-point format
- [`C++17`](https://github.com/dou-geometry/cpp-lib/tree/C++17)：stdc++17 compatible code
- [`CUDA`](https://github.com/dou-geometry/cpp-lib/tree/CUDA)：Cuda compatible code
- [`GMP`](https://github.com/dou-geometry/cpp-lib/tree/GMP)：Library base on GMP

---

- [`gnu-prod-env`](https://github.com/dou-geometry/cpp-lib/tree/gnu-prod-env): Installation Ready Branch

# Overview

This project is mainly to maintain a general-physics-oriented C++ library. Following is a list of our goals:

- [x] Coordination/Vectors Carrier
- [x] Linear Algebra
- [x] Plotting (though SageMath)
- [x] Dynamic Systems
  - [x] RK4
- [ ] Numerical Integration
- [ ] boxCounting

# Development Team

- [`math-dev`](https://github.com/dou-geometry/cpp-lib/tree/math-dev) (Active)
- [`rk4-dev`](https://github.com/dou-geometry/cpp-lib/tree/rk4-dev) (Finished, Dissolved)
- [`phys-dev`](https://github.com/dou-geometry/cpp-lib/tree/phys-dev) (Active)

Please initialize group via a new branch, or (if wanted to resume a dev-team) by creating pull request from [`main`](https://github.com/dou-geometry/cpp-lib/tree/main) to corresponding branch.
