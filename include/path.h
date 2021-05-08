#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <cstring>
#include <vector>

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>
#include <visualization_msgs/MarkerArray.h>

#include "node3d.h"
#include "constants.h"
#include "helper.h"

#include "tejas.h"
namespace HybridAStar {
/*!
   \brief A class for tracing and visualizing the path generated by the Planner
*/
class Path {
 public:
  /// The default constructor initializing the path object and setting publishers for the same.
  Path(bool smoothed = false) {
    std::string pathTopic = "/path";
    std::string pathNodesTopic = "/pathNodes";
    std::string pathVehicleTopic = "/pathVehicle";
    std::string pathPoseTopic = "/pathPose";

    if (smoothed) {
      pathTopic = "/sPath";
      pathNodesTopic = "/sPathNodes";
      pathVehicleTopic = "/sPathVehicle";
      this->smoothed = smoothed;
    }

    // _________________
    // TOPICS TO PUBLISH
    pubPath = n.advertise<nav_msgs::Path>(pathTopic, 1);
    pubPathNodes = n.advertise<visualization_msgs::MarkerArray>(pathNodesTopic, 1);
    pubPathVehicles = n.advertise<visualization_msgs::MarkerArray>(pathVehicleTopic, 1);
    pubPathPoses = n.advertise<geometry_msgs::PoseStamped>(pathPoseTopic, 1);

    // CONFIGURE THE CONTAINER
    path.header.frame_id = "path";
  }

  //  // __________
  //  // TRACE PATH
  //  /*!
  //     \brief Given a node pointer the path to the root node will be traced recursively
  //     \param node a 3D node, usually the goal node
  //     \param i a parameter for counting the number of nodes
  //  */
  //  void tracePath(const Node3D* node, int i = 0);
  /*!
     \brief Given a node pointer the path to the root node will be traced recursively
     \param node a 3D node, usually the goal node
     \param i a parameter for counting the number of nodes
  */
  void updatePath(const std::vector<Node3D> &nodePath);
  /*!
     \brief Adds a segment to the path
     \param node a 3D node
  */
  void addSegment(const Node3D& node);
  /*!
     \brief Adds a node to the path
     \param node a 3D node
     \param i a parameter for counting the number of nodes
  */
  void addNode(const Node3D& node, int i);
  /*!
     \brief Adds a vehicle shape to the path
     \param node a 3D node
     \param i a parameter for counting the number of nodes
  */
  void addVehicle(const Node3D& node, int i);

  // ______________
  // PUBLISH METHODS

  /// Clears the path
  void clear();
  /// Publishes the path
  void publishPath() { pubPath.publish(path); }
  /// Publishes the nodes of the path
  void publishPathNodes() { pubPathNodes.publish(pathNodes); }
  /// Publishes the vehicle along the path
  void publishPathVehicles() { pubPathVehicles.publish(pathVehicles); }

  void publishPathPoses() { pubPathPoses.publish(tejas);}

  geometry_msgs::PoseStamped pathPose;
  Tejas tejas;
 private:
  /// A handle to the ROS node
  ros::NodeHandle n;
  /// Publisher for the path as a spline
  ros::Publisher pubPath;

  ros::Publisher pubPathPoses;
  /// Publisher for the nodes on the path
  ros::Publisher pubPathNodes;
  /// Publisher for the vehicle along the path
  ros::Publisher pubPathVehicles;
  /// Path data structure for visualization
  nav_msgs::Path path;
  /// Nodes data structure for visualization
  visualization_msgs::MarkerArray pathNodes;
  /// Vehicle data structure for visualization
  visualization_msgs::MarkerArray pathVehicles;
  /// Value that indicates that the path is smoothed/post processed
  bool smoothed = false;
};
}
#endif // PATH_H
