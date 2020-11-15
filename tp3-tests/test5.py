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


keysdict = ["type", "source", "destination", "hops"]

net='127.1.1.2'
clientnet = '127.1.1.9'
ipreceived = '122.12.13.2'
distancesdict = []
hopslist = []

hopslist.append(ipreceived)
hopslist.append(ipreceived)

print(hopslist)

valuesdict1 = ["trace", net, clientnet, hopslist]
D = dict(zip(keysdict, valuesdict1))

print(D)
