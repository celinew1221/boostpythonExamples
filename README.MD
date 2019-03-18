compilation
g++ -std=c++11 -flto -fPIC -shared  -I/usr/include/python3.5m -I/usr/local/boost_1_69_0/ *.cpp -o myfoo.so -Wall -Wno-deprecated-declarations -lpython3.5m -lboost_python35 -lboost_numpy35
