# Lab 1

from stackLib import * #* means all -> importing everything

# take in a string
# return a length-2 list, L
# L[0] is True if result of bracket checking indicates all brackets are matched
# L[0] is False otherwise
# L[1] indicates index of input string where bracket checking failed
def bc(iString):
   bcStack = stack()
   i = 0
   for ele in iString:
      if ((ele == '(') or (ele == '[') or (ele == '{')):
         bcStack.push(ele)
      elif ((ele == ')') or (ele == ']') or (ele == '}')):
         popped_value = bcStack.pop()
         if ((popped_value != '(') and (ele == ')')):
            return [False,i]
         elif ((popped_value != '[') and (ele == ']')):
            return [False,i]
         elif ((popped_value != '{') and (ele == '}')):
            return [False,i]
      i = i + 1
   
   # ensure there are no more brackets in the stack
   if bcStack.pop() == False:
      return [True,-1]
   else:
      return [False,i]

# testing
print(bc("(3+4)*[2*{3-1}]")) # [True,-1]
print(bc("(3+4)*[2*(3-1}]")) # [False,13]