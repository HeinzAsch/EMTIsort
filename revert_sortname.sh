#!/bin/sh
echo "Replacing all instances of 'EMTIsort' with 'GRIFFsort' in 'current' and its subdirectories."
cd current
grep -rl EMTIsort . | xargs sed -i 's/EMTIsort/GRIFFsort/g'
