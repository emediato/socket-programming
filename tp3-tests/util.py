from GVL import *
import ipaddress
import threading
import random, time
import numpy as np
from threading import Condition, Lock
from simple_pid import PID
from threading import Thread
import os
import math
import struct
import re
from collections import namedtuple
import json
#from serverUDP import socketmain

def select_option_local(sentence):
    i=0
    for word in sentence.split():
        auxword = (sentence.split(' ')[i])
        x=sentence.split() #LIST OF WORDS
        if "add" in auxword:
            x = x[x.index("add") + 1] + ' '+ x[x.index("add") + 2]  #NEXT WORD
            add_local(x)

        if "del" in auxword:
            x = x[x.index("del") + 1]
            del_local(x)

        if "trace" in auxword:
            x = x[x.index("del") + 1]
            trace_data(x)
            #del_local((sentence.split(' ')[i+1]))
        i+1

def add_local(ipandweightreceived):
    global net
    auxnet = net + '.txt'

    with open('127.1.1.2.txt', 'a') as file :
        filedata = file.write("\n")
        filedata = file.write( ipandweightreceived )
        file.close()

def add_dictionary(file, ipreceived):
    path = os.getcwd()
    text_files = [f for f in os.listdir(path) if f.endswith('.txt')]
#['euc-cn.txt', 'euc-jp.txt', 'euc-kr.txt', 'euc-tw.txt', ... 'windows-950.txt']
    for file in text_files:
        auxbool = (compare_data_file (file, ipreceived))
        if auxbool == True:
            print("Ip already exist localy.")
        else:
            update_data_destination(file, ipreceived)
            print("Ip do not find. Added in destination of" , net )


def del_local(ipreceived):
    global net
    auxnet = net + '.txt'

    with open(auxnet, 'r') as file :
        filedata = file.read()
    filedata = filedata.replace("127.0.1.2", " ")

    with open(auxnet, 'w') as file:
        file.write(filedata)


def del_distance_file(filename, ipreceived):
    key= 'distances'

    f1 = open(filename, 'r')

    punc = '''[]{};:'"\,'''
    auxlist = ''
    newline = ''
    nextdistance = ''
    for line in f1:
        newline = line
        for ele in line:
            if ele in punc:
                line = line.replace(ele, "")

        if key in line:
            x=line.split()
            next = x[x.index(ipreceived)] #NEXT WORD
            print(next)
            if (ipreceived == next):
                nextdistance = x[x.index(ipreceived) +1] #apagar ip e distancia

        next = str(next)
        with open(filename, 'r') as file :
          filedata = file.read()
        # Replace the target string
        filedata = filedata.replace(next, "")
        filedata = filedata.replace(nextdistance, "")
        # Write the file out again
        with open(filename, 'w') as file:
          file.write(filedata)

    f1.close()


def simula_update(period): #nviar mensagens deupdateperiodicamente paratodos seus vizinhos a cadaπsegundos.
    global net
    mindist = update_data()
    ROUTING_TABLE.append(mindist)
    print(ROUTING_TABLE)
#    path = os.getcwd()
#    text_files = [f for f in os.listdir(path) if f.endswith('.txt')]
#    for file in text_files:
#        with open(file) as fh:
#          lines = fh.readlines()
#          for line in lines:
#              for word in line.split():
#                  auxword = (line.split(' ')[i])
#                  if (net in auxword): #se o ip estiver na palavra adiionara na tabela
#                      ROUTING_TABLE.append({auxword[0]: [int(auxword[1]), auxword[0]]})
                        #NEIGHBORS.append(line[0])
    time.sleep(period) # Atualizações Periódicas

