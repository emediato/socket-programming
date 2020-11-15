from util import *
from GVL import *

# importing the module
import re
from collections import defaultdict
# initializing the list object



def main():
    lst=[]
    i=0

    # opening and reading the file
    with open('2.txt') as fh:
      lines = fh.readlines()

      #howmanywords = len (line.split())
      statetype = "type"
      statedestination = "destination"
      statehops = "hops"
      statesource = "source"
      statepayload = "payload"

      punc = '''[]{};:'"\,'''

      pattern =re.compile('''((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.)
        {3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)''')

      for line in lines:
          lst.append(line)
          i=0
         # line=line.translate(r' "",: ')
          for ele in line:
              if ele in punc:
                  line = line.replace(ele, "")

          for word in line.split():
              auxword = (line.split(' ')[i])

              if statetype in auxword:
                  x=line.split(' ')[i+1]
                  x = x.rstrip()
                  if ("data" in x):
                      print(line)
                      simuladata(line)
                #arraylocaltype.append(x)

              if statesource in auxword:
                  x=line.split(' ')[i+1]
                  x = x.rstrip()
                  if validate_ip(x):
                      arraylocalsource.append(x)

              if statedestination in auxword:
                  x=line.split(' ')[i+1]
                  x = x.rstrip()
                  if validate_ip(x):
                      arraylocaldestination.append(x)

              if statehops in auxword:
                  x=line.split(' ')[i+1]
                  x = x.rstrip()
                  if validate_ip(x):
                      arraylocalhops.append(x)

              i=i+1


    print(arraylocalsource)

          #for key in line: print(key, ':', line[key])
          #Output = list(filter(lambda x:trace in x, lst))
          #print(line)
          #print("!")
    # decalring the regex pattern for IP addresses
    #pattern =re.compile('''((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.)
    #{3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)''')


if __name__ == "__main__":
    main() # FILE

# extracting the IP addresses
#for line in fstring:
   #lst.append(pattern.search(line)[0])
# displaying the extracted IP adresses
#print(lst)
#print(lst)
#for statesource in lst:
#    print(lst[statesource])
