#include "ros/ros.h"
#include <sstream>
#include <pcl/PCLPointCloud2.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

const int frames = 10; //how many frames to combine

static int fcounter=0;
static pcl::PCLPointCloud2 pclarray[frames];
static sensor_msgs::PointCloud2 sum;

void chatterCallback(sensor_msgs::PointCloud2 msg)
{
  //convert sensor_msgs to pcl format
  pcl::PCLPointCloud2 pclmsg;
  pcl_conversions::toPCL(msg, pclmsg);

  if (fcounter == frames)
  {
    //store pcl msg using first in first out
    for (int i=0; i<=frames-2; i++)
      pclarray[i] = pclarray[i+1];
    pclarray[frames-1] = pclmsg;

    //accumulate pcl msg
    pcl::PCLPointCloud2 pclsum;
    for (int j=0; j<=frames-1; j++)
      pcl::concatenatePointCloud(pclsum, pclarray[j], pclsum);

    //convert pclsum into sensor_msgs
    pcl_conversions::fromPCL(pclsum, sum); //function replaces sum so no need to clear sum
  }

  else
  {
    pclarray[fcounter] = pclmsg;
    fcounter++;
  }
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"concat_pcl");
    ros::NodeHandle ns;
    ros::NodeHandle np;
    ros::Subscriber sub = ns.subscribe("/quad/camera_/depth/points", 1000, chatterCallback);
    ros::Publisher pub = np.advertise<sensor_msgs::PointCloud2>("/concatPclTopic",1000);
    ros::Rate loop_rate(100);
    while (ros::ok())
    {
      pub.publish(sum);
      ros::spinOnce();
      loop_rate.sleep();
    }
    return 0;
  }
