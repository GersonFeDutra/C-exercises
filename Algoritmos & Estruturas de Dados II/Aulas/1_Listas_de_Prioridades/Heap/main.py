from libC import *
# Using the functions defined in `libC`.

LEN = 20
data_list = (Data * LEN)()
priorities_list = (c_uint32 * LEN)()

for i in range(LEN):
    data_list[i].number = c_int(i)
    data_list[i].name = b'%d' % i
    priorities_list[i] = i

new_heap = libC.new_heap_from(data_list, priorities_list, LEN, LEN)

# if new_heap == None:
# exit()

libC.print_heap(new_heap)
