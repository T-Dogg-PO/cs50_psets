from cs50 import SQL
from sys import argv, exit

# First check to see that one command line arguments were provided. If not, exit
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

# Access the database through db
db = SQL("sqlite:///students.db")

# Convert argv to a string we can use
house_input = argv[1]

# Execute our query on the database
rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", (argv[1],));

# Iterate over our rows to print out our data in the format we want
for row in rows:
    if (row["middle"] == None):
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")