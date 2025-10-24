#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

void drawing(Mat imgdil,Mat img,string text){

vector<vector<Point>>contours;
vector<Vec4i>hierachy;

findContours(imgdil,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);     //画轮廓
//drawContours(img,contours,-1,Scalar(0,69,255),2); 

vector<vector<Point>>conPoly(contours.size());
vector<Rect>boundRect(contours.size());

for(int i=0;i<contours.size();i++){  
           int area=contourArea(contours[i]);
            
        if(area>30000){
            float peri =arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.01*peri,true);
            boundRect[i]=boundingRect(conPoly[i]);
            int objCor =(int)conPoly[i].size();
            if (objCor>4){
            //drawContours(img,contours,i,Scalar(0,69,255),2); 
            rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(255,0,0),5);
            putText(img,text,{100,100}, FONT_HERSHEY_DUPLEX,3, Scalar(255,0,0), 2);
            }
            
        }



}

}




int main(){
        Scalar lower1(165,96,149);
        Scalar upper1(179,255,255);
        Scalar lower2(44,180,131);
        Scalar upper2(97,255,255);

string path="/home/ep/桌面/CV/TrafficLight.mp4";
    VideoCapture cap(path);

double fps_input = cap.get(CAP_PROP_FPS);
int fps=(fps_input > 0) ? fps_input : 30;  
int frame_width = cap.get(CAP_PROP_FRAME_WIDTH); 
int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);  
Size frame_size(frame_width, frame_height);

 
VideoWriter video1;
string filename="epepep.avi";
int fourcc = VideoWriter::fourcc('X','V','I','D');
video1.open(filename,fourcc,fps,frame_size,true);



   

    Mat img,img1,img2,img3,img4,imgred,imggreen,imgred1,imgred2;
    Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5));


    bool paused =false;
    while (true){
        if(!paused){
        cap.read(img);
        imshow("1",img);
        cvtColor(img,img1,COLOR_BGR2HSV);
        inRange(img1,lower1,upper1,imgred);
        inRange(img1,lower2,upper2,imggreen);
        //imshow("red",imgred);
        //imshow("green",imggreen);
        //bitwise_or(imgred,imggreen,img1);
        //imshow("hsv",img1);


        //red
        GaussianBlur(imgred,imgred,Size(5,5),5,5);
        Canny(imgred,imgred,50,150);
        dilate(imgred,imgred,kernel);

        drawing(imgred,img,"red");
        
        //green
        GaussianBlur(imggreen,imggreen,Size(5,5),5,5);
        Canny(imggreen,imggreen,50,150);
        dilate(imggreen,imggreen,kernel);

        drawing(imggreen,img,"green");
        
        imshow("2",img);
        video1.write(img);
        
        }
        int key=waitKey(30);
        if (key==32){
            paused=!paused;
        }
        else if(key==27){
            break;
        }
        
 
    }
    video1.release();
    cap.release();
}
