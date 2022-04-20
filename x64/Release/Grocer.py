# Carter Wooton CS 210 April 17, 2022
import re
import string

# Option 1
def items_list():
    print()
    print('List of items purchased with quantities')
    with open('Daily Grocery Log.txt', 'r') as f:        # Reads given daily log
        grocery_items = f.readlines()
    no_dupes = list(dict.fromkeys(grocery_items))        # Creates a list with no duplicates
    for item in no_dupes:
        print(item.strip(), end=' ')
        print(grocery_items.count(item))
    
    print()

# Option 2
def item_frequency(item):
    item_frequency = 0
    with open('Daily Grocery Log.txt', 'r') as f:
        grocery_items = f.readlines()
    for i in grocery_items:
        if i.strip() == item.capitalize().strip():
            item_frequency += 1
    return item_frequency

# Option 3
def item_graphic():
    # Reads given daily log
    with open('Daily Grocery Log.txt', 'r') as f:        # Reads given daily log
        grocery_items = f.readlines()
    no_dupes = list(dict.fromkeys(grocery_items))
    with open('frequency.dat', 'w') as fdat:             # Writes a new file to be used by C++
        for item in no_dupes:
            fdat.write(str(item.strip()))
            fdat.write(' ')
            fdat.write(str(grocery_items.count(item)))
            fdat.write('\n')
            
    
