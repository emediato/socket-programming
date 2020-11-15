import string

market_2nd = [ {'nome': 'a', 'end': 'casa a '}, {'nome': 'b', 'end': 'predio b'}, {'nome': 'c', 'end': 'predio c'}]
nomes = [item ['nome'] for item in market_2nd]
print (nomes) #apenas nomes
print (market_2nd[::-1]) #de tras pra frente
print (market_2nd[-1]) # ultimo elemento lista

#alfabeto lower case
#alfabeto upper case
for i in range(97, 123):
    print("{:c}".format(i), end='')

n = 16
myDict = {}
for i in range(0, n):
    char = 'abcd'[i%4]
    try:
        myDict[char] += 1
    except KeyError:
        myDict[char] = 1
    print(myDict)

def spam(divideBy):
        return 42 / divideBy
    except ZeroDivisionError:
        print('Error: Invalid argument.')
print(spam(2))


bacon = 'BAcon'
eggs = 'bacon'
assert eggs.lower() != bacon.lower(), 'the variables are the same.'

class Solution:
    # @param A : tuple of integers
    # @return an integer
    def maxSubArray(self, A):
        curr_max = global_max = A[0]
        # iterate through each index of array:
        for i in range(1,len(A)):
            curr_max= max(A[i], (A[i] + curr_max))
            if curr_max > global_max:
                global_max = curr_max
            #condition to check and update global max
        return global_max



############################################ modulo array

Tipo list[-1] retorna o ultimo elemento da lista
List[-2]
O penúltimo e assim por diante
List[1:] retorna todos elementos da lista a partir da posição 1
List[:2] retorna todos elementos até a posição 2

A=[1, 3, -1]

f(1, 1) = f(2, 2) = f(3, 3) = 0
f(1, 2) = f(2, 1) = |1 - 3| + |1 - 2| = 3
f(1, 3) = f(3, 1) = |1 - (-1)| + |1 - 3| = 4
f(2, 3) = f(3, 2) = |3 - (-1)| + |2 - 3| = 5

So, we return 5.


f(i, j) = |A[i] - A[j]| + |i - j| can be written in 4 ways (Since we are looking at max value, we don’t even care if the value becomes negative as long as we are also covering the max value in some way).

(A[i] + i) - (A[j] + j)
-(A[i] - i) + (A[j] - j)
(A[i] - i) - (A[j] - j)
(-A[i] - i) + (A[j] + j) = -(A[i] + i) + (A[j] + j)

Note that case 1 and 4 are equivalent and so are case 2 and 3.

We can construct two arrays with values: A[i] + i and A[i] - i. Then, for above 2 cases, we find the maximum value possible. For that, we just have to store minimum and maximum values of expressions A[i] + i and A[i] - i for all i.

############################################ modulo array
class Solution:
    # @param A : list of integers
    # @return an integer
    def maxArr(self, a):
        n = len(a)
        ap = [a[i] + i for i in range(n)]
        am = [a[i] - i for i in range(n)]
        return max(max(ap) - min(ap), max(am) - min(am))


####  Can you maintain depth of a node while traversing the tree.
#How can it help you after the tree traversal?

# Definition for a  binary tree node
# class TreeNode:
#    def __init__(self, x):
#        self.val = x
#        self.left = None
#        self.right = None

Approach 1: Maintain a vector of size ‘depth’ of the tree. Do any kind of tree traversal keeping
 track of the current depth. Append the current element to vector[currentDepth]. Since we need stuff
 left to right, make sure left subtree is visited before the right subtree ( Any of traditional
  pre/post/inorder traversal should suffice ).

Approach 2: This is important. A lot of times, you’d be asked to do a traditional level order traversal.
Or to put in formal words, a traversal where the extra memory used should be proportional to the nodes
on a level rather than the depth of the tree. To do that, you need to make sure you are accessing all
the nodes on a level before accessing the nodes on next. This is a typical breadth first search problem.
 Queue FTW.

