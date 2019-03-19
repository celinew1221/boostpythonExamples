#include <iostream>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
using namespace boost::python;
using namespace boost::python::numpy;
using namespace std;

class Foo
{
    public:
        Foo(int, double);
        void add(int);
        int get_val();
        void set_val(int);
        void print();
        ndarray np_modify(ndarray&, ndarray&);
    private:
        int val;
        double dval;
};
