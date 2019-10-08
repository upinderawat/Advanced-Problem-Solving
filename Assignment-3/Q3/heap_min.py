import random
class HeapMin(object):
	def __init__(self, heap_arr=None):
		self.__heap_arr = [0]
		if heap_arr is not None:
			self.__heap_arr.extend(heap_arr)
		else:
			self.__heap_arr = [0] 

		self.build_heap()
	
	def __str__(self):
		return "heap_arr:{}\n".format(self.__heap_arr)
	
	def __repr__(self):
		return "<class 'Heap_min'>"

	def get_heap_arr(self):
		return self.__heap_arr

	def get_heap_size(self):
		return len(self.__heap_arr)-1

#top down min-heapify in order of O(log(n))
	def min_heapify(self, index):
		smallest = index
		left = 2*index
		right = left + 1
		if left <= self.get_heap_size() and self.__heap_arr[left][0] < self.__heap_arr[smallest][0]:
			smallest = left
		if right <= self.get_heap_size() and self.__heap_arr[right][0] < self.__heap_arr[smallest][0]:
			smallest = right
		if smallest != index:
			self.__heap_arr[smallest], self.__heap_arr[index] = self.__heap_arr[index], self.__heap_arr[smallest]
			self.min_heapify(smallest)
		return smallest #used to optimize minheapify calls in push_heap

#bottom up manner calling min_heapify
	def build_heap(self):
		i=self.get_heap_size()//2
		while i>=1:
			self.min_heapify(i)
			i-=1
	
	def push_heap(self, ele):
		self.__heap_arr.append(ele)
		i= self.get_heap_size()//2
		while i>=1:
			j=self.min_heapify(i)
			if j==i:
				break
			i//=2
	def extract_min(self):
		if self.get_heap_size() == 0:
			return None
		tmp = self.__heap_arr[1]
		self.__heap_arr[1], self.__heap_arr[-1] = self.__heap_arr[-1], self.__heap_arr[1]
		self.__heap_arr.pop() #remove last element
		self.min_heapify(1)
		return tmp
