
from ctypes import *
import sys

# parametros: path y programa
if (len(sys.argv) < 2):
    print("")
    print("Usage:")
    print(" * ./main_preload.py <file name>")
    print("")
    print("Ejemplo:")
    print(" ./main_preload.py /tmp/expand/P1/demo.txt")
    print("")
    sys.exit()

fname = sys.argv[1]

# open
try:
    print("path: " + fname)
    f = open(fname, "r+", encoding="utf-8")
    print(f"f = open({fname}, 'r+', encoding='utf-8')")
    print(f)
    f.close()
except IOError as e:
    print(e)
    sys.exit()
except:
    print("open failed !")
    sys.exit()

