#!/usr/bin/env bash
file="key.txt"

while IFS= read -r line || [[ -n "$line" ]]; do
  zowe tso send as "$line" --data "ex $1"
done < "$file"