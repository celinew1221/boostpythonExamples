import myfoo
import numpy as np

np2dresult = np.zeros((10, 3), dtype=np.float64)

foo = myfoo.Foo(1,2)
print("before modification result:\n", np2dresult)
test = foo.np_modify(np2dresult)
print("after modification result:\n", np2dresult)
print("ndarray created in c++:\n", test)
