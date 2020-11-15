import json# Read in the file

f1 = open('127.1.1.2.txt', 'r')
nextdistance = ''
x=''
for line in f1:
    for word in line:
        if "127.0.1.2" in word:
        #x=line.split(' ')
            next = x[x.index("127.0.1.2")] #NEXT WORD
            nextdistance = x[x.index("127.0.1.2") +1] #apagar ip e distancia
    next = str(next)
    nextdistance = str(nextdistance)
with open('127.1.1.2.txt', 'r') as file :
    filedata = file.read()
    # Replace the target string
filedata = filedata.replace(next, " ")
filedata = filedata.replace(nextdistance, " ")
    # Write the file out again
with open('127.1.1.2.txt', 'w') as file:
    file.write(filedata)

f1.close()
