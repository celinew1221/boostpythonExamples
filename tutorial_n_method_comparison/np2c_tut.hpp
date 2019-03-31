#include <iostream>
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/Geometry"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/eigen.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace boost::python;
using namespace boost::python::numpy;
using namespace std;
using namespace cv;
using namespace std::chrono;

void printmat3D(Mat_<float>, int, int, int);
void printmat3D(vector<Mat>, int, int, int);
void printmat3D(Mat, int, int, int);
void printmat2D(Mat, int, int);

class Foo
{
    public:
        Foo(int, double);
        void add(int);
        int get_val();
        void set_val(int);
        void print();
        ndarray np_modify(ndarray&);
        void mat_conversion(ndarray&, ndarray&, ndarray&, ndarray&, ndarray&);
        void channel_conversion_from_non_contin(ndarray&, ndarray&, ndarray&);
        void channel_conversion_from_cont(ndarray&);
        void channel_conversion_from_split(ndarray&);
        void channel_conversion_from_copy(ndarray& image);
        private:
        int val;
        double dval;
};
