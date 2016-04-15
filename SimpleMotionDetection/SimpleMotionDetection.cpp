#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <unistd.h>

using namespace cv;
using namespace std;


static void help(char** av)
{
    cout << endl
        << av[0] << " shows the usage of the OpenCV serialization functionality."         << endl
        << "usage: "                                                                      << endl
        <<  av[0] << " stringvideoFile "                                                 << endl;
}

double simpleHash(Mat& I)
{
    double res;
	res = 0;
	int cnt = 0;
	uchar prev = 0x00;

    // accept only char type matrices
//    CV_Assert(I.depth() == CV_8U);
	cout<<"CV_8U="<<CV_8U<<endl;

    const int channels = I.channels();
	cout<<"depth="<< I.depth()<<endl;
	cout<<"channels="<<channels<<endl;

    switch(channels)
    {
    case 1:
        {

            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
		{

		if (static_cast<unsigned>(*it) > 100){
			++cnt;
        	      res = (res + static_cast<unsigned>(*it));  
		}
		
//		cout<<"sum="<<res<<endl;
		
		prev = max(*it, prev);

//		cout<<"point_value="<< static_cast<unsigned>(*it)<<endl;
		}
              res = res/cnt;
		cout.precision(3);		
//		cout<<"sum="<<res<<endl;
		cout<<"cnt="<<cnt<<endl;


		cout<<"max_point_value="<< static_cast<unsigned>(prev)<<endl;

            break;
        }
    
    }

return cnt;    
}



int main(int ac, char** av)
{

if (ac != 2)
    {
        help(av);
        return 1;
    }

    int erosion_size=5;
    Mat frame1,frame2;
    Mat grayImage1,grayImage2;
    Mat differnceImage;
    Mat thresholdImage;
    int static_frames_cnt=0;
    double hash;
   double prev_hash =0;
   double fps;
	int frame_cnt = 0;
	bool static_frame_marked;
	char file[255];

    namedWindow("Webcam Video");

   //default webcam device id=0;

    //check if the webcam was opened properly
    Mat element = getStructuringElement( MORPH_RECT,Size( 2*erosion_size + 1, 2*erosion_size+1 ),Point( erosion_size, erosion_size ) );

    VideoCapture cap(av[1]);
	 fps = cap.get(CV_CAP_PROP_FPS);

	cout << "Frames per second using video.get(CV_CAP_PROP_FPS) : " << fps << endl;


    while (1)
    {

        //  cap.open(0);
         if(!cap.isOpened())
         {
             cout<<"Webcam can't be opened"<<endl;
             getchar();
             return -1;
         }

            cap.read(frame1);
		++frame_cnt;
            cvtColor(frame1,grayImage1,CV_RGB2GRAY);

            cap.read(frame2);
		++frame_cnt;
            cvtColor(frame2,grayImage2,CV_RGB2GRAY);

		absdiff(grayImage1,grayImage2,differnceImage);
		hash = simpleHash(differnceImage);
	
		cout<<"fps="<< fps<<endl;
		cout<<"hash="<< hash<<endl;
		if (hash<5 && prev_hash<5)
		{
			//detect static during 2 sec
			if (++static_frames_cnt > fps * 0.5){
				if (static_frame_marked==false){
				static_frame_marked = true;
				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;

				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;
				cout<<"detect static"<<endl;
 vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

	sprintf (file, "./frames_selected/alpha%d.png", frame_cnt);
        imwrite( file, frame1, compression_params);


				}
						//++static_frames_cnt
			}
		} else {
			static_frames_cnt = 0;
			static_frame_marked = false;
		}

//           threshold(differnceImage,thresholdImage,5,255,CV_THRESH_BINARY);

  //          blur(thresholdImage,thresholdImage,Size(30,30));
             
//             threshold(differnceImage,thresholdImage,5,255,CV_THRESH_BINARY);

 //         erode(thresholdImage,thresholdImage,element,Point(-1,-1));

           threshold(differnceImage,thresholdImage,20,255,CV_THRESH_BINARY);
		cv::erode(thresholdImage, thresholdImage, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));



             imshow("Theshold",thresholdImage);

             imshow("absDiff",differnceImage);

           imshow("Webcam Video",frame1);
	prev_hash = hash;
//	usleep(100000);

		//cout<< (double)ret<<endl;
           switch(waitKey(10))
           {
           case 27:
               return -1;
               break;

           }


   }

}

