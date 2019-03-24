
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

ndarray Foo::np_modify(ndarray& result){
    //double data_belong2c[10]; try this to see what happen
    double* data_belong2c = new double[10]; // need to dynamically allocate, or c++ will destroy this after return
    for (int i = 0; i<10; ++i){data_belong2c[i] = i;}

    ndarray data_belong2c_np = from_data(data_belong2c, dtype::get_builtin<double>(), boost::python::make_tuple(10),
                                         boost::python::make_tuple(sizeof(double)), boost::python::object());

    double* result_pt = reinterpret_cast<double*>(result.get_data());
    result_pt[0] = 2000;    // this will change original result_pt

    return data_belong2c_np;
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
