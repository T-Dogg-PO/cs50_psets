from sys import argv
import copy

def main():
    array_diff([1,2], [1])

def array_diff(a, b):
    return [x for x in a if x not in b]

main()