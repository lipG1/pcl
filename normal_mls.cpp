#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <pcl/console/time.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h> //�����������ӻ���
#include <boost/thread/thread.hpp>
#include <pcl/point_cloud.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);

using namespace std;
typedef pcl::PointXYZ point;
typedef pcl::PointCloud<point> pointcloud;



int main(int argc, char** argv)
{
    pointcloud::Ptr cloud(new pointcloud);
    pcl::io::loadPCDFile(argv[1], *cloud);
    cout << "points size is:" << cloud->size() << endl;
    pcl::search::KdTree<point>::Ptr tree(new pcl::search::KdTree<point>);

    //�����洢��mls����
    pcl::PointCloud<pcl::PointNormal> mls_points;
    //   pcl::PointCloud<point> mls_points;

    //����mls����
    pcl::MovingLeastSquares<point, pcl::PointNormal> mls;

    //   pcl::MovingLeastSquares<point,point> mls;

    mls.setComputeNormals(true);
    mls.setInputCloud(cloud);
    mls.setPolynomialFit(true); //����Ϊtrue����ƽ�������в��ö���ʽ�������߾���
    mls.setPolynomialOrder(2); //MLS��ϵĽ�����Ĭ����2
    mls.setSearchMethod(tree);
    mls.setSearchRadius(5.1);  //�����뾶

    mls.process(mls_points);
    pcl::PointCloud<pcl::PointNormal>::Ptr mls_points_normal(new pcl::PointCloud<pcl::PointNormal>);
    mls_points_normal = mls_points.makeShared();

    cout << "mls poits size is: " << mls_points.size() << endl;


    boost::shared_ptr<pcl::visualization::PCLVisualizer> view(new pcl::visualization::PCLVisualizer("test"));
    view->setBackgroundColor(0.0, 0, 0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointNormal> v(mls_points_normal, 0, 250, 0);
    view->addPointCloud<pcl::PointNormal>(mls_points_normal, v, "sample");
    view->addPointCloudNormals<pcl::PointNormal>(mls_points_normal, 10, 10, "normal");
    view->addCoordinateSystem(1.0); //�����ռ�ֱ������ϵ
    view->spin();


    // Save output
    pcl::io::savePCDFile("mid-mls.pcd", mls_points);

}
