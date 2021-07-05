from ctypes import *
libC = CDLL("./libs/c_world.so")

libC.run()
print("Hello world from Python!")

libC.ask.argtypes = []
libC.ask.restype = c_char_p
gotcha_something = libC.ask()
print("From C to Python:", gotcha_something)

text = b"Yes, it is!"
libC.answer.argtypes = [c_char_p]
libC.answer(text)
