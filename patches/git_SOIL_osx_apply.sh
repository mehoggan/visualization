#!/bin/bash

pushd `dirname "${0}"`
BASEDIR=$(pwd)
popd > /dev/null

BUILD_DIRS=($(find "${BASEDIR}/.." -maxdepth 1 -name '*build*' -type d))
printf 'BUILD_DIRS = %s\n' "${BUILD_DIRS[@]}"

SOIL_osx_patch() {
  pushd "${1}/SOIL-src"
  git apply --ignore-space-change --ignore-whitespace "${BASEDIR}/SOIL_osx_fix.patch"
  popd
}

for dir in "${BUILD_DIRS[@]}";
do
  echo "Running patch in ${dir}."
  SOIL_osx_patch "${dir}"
done
