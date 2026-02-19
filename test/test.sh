#!/bin/bash

LIGHT_RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m'
GOOD="✓"
BAD="✗"
USAGE="Usage: ./test.sh <path_to_executable minishell> [test_file]"

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
	echo "$USAGE"
	exit 1
fi

TEST_FILE="${2:-test_cmd}"

if [ ! -f "$TEST_FILE" ]; then
	echo "Error: Test file '$TEST_FILE' not found."
	exit 1
fi

MINISHELL=$1

error() {
	echo -e "${LIGHT_RED}Wrong ${BAD}${NC}: $5"
	if [ "$2" != "$4" ]; then
		echo "got $4 instead of $2"
	fi
	echo "mini: $3"
	echo "bash: $1"
}

pass() {
	echo -e "${GREEN} PASS ${GOOD}${NC} $1"
}

test_command() {
	cmd=$1
	expected=$(echo "$cmd" | bash --posix)
	expected_code=$?
	output=$(echo "$cmd" | "$MINISHELL")
	exit_code=$?
	if [ $expected_code -ne $exit_code ]; then
		error "$expected" "$expected_code" "$output" "$exit_code" "$cmd"
		return 0
	elif [[ "$expected" != "$output" ]]; then
		error "$expected" "$expected_code" "$output" "$exit_code" "$cmd"
		return 0
	else
		pass "$cmd"
	fi
	return 1
}

while IFS= read -r line; do
	if [[ -z "$line" ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*# ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*===== ]]; then
		echo "$line"
		continue
	fi
	test_command "$line"
done < "$TEST_FILE"
