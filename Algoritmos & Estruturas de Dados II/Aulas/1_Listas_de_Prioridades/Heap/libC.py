from ctypes import *
libC = CDLL('./libs/heap_array.so')
FLAGS = ["NOT_OK", "OK", "NULL_ERROR", "INVALID_INDEX_ERROR"]


# Definitions of the `libC` structures
class Data(Structure):
    _fields_ = [("number", c_int),
                ("name", c_char_p)]


# Definitions of the `libC` functions.

libC.new_heap.argtypes = [c_uint8]
libC.new_heap.restype = c_void_p

libC.heap_insert.argtypes = [c_void_p, Data, c_uint32]
libC.heap_insert.restype = c_uint8

libC.new_heap_from.argtypes = [POINTER(Data), POINTER(c_uint32), c_uint8, c_uint8]
libC.new_heap_from.restype = c_void_p

libC.heap_insert.argtypes = [c_void_p, Data, c_uint32]
libC.heap_insert.restype = c_uint8

libC.heap_remove.argtypes = [c_void_p]
libC.heap_remove.restype = c_uint8

libC.heap_pop.argtypes = [c_void_p, c_void_p]
libC.heap_pop.restype = c_uint8

libC.heap_change_priority.argtypes = [c_void_p, c_uint8, c_uint16]
libC.heap_change_priority.restype = c_uint8

libC.heap_sort.argtypes = [c_void_p, POINTER(POINTER(Data))]
libC.heap_sort.restype = c_uint8

libC.print_heap.argtypes = [c_void_p]
