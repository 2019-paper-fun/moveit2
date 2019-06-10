/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, University of Colorado, Boulder
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Univ of CO, Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Wraps a trajectory_visualization playback class for Rviz into a stand alone display
*/

#ifndef MOVEIT_TRAJECTORY_RVIZ_PLUGIN__TRAJECTORY_DISPLAY
#define MOVEIT_TRAJECTORY_RVIZ_PLUGIN__TRAJECTORY_DISPLAY

#include <rviz_common/display.hpp>

#include <moveit/rviz_plugin_render_tools/trajectory_visualization.hpp>
#ifndef Q_MOC_RUN
#include <moveit/rdf_loader/rdf_loader.h>
#endif

namespace rviz_common
{
class StringProperty;
}

namespace moveit_rviz_plugin
{
class TrajectoryDisplay : public rviz_common::Display
{
  Q_OBJECT
  // friend class TrajectoryVisualization; // allow the visualization class to access the display

public:
  TrajectoryDisplay();

  ~TrajectoryDisplay() override;

  void loadRobotModel();

  void update(float wall_dt, float ros_dt) override;
  void reset() override;

  // overrides from Display
  void onInitialize() override;
  void onEnable() override;
  void onDisable() override;
  //void setName(const QString& name) override;

  rclcpp::Node::SharedPtr node_;
  const std::string NODE_NAME = "trajectory_display";  // name of node

private Q_SLOTS:
  /**
   * \brief Slot Event Functions
   */
  void changedRobotDescription();

protected:
  // The trajectory playback component
  TrajectoryVisualizationPtr trajectory_visual_;

  // Load robot model
  rdf_loader::RDFLoaderPtr rdf_loader_;
  robot_model::RobotModelConstPtr robot_model_;
  robot_state::RobotStatePtr robot_state_;
  bool load_robot_model_;  // for delayed robot initialization

  // Properties
  rviz_common::properties::StringProperty* robot_description_property_;
};

}  // namespace moveit_rviz_plugin

#endif
