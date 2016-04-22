import os


words = os.system("wc out.txt")
headntail = os.system("(head -n1 && tail -n1) < out")

print(type(words))
print(type(headntail))
