
# myls.py
# Import the argparse library
import argparse
import os
import sys
import re
import pyperclip

#pattern = re.compile(r'(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})') # IP number

def extractdata(filename):
    # opening and reading the file
    with open(filename) as fh:
        string = fh.readlines()

    # decalring the regex pattern for IP addresses
    pattern =re.compile('''((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.)
    {3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)''')

    # initializing the list objects
    valid =[]
    invalid=[]

    # extracting the IP addresses
    for line in string:
        line = line.rstrip()
        result = re.search(line)

        # valid IP addresses
        if result:
          valid.append(line)

        # invalid IP addresses
        else:
          invalid.append(line)

    # displaying the IP addresses
    print("Valid IPs")
    print(valid)
    print("Invalid IPs")
    print(invalid)


def readfile(filename):
    addstate = "add"
    delstate = "del"

    with open(filename, "r") as f:
        lines = f.readlines()
        for line in lines:
            #print (line)
            for word in line.split():
                if word == addstate:
                    print((line.split(' ')[1])) # position/word 2 phrase
                    print((line.split(' ')[2])) # position 3 in the phrase
            #    if word == delstate:
            #        print(word+1)



def main():
    # Create the parser
    my_parser = argparse.ArgumentParser(description='List the content of a folder')
    # Add the arguments
    my_parser.add_argument('FILE',
                           metavar='FILE to virtual topology',
                           type=str,
                           help='the FILE to list')
    # Execute the parse_args() method
    args = my_parser.parse_args()

    #input_path = args.Path
    input_file = args.FILE

    extractdata(input_file)
    while True:
        filename = input('Insira os comandos add <ip> <weight> || del <ip> :')
        extractdata(filename)

#    if not os.FILE.isdir(input_file):
#        print('The file specified does not exist')
#        sys.exit()

#    print('\n'.join(os.listdir(input_path)))

if __name__ == "__main__":
    main() # FILE
