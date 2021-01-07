# Lab 4

# take integer inputs
# based on input->return an output integer that is between 10 and 100
def f(inNum):
   outNum = (inNum%90)+10
   return outNum

# testing
print(f(89))
print(f(0))