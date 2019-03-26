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
using namespace boost::python;
using namespace boost::python::numpy;
using namespace std;
using namespace cv;

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
        void mat_eigen_conversion(ndarray&, ndarray&, ndarray&, ndarray&, ndarray&);
    private:
        int val;
        double dval;
};
