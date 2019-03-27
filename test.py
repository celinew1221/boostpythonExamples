import myfoo
import numpy as np
import copy
from time import time

# numpy demo
print("NUMPY DEMO")
np2dresult = np.zeros((10, 3), dtype=np.float64)
foo = myfoo.Foo(1,2)
print("before modification result:\n", np2dresult)
test = foo.np_modify(np2dresult)
print("after modification result:\n", np2dresult)
print("ndarray created in c++:\n", test)

print("\n----------------------------\n--------------------------------\n")

# opencv demo
print("OPENCV AND EIGEN DEMO")
image = np.array([[[0, 1, 2],[2, 3, 4]],[[5,6,7],[8,9,10]]], dtype=np.float32)
final = np.array([[[0, 3, 1],[2, 37, 4]],[[5,6,77],[83,92,10]]], dtype=np.float32)
ch1 = np.array(image[:,:,0])
foo.mat_conversion(image, ch1, np.array(image[:,:,1]), np.array(image[:,:,2]), final)
print("=====Numpy <--> Mat, and change numbers result=====")
print("after changing ch1 and warp, my original image shouldn't change")
print("channel 0\n",image[:,:,0])
print("channel 1\n",image[:,:,1])
print("channel 2\n",image[:,:,2])
print("after changing 0,0,0 to 1000 in c++, channel 1 is\n", ch1)
print("after changing ch1, which is used to merged to the warp, warp is")
print("channel 0\n",final[:,:,0])
print("channel 1\n",final[:,:,1])
print("channel 2\n",final[:,:,2])

print("=====Channel Comparison=====") # turns out copy element by element is the fastest
print("use np.array to make contiguous channel")
start = time()
foo.channel_conversion_from_non_contin(np.array(image[:,:,0]), np.array(image[:,:,1]), np.array(image[:,:,2]))
print(time() - start, "s")

print("use transpose to switch to channel first to get contiguous channels")
start = time()
img = np.ascontiguousarray(np.transpose(image, (2, 0, 1)))
foo.channel_conversion_from_cont(img)
print(time() - start, "s")

print("split from Mat into channels")
start = time()
foo.channel_conversion_from_split(image)
print(time() - start, "s")

print("copy from Mat element by element")
start = time()
foo.channel_conversion_from_copy(image)
print(time() - start, "s")
