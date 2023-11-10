#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

declare -r FILTER=-build/c++23,-runtime/references,\
-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order,-build/include_subdir

grep -E -r --include=\*.{cpp,h,hpp} -L 'cmake-build-debug' ./let_* ./hw_* | xargs python3 -m cpplint --linelength=120 --filter=${FILTER} --output=vs7

popd
