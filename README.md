此pcl库用于记录自己学习pcl库的过程。
＃pcd_txt.cpp是针对点云转换为二维的方案，可以简单高效的对点云进行处理，寻找特定边缘。
boundry.cpp用于寻找点云边界，基于法线方向。
DoN.cpp用于进行点云分割，类似于图像的高频低频，体现点云中变化快慢，以不同的k值估计
法线方向并比较法线差，若为平面，则基本为0，凹面则存在较大变化，因此可以用于分割地面与
物体
normals.cpp，normals_mls.cpp,normals_subset.cpp均为求法线，分别是全部，同一方向，
以及局部求法线。
