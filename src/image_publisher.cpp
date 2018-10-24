#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include<vector>
#include <dirent.h>
#include<string>

#include<algorithm>



int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  
/////////////////////////////////////////////////////////////////
  DIR *dir;
  struct dirent *ent;
  printf("\n  entering \n");
  std::vector<std::string> ss;
  if ((dir = opendir ("/home/prakveer/Desktop/online_photometric_calibration/sequence_30/images/") )!= NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      //printf ("%s\n", ent->d_name);
      ss.push_back(ent->d_name);
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
    
    sort(ss.begin(), ss.end());
   //cv::Mat image1;
  // std::string d ="/home/prakveer/Desktop/online_photometric_calibration/sequence_30/images/";
  // for(int i =0; i<ss.size(); i++){
      
  //     d.append(ss[i]);
  //     std::cout<<d<<"\n";
  //     image1 = cv::imread(d, CV_LOAD_IMAGE_GRAYSCALE);

  //     if(image1.empty())
  //       std::cout<<" FAILED "<<std::endl;

  //     d ="/home/prakveer/Desktop/online_photometric_calibration/sequence_30/images/";
  // }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

  ros::Rate loop_rate(5);
  int i=0;
  cv::Mat image2;
  std::string d2 ="/home/prakveer/Desktop/online_photometric_calibration/sequence_30/images/";
  sensor_msgs::ImagePtr msg;

  while ((nh.ok()) && (i < ss.size()-2)) {

    d2 ="/home/prakveer/Desktop/online_photometric_calibration/sequence_30/images/";
    d2.append(ss[i+2]);
    image2 = cv::imread(d2, CV_LOAD_IMAGE_GRAYSCALE);
    //cv::Size m_img_new_size(640, 480);
    //cv::resize(image2, image2, m_img_new_size);

    if(image2.empty())
      std::cout<<" FAILED "<<std::endl;
    else{
      msg = cv_bridge::CvImage(std_msgs::Header(), "mono8", image2).toImageMsg();
      pub.publish(msg);
    }

    i++;

    ros::spinOnce();
    std::cout<<d2<<"\n";
    std::cout<<" i "<<i<<std::endl;
    loop_rate.sleep();
  }

  std::cout<<" I'M DONE ";
  return 0;

}