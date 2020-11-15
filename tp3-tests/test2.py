import ipaddress
import sys
# Return double of n
def addition(n):
    return n + n

# We double all numbers using map()
numbers = (21, 2, 3, 4)
result = map(addition, numbers)
print(list(result))

def main(argv):
    result = map(lambda x: x + x, numbers)
    print(list(result))

    #s = input()
    # List of strings
    net =(ipaddress.ip_interface(argv[0]))
    print(net)
    print(net.ip)
    print(net.hostmask)

    #mapeando = map(net.ip, net.hostmask)
    #print(mapeando)

    netfour = str(net)
    l = [netfour, 'bat', 'cat', 'mat']

    # map() can listify the list of strings individually
    test = list(map(list, l))
    print(test)

    # Add two lists using map and lambda
    numbers1 = [2, 2, 3]
    numbers2 = [4, 5, 6]

    result = map(lambda x, y: x + y, numbers1, numbers2)
    print(list(result))
if __name__ == "__main__":
    main(sys.argv[1:]) # FILE
