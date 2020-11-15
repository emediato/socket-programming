def integer_to_string(n, base):

    str = "";
    while (n > 0):
        digit = n % base;
        n = int(n / base);
        str = chr(digit + ord('0')) + str;
    return str;

# function to check for palindrome
def isPalindrome(i, k):
    temp = i;

    # m stores reverse of a number
    m = 0;
    while (temp > 0):
        m = (temp % 10) + (m * 10);
        temp = int(temp / 10);

    # if reverse is equal to number
    if (m == i):

        # converting to base k
        str = integer_to_string(m, k);
        str1 = str;

        # reversing number in base k
        # str=str[::-1];

        # checking palindrome
        # in base k
        if (str[::-1] == str1):
            return i;
    return 0;

# function to find sum of palindromes
def sumPalindrome(n, k):

    sum = 0;
    for i in range(n):
        sum += isPalindrome(i, k);
    print("Total sum is", sum);

# Driver code
n = 1000000;
k = 2;

sumPalindrome(n, k);

# This code is contributed
# by mits
