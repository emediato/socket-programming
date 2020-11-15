    # @param A : list of integers
    # @param B : integer
    # @return an integer

    /*
i18n is a short way to write down internationalization
given a pattern i18n and an input string check if the input string matches the pattern

Given *s* = "apple", *abbr* = "a2e":
Return false.

Given *s* = "internationalization", *abbr* = "i12iz4n":
Return true.

Given *s* = "internationalization", *abbr* = "i18n":
Return true.

Given *s* = "apple", *abbr* = "a5":
Return false.
*/

import re, string
"a0" "a111" "a4"

    n = len (guess)

    for i in range (0, n):
        if (guess[i] % 10): #if it is decimal number



        return False


Given a sorted (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. If target exists, then return its index, otherwise return -1.


Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1

def searchtarget(self, A, B):
    #a list nums
    #b target
    # if N is too large the complexity is going to increase
    i, j = 0,0
    output = []

    while (i <= len(A)):
        temp = A[i]
        if (temp == B):
            output.append(i)
        i += 1

    if (output[0] == None ):
        return -1



def diffPossible(self, A, B):
        l,h = 0,1
        while l<=h<len(A):
            t = A[h]-A[l]
            if t<B or h==l:
                h+=1
            elif t>B:
                l+=1
            else:
                return 1
        return 0

def intersect(self, A, B):
        output = []
        n,m = len(A), len(B)
        i, j = 0,0
        while i < n and j < m:
            if A[i] > B[j]:
                j += 1
            elif A[i] < B[j]:
                i += 1
            else:
                output.append(B[j])
                i += 1
                j += 1
        return output

def maxSubArray(self, A):
    b=A[0]
    c=A[0]
    for i in range(1,len(A)):
        b=max(A[i],b+A[i])
        if b>c:
            c=b
    return c

def rotate(self, A):
        n = len(A)
        B = [[0 for i in range(n)] for j in range(n)]

        for i in xrange(n):
            for j in xrange(n):
                B[j][n-i-1] = A[i][j]

        return B

    # @param A : list of integers
    # @param B : integer
    # @return an integer
def threeSumClosest(self, A, B):
        A.sort()
        closest = None
        for i in range(len(A) - 2):
            j, k = i + 1, len(A) - 1
            while k > j:
                threeSum = A[i] + A[j] + A[k]
                if threeSum == B:
                    return threeSum
                if closest is None or abs(B - threeSum) < abs(B - closest):
                    closest = threeSum
                if threeSum < B:
                    j += 1
                else:
                    k -= 1
        return closest
    # @param A : list of integers
    # @return A after the sort
def sortColors(self, A):
        count0 = 0
        count1 = 0
        # count occurances of
        # 0's and 1's.
        for i in range(len(A)):
            if A[i]==0:
                count0 += 1
            elif A[i]==1:
                count1 += 1
        # length of list A
        # to calculate the
        # number of 2's
        length = len(A)
        # clear the list
        A.clear()

        # append all 0's
        for i in range(count0):
            A.append(0)

        # append all 1's
        for i in range(count1):
            A.append(1)

        # append all remaining 2's
        for i in range(length-count0-count1):
            A.append(2)
        return

class Solution: #Container With Most Water
    # @param A : list of integers
    # @return an integer
    def maxArea(self, A):
        l = 0
        r = len(A) -1
        area = 0

        while l < r:
            area = max(area, min(A[l], A[r]) * (r - l))
            if A[l] < A[r]:
                l += 1
            else:
                r -= 1

        return area

#Suppose a sorted array A is rotated at some pivot unknown to you beforehand.
class Solution:
    # @param A : tuple of integers
    # @return an integer
    def findMin(self, a):
        l, r = 0, len(a) - 1

        while a[l] > a[r]:
            m = (l + r) // 2
            if a[m] < a[r]:
                r = m
            else:
                l = m +1

        return a[l]
