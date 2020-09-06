from cs50 import get_int
from sys import exit

# Ask the user for their credit card number
number = get_int("Number: ")

# Validate that the given number is either 13, 15 or 16 digits long
cc_length = 0
validation_number = number

while (validation_number > 0):
    cc_length += 1
    validation_number = validation_number // 10     # Use floor division here to reduce the decimal places each loop

# If the given number is not 13, 15 or 16 digits long, print error message
if (cc_length != 13) and (cc_length != 15) and (cc_length != 16):
    print("INVALID")
    exit(1)

# Create numbers for the first step of the checksum formula
dividing_number = 100
dividing_number_2 = 10

checksum_1 = 0
checksum_2 = 0

# Perform first loop of checksum
for i in range(cc_length // 2):
    checksum_1 = ((number % dividing_number) // dividing_number_2) * 2
    checksum_2 = checksum_2 + (checksum_1 // 10) + (checksum_1 % 10)
    dividing_number *= 100
    dividing_number_2 *= 100

# Reset variables for second step of checksum
dividing_number = 10
dividing_number_2 = 1

checksum_3 = 0

# Perform second loop of checksum
for i in range(0, cc_length, 2):
    checksum_3 = checksum_3 + ((number % dividing_number) // dividing_number_2)
    dividing_number *= 100
    dividing_number_2 *= 100

# First validation of results
if (((checksum_2 + checksum_3) % 10) != 0):
    print("INVALID")
    exit(1)

# Set variable for final validation
final_validation = 0

# Perform checks for each credit card
# Credit card length of 15 / check for AMEX
if (cc_length == 15):
    final_validation = number // 10000000000000
    if (final_validation == 34) or (final_validation == 37):
        print("AMEX")
        exit(0)
    else:
        print("INVALID")
        exit(1)

# Credit card length of 13 / check for VISA
elif (cc_length == 13):
    final_validation = number // 1000000000000
    if (final_validation == 4):
        print("VISA")
        exit(0)
    else:
        print("INVALID")
        exit(1)

# Credit card length of 16 / check for Mastercard and VISA / final condition
else:
    final_validation = number // 100000000000000
    if (final_validation >= 51) and (final_validation <= 55):
        print("MASTERCARD")
        exit(0)
    else:
        final_validation = number // 1000000000000000
        if (final_validation == 4):
            print("VISA")
            exit(0)
        else:
            print("INVALID")
            exit(1)
