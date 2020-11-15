import json
import re,os
import pickle

key0 ='type'
key1= 'source'
key2= 'destination'
key3 ='hops'
key4='payload'

#keywords = set(keywords)
# Output: {'name': 'Bob', 'languages': ['English', 'Fench']}

filename = '2.txt'
#with open('2.txt', 'wb') as json_file:
#outfile = open(filename,'wb')
#pickle.dump('destination',outfile)
# loads : get the data from var
#data = pickle.load('destination')


#    json_file.update({'destination': '8.8.8.10'})
#    data = json_file.read()
with open(filename) as fh:
  lines = fh.readlines()
      #howmanywords = len (line.split())
  statetype = "type"
  statedestination = "destination"
  statehops = "hops"
  statesource = "source"
  statepayload = "payload"
  for line in lines:
      #print(line)
      #d = json.load(str(line))
      d = json.dumps(line)
      print ("initial 1st dictionary", line)
      print ("type of ini_object", type(line))
      d = json.loads(line)
      for i in d[statesource]:
          print(i)
      #print (d[statesource])
      #if (d[statesource]=='127.0.1.2'):
        #  d['destination'] = '8.8.8.10'


#Update the values

#Save
#with open('variables.pkl', 'wb') as file:
#    pickle.dumps(d, file)



#print(description)

# Output: ['English', 'French']
#print(json_data['source'])
