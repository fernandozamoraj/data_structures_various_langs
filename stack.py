class Node:
	def __init__(self, data):
		self.data = data
		self.next = None
		
class Stack:
	
	def __init__(self):
		self.top = None

	def push(self, data):
		
		oldTop = self.top
		self.top = Node(data)
		self.top.next = oldTop
		
	def pop(self):
		popped = None
		if(self.top != None):
			popped = self.top.data
			self.top = self.top.next
			
		return popped
		
	def __repr__(self):
		asString = "Stack: "
		
		temp = self.top
		
		if(temp != None):
			asString = asString + "{},".format(temp.data)
			
			while(temp.next != None):
				temp = temp.next
				asString = asString + " {},".format(temp.data)
			
		return asString
		
		
myStack = Stack()

print(myStack)

myStack.push(1)
myStack.push(2)
myStack.push(3)
myStack.push(4)

print(myStack)

print("Popped {}".format(myStack.pop()))
print("Popped {}".format(myStack.pop()))
print("Popped {}".format(myStack.pop()))
print("Popped {}".format(myStack.pop()))
print("Popped {}".format(myStack.pop()))
print("Popped {}".format(myStack.pop()))
print(myStack)
print(myStack)

