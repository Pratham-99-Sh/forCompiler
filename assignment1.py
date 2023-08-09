a = int(input("Enter a number: "))
b = float(input("Enter a float : "))

print("The sum is : ", a + b)
print("The difference is : ", a - b)
print("The product is : ", a * b)
print("The quotient is : ", a / b, "\n\n")


c = int(input("Enter a number: "))
d = int(input("Enter a number: "))

print("The and of the two numbers is : ", c & d)
print("The or of the two numbers is : ", c | d)
print("The xor of the two numbers is : ", c ^ d)
print("The not of the two numbers is : ", ~c)
print("The left shift of the two numbers is : ", c << 2)
print("The right shift of the two numbers is : ", c >> 2, "\n\n")

str1 = "word1"
str2 = "word2"

print("The concatenation of the two strings is : ", str1 + str2)
print("The repetition of the two strings is : ", str1 * 3)
print("The slicing of the two strings is : ", str2[1:3])
print("The slicing of the two strings is : ", str1[1:])
print("The slicing of the two strings is : ", str1[:3])
print("The slicing of the two strings is : ", str2[:])
print("The slicing of the two strings is : ", str1[-1])
print("The slicing of the two strings is : ", str2[-1])
print("The slicing of the two strings is : ", str1[-3:-1], "\n\n")

# write a program to demonstrate the lists and different list operations slicing , append, remove , etc
list1 = [1, 2, 3, 4, 5]
list2 = [6, 7, 8, 9]

print("The concatenation of the two lists is : ", list1 + list2)
print("The repetition of the two lists is : ", list1 * 3)
print("The slicing of the two lists is : ", list2[1:3])
print("The slicing of the two lists is : ", list1[1:])
print("The slicing of the two lists is : ", list1[:3])
print("The slicing of the two lists is : ", list2[:])
print("The slicing of the two lists is : ", list1[-1])
print("The slicing of the two lists is : ", list2[-1])
print("The slicing of the two lists is : ", list1[-3:-1], "\n\n")

list1.append(6)
print("The list after appending is : ", list1)
list1.remove(6)
print("The list after removing is : ", list1)
list1.insert(2, 6)
print("The list after inserting is : ", list1)
list1.pop(2)
print("The list after popping is : ", list1)
list1.sort()
print("The list after sorting is : ", list1)
list1.reverse()
print("The list after reversing is : ", list1, "\n\n")

# write a program to demostrate dictionary with different data types and access and add and remove elements
dict1 = {1: "one", 2: "two", 3: "three"}
print("The dictionary is : ", dict1)
print("The value of key 1 is : ", dict1[1])
print("The value of key 2 is : ", dict1[2])
print("The value of key 3 is : ", dict1[3], "\n\n")

dict1[4] = "four"
print("The dictionary after adding is : ", dict1)
del dict1[4]
print("The dictionary after deleting is : ", dict1, "\n\n")

# write a program to make different kind of sets and perform different set operations
set1 = {1, 2, 3, 4, 5}
set2 = {6, 7, 8, 9}

print("The union of the two sets is : ", set1 | set2)
print("The intersection of the two sets is : ", set1 & set2)
print("The difference of the two sets is : ", set1 - set2)
print("The symmetric difference of the two sets is : ", set1 ^ set2, "\n\n")

# write a program to make different kind of tuples and perform different tuple operations
tuple1 = (1, 2, 3, 4, 5)
tuple2 = (6, 7, 8, 9)

print("The concatenation of the two tuples is : ", tuple1 + tuple2)
print("The repetition of the two tuples is : ", tuple1 * 3)
print("The slicing of the two tuples is : ", tuple2[1:3])
print("The slicing of the two tuples is : ", tuple1[1:])
print("The slicing of the two tuples is : ", tuple1[:3])
print("The slicing of the two tuples is : ", tuple2[:])
print("The slicing of the two tuples is : ", tuple1[-1])
print("The slicing of the two tuples is : ", tuple2[-1])
print("The slicing of the two tuples is : ", tuple1[-3:-1], "\n\n")

