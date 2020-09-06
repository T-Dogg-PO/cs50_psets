import csv
from sys import argv, exit
import copy

# Using the sys library and argv module, we can start running our program with command-line arguments

# Check to make sure that 2 arguments were provided (the csv file and the txt file)
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Open the csv file containing the names of our subjects and their corresponding DNA sequences
# Store values in a dictionary / hash table called csv_file
csv_file = csv.DictReader(open(argv[1]))

# Open the txt file containing the unknown persons DNA sequences
# Store text in txt_file
f = open(argv[2])
txt_file = f.read()

# Compute the STR counts from txt_file
# First create a list which we will store the keys (and tell us how many we need to track)
dna_list = copy.deepcopy(csv_file.fieldnames)
# Remove the first entry (the names field)
dna_list.pop(0)

# Create a list for counting the number of times each DNA sequence appears
dna_counter = []

# Begin loop for checking txt_file for the entries in dna_list
# Loop through whole thing according to the number of entries we are looking for in dna_list
for i in range(len(dna_list)):
    # Each time we begin the loop, add an entry to the dna_counter list for tracking results
    dna_counter.append(0)
    # For each entry in dna_list, loop through the entire txt_file
    for j in range(len(txt_file)):
        # Create variable x for use in searching, equal to the string length of the current
        # entry in the dna_list plus where we are in the txt_file loop
        x = len(dna_list[i]) + j
        # Check if the substring j-x matches the entry in dna_list
        if (txt_file[j:x] == dna_list[i]):
            # Initalize temporary variables for tracking once we have found a match
            high = 0
            counter = 0
            # Search through remainder of txt_file, in increments of the length of the entry
            # we are searching for
            if (j < (len(txt_file))):
                y = 0
            else:
                y = (len(txt_file) - j)
            for k in range(y,(len(txt_file)),(len(dna_list[i]))):
                # If a match is found, add one to the high counter, and increment our other
                # counter by the length of the entry we are searching for. This will be used
                # to keep checking the txt_file by the correct increments
                if (txt_file[(j+counter):(x+counter)] == dna_list[i]):
                    high += 1
                    counter += len(dna_list[i])
                # When no sequential matches are found, break this part of the loop
                else:
                    break
            # If a new high is found, replace that in our tracking list
            if (high > dna_counter[i]):
                dna_counter[i] = high

# Check for a match between dna_counter and the entries of people in the csv
# Loop through each of the rows of csv_file
#print(f"{dna_counter}")
for rows in csv_file:
    values = list(rows.values())
    for columns in range(len(dna_counter)):
        if ((int(values[columns + 1])) != (int(dna_counter[columns]))):
            break
        elif (columns == (len(dna_counter) - 1)):
            print(f"{values[0]}")
            exit(0)
print("No match")
exit(1)