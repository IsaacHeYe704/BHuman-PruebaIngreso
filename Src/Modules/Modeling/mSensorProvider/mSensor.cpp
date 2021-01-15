#include "mSensor.h"
MAKE_MODULE(mSensor, modeling)





void mSensor::update(mSensorRepresentation& mSensorRepresentation)
{
    float xDistance = 0;
    float yDistance = 0;
    

//here i will  set the distance to the ball
//if the robot is seing the ball he will do it with his information
    if(theBallModel.seenPercentage > 0)
    {
        xDistance = abs(theBallModel.lastPerception.x());
        yDistance = abs(theBallModel.lastPerception.y());
        mSensorRepresentation.distance =  (float) sqrt((xDistance*xDistance) + (yDistance*yDistance));

    }else  //if he is not seing the ball he will try to get its position by the teamInfo
    {
        xDistance = abs(theRobotPose.translation.x())-abs(theTeamBallModel.position.x());
        yDistance = abs(theRobotPose.translation.y())-abs(theTeamBallModel.position.y());
        mSensorRepresentation.distance =  (float) sqrt((xDistance*xDistance) + (yDistance*yDistance)) - 1000;
    }
    
    
    
    if(mSensorRepresentation.distance < 1000  && mSensorRepresentation.distance !=0)
    {
        mSensorRepresentation.mDistance = true;
    }else
    {
        
        mSensorRepresentation.mDistance = false;
    }
     
}


