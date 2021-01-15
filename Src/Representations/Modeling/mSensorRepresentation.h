/**
 * @file BallModel.h
 *
 * Declaration of struct BallModel
 *
 * @author <A href="mailto:tlaue@uni-bremen.de">Tim Laue</A>
 */

#pragma once

#include "Tools/Streams/AutoStreamable.h"
#include "Representations/Communication/BHumanTeamMessageParts/BHumanMessageParticle.h"
//#include "Representations/Communication/BHumanMessage.h"
#include "Representations/Communication/BHumanTeamMessageParts/BHumanStandardMessage.h"

STREAMABLE(mSensorRepresentation, COMMA public BHumanMessageParticle<idmSensorRepresentation>
{
    void operator>>(BHumanMessage& m) const override;
   void operator<<(const BHumanMessage& m) override  ,
	(bool)(false) mDistance,
    (float)(0) distance,
    
});

inline void mSensorRepresentation::operator>>(BHumanMessage& m) const
{
  m.theBHumanStandardMessage.mDistance = mDistance;                               
  m.theBHumanStandardMessage.distance = distance;
}

inline void mSensorRepresentation::operator<<(const BHumanMessage& m)
{
  if(m.hasBHumanParts)
  {
    mDistance = (bool) m.theBHumanStandardMessage.mDistance;
    distance = (float)m.theBHumanStandardMessage.distance;
  }else
  {
      mDistance = false;
      distance = 0;
  }
}


//STREAMABLE(mSensorRepresentation,
//{
// ,
//	(bool)(false) mDistance,
//    (float)(0) distance,
//    (Pose2f) myPose,
//    (Angle) angeltoGoal,
//    (int) distanciaOtro,
//});