def update_data():
    keysdict = ["type", "source", "destination", "distances"]

    global net, clientnet, ROUTING_TABLE

    filename =net+".txt"
    f1 = open(filename, 'r')

    punc = '''[]{};:'"\,'''
    auxlist = ''
    newline = ''
    distancesdict = []
    weightlist = []
    addresslist= []
    file1 = open(filename, 'r')
    count = 0

    # Using for loop
    #print("Using for loop")
    for line in file1:
        for ele in line:
            if ele in punc:
                line = line.replace(ele, "")
        count += 1
        x = line.split()
        for word in x:
            if (validate_ip(word)):
                address = x
                weight = x[x.index(word) + 1]
                objdict = dict(zip(address, weight))
                weightlist.append(weight)
                addresslist.append(address)
                distancesdict.append(objdict)

    file1.close()

    mindistance = min(weightlist)
    minadd = addresslist[weightlist.index(mindistance)]
    #minadd = minadd[0]
    #print(mindistance)
    #print(minadd)

    valuesdict1 = ["update", net, mindistance, distancesdict]
    D = dict(zip(keysdict, valuesdict1))

    print(D)
    return minadd


def update_data_destination(filename, ipreceived):
    global net
    key2= 'destination'

    f1 = open(filename, 'r')

    punc = '''[]{};:'"\,'''
    auxlist = ''
    newline = ''

    for line in f1:
        newline = line
        for ele in line:
            if ele in punc:
                line = line.replace(ele, "")
        #print(line)
        #print(newline)
        if key2 in line:
            x=line.split()
            next = x[x.index(key2) + 1] #NEXT WORD
            #print("prox palavra")
            #print (next)
        next = str(next)
        ipreceived = str(ipreceived)
        with open(filename, 'r') as file :
          filedata = file.read()
        # Replace the target string
        filedata = filedata.replace(next, ipreceived)
        # Write the file out again
        with open(filename, 'w') as file:
          file.write(filedata)

    f1.close()
    print ("function update")



def compare_data_file(filename, ip):
    with open(filename) as fh:
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
          #lst.append(line)
          i=0
         # line=line.translate(r' "",: ')
          for ele in line:
              if ele in punc:
                  line = line.replace(ele, "")

          for word in line.split():
              auxword = (line.split(' ')[i])

              if statetype in auxword:
                  x=line.split() #LIST OF WORDS
                  next = x[x.index(statetype) + 1] #NEXT WORD
                  #x = x.rstrip()
                  if ("data" in x):
                      payloadmessage = x[x.index(payload)+1]
                      simuladata(payloadmessage)
                  if ("update" in x):
                      print(line)
                      update_data(line)
                #arraylocaltype.append(x)

              if statesource in auxword:
                  x=line.split() #LIST OF WORDS
                  next = x[x.index(statetype) + 1] #NEXT WORD
                  if validate_ip(x):
                      arraylocalsource.append(x)

              if statedestination in auxword:
                  x=line.split() #LIST OF WORDS
                  next = x[x.index(statetype) + 1] #NEXT WORD
                  if validate_ip(x):
                      arraylocaldestination.append(x)

              if statehops in auxword:
                  x=line.split() #LIST OF WORDS
                  next = x[x.index(statetype) + 1] #NEXT WORD
                 # x=line.split(' ')[i+1]
                  #x = x.rstrip()
                  if validate_ip(x):
                      arraylocalhops.append(x)

              i=i+1


def simuladata(payloadmessage):
    print (payloadmessage)

def trace_data(ipreceived):
    global net, clientnet
    keysdict = ["type", "source", "destination", "hops"]

    distancesdict = []
    hopslist = []

    hopslist.append(ipreceived)

    print(hopslist)

    valuesdict1 = ["trace", net, clientnet, hopslist]
    D = dict(zip(keysdict, valuesdict1))



def validate_ip(s):
    a = s.split('.')
    if len(a) != 4:
        return False
    for x in a:
        if not x.isdigit():
            return False
        i = int(x)
        if i < 0 or i > 255:
            return False
    return True

def read_data_file(filename):
    # opening and reading the file
    with open(filename) as fh:
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
                  if ("add" in x):

                      add_local(x)
                  if ("update" in x):
                      pass
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
