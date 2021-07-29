This branch `main` is aimed for developing a library specific for GNU++20.

# Types

- `d::<namespace>::<class>`, (normalerweise) a VLA version of class
- `d::<namespace>::compact::<class>`, a standard (non-VLA, non linked list) version of class
- `d::<namespace>::linked::<class>`, a linked-list version of class
- `d::<namespace>::linked::compact::<class>`, for a 2-level class, this means the highest-level carrier is using `d::Karabinerhaken` meanwhile the lower-levels are using `::compact` classes.

# Table of Contents

- [Classes](./cls)
  - [Structure](./cls/structure)
    - [Karabinerhaken](./cls/structure/Karabinerhaken)
  - [Carrier](./cls/carrier)
    - [Linear Algebra](./cls/carrier/linear)
      - [coord](./cls/carrier/linear/coord)
- [Concepts](./concepts)
- [Dynamics](./dyn)
- [Numerical](./numerical)
- [Manipulation](./manip)
- [Connection](./conn)
- [Dou](./dou)
- [Analysis](./analysis)
