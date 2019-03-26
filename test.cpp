
#include "test.hpp"

void printmat3D(Mat image_mat, int row, int col, int depth){
    for (int k=0; k<depth; ++k) {
        cout << "channel "<<k<<endl;
        for (int i = 0; i<row; ++i){
            for(int j=0; j<col; ++j){
                cout<<image_mat.at<Vec3f>(i, j)[k]<<" ";
            }
            cout << endl;
        }
    }
}

void printmat2D(Mat image_mat, int row, int col){
    for (int i = 0; i<row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << image_mat.at<float>(i, j) << " ";
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
    result_pt[0] = 2000;    // this will change original result_pt therefore result in python

    return data_belong2c_np;
}

void Foo::mat_eigen_conversion(ndarray& image, ndarray& ch1, ndarray& ch2, ndarray& ch3, ndarray& warp){
    // get row and col
    int row = image.shape(0);
    int col = image.shape(1);
    int depth = image.shape(2);

    // get raw pointer of image and use it to construct mat
    float* image_pt = reinterpret_cast<float*>(image.get_data());
    float* warp_pt = reinterpret_cast<float*>(warp.get_data());

    // get them as a whole
    cout << "directly convert image to 3D Mat" <<endl;
    int size[3] = {row, col, depth};
    Mat image_mat(row, col, CV_32FC3, image_pt);
    Mat warp_mat(row, col, CV_32FC3, warp_pt);
    printmat3D(image_mat, row, col, depth);

    // get them per channel
    cout << "convert each channel to 2D Mat and its first element to 1000.\nNote this will also change the numpy array" << endl;
    float* ch1_pt = reinterpret_cast<float*>(ch1.get_data());
    float* ch2_pt = reinterpret_cast<float*>(ch2.get_data());
    float* ch3_pt = reinterpret_cast<float*>(ch3.get_data());
    Mat ch1_mat(row, col, CV_32FC1, ch1_pt);
    Mat ch2_mat(row, col, CV_32FC1, ch2_pt);
    Mat ch3_mat(row, col, CV_32FC1, ch3_pt);
    ch1_mat.at<Vec3f>(0,0)[0] = 1000;
    printmat2D(ch1_mat, row, col);
    printmat2D(ch2_mat, row, col);
    printmat2D(ch3_mat, row, col);

    // merge
    cout << "Merge the 2D channels into the warp numpy array passed into this function. Note this will change the numpy warp array" << endl;
    vector<Mat> before_merge = {ch1_mat, ch2_mat, ch3_mat};
    merge(before_merge, warp_mat);
    printmat3D(warp_mat, row, col, depth);
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