from collections import deque
class Solution:
    # @param A : root node of tree
    # @return a list of list of integers
    def levelOrder(self, A):
        ans = []
        sub = []
        if A == None:
            return ans
        q = deque()
        s = deque()
        q.append(A)
        while(q):
            n = q.popleft()
            sub.append(n.val)
            if n.left:
                s.append(n.left)
            if n.right:
                s.append(n.right)
            if not q:
                q = s
                s = deque()
                ans.append(sub[:])
                sub.clear()
        return ans



There are two main ways to traverse a graph: Breadth-first or Depth-first. Let’s try the Breadth-first
approach first, which requires a queue.


import collections
class graph:
    def __init__(self,adjacency=None):
        if adjacency is None:
            adjacency = {}
        self.adjacency = adjacency

def bfs(graph, startnode):
# Track the visited and unvisited nodes using queue
        seen, queue = set([startnode]), collections.deque([startnode])
        while queue:
            vertex = queue.popleft()
            print(vertex)
            for node in graph[vertex]:
                if node not in seen:        #checking if not visited
                    seen.add(node)
                    queue.append(node)



# The graph dictionary
adjacency = {
          "a" : set(["b","c"]),
          "b" : set(["a", "d"]),
          "c" : set(["a", "d"]),
          "d" : set(["e"]),
          "e" : set(["a"])
        }

bfs(adjacency, "a")


For the Depth-first approach, please see Clone Graph Part II.


    C
    C++
    Java
    Python

Implementation of DFS in python:
def dfs(graph, vertex, visited=None):
    if visited is None:
        visited = set()
    visited.add(vertex)
    print(vertex)
    for node in graph[vertex] :
        if node not in visited:
        dfs(graph, node, visited)

graph = {'0': set(['1', '2']),
         '1': set(['0', '3', '4']),
         '2': set(['0', ‘4’]),
         '3': set(['1', ‘4’]),
         '4': set([‘1’, '2', '3'])}


How does the breadth-first traversal works? Easy, as we pop a node off the queue, we copy each of its neighbors
and push them to the queue.
A straight forward breadth-first traversal seemed to work. But some details are still missing.
For example, how do we connect the nodes of the cloned graph?
Before we continue, we first need to make sure if the graph is directed or not. If you notice how Node
is defined above, it is quite obvious that the graph is a directed graph. Why?
For example, A can have a neighbor called B. Therefore, we may traverse from A to B. An undirected graph
implies that B can always traverse back to A. Is it true here? No, because whether B could traverse back
to A depends if one of B’s neighbor is A.
The fact that B can traverse back to A implies that the graph may contain a cycle. You must take extra
care to handle this case. Imagine that you finished implementing without considering this case, and later
 being pointed out by your interviewer that your code has an infinite loop, yuck
Let’s analyze this further by using the below example:
A simple graph
A <-> B
Assume that the starting point of the graph is A. First, you make a copy of node A (A2), and found
that A has only one neighbor B. You make a copy of B (B2) and connects A2->B2 by pushing B2 as A2′s
neighbor. Next, you find that B has A as neighbor, which you have already made a copy of. Here, we
have to be careful not to make a copy of A again, but to connect B2->A2 by pushing A2 as B2′s neighbor.
But, how do we know if a node has already been copied?
Easy, we could use a hash table! As we copy a node, we insert it into the table. If we later find
 that one of a node’s neighbor is already in the table, we do not make a copy of that neighbor, but to
 push its neighbor’s copy to its copy instead. Therefore, the hash table would need to store a mapping of
 key-value pairs, where the key is a node in the original graph and its value is the node’s copy.

UndirectedGraphNode.__hash__ = lambda self: id(self)

class Solution:
    def __init__(self):
        self.visited = {}


