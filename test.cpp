
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

void Foo::mat_eigen_conversion(ndarray& image){
    // get row and col
    int row = image.shape(0);
    int col = image.shape(1);
    int depth = image.shape(2);
    cout << "row: "<<row<<" col: "<<col<<" depth: "<<depth<<endl;
    // get raw pointer of image and use it to construct mat
    double* image_pt = reinterpret_cast<double*>(image.get_data());
    size_t size[3] = {6,3,1};
    Mat_<double> image_mat(row, col, image_pt, size);

    // print
    cout<<"c++ image converted to MAT_<double>"<<endl;
    for (int k=0; k<depth; ++k) {
        cout << "channel "<<k<<endl;
        for (int i = 0; i<row; ++i){
            for(int j=0; j<col; ++j){
                cout<<image_mat(i, j, k)<<" ";
            }
            cout << endl;
        }
    }
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
        .def("mat_eigen_conversion", &Foo::mat_eigen_conversion)
        .def("get_val", &Foo::get_val)
        .def("set_val", &Foo::set_val)
        .def("print", &Foo::print);
}
