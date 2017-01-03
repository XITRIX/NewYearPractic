#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "List.h"
#include "Image.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv)
{
    Image img = *new Image(2,2);
    Image img2 = *new Image(img);
    img = img2;
    img.load("./pic.pgm");
    
    return 0;
}