class Solution:
    # @param node, a undirected graph node
    # @return a undirected graph node
    def cloneGraph(self, node):
        if not node:
            return

        hashMap = dict()
        Q = deque([node])
        hashMap[node] = UndirectedGraphNode(node.label)

        while Q:
            current = Q.pop()
            node_copy = hashMap[current]

            for n in current.neighbors:
                if n not in hashMap:
                    n_copy = UndirectedGraphNode(n.label)
                    node_copy.neighbors.append(n_copy)
                    hashMap[n] = n_copy

                    Q.appendleft(n)
                else:
                    n_copy = hashMap[n]
                    node_copy.neighbors.append(n_copy)

        return hashMap[node]

n = 16
myDict = {}
for i in range(0, n):
    char = 'abcd'[i%4]
    try:
        myDict[char] += 1
    except KeyError:
        myDict[char] = 1
    print(myDict)

{'a': 1}
{'a': 1, 'b': 1}
{'a': 1, 'b': 1, 'c': 1}
{'a': 1, 'b': 1, 'c': 1, 'd': 1}
{'a': 2, 'b': 1, 'c': 1, 'd': 1}
{'a': 2, 'b': 2, 'c': 1, 'd': 1}
{'a': 2, 'b': 2, 'c': 2, 'd': 1}
{'a': 2, 'b': 2, 'c': 2, 'd': 2}
{'a': 3, 'b': 2, 'c': 2, 'd': 2}
{'a': 3, 'b': 3, 'c': 2, 'd': 2}
{'a': 3, 'b': 3, 'c': 3, 'd': 2}
{'a': 3, 'b': 3, 'c': 3, 'd': 3}
{'a': 4, 'b': 3, 'c': 3, 'd': 3}
{'a': 4, 'b': 4, 'c': 3, 'd': 3}
{'a': 4, 'b': 4, 'c': 4, 'd': 3}
{'a': 4, 'b': 4, 'c': 4, 'd': 4}




# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
from collections import deque
class Solution:
    # @param A : root node of tree
    # @return a list of list of integers
    def levelOrder(self, A):
        list = []
        l = deque()
        if A is None:
            return []
        list.append([A.val])
        if A.left is not None:
            l.append(A.left)
        if A.right is not None:
            l.append(A.right)

        while len(l) > 0:
            l2 = []
            #node = l.popleft()
            #l2.append(node.val)
            l1 = deque()
            while len(l) > 0:
                node1 = l.popleft()
                l2.append(node1.val)
                if node1.left is not None:
                    l1.append(node1.left)
                if node1.right is not None:
                    l1.append(node1.right)

            l = l1
            list.append(l2)
        return list


# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
from collections import deque
class Solution:
    # @param A : root node of tree
    # @return a list of list of integers
    def levelOrder(self, A):
        list = []
        l = deque()
        if A is None:
            return []
        list.append([A.val])
        if A.left is not None:
            l.append(A.left)
        if A.right is not None:
            l.append(A.right)

        while len(l) > 0:
            l2 = []
            #node = l.popleft()
            #l2.append(node.val)
            l1 = deque()
            while len(l) > 0:
                node1 = l.popleft()
                l2.append(node1.val)
                if node1.left is not None:
                    l1.append(node1.left)
                if node1.right is not None:
                    l1.append(node1.right)

            l = l1
            list.append(l2)
        return list





Approach 1: Maintain a vector of size ‘depth’ of the tree. Do
any kind of tree traversal keeping track of the current depth.
Append the current element to vector[currentDepth].
Since we need stuff left to right, make sure left subtree is
visited before the right subtree ( Any of traditional pre/post/inorder
traversal should suffice ).

Approach 2: This is important. A lot of times, you’d be asked to do
a traditional level order traversal. Or to put in formal words,
a traversal where the extra memory used should be proportional
to the nodes on a level rather than the depth of the tree. To
do that, you need to make sure you are accessing all the nodes
on a level before accessing the nodes on next.
This is a typical breadth first search problem. Queue FTW.


