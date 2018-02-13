#!/bin/bash

pushd `dirname "${0}"`
BASEDIR=$(pwd)
popd > /dev/null

BUILD_DIRS=($(find "${BASEDIR}/.." -maxdepth 1 -name '*build*' -type d))
printf 'BUILD_DIRS = %s\n' "${BUILD_DIRS[@]}"

s2_geometry_patch() {
  pushd "${1}/s2-geometry-src"
  git apply --ignore-space-change --ignore-whitespace "${BASEDIR}/s2_geometry.patch"
  popd
}

for dir in "${BUILD_DIRS[@]}";
do
  echo "Running patch in ${dir}."
  s2_geometry_patch "${dir}"
done
