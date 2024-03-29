import ctypes
import sys
import os

if   sys.platform == 'win32':  ext = ".dll"
elif sys.platform == 'linux':  ext = ".so"
elif sys.platform == "darwin": ext = ".dylib"
else: raise ImportError("Unsupported Platform")

file = os.path.abspath(os.path.join(os.path.dirname(__file__), "libcppcore"+ext))
lib = ctypes.CDLL(file)
