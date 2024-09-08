#!/bin/bash

# if num of args less than 5;
if [ "$#" -lt 5 ]; then
    echo "Usage: $0 <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <num_times_to_eat>"
    exit 1
fi

# Define the program and its arguments
PROGRAM="./philo"
NUM_PHILOSOPHERS="$1"
TIME_TO_DIE="$2"
TIME_TO_EAT="$3"
TIME_TO_SLEEP="$4"
NUM_TIMES_TO_EAT="$5"

# Run the program and capture its output
OUTPUT=$($PROGRAM "$NUM_PHILOSOPHERS" "$TIME_TO_DIE" "$TIME_TO_EAT" "$TIME_TO_SLEEP" "$NUM_TIMES_TO_EAT")

# Print the raw output (for debugging purposes)
echo "Raw output:"
echo "$OUTPUT"
echo

# Initialize an array to hold the counts
EAT_COUNT=()

# Initialize count for each philosopher
for (( i=1; i<=NUM_PHILOSOPHERS; i++ )); do
    EAT_COUNT[$i]=0
done

# Process the output to count the number of times each philosopher has eaten
# IFS = internal field separator
while IFS= read -r line; do
    # Extract the philosopher ID from each line
    PHILOSOPHER_ID=$(echo "$line" | awk '{print $2}')
    
    # Check if the line indicates the philosopher is eating
    if echo "$line" | grep -q "is eating"; then
        EAT_COUNT[$PHILOSOPHER_ID]=$((EAT_COUNT[$PHILOSOPHER_ID] + 1))
    fi
done <<< "$OUTPUT"

# Print the number of times each philosopher has eaten
echo "Number of times each philosopher has eaten:"
for (( i=1; i<=NUM_PHILOSOPHERS; i++ )); do
    echo "Philosopher $i: ${EAT_COUNT[$i]} times"
done
