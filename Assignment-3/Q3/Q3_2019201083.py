import os
import sys
from sort_less import quicksort
from heap_min import HeapMin


def merge_num_chunks(hp):
	try:
		with open(sys.argv[2],'w') as wf:
			while True:
				tup = hp.extract_min()
				if tup:
					ele, f = tup
				else:
					#operation complete
					break
				wf.write(str(ele)+"\n")
				ele = f.readline()
				if ele:
					hp.push_heap((int(ele), f))

	except FileNotFoundError as e:
		print(sys.argv[2],e)
	except Exception as e:
		print("merge_num_chunks: ", e)
def df(num_chunks):
	try: 
		file_des = [open("temp_"+str(i)) for i in range(num_chunks)] 
		#store the inital num_chunks elements
		arr = [(int(file_des[i].readline()), file_des[i]) for i in range(num_chunks)]
		hp = HeapMin(arr)
		merge_num_chunks(hp)
	except Exception as e:
		print("df: ",e)
	finally:
		[file_des[i].close() for i in range(num_chunks)]

def save_sorted_chunk(chunk, file_name):
	""" store each sorted chunk of size chunk_size(except for last) in
	memory following naming convention temp_<i>.
	Each number is delimited by newline character 
	"""
	try:
		with open(file_name, 'w+') as f :
			for c in chunk:
				f.write(str(c)+"\n")
	except Exception as e:
		print("save_sorted_chunk: ",e)

def read_chunk_size(f, chunk_size):
	"""reads from file pointer delimited by chunk_size(not byte ordered) or EOF 
	and returns a tuple of list of mapped integers(from bytes) and number of 
	bytes read 
	"""
	if f.closed:
		print("File is closed")
		return

	b= bytes()
	i=0
	while i<chunk_size:
		a = f.readline()
		if a:
			b+= a
		else:
			break
		i+=1
	# print(b)
	chunk = [int(i) for i in b.split()]
	return (chunk, i)

def main():
	chunk_size = 1000
	num_chunks = 0
	last_chunk_size = 0

	if len(sys.argv) != 3:
		print("Incorrect Arguments")
		return
	try:
		with open(sys.argv[1],'rb') as f:
			# read chunk by chunk till EOF
			while True:
				chunk, last_chunk_size = read_chunk_size(f, chunk_size)
				if chunk:
					quicksort(chunk, 0, len(chunk)-1)
					# chunk.sort()
					save_sorted_chunk(chunk, "temp_"+str(num_chunks))
					num_chunks+=1
				else:
					print ("End of chunk:", num_chunks)
					break
		df(num_chunks)		
	except FileNotFoundError as e:
		print(sys.argv[1],e)
	except Exception as e:
		print("main: ",e)
	finally:
		[os.remove("temp_"+str(i)) for i in range(num_chunks)]

if __name__ == '__main__':
	main()