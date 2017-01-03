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
    
    
    List<Image> list = *new List<Image>;
    list.add(img);
    list.add(img2);
    
    Image img3 = *new Image(list.get(list.length()-1));
    cout << img3.gerMy() << endl;
    
    return 0;
}
