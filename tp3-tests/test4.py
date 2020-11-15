import json# Read in the file

key2= 'destination'

f1 = open('2.txt', 'r')

punc = '''[]{};:'"\,'''
auxlist = ''
newline = ''

for line in f1:
    newline = line
    for ele in line:
        if ele in punc:
            line = line.replace(ele, "")
    print(line)
    print(newline)

    if key2 in line:
        x=line.split()
        next = x[x.index(key2) + 1] #NEXT WORD
        print("prox palavra")
        print (next)
    next = str(next)
    with open('2.txt', 'r') as file :
      filedata = file.read()
    # Replace the target string
    filedata = filedata.replace(next, "127.0.1.2")
    # Write the file out again
    with open('2.txt', 'w') as file:
      file.write(filedata)

f1.close()
