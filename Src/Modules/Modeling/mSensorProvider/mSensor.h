/**
 * @file BallDropInLocator.h
 *
 * This file declares a module that computes the position where the ball is put after it goes out.
 *
 * @author Arne Hasselbring
 */

#pragma once


#include "Representations/Configuration/FieldDimensions.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/mSensorRepresentation.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/TeamPlayersModel.h"




#include "Tools/Module/Module.h"

#include<iostream>
#include<cstdlib>
#include<math.h>

// , TeamTalk, mSensorRepresentation, ActivationGraph, AlternativeRobotPoseHypothesis, ArmMotionRequest, BallDropInModel, BehaviorStatus, FieldBall, FieldCoverage, GlobalFieldCoverage, HeadAngleRequest, HeadMotionRequest, HulkFieldCoverage, LEDRequest, MotionRequest, ObstacleModel, PathPlanner, RobotPose, SelfLocalizationHypotheses
//Hypothesis
MODULE(mSensor,
  {,
    REQUIRES(FieldDimensions),
    REQUIRES(BallModel),
    REQUIRES(TeamBallModel),
    REQUIRES(RobotPose),
    REQUIRES(TeamPlayersModel),
    PROVIDES(mSensorRepresentation),                   // Class provides a method to update BallPercept.
    DEFINES_PARAMETERS(                      // Has parameters that must have an initial value. If LOADS_PARAMETERS is used instead,
    {,                                       // they are loaded from a configuration file that has the same name as the module defined, but starts with lowercase letters.
      (float)(42.0f) focalLen,               // Has a parameter named focalLen of type  it has float. By defaultthe value 42.0f.
      (int)(21) resWidth,                    // All attributes are streamed and can be accessed by requesting 'parameters:MyImageProcessor'
    }),
  });
 
 
  class mSensor : public mSensorBase
  {
          
    void update(mSensorRepresentation& mSensorRepresentation);
    
  };
 

 

