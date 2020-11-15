import json
import re,os
import pickle
import fileinput

key0 ='type'
key1= 'source'
key2= 'destination'
key3 ='hops'
key4='payload'

filename = '2.txt'
punc = '''[]{};:'"\,'''

with open('2.txt') as fh:
  filedata = fh.read()
  lines = fh.readlines()

 for line in lines:
     print (line)

     for ele in line:
         if ele in punc:
             line = line.replace(ele, "")

     for word in line.split():
         print (word)
         if key2 in word:
             x=line.split() #LIST OF WORDS
             next = x[x.index(key2) + 1] #NEXT WORD
             filedata = filedata.replace(next, '9.9.9.9')


with open('file.txt', 'w') as file:
  file.write(filedata)
