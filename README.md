This package concatenates pointclouds received from the sensor.
It was created as the physical sensor on the drone sends frames at high frequency but does not pick up enough points in each frame.


The number of frames to combine can be adjusted under
const int frames = 10; //how many frames to combine

Edit the point_cloud_topic in sensors.yaml file of the sensor as
 point_cloud_topic: concatPclTopic

 Add
 <!-- rosrun concat_pcl -->
   <node name="concat_pcl" pkg="concat_pcl" type="concat_pcl"></node>
to the launch file 
