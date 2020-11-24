#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <filesystem>



#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/videoio/videoio.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>

using namespace std; 
using namespace cv;


int main(int argc, char *argv[]){
    
    vector<string> fileName; /* */
    string path = "/home/alex/Documents/8vo/vision-artificial/practicas/parte-2/Icons-50/airplane";
    cv::glob(path, fileName, false);
    cout << fileName.size() << endl;
    for(int i =0; i < fileName.size(); i++){
        cout << fileName[i] << endl;
    }
    
    return 0;

}