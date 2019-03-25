import myfoo
import numpy as np

# numpy demo
print("NUMPY DEMO")
np2dresult = np.zeros((10, 3), dtype=np.float64)
foo = myfoo.Foo(1,2)
print("before modification result:\n", np2dresult)
test = foo.np_modify(np2dresult)
print("after modification result:\n", np2dresult)
print("ndarray created in c++:\n", test)

print("\n----------------------------\n")

# opencv demo
print("OPENCV AND EIGEN DEMO")
image = np.ascontiguousarray([[[0, 1, 2],[2, 3, 4]],[[5,6,7],[8,9,10]]], dtype=np.float32)
print("image passed in:")
print("channel 0\n",image[:,:,0])
print("channel 1\n",image[:,:,1])
print("channel 2\n",image[:,:,2])
foo.mat_eigen_conversion(image)