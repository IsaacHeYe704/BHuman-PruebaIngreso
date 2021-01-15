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

MODULE(mSensor,
  {,
    REQUIRES(FieldDimensions),
    REQUIRES(BallModel),
    REQUIRES(TeamBallModel),
    REQUIRES(RobotPose),
    REQUIRES(TeamPlayersModel),
    PROVIDES(mSensorRepresentation),                   
    
  });
 
 
  class mSensor : public mSensorBase
  {
          
    void update(mSensorRepresentation& mSensorRepresentation);
    
  };
 

 

