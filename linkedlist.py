class Node:
	def __init__(self, data):
		self.data = data
		self.next = None

class List:	
	
	def __init__(self):
		self.head = None
		
	def add_to_tail(self, data):
		
		if(self.head == None):
			self.head = Node(data)
		else:
			current = self.head
			
			while(current.next != None):
				current = current.next			
		
			current.next = Node(data)
		
	def get_values(self):
		
		current = self.head
		
		asList = []
		while(current != None):
			asList.append(current.data)
			current = current.next
		
		return asList
		
	def insert_at(self, index, data):
		
		temp = self.head
		
		if(index == 0 or self.head == None):
			self.head = Node(data)
			self.head.next = temp
		else:
				
			current = self.head
			
			for i in range(1, index):
				if(current != None and current.next != None):
					current = current.next
			temp = current.next
			current.next = Node(data)
			current.next.next = temp
		
		
		
list = List()
list.add_to_tail("a")
list.add_to_tail(2)
list.add_to_tail("d")
list.add_to_tail(4)
list.insert_at(1, "c")
list.insert_at(0, "i")
list.insert_at(5, 5)
list.insert_at(30, 30)

print(list.get_values())
