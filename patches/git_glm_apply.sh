#!/bin/bash

pushd `dirname "${0}"`
BASEDIR=$(pwd)
popd > /dev/null

BUILD_DIRS=($(find "${BASEDIR}/.." -maxdepth 1 -name '*build*' -type d))
printf 'BUILD_DIRS = %s\n' "${BUILD_DIRS[@]}"

glm_patch() {
  pushd "${1}/glm-src"
  git apply --ignore-space-change --ignore-whitespace "${BASEDIR}/glm_linux_fix.patch"
  git apply --ignore-space-change --ignore-whitespace "${BASEDIR}/glm_fix.patch"
  git apply --ignore-space-change --ignore-whitespace "${BASEDIR}/glm_template_fixes.patch"
  popd
}

for dir in "${BUILD_DIRS[@]}";
do
  echo "Running patch in ${dir}."
  glm_patch "${dir}"
done
