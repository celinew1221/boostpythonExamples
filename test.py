import myfoo
import numpy as np

np2d = np.empty((10,2), dtype=np.float64)
np4d = np.zeros([6,6,3,3], dtype=np.float64)

foo = myfoo.Foo(1,2)
test = foo.np_modify(np2d, np4d)
print(np2d)
