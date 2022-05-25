#include "Ball.h"

Ball::Ball()
{  

}



void Ball::Catch()
{

}


bool Ball::Throw(Catapult catapult, int position)
{
  if(catapult.GetPosition() > catapult.startPosition)
  {
    catapult.GoDown(catapult.delayBetweenPositionChange, catapult.startPosition);
    return false;
  }
  catapult.GoUp(position);
  return true;
}


void Ball::Test()
{

} 
