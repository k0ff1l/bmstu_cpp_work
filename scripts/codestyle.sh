#!/usr/bin/env bash

pushd "$(git rev-parse --show-toplevel)"

set -e

declare -r FILTER="-build/include_subdir,-legal/copyright,-build/include_what_you_use"
declare -r FLAGS="--output=vs7"

find . -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) -print0 |
  xargs -0 cpplint $FLAGS --linelength=120 --filter=$FILTER --exclude=./cmake-build-debug/

popd
