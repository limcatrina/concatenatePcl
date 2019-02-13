# concatenatePCL 

## Description
This ROS package concatenates X number of pointclouds received from the sensor where X is an integer that can be modified. 
It was created as the physical sensor on the drone sends frames at high frequency but does not pick up enough points in each frame. Messages from the sensor are combined using FIFO. 

Package is tested for Ubuntu 16.04, ROS-Kinetic 

## Setting up the Code 
### Editing the number of frames
The number of frames to combine can be adjusted in the concat_pcl.cpp file in the src folder. Search for the line below in the .cpp file. 
``
const int frames = 10; //how many frames to combine
``

### Editing the topics
Edit the subscriber topic in the concat_pcl.cpp file. The subscriber topic is the topic that the sensor is publishing on. 
Edit the point_cloud_topic in sensors.yaml file of the sensor to
```
 point_cloud_topic: concatPclTopic
```
### Running package
```
roscore
rosrun concat_pcl concat_pcl
```

### Launching package
Add the following lines below to the launch file
```
 <!-- rosrun concat_pcl -->
   <node name="concat_pcl" pkg="concat_pcl" type="concat_pcl"></node>
```
