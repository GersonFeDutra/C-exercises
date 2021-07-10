from libC import *
# Using the functions defined in `libC`.

heap = libC.new_heap(c_uint8(15))

# if heap == None:
# 	exit()

# Create a new data 'struct'
data = Data(c_int(10), b'teste')
print(data.number, data.name)

print(FLAGS[libC.heap_insert(heap, data, c_uint32(1))])

# Creates a new 'struct' to cache the data returned by the `libC`.
ret = Data()
print(ret.number, ret.name)

print(FLAGS[libC.heap_pop(heap, pointer(ret))])
print(ret.number, ret.name)

print(FLAGS[libC.heap_remove(heap)])
libC.print_heap(heap)

# Note que o ponteiro de heap é removido automaticamente pelo Python, quando não mais estiver sendo
# referenciado.
