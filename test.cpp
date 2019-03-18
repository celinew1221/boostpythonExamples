
#include "test.hpp"

/* Real C++ code */
Foo::Foo(int n, double x)
{
    val = n;
    dval = x;
}

void Foo::add(int n)
{
    cout<< val + n<<endl;
}

ndarray Foo::np_modify(object& p1, object& p2){
    ndarray nparray = extract<ndarray>(p1);
    ndarray nparray2 = extract<ndarray>(p2);

    cout << extract<char const *>(str(nparray)) <<endl;
    double* data_pt = reinterpret_cast<double*>(nparray.get_data());

    for (int i = 0; i < 20; ++i){
            cout << data_pt[i] << endl;
    }
    return nparray;
}

int Foo::get_val()
{
    return val;
}

void Foo::set_val(int _val){
    val = _val;
}

void Foo::print(){
    cout<<"val: "<<val<<" dval: "<<dval<<endl;
}

/* boost python wrapper */
BOOST_PYTHON_MODULE(myfoo)
{
    Py_Initialize();
    boost::python::numpy::initialize();
    class_<Foo>("Foo", init<int, double>())
        .def("add", &Foo::add)
        .def("np_modify", &Foo::np_modify)
        .def("get_val", &Foo::get_val)
        .def("set_val", &Foo::set_val)
        .def("print", &Foo::print);
}
