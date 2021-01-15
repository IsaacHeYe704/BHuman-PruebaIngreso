/**
 * @file CodeReleaseKickAtGoalCard.cpp
 *
 * This file implements a basic striker behavior for the code release.
 * Normally, this would be decomposed into at least
 * - a ball search behavior card
 * - a skill for getting behind the ball
 *
 * @author Arne Hasselbring
 */

#include "Representations/BehaviorControl/FieldBall.h"
#include "Representations/BehaviorControl/Skills.h"
#include "Representations/Configuration/FieldDimensions.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Communication/TeamData.h"
#include "Tools/BehaviorControl/Framework/Card/Card.h"
#include "Tools/BehaviorControl/Framework/Card/CabslCard.h"
#include "Tools/Math/BHMath.h"

#include "Representations/Modeling/mSensorRepresentation.h"

#include<iostream>
#include<cstdlib>
#include<math.h>
CARD(CodeReleaseKickAtGoalCard,
{,
  CALLS(Activity),
  CALLS(InWalkKick),
  CALLS(LookForward),
  CALLS(Stand),
  CALLS(WalkAtRelativeSpeed),
  CALLS(WalkToTarget),
  REQUIRES(FieldBall),
  REQUIRES(FieldDimensions),
  REQUIRES(RobotPose),
  
  REQUIRES(mSensorRepresentation),
  REQUIRES(TeamData),
  
  DEFINES_PARAMETERS(
  {,
    (float)(0.8f) walkSpeed,
    (int)(1000) initialWaitTime,
    (int)(7000) ballNotSeenTimeout,
    (Angle)(5_deg) ballAlignThreshold,
    (float)(500.f) ballNearThreshold,
    (Angle)(10_deg) angleToGoalThreshold,
    (float)(400.f) ballAlignOffsetX,
    (float)(100.f) ballYThreshold,
    (Angle)(2_deg) angleToGoalThresholdPrecise,
    (float)(150.f) ballOffsetX,
    (Rangef)({140.f, 170.f}) ballOffsetXRange,
    (float)(40.f) ballOffsetY,
    (Rangef)({20.f, 50.f}) ballOffsetYRange,
    (int)(10) minKickWaitTime,
    (int)(3000) maxKickWaitTime,
    (int) (0) cantidadMediaRotacion,
  }),
});

class CodeReleaseKickAtGoalCard : public CodeReleaseKickAtGoalCardBase
{
    
  bool preconditions() const override
  {
    return true;
  }

  bool postconditions() const override
  {
    return true;
  }

  option
  {
    theActivitySkill(BehaviorStatus::codeReleaseKickAtGoal);

    initial_state(start)
    {
      transition
      {
        if(state_time > initialWaitTime)
            goto turnToBall;
//        if(theTeamData.teammates[0].shoulRotate == true)
//            goto darVueltita;
      }

      action
      {
        theLookForwardSkill();
        theStandSkill();
      }
    }
state(turnToBall)
    {
      transition
      {
//        if(!theFieldBall.ballWasSeen(ballNotSeenTimeout))
//          goto searchForBall;
        if( themSensorRepresentation.distance > 1200 )
          goto walkToBall;
      }

      action
      {
        theLookForwardSkill();
        theWalkToTargetSkill(Pose2f(walkSpeed, walkSpeed, walkSpeed), Pose2f(theFieldBall.positionRelative.angle(), 0.f, 0.f));
      }
    }
    

    state(walkToBall)
    {
      transition
      {
          const Angle angleToGoal = calcAngleToGoal();
//        if(!theFieldBall.ballWasSeen(ballNotSeenTimeout))
//          goto searchForBall;
        if(themSensorRepresentation.distance > 1200 )
          goto alignBehindBall;
          
//        if(theFieldBall.positionRelative.squaredNorm() < sqr(ballNearThreshold))
//          goto darVueltita;
      }

      action
      {
        theLookForwardSkill();
        theWalkToTargetSkill(Pose2f(walkSpeed, walkSpeed, walkSpeed), theFieldBall.positionRelative);
      }
    }

    state(darVueltita)
    {
      

      transition
      {
        const Angle angleToGoal = calcAngleToGoal();
        if(theFieldBall.ballWasSeen() &&  angleToGoal < 200 )
          goto start;
        if(theFieldBall.ballWasSeen() &&  angleToGoal > 180 )
          goto start;
      }

      action
      {
        theLookForwardSkill();
        theWalkAtRelativeSpeedSkill(Pose2f(walkSpeed, 0.f, 0.f));
      }
    }

    state(alignBehindBall)
    {
      const Angle angleToGoal = calcAngleToGoal();

      transition
      {
        /*if(!theFieldBall.ballWasSeen(ballNotSeenTimeout))
          goto searchForBall;*/
          if(themSensorRepresentation.mDistance)
            goto darVueltita;
      }

      action
      {
        theLookForwardSkill();
        theWalkToTargetSkill(Pose2f(walkSpeed, walkSpeed, walkSpeed), Pose2f(angleToGoal, theFieldBall.positionRelative.x() - ballOffsetX, theFieldBall.positionRelative.y() - ballOffsetY));
      
        }
    }

   

    state(searchForBall)
    {
      transition
      {
        if(theFieldBall.ballWasSeen())
          goto turnToBall;
      }

      action
      {
        theLookForwardSkill();
        theWalkAtRelativeSpeedSkill(Pose2f(walkSpeed, 0.f, 0.f));
      }
    }
  }

  Angle calcAngleToGoal() const
  {
      
       Angle angleToGoal =(theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle();
      if(angleToGoal < 0 )
        {
              angleToGoal = angleToGoal *-1;
        }
      
    return angleToGoal;
  }
};

MAKE_CARD(CodeReleaseKickAtGoalCard);
