class Events{
private:
  static int ballEvent;  

public:
  Events(){
    ballEvent = nothing;
  }
  
  enum Event{
    nothing,
    
    ballErased,
    ballHitedTheWall, 
    ballMovedOutsidetheBoard, 

    wallCreated,
    timeoutBeforeWallBlinkingIsOver, 
    timeoutWallBlinkingIsOver,
    wallErased,
  
    winAnimationIsOver,
    gameOverAnimationIsOver,
  };

  static Event GetBallEvent(){
    if(ballEvent == wallCreated){
      ballEvent = nothing; 
      return wallCreated;
    }
    if(TheBall::IsBallErased())               return ballErased;
    if(TheBall::IsBallHitedTheWall())         return ballHitedTheWall;
    if(TheBall::IsBallMovedOutsideTheBoard()) return ballMovedOutsidetheBoard;
    return nothing;
  }

  static Event GetWallEvent(){
    int wallEvent = TheWall::GetEvent();
    if(wallEvent == wallCreated) ballEvent = wallCreated;
    return wallEvent;
  }

  Event GetGameEvent(){


    
    return nothing;
  }
};
