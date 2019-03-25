
#include "test.hpp"

void printmat3D(Mat_<float> image_mat, int row, int col, int depth){
    cout<<"c++ image converted to MAT_<float>"<<endl;
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

void printmat2D(Mat_<float> image_mat, int row, int col){
    cout<<"c++ image converted to MAT_<float>"<<endl;
    for (int i = 0; i<row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << image_mat(i, j) << " ";
        }
        cout << endl;
    }
}

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

    // get raw pointer of image and use it to construct mat
    float* image_pt = reinterpret_cast<float*>(image.get_data());

    // get them as a whole
    int size[3] = {2, 2, 3};
    Mat_<float> image_mat(3, size, image_pt);
    printmat3D(image_mat, row, col, depth);

    // get them per channel
    Range ranges[3] = {Range::all(), Range::all(), Range(0, 1)};
    printmat2D(image_mat(ranges), row, col);
    ranges[3] = {Range::all(), Range::all(), Range(1, 2)};
    printmat2D(image_mat(ranges), row, col);
    ranges[3] = {Range::all(), Range::all(), Range(2, 3)};
    printmat2D(image_mat(ranges), row, col);
//    vector<Mat_<float>> image_vector({channel1, channel2, channel3});
//    Mat image_merge;
//    merge(image_vector, image_merge); // this does not work properly TODO
//    printmat(image_merge, row, col, depth);
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
