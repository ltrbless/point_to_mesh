#include "Model.h"
#include <iostream>

using namespace std;

int main()
{

  // specify the positions of the points
  Eigen::Vector3d v1(0, 0, 0);
  Eigen::Vector3d v2(0, 1, 0);
  Eigen::Vector3d v3(1, 0, 0);
  vector<Eigen::Vector3d> points = {v1, v2, v3};

  // specify the indexes of endpoints, leave this vector empty if there are no segments
  vector<pair<int, int>> segments;

  // specify the indexes of vertices
  Eigen::Vector3i f1(0, 1, 2);
  vector<Eigen::Vector3i> faces = {f1};

  // see the note below for details
  double limit_cube_len = 1e3;

  // construction
  Model m(points, segments, faces, limit_cube_len);

  // perform a closest point query
  P2M_Result res;
  Eigen::Vector3d query_point(0, 0, 1);
  m.p2m(query_point, res);
  std::cout << res.dis << "\n";
}