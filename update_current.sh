#!/bin/sh
DIR="$(ls | tail -1)"
rm current
echo "Old symbol named 'current' removed."
ln -s ${DIR} current
echo "New symbol created:"
CHECK="$(ls -lh | grep -w "current")"
echo "${CHECK}"
