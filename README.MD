compilation
g++ -std=c++11 -O3 -DNDEBUG -march=native -fPIC -shared -flto -I/usr/include/python3.5m *.cpp -o myfoo.so -lopencv_core -lopencv_highgui -lopencv_imgproc -lboost_python35 -lboost_numpy35
