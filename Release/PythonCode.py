import re
import string
import os
from collections import Counter


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def CreateList():
    #open list 
    fileName = "U:/Project3/Release/list.txt"
    my_file = open(fileName, "r+")
    content = my_file.read()
   
    #split txt file into array 
    all_items = content.split('\n')
    
    #count frequency of each list item
    itemCount = Counter(all_items)
    my_file.close()

    return itemCount;

#Function reads imported list of items sold, counts and prints the frequecy of each item
#and writes the data to a .dat file
def PrintAllItemCounts():
    #open list 
    fileName = "U:/Project3/Release/list.txt"
    my_file = open(fileName, "r+")
    content = my_file.read()
   
    #split txt file into array 
    all_items = content.split('\n')
    
    #count frequency of each list item
    itemCount = Counter(all_items)

    file2 = "U:/Project3/Release/frequency.dat"
    
    #create/open .dat file
    f = open(file2, 'w+')

    #iterate through count, if not blank store data to file, print data 
    for x, y in itemCount.items():
        if (x.strip() != ""):
            print(x.ljust(12), y)
            f.write(str(x) + " " +str(y)+ "\n")
    
    #close files
    f.close()
    my_file.close()

#Funtion to count the frequency of a single item in the list

def PrintSingleItemCount(item):
    purchased = False;
    #open list 
    fileName = "U:/Project3/Release/list.txt"
    my_file = open(fileName, "r+")
    content = my_file.read()
   
    #split txt file into array 
    all_items = content.split('\n')
    
    #count frequency of each list item
    itemCount = Counter(all_items)
    
    for x, y in itemCount.items():
        if x == item:
            print("---------------------")
            print(x, ' ', y)
            print("---------------------")
            purchased = True;

    my_file.close()

    if (purchased == False):
        print("That item was not purchased.")

    return 0;

#program to search for items of a given frequency or greater
def PrintItemsOfXorGreaterFrequency(item):
    purchased = False;
    #open list 
    fileName = "U:/Project3/Release/list.txt"
    my_file = open(fileName, "r+")
    content = my_file.read()
   
    #split txt file into array 
    all_items = content.split('\n')
    
    #count frequency of each list item
    itemCount = Counter(all_items)
    
    for x, y in itemCount.items():
        if y >= item:
            print("---------------------")
            print(x, ' ', y)
            print("---------------------")
            purchased = True;

    my_file.close()

    if (purchased == False):
        print("No items of that frequency were purchased.")

    return 0;
