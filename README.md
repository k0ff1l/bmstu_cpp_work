# cmake-example-repo

| **CI Service** | Build Status |           Codestyle Check            |
|:---------------|--------------|------------:|
| GitHub Actions | [![Build Status (GitHub Actions)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cmake-tests.yml/badge.svg)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cmake-tests.yml) |[![Build Status (GitHub Actions)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cpp-style-check.yml/badge.svg)](https://github.com/k0ff1l/bmstu_cpp_work/actions/workflows/ci-cpp-style-check.yml)|

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
