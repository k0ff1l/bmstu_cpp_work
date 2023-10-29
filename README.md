# cmake-example-repo

| **CI Service** | Build Status |
|:---------------|-------------:|
| GitHub Actions | [![Build Status (GitHub Actions)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cmake-tests.yml/badge.svg)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cmake-tests.yml) |

## Сборка

После того как склонировали, собирите:
bash
```
cmake -S . -B mybuild
cd mybuild
cmake --build .
```

Запустить тесты:
```
ctest
```
