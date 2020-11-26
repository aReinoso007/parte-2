#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>

#include <dirent.h>

#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/videoio/videoio.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>

#include <math.h>


using namespace std;
using namespace cv;

class Clasification{
    private:
        /* data */
        std::vector<std::string> test_books;
        std::vector<std::string> train_books;

        std::vector<std::string> test_planes;
        vector<string> train_planes;

        std::vector<std::string> test_balls;
        std::vector<std::string> train_balls;


        Mat b_hist;
        Mat g_hist;
        Mat r_hist;

        double euclideanDistance(Mat,Mat);
        void test_train(vector<string> , vector<string>, vector<string>);
        Mat histograma(Mat, int);
        void cargarImages();
        double distancia(Mat , vector<string> );

    public:
        
        void clasificar();

        void prueba();


};






