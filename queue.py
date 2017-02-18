class Node:
	def __init__(self, data):
		self.data = data
		self.next = None
		
	def __repr__(self):
		return "Node: {}".format(self.data)
		
		
class Queue:
	def __init__(self):
		self.head = None
		self.tail = None
	
	def __repr__(self):
		asList = ""
		current = self.head
		
		while(current != None):
			asList += "{}, ".format(current.data)
			current = current.next
		return "Queue: " + asList
		
	def enque(self, data):
		if(self.head == None):
			self.head = Node(data)
			self.tail = self.head
		else:
			self.tail.next = Node(data)
			self.tail = self.tail.next
			
	def deque(self):
		nextData = None
		if(self.head != None):
			nextData = self.head.data
			self.head = self.head.next
			
		return nextData
		
	def peek(self):
		if(self.head != None):
			return self.head.data
			
		return None

				
q = Queue()

q.enque(1)
q.enque(2)
q.enque(3)
q.enque(4)

print(q)

print(q.deque())
print(q.deque())
print(q.deque())
print(q.deque())
print(q.deque())
print(q.deque())

print(q)

