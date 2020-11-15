
def isPalindrome(s):
    return s == s[::-1]

def dec_to_bin(x):
    return int(bin(x)[2:])

# Driver code
i = 11
s = str(11)
b = dec_to_bin(i)

ans = isPalindrome(s)

if ans:
    print("Yes")
else:
    print("No")
print(b)
