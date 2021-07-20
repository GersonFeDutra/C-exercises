from ctypes import *
libC = CDLL('libs/binary_tree.so')


class Student(Structure):
    _fields_ = [('id', c_int),
                ('name', c_char * 152),
                ('av1', c_float),
                ('av2', c_float)]


libC.new_tree.restype = c_void_p

libC.insert_node.restype = c_int
libC.insert_node.argtypes = [c_void_p, Student]

libC.travel_tree.restype = c_int
libC.travel_tree.argtypes = [c_void_p, c_int]

libC.print_tree_by_level.argtypes = [c_void_p]
