#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include <boost/thread/thread.hpp>
#include <pcl/console/parse.h>
#include <iostream>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);

using namespace std;

//2 �����룺
int main()
{
    

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("don_cluster_0_1.pcd", *cloud);  //�����䲻������

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud(cloud);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    ne.setSearchMethod(tree);
    pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>());
    ne.setKSearch(20);  //Ӱ�취����׼ȷ�Ե���Ҫ���أ�
    //ne.setRadisuSearch(0.3);
    ne.compute(*cloud_normals); //�������ļ���

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));  //����һ��boost�������󣬲������ڴ�ռ�
    viewer->setBackgroundColor(0.0, 0, 0);
    // pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud); 
    //pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZ> rgb(cloud);
    pcl::visualization::PointCloudColorHandlerRandom<pcl::PointXYZ> v(cloud);  //�þ����˼�ǣ�������ĵ�����ɫ��Random��ʾ���������ɫ������������������Ⱦɫ�ʵķ�ʽ.
    //viewer->addPointCloud<pcl::PointXYZRGB>(cloud,visual,"sample cloud");
    viewer->addPointCloud<pcl::PointXYZ>(cloud, v, "sample cloud");

    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");//��Ⱦ���ԣ����ӻ����ߣ�3ά����
    viewer->addPointCloudNormals<pcl::PointXYZ, pcl::Normal>(cloud, cloud_normals, 10, 5, "normal"); //���У�����5��ʾ����������ÿ5������ʾһ������������ȫ����ʾ��������Ϊ1��  15��ʾ�������ĳ��ȣ����һ��������ʱ����֪�� ���Ӱ��ģ�
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();


    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
}



