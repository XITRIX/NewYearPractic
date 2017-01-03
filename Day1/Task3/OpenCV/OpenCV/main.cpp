 #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "List.h"
#include "Image.h"

using namespace cv;
using namespace std;

void transparenRect(Mat image,int x,int y,int w,int h,Scalar clr) {
    Mat roi = image(Rect(x, y, w, h));
    Mat color(roi.size(), CV_8UC3, clr);
    double alpha = 0.3;
    addWeighted(color, alpha, roi, 1.0 - alpha , 0.0, roi);
}

int main( int argc, char** argv)
{
    char trackbarWindow[] = "Trackbar";
    
    int min = 0, max = 1000;
    int hmin = 100, smin = 100, vmin = 100,
    hmax = 200, smax = 200, vmax = 200;
    
    namedWindow("Threshold", 0);
    /*namedWindow(trackbarWindow, 0);
    
    createTrackbar("H min:", trackbarWindow, &hmin, hmax);
    createTrackbar("H max:", trackbarWindow, &hmax, hmax);
    createTrackbar("S min:", trackbarWindow, &smin, smax);
    createTrackbar("S max:", trackbarWindow, &smax, smax);
    createTrackbar("V min:", trackbarWindow, &vmin, vmax);
    createTrackbar("V max:", trackbarWindow, &vmax, vmax);
    createTrackbar("Size min:", trackbarWindow, &min, max);
    createTrackbar("Size max:", trackbarWindow, &max, max);*/
    
    /*VideoCapture capture;
    capture.open(0);
    if(!capture.isOpened()){
        cout << "Камера не может быть открыта." << endl;
        exit(1);
    }*/
    
    Mat threshold, HSV, blurred, layered;
    
    List<Mat> playerTiles = *new List<Mat>;
    playerTiles.add(imread("./189.png"));
    playerTiles.add(imread("./190.png"));
    playerTiles.add(imread("./191.png"));
    playerTiles.add(imread("./190.png"));
    
    int i = 0;
    for (;;){
        Mat background = imread("./image_one_sticker.jpg");
        resize(background, background, *new Size(800,700));
        Mat M = playerTiles.get(i++);
        i %= playerTiles.length();
        //capture >> background;
        cvtColor(background, HSV, COLOR_BGR2HSV);
        medianBlur(HSV, blurred, 21);
        inRange(blurred, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), threshold);
        layered = background;
        Rect r;
        for(int y = 0; y < threshold.rows; y++){
            for(int x = 0; x < threshold.cols; x++){
                int value = threshold.at<uchar>(y, x);
                if(value == 255){
                    Rect rect;
                    floodFill(threshold, Point(x, y), Scalar(200), &rect);
                    if(rect.width >= min && rect.width <= max && rect.height >= min && rect.height <= max){
                        //rectangle(background, rect, Scalar(255, 0, 255, 4));
                        resize(M, M, *new Size(rect.width,rect.height));
                        M.copyTo(layered(rect));
                        r = rect;
                    }
                }
            }
        }
        
        //imshow("pl", M);
        imshow("pic", layered);
        //imshow("Threshold", threshold);
        waitKey(30);
    }
    
    //Mat tmp_img(background.size(),CV_8U);
    
    
    
    //waitKey(0);
    
    return 0;
}
