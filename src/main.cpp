#include <opencv2/opencv.hpp>


int lowHue = 0, lowSat = 0, lowVal = 0;
int hightHue = 179, hightSat = 255, hightVal = 255;

int main(){
    
    
    cv::VideoCapture cap;
    cap.open(2);
    cv::Mat frame;
    cv::Mat gray, blur, hsv;
    cv::Mat binary;
    
    cv::namedWindow("Camera");
    cv::createTrackbar("Low Hue", "Camera", &lowHue, 179);
    cv::createTrackbar("Low Sat", "Camera", &lowSat, 255);
    cv::createTrackbar("Low Val", "Camera", &lowSat, 255);
    cv::createTrackbar("Hight Hue", "Camera", &hightHue, 179);
    cv::createTrackbar("Hight Sat", "Camera", &hightSat, 255);
    cv::createTrackbar("Hoght Val", "Camera", &hightSat, 255);
    int key = -1;
    while(key != 27) {
        key = cv::waitKey(33);
        cap >> frame;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV); 
        //cv::threshold(gray, binary, 80, 150, cv::THRESH_BINARY);
        cv::inRange(hsv, cv::Scalar(lowHue, lowSat, lowVal), cv::Scalar(hightHue, hightSat, hightVal), binary);
        cv::Moments m = cv::moments(binary);
        double k = m.m00;
        double x_c = m.m10 / (k + 0.01);
        double y_c = m.m01 / (k + 0.01);
        cv::circle(frame, cv::Point(x_c, y_c), 50, cv::Scalar(255, 255, 0), 5); 
        
        cv::imshow("Camera", frame);
        cv::imshow("Binary", binary);
    }
    cv::destroyAllWindows();
    cap.release();
    return 0;
}