import json

person = '{"name": "Bob", "languages": ["English", "Fench"]}'
person_dict = json.loads(person)

# Output: {'name': 'Bob', 'languages': ['English', 'Fench']}
print( person_dict)

# Output: ['English', 'French']
print(person_dict['languages'])
dict1 = {}
# creating dictionary

with open('2.txt', 'wb') as json_file:
    json.dump(data, codecs.getwriter('utf-8')(f), ensure_ascii=False)

    #json_data = json.load(json_file)
    for line in json_file:
        # reads each line and trims of extra the spaces
        # and gives only the valid words
        command, description = line.strip().split(None, 1)
        y = json.dumps(line)
        print(y)
        #print(type(line))
        #print(description)
        dict1[command] = description.strip()

#print(description)

# Output: ['English', 'French']
#print(json_data['source'])
