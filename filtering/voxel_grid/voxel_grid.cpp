#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
  viewer.setBackgroundColor(0, 0, 0);
  //pcl::PointXYZ o;
  //o.x = 1.0;
  //o.y = 0;
  //o.z = 0;
  // viewer.addSphere(o, 0.25, "sphere", 0);
  cout << "I only run once" << endl;
}

// void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
// {
//   static unsigned count = 0;
//   stringstream ss;
//   ss << "Once per viewer loop" << count++;
//   viewer.removeShape("text", 0);
//   viewer.addText(ss.str(), 200, 300, "text", 0);
// }


int main (int argc, char** argv)
{
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());
  
  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("../data/table_scene_lms400.pcd", *cloud); // Remember to download the file first!

  std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
			<< " data points (" << pcl::getFieldsList (*cloud) << ").";

  // Create the filtering object
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.01f, 0.01f, 0.01f);
  sor.filter (*cloud_filtered);

  std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height 
			<< " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";

  pcl::PCDWriter writer;
  writer.write ("../data/table_scene_lms400_downsampled.pcd", *cloud_filtered, 
				Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false); 

  return (0);
}
