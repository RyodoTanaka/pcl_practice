#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

#define WIDTH 5
#define HEIGHT 1

using namespace std;

int main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filterd (new pcl::PointCloud<pcl::PointXYZ>);
   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filterd_second (new pcl::PointCloud<pcl::PointXYZ>);

  // Fill in the random datas
  cloud->width = WIDTH;
  cloud->height = HEIGHT;
  cloud->points.resize(cloud->width * cloud->height);
  for(int i=0; i<cloud->points.size(); i++){
	cloud->points[i].x = 1024*rand()/(RAND_MAX + 1.0f);
	cloud->points[i].y = 1024*rand()/(RAND_MAX + 1.0f);
	cloud->points[i].z = 1024*rand()/(RAND_MAX + 1.0f);
  }
  
  cout << "Before Filtering" << endl;
  for(int i=0; i<cloud->points.size(); i++){
	cout << cloud->points[i].x << " "
		 << cloud->points[i].y << " "
		 << cloud->points[i].z << endl;
  }

  // Filtering
  // On z
  pcl::PassThrough<pcl::PointXYZ> pass_z;
  pass_z.setInputCloud(cloud);
  pass_z.setFilterFieldName("z");
  pass_z.setFilterLimits(0.0, 0.3);
  pass_z.setFilterLimitsNegative(false);
  pass_z.filter(*cloud_filterd);
  cout << "After Filtering Z" << endl;
  for(int i=0; i<cloud_filterd->points.size(); i++){
	cout << cloud_filterd->points[i].x << " "
		 << cloud_filterd->points[i].y << " "
		 << cloud_filterd->points[i].z << endl;
  }
  // On x
  pcl::PassThrough<pcl::PointXYZ> pass_x;
  pass_x.setInputCloud(cloud_filterd);
  pass_x.setFilterFieldName("x");
  pass_x.setFilterLimits(-0.3, 0.2);
  pass_x.setFilterLimitsNegative(false); // Limitの内(false)か外(true)か
  pass_x.filter(*cloud_filterd_second);

  cout << "After Filtering X" << endl;
  for(int i=0; i<cloud_filterd_second->points.size(); i++){
	cout << cloud_filterd_second->points[i].x << " "
		 << cloud_filterd_second->points[i].y << " "
		 << cloud_filterd_second->points[i].z << endl;
  }

  return 0; 
}
