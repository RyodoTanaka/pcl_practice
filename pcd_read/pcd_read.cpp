#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
  viewer.setBackgroundColor(0, 0, 0);
  pcl::PointXYZ o;
  o.x = 1.0;
  o.y = 0;
  o.z = 0;
  viewer.addSphere(o, 0.25, "sphere", 0);
  cout << "I only run once" << endl;
}

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
  static unsigned count = 0;
  stringstream ss;
  ss << "Once per viewer loop" << count++;
  viewer.removeShape("text", 0);
  viewer.addText(ss.str(), 200, 300, "text", 0);
}


int main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

  if (pcl::io::loadPCDFile("../../data/robot/raw_0.pcd", *cloud) == -1) //* load the file
	{
	  PCL_ERROR ("Couldn't read file raw_0.pcd \n");
	  return (-1);
	}
  std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;

  // init of pcl viewer
  pcl::visualization::CloudViewer viewer("Cloud Viewer");

  // blocks until the cloud is actually rendered
  viewer.showCloud(cloud);

  //use the following functions to get access to the underlying more advanced/powerful
  //PCLVisualizer
    
  //This will only get called once
  viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
  //This will get called once per visualization iteration
  viewer.runOnVisualizationThread (viewerPsycho);
  while (!viewer.wasStopped ())
    {
	  //you can also do cool processing here
	  //FIXME: Note that this is running in a separate thread from viewerPsycho
	  //and you should guard against race conditions yourself...
	  //user_data++;
    }
  return 0;
  
  
  // access point cloud datas directory
  // or (size_t i = 0; i < cloud->points.size (); ++i)
  //  std::cout << "    " << cloud->points[i].x
  //            << " "    << cloud->points[i].y
  //            << " "    << cloud->points[i].z << std::endl;
}
