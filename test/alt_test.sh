#!/bin/bash

RED='\033[1;31m'
LIGHT_RED='\033[0;31m'
GREEN='\033[1;32m'
YELLOW='\033[0;33m'
NC='\033[0m'
BOLD='\033[1;0m'
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

error_stdout() {
	echo -e "${LIGHT_RED}STDOUT mismatch ${BAD}${NC}"
	# if command -v diff >/dev/null 2>&1; then
	# 	diff_output=$(diff --old-line-format='bash: %L' \
	# 					--new-line-format='mini: %L' \
	# 					--unchanged-line-format='' \
	# 					<(printf '%s\n' "$1") <(printf '%s\n' "$2"))
	# 	if [ -n "$diff_output" ]; then
	# 		echo "$diff_output"
	# 	fi
	# else
		echo "  bash posix stdout: $1"
		echo "  minishell  stdout: $2"
	# fi
}

error_stderr() {
	echo -e "${LIGHT_RED}STDERR mismatch ${BAD}${NC}"
	echo "  bash posix stderr: $1"
	echo "  minishell  stderr: $2"
}

error_exitcode() {
	echo -e "${LIGHT_RED}EXIT CODE mismatch ${BAD}${NC}: got $2 instead of $1"
}

pass() {
	echo -e "${GREEN} PASS ${GOOD}${NC}"
}

test_command() {

	cmd=$1

	echo -e "${YELLOW} - Testing: $1 ${NC}"

	bash_stderr_tmp=$(mktemp)
	mini_stderr_tmp=$(mktemp)

	expected_stdout=$(echo "$cmd" | bash --posix 2>"$bash_stderr_tmp")
	expected_code=$?
	expected_stderr=$(cat "$bash_stderr_tmp")

	actual_stdout=$(echo "$cmd" | "$MINISHELL" 2>"$mini_stderr_tmp")
	exit_code=$?
	actual_stderr=$(cat "$mini_stderr_tmp")

	rm -f "$bash_stderr_tmp" "$mini_stderr_tmp"

	#expected_stderr_clean=$(echo "$expected_stderr" | sed 's/^bash: line [0-9]*: //')

	local failed=0

	if [ "$expected_code" -ne "$exit_code" ]; then
		failed=1
	fi
	if [ "$expected_stdout" != "$actual_stdout" ]; then
		failed=1
	fi
	if [ "$expected_stderr_clean" != "$actual_stderr" ]; then
		failed=1
	fi

	if [ "$failed" -eq 1 ]; then
		echo -e "${RED} Wrong ${BAD}${NC}"

		if [ "$expected_code" -ne "$exit_code" ]; then
			error_exitcode "$expected_code" "$exit_code"
		fi
		if [ "$expected_stdout" != "$actual_stdout" ]; then
			error_stdout "$expected_stdout" "$actual_stdout"
		fi
		if [ "$expected_stderr_clean" != "$actual_stderr" ]; then
			error_stderr "$expected_stderr_clean" "$actual_stderr"
		fi
		return 0
	else
		pass "$cmd"
		return 1
	fi
}

while IFS= read -r line; do
	if [[ -z "$line" ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*# ]]; then
		continue
	fi
	if [[ "$line" =~ ^[[:space:]]*===== ]]; then
		echo -e "${BOLD} $line ${NC}"
		continue
	fi
	test_command "$line"
done < "$TEST_FILE"
