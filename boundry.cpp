#include <iostream>
#include <vector>
#include <ctime>
#include <boost/thread/thread.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/features/eigen.h>
#include <pcl/features/feature.h>
#include <pcl/features/normal_3d.h>
#include <pcl/impl/point_types.hpp>
#include <pcl/features/boundary.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/kdtree/kdtree_flann.h>
using namespace std;

int main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
   // pcl::io::loadPCDFile<pcl::PointXYZ>("point_pcd.pcd", *cloud);

    // if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/yxg/pcl/pcd/mid.pcd",*cloud) == -1)
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) == -1)
    {
        PCL_ERROR("COULD NOT READ FILE mid.pcl \n");
        return (-1);
    }

    std::cout << "points size is:" << cloud->size() << std::endl;
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::PointCloud<pcl::Boundary> boundaries;
    pcl::BoundaryEstimation<pcl::PointXYZ, pcl::Normal, pcl::Boundary> est;
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
    
    //pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;  //����һ������k���ڲ�ѯ,��ѯ��ʱ�����õ��ڵ����У����һ�����ڵ����䱾��
    //kdtree.setInputCloud(cloud);
    //int k =2;
    //float everagedistance =0;
    //for (int i =0; i < cloud->size()/2;i++)
    //{
    //        vector<int> nnh ;
    //        vector<float> squaredistance;
    //          pcl::PointXYZ p;
    //           p = cloud->points[i];
    //        kdtree.nearestKSearch(cloud->points[i],k,nnh,squaredistance);һ��k���������ڣ�˵��ֻ�ڸ������ڽ����������൱��ָ������
    //        everagedistance += sqrt(squaredistance[1]);
    //           cout<<everagedistance<<endl;
    //}
    //everagedistance = everagedistance/(cloud->size()/2);
    //cout<<"everage distance is : "<<everagedistance<<endl;





    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normEst;  //����pcl::PointXYZ��ʾ�����������ݣ�pcl::Normal��ʾ�������,��pcl::Normalǰ�����Ƿ������һ��������
    normEst.setInputCloud(cloud);
    normEst.setSearchMethod(tree);
    // normEst.setRadiusSearch(2);  //������Ƶİ뾶
    normEst.setKSearch(5);  //������Ƶĵ���
    normEst.compute(*normals);
    cout << "normal size is " << normals->size() << endl;

    //normal_est.setViewPoint(0,0,0); //���Ӧ�û�ʹ����һ��
    est.setInputCloud(cloud);
    est.setInputNormals(normals);
    //  est.setAngleThreshold(90);
    //   est.setSearchMethod (pcl::search::KdTree<pcl::PointXYZ>::Ptr (new pcl::search::KdTree<pcl::PointXYZ>));
    est.setSearchMethod(tree);
    est.setKSearch(20);  //һ���������ֵԽ�ߣ����ձ߽�ʶ��ľ���Խ��
    //  est.setRadiusSearch(everagedistance);  //�����뾶
    est.compute(boundaries);

    //  pcl::PointCloud<pcl::PointXYZ> boundPoints;
    pcl::PointCloud<pcl::PointXYZ>::Ptr boundPoints(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl::PointCloud<pcl::PointXYZ> noBoundPoints;
    int countBoundaries = 0;
    std::vector<int>indices;
    for (int i = 0; i < cloud->size(); i++) {
        uint8_t x = (boundaries.points[i].boundary_point);
        int a = static_cast<int>(x); //�ú����Ĺ�����ǿ������ת��
        if (a == 1)
        {
            //  boundPoints.push_back(cloud->points[i]);
            (*boundPoints).push_back(cloud->points[i]);
            indices.push_back(i);
            countBoundaries++;
        }
        /*else
            noBoundPoints.push_back(cloud->points[i]);*/

    }
    pcl::IndicesPtr index(new std::vector<int>(indices));
    //�ҵ��˱߽�
    std::cout << "boudary size is��" << countBoundaries << std::endl;
    //  pcl::io::savePCDFileASCII("boudary.pcd",boundPoints);
    //������������
    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
    kdtree.setInputCloud(cloud);//ֱ����index��ָ��cloud������
    int k = 2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_line(new pcl::PointCloud<pcl::PointXYZ>);
    for (int i = 0; i < indices.size(); i++) 
    {
        int index = indices[i];
        std::vector<int>nnh(k);
        std::vector<float> distances(k);
        kdtree.nearestKSearch(cloud->points[index], k, nnh, distances);
        if (distances[1] <= 0.5)
           (*cloud_line).push_back(cloud->points[nnh[1]]);//�õ��˱߽�㣬�ٻ�ͼ����
            //cout << " the distance is  " << distances[1] << endl;
    }



    //��ʾ�뱣��
    pcl::io::savePCDFileASCII("boudary1.pcd", *boundPoints);
    //pcl::io::savePCDFileASCII("NoBoundpoints.pcd", noBoundPoints);
    pcl::visualization::CloudViewer viewer("test");
    viewer.showCloud(boundPoints);
    while (!viewer.wasStopped())
    {
    }
    pcl::visualization::CloudViewer viewer1("test1");
    viewer1.showCloud(cloud_line);
    while (!viewer1.wasStopped())
    {
    }
    return 0;
}
