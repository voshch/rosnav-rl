#ifndef ROSNAV_CONFIG_H_
#define ROSNAV_CONFIG_H_

#include <ros/console.h>
#include <ros/ros.h>

#include <rosnav/RosnavLocalPlannerReconfigureConfig.h>


namespace rosnav
{

/**
 * @class RosnavConfig
 * @brief Config class for the rosnav_local_planner and its components.
 */
class RosnavConfig
{
  public:

    struct Robot
    {
      double max_vel_x; //!< Maximum translational velocity of the robot
      double max_vel_x_backwards; //!< Maximum translational velocity of the robot for driving backwards
      double max_vel_y; //!< Maximum strafing velocity of the robot (should be zero for non-holonomic robots!)
      double max_vel_trans; //!< Maximum translational velocity of the robot for omni robots, which is different from max_vel_x
      double max_vel_theta; //!< Maximum angular velocity of the robot
      bool use_proportional_saturation; //<! If true, reduce all twists components (linear x and y, and angular z) proportionally if any exceed its corresponding bounds, instead of saturating each one individually
    } robot; //!< Robot related parameters

    RosnavConfig() {
      robot.max_vel_x = 2.0;
      robot.max_vel_x_backwards = 2.0;
      robot.max_vel_y = 0.0;
      robot.max_vel_trans = 100.0;
      robot.max_vel_theta = 0.3;
      robot.use_proportional_saturation = false;
    };

    /**
     * @brief Load parmeters from the ros param server.
     * @param nh const reference to the local ros::NodeHandle
     */
    void loadRosParamFromNodeHandle(const ros::NodeHandle& nh);

    /**
     * @brief Reconfigure parameters from the dynamic_reconfigure config.
     * Change parameters dynamically (e.g. with <c>rosrun rqt_reconfigure rqt_reconfigure</c>).
     * A reconfigure server needs to be instantiated that calls this method in it's callback.
     * In case of the plugin \e rosnav_local_planner default values are defined
     * in \e PROJECT_SRC/cfg/RosnavLocalPlannerReconfigure.cfg.
     * @param cfg Config class autogenerated by dynamic_reconfigure according to the cfg-file mentioned above.
     */
    void reconfigure(RosnavLocalPlannerReconfigureConfig& cfg);

    /**
     * @brief Check parameters and print warnings in case of discrepancies
     *
     * Call this method whenever parameters are changed using public interfaces to inform the user
     * about some improper uses.
     */
    void checkParameters() const;

    /**
     * @brief Return the internal config mutex
     */
    boost::mutex& configMutex() {return config_mutex_;}

  private:
    boost::mutex config_mutex_; //!< Mutex for config accesses and changes
};


}

#endif