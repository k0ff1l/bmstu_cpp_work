#!/usr/bin/env bash

pushd $(git rev-parse --show-toplevel)

set -e

declare -r FILTER=-build/include_subdir,-legal/copyright

grep -E -r --include=\*.{cpp,h,hpp} -L 'cmake-build-debug' ./let_* ./hw_* ./sand* | xargs python3 -m cpplint --linelength=120 --filter=$FILTER --output=vs7 | grep -v "Done processing"

popd
