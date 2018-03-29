#ifndef VISION_BACKBOARD_FINDER_H_
#define VISION_BACKBOARD_FINDER_H_

#include "VisionProcess.h"

/**
 * @author jakey
 *
 * Task which updates information regarding distance, angle, and other vision-targeting information.
 */
class Logger;
class Constants;
class Drive;

class BackboardFinder : public VisionProcess {
 public:
  BackboardFinder();
  /**
   * The current distance offset from the target's center axis.
   * @return offset from target center
   */
  double GetX();

  double GetHDiff();
  double GetVDiff();

  /**
   * The current distance to the target.
   * @return distance to target
   */
  double GetDistance();

  /**
   * The angular difference between robot and center line of field
   * Helps orient target of angled shots
   * @return angle of robot on field relative to goal
   */
  double GetAngle();

  /**
   * Checks whether there is line-of-sight from the sensor to the target.
   * @return true if target appears in sensor, false otherwise.
   */
  bool SeesTarget();

  /**
   * Updates sensor information regarding target data.
   */
  void DoVision();

  /**
   * Is our tracking working
   * @return true if we have fresh data
   */
  bool HasFreshTarget();

  bool HasLock();


  /**
   * Logs camera information
   */
  void LogCamera();
  void SetUseSkew(bool useSkew);



 private:
  double x_;
  double distance_;
  double angle_;
  bool seesTarget_;
  double lastUpdate_;
  double width_;
  double vDiff_;
  Logger* cameraLog_;
  Constants* constants_;
  bool useTopForWidth_;
  Drive* drive_;
  double orientation_;
  bool useSkew_;
};

#endif  // VISION_BACKBOARD_FINDER_H_
