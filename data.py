import re
import string
import os.path
from os import path

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# To call this function, pass this function into the CallIntFunc function along with the desired search term.

    # Returns the number of occurrances of the desired search term.

    # int wordCount

def CountInstances(searchTerm):

    searchTerm = searchTerm.lower()

    # This should open the file in read mode

    text = open("CS210_Project_Three_Input_File.txt", "r")
    wordCount = 0

    # This should check each line of the input file

    for line in text:

        line = line.strip()
        word = line.lower()

        if word == searchTerm:

        # This should increment number of times the word appears

            wordCount += 1

    return wordCount

    text.close()

# To call this function, pass the function name into the CallProcedure function.
# Returns a list of all unique items in CS210, and prints all of their occurrances.

def CountAll():

    # This should open the file in read mode

    text = open("CS210_Project_Three_Input_File.txt", "r")
    dictionary = dict()

    #This should check each line of the input file, remove any errant spaces and newline characters and convert characters to lowercase for better matching

    for line in text:

        line = line.strip()
        word = line.lower()

    #This should check if the word is already in the dictionary

        if word in dictionary:

    #This should increment number of times the word appears

            dictionary[word] = dictionary[word] + 1

        else:

            dictionary[word] = 1

    #This should print all contents of the dictionary

    for key in list (dictionary.keys()):

        print(key.capitalize(), ":", dictionary[key])

    text.close()

    # This should count the number of appearances for each item, then write to frequency.dat

    # To call this function, pass this function into the CallProcedure function.

    # Returns a a document (frequency.dat) with each unique word and the number of times that word occurs..

def CollectData():

    # This should open the input file in read mode

    text = open("CS210_Project_Three_Input_File.txt", "r")

    frequency = open("frequency.dat", "w")

    dictionary = dict()

    # This should check each line of the input file

    for line in text:

        line = line.strip()
        word = line.lower()

    #This should check if the word is already in the dictionary

    if word in dictionary:

        dictionary[word] = dictionary[word] + 1

    else:

        dictionary[word] = 1

    # This should write each key and value pair to frequency.dat

    for key in list (dictionary.keys()):

    #This should format the key-value pair as strings followed by a newline.

        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    text.close()

    frequency.close()

    
