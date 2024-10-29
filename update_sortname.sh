#!/bin/sh
echo "Replacing all instances of 'GRIFFsort' with 'EMTIsort' in 'current' and its subdirectories."
cd current
grep -rl GRIFFsort . | xargs sed -i 's/GRIFFsort/EMTIsort/g'
