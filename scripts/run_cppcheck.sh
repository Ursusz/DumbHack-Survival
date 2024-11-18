#!/usr/bin/bash

cppcheck --enable=all \
    --inline-suppr \
    --project="${BUILD_DIR:-cmake-build-debug}"/compile_commands.json \
    -i"${BUILD_DIR:-cmake-build-debug}" --suppress="*:${BUILD_DIR:-cmake-build-debug}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    -i"${GEN_DIR:-generated}" --suppress="*:${GEN_DIR:-generated}/*" \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=useStlAlgorithm \
    --check-level=exhaustive \
    --error-exitcode=1
