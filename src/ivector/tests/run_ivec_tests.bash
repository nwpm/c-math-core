#!/bin/bash

cd ./../../../build/bin || exit

for test_file in ./*_ivec?; do
  echo "Running $test_file..."
  $test_file --verbose || echo "Tests $test_file FAILED"
done

echo
echo "All tests passed"
