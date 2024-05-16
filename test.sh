#!/bin/bash 
 
if [ $# -ne 2 ]; then 
  echo "Usage: $0 <my_nm_binary> <path_to_test>" 
  exit 1 
fi 
 
COLOR_RED='\033[0;31m' 
COLOR_RESET='\033[0m'
COLOR_GREEN='\033[0;32m' 
MY_NM_BINARY=$1 
TEST_PATH=$2 
PASS=0 
 
# Iterate over all executable files in the specified path 
find "$TEST_PATH" -type d -name .git -prune -o -type f -print0| while read -d $'\0' file
do
  # Run nm on the file using your custom nm binary 
  echo "Testing $file..."
  output_my_nm=$( "$MY_NM_BINARY" "$file" 2>/dev/null) 
 
  # Run nm on the file using the system nm 
  output_system_nm=$( nm "$file" 2>/dev/null) 
 
  # Compare the outputs 
  if [ "$output_my_nm" != "$output_system_nm" ]; then 
    echo -e "${COLOR_RED}Test failed${COLOR_RESET}" 
    PASS=1
  else 
    echo -e "${COLOR_GREEN}Test passed${COLOR_RESET}" 
  fi 
done 
 
if [ $PASS -ne 0 ]; then 
  echo "Some tests failed!" 
  exit 1 
fi 
echo "All tests passed!" 

