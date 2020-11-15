
#decimal to binary
#The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.

#Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

def isPalindrome(s):
    if s == s[::-1]:
        return True
    else:
        return False

def decimaltobin(x):
    return int(bin(x)[2:])

totaldecimal = 0
decimal = 1
binary = 0

for decimal in range(1,999999):
    auxs=str(decimal)
    ansd = isPalindrome(auxs)
    binary = decimaltobin(decimal)
    auxs = str(binary)
    ansb = isPalindrome(auxs)
    if ansb == True :
        if ansd == True :
            totaldecimal += decimal
        #totalbinary = totalbinary + ansb


print (totaldecimal)
#print (totalbinary)

#        continue
#    total += x

#print (total)
