//open the Gocator camera, get one snapshot, visualize it, and wait for "q" to close

//PCL visualiser
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>

//Gocator3100 Lib
#include "../gocator3100.h"

//constants
#define SENSOR_IP "192.168.1.10"

//main
int main(int argc, char **argv)
{
	//gocator camera
	Gocator3100::Device camera(SENSOR_IP);

	//configure camera (exposure and spacing)
	Gocator3100::CaptureParams capture_params;
	capture_params.exposure_time_ = 20000; //useconds
	capture_params.spacing_interval_ = 0.1; //mm
	camera.configure(capture_params);

	//point cloud
	pcl::PointCloud<pcl::PointXYZ>::Ptr p_cloud_(new pcl::PointCloud<pcl::PointXYZ>());

	//visualization window
	pcl::visualization::PCLVisualizer viewer_("Gocator3109 Snapshot");
	while(1)
	{
		//get a single snapshot in this thread
		camera.getSingleSnapshot(*p_cloud_);
		// pcl::io::savePCDFileASCII("PointCloudGpcator.pcd",*p_cloud_);
		// pcl::io::savePLYFileASCII("PointCloudGpcator.ply",*p_cloud_);

		//Just check point cloud dimensions
		//std::cout << "p_cloud_ size is: " << p_cloud_->width << std::endl;

		//visualization starts here
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> p_cloud_color_handler(p_cloud_, 255, 255, 255);
		viewer_.removePointCloud("snapshot");
		viewer_.addPointCloud (p_cloud_, p_cloud_color_handler, "snapshot");
		viewer_.addCoordinateSystem (0.10, 0);
		viewer_.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
		viewer_.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "snapshot");
		viewer_.setPosition(300,200); // Setting visualiser window position
		viewer_.spinOnce (1000);
}
	//bye
return 1;
}