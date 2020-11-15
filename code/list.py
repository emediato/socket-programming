import string

market_2nd = [ {'nome': 'a', 'end': 'casa a '}, {'nome': 'b', 'end': 'predio b'}, {'nome': 'c', 'end': 'predio c'}]
nomes = [item ['nome'] for item in market_2nd]
print (nomes) #apenas nomes
print (market_2nd[::-1]) #de tras pra frente
print (market_2nd[-1]) # ultimo elemento lista


for i in range(97, 123):
    print("{:c}".format(i), end='')
