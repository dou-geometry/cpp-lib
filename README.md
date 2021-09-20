# ようこそ、ドー幾何学のC++ライブラリ

## ライセンス

Throughout the whole project, we'll be licensing under GPL v3, a strong-copyleft license.

## コンパイルフラグ

- `-DSANITYCHECK`: Enable additional sanity check within the code that's normally useless (if...you know, you use the library correctly)
- `-DHOLD`: Hold before exit, usually to fudge with data that'll be clean up after program termination

## ブランチ

- [main](./main)：gnu++20 code, using quadruple-precision floating-point format
  - [phys-dev](./phys-dev)
  - [math-dev](./math-dev)
- [C++17](./C++17)：stdc++17 compatible code
- [CUDA](./CUDA)：Cuda compatible code
- [GMP](./GMP)：Library base on GMP