1. Using the functional coding style
The functional coding style treats everything like a math equation.
 The two most common ways to compute the sum of my_list would be
 to use a local function or a lambda expression. Here’s how you’d do
 it with a local function in Python 3.6:


import functools
my_list = [1, 2, 3, 4, 5]
def add_it(x, y):
    return (x + y)
sum = functools.reduce(add_it, my_list)
print(sum)

The functools package provides access to higher-order functions for
data manipulation. However, you don’t always use it to perform
functional programming with Python. Here’s a simple example using
my_list with a lambda function:

square = lambda x: x**2
double = lambda x: x + x
print(list(map(square, my_list)))
print(list(map(double, my_list)))

As you can see, the lambda expression is simpler (or, at least,
 shorter) than a similar procedural approach. Here’s a lambda
 function version of the functools.reduce() call:

import functools
my_list = [1, 2, 3, 4, 5]
sum = functools.reduce(lambda x, y: x + y, my_list)
print(sum)

2. Using the imperative coding style

In imperative programming, you focus on how a program operates.
Programs change state information as needed in order to achieve a
 goal. Here’s an example using my_list:

sum = 0
for x in my_list:
    sum += x
print(sum)

Unlike the previous examples, the value of sum changes with each
iteration of the loop. As a result, sum has state. When a variable
has state, something must maintain that state, which means that the
 variable is tied to a specific processor. Imperative coding works
 on simple applications, but code executes too slowly for optimal
 results on complex data science applications.

3. Using the object-oriented coding style

Object-oriented coding is all about increasing an application’s
ability to reuse code and make it easier to understand. The
encapsulation that object-orientation provides allows developers
to treat code as a black box. Using object-orientation features like
 inheritance make it easier to expand the functionality of existing
 code. Here is the my_list example in object-oriented form:

class ChangeList(object):
    def __init__(self, any_list):
        self.any_list = any_list
    def do_add(self):
      self.sum = sum(self.any_list)
create_sum = ChangeList(my_list)
create_sum.do_add()
print(create_sum.sum)

In this case, create_sum is an instance of ChangeList. The inner
 workings of ChangeList don’t matter to the person using it. All
 that really matters is that you can create an instance using a
 list and then call the do_add() method to output the sum of the
 list elements. Because the inner workings are hidden, the overall
  application is easier to understand.

4. Using the procedural coding style

The procedural style relies on procedure calls to create modularized
code. This approach simplifies your application code by breaking it
into small pieces that a developer can view easily. Even though
procedural coding is an older form of application development,
it’s still a viable approach for tasks that lend themselves to
step-by-step execution. Here’s an example of the procedural coding
style using my_list:

def do_add(any_list):
    sum = 0
    for x in any_list:
        sum += x
    return sum
print(do_add(my_list))

The use of a function, do_add(), simplifies the overall code i
n this case. The execution is still systematic, but the code
is easier to understand because it’s broken into chunks. However,
this code suffers from the same issues as the imperative paradigm
in that the use of state limits execution options, which means that
this approach may not use hardware efficiently when tackling
complex problems.

###########################################
def findMinIndex(A, start):
    min_index = start

    start += 1

    while start < len(A):
        if A[start] < A[min_index]:
            min_index = start

        start += 1

    return min_index

def selectionSort(A):
    i = 0

    while i < len(A):
        min_index = findMinIndex(A, i)

        if i != min_index:
            A[i], A[min_index] = A[min_index], A[i]

        i += 1

A = [5, 2, 6, 7, 2, 1, 0, 3]

selectionSort(A)

for num in A:
    print(num, end=' ')



#fibonacci par number

total = 0
x, y = 0, 1
while y < 4000000:
    x, y = y, x + y
    if x % 2:
        continue
    total += x

print (total)



#lowerlist = ['this', 'is', 'lowercase']
upper = str.upper
upperlist = []
append = upperlist.append
for word in lowerlist:
    append(upper(word))
    print(upperlist)
    #Output = ['THIS', 'IS', 'LOWERCASE']
#Optimizing loops





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
