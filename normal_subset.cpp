#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include<pcl/pcl_base.h>
#include<pcl/visualization/pcl_visualizer.h>
#include<pcl/io/pcd_io.h>
#include<pcl/filters/voxel_grid.h>
#include<pcl/filters/extract_indices.h>
#include<pcl/point_types.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
using namespace std;
int main()
{
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::io::loadPCDFile("point_pcd.pcd", *cloud);
//�²���
pcl::VoxelGrid<pcl::PointXYZ> vg;
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
vg.setInputCloud(cloud);
vg.setLeafSize(1.1f, 1.1f, 1.1f);//���ܴ���ֵ̫Сû�����²��������⣬����0.01f
vg.filter(*cloud_filtered);
std::cout << "PointCloud after filtering has: " << cloud_filtered->points.size() << " data points." << std::endl; //*
//����
cout << "Downsampling cloud's size is " << cloud_filtered->points.size() << endl;
stringstream ss;
ss << "downsampling cloud.pcd";
pcl::PCDWriter writer;
writer.write<pcl::PointXYZ>(ss.str(), *cloud_filtered, false);
//... read, pass in or create a point cloud ...

// Create a set of indices to be used. For simplicity, we're going to be using the first 10% of the points in cloud
std::vector<int> indices(std::floor(cloud_filtered->points.size() / 10));
//��ȡ����������
for (std::size_t i = 0; i < indices.size(); ++i) indices[i] = i;//�����ȶ��������ж��壬�����ֻ�г�ʼֵ��
pcl::IndicesPtr indicesptr(new std::vector<int>(indices));
pcl::ExtractIndices<pcl::PointXYZ> extract;
extract.setInputCloud(cloud_filtered);
extract.setIndices(indicesptr);
extract.setNegative(false);//�����Ϊtrue,������ȡָ��index֮��ĵ���
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_extract(new pcl::PointCloud<pcl::PointXYZ>);
extract.filter(*cloud_extract);
// Create the normal estimation class, and pass the input dataset to it
pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
ne.setInputCloud(cloud_filtered);

// Pass the indices
//pcl:: shared_ptr<std::vector<int>> indicesptr(new std::vector<int>(indices));
//pcl::IndicesPtr indicesptr(new std::vector<int>(indices));
ne.setIndices(indicesptr);


// Create an empty kdtree representation, and pass it to the normal estimation object.
// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
ne.setSearchMethod(tree);

// Output datasets
pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);

// Use all neighbors in a sphere of radius 3cm
ne.setRadiusSearch(5.5);
//ne.setKSearch(3);

// Compute the features
ne.compute(*cloud_normals);

// cloud_normals->points.size () should have the same size as the input indicesptr->size ()
boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));  //����һ��boost�������󣬲������ڴ�ռ�
viewer->setBackgroundColor(0, 0, 0);
// pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud); 
//pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZ> rgb(cloud);
pcl::visualization::PointCloudColorHandlerRandom<pcl::PointXYZ> v(cloud_filtered);  //�þ����˼�ǣ�������ĵ�����ɫ��Random��ʾ���������ɫ������������������Ⱦɫ�ʵķ�ʽ.
//viewer->addPointCloud<pcl::PointXYZRGB>(cloud,visual,"sample cloud");
viewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, v, "sample cloud");

viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");//��Ⱦ���ԣ����ӻ����ߣ�3ά����
viewer->addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud_extract, cloud_normals, 2,15, "normal"); //���У�����5��ʾ����������ÿ5������ʾһ������������ȫ����ʾ��������Ϊ1��  15��ʾ�������ĳ��ȣ����һ��������ʱ����֪�� ���Ӱ��ģ�
viewer->addCoordinateSystem(1.0);
viewer->initCameraParameters();


while (!viewer->wasStopped())
{
    viewer->spinOnce(100);
    boost::this_thread::sleep(boost::posix_time::microseconds(100000));
}
}
