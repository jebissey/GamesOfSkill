class Events{
public:
  Events(){
    ballEvent = nothing;
  }
  
  enum StateEvent{
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

  static int ballEvent;  
  static StateEvent GetBallEvent(){
    if(ballEvent == wallCreated){
      ballEvent = nothing; 
      return wallCreated;
    }
    if(TheBall::IsBallErased())               return ballErased;
    if(TheBall::IsBallHitedTheWall())         return ballHitedTheWall;
    if(TheBall::IsBallMovedOutsideTheBoard()) return ballMovedOutsidetheBoard;
    return nothing;
  }

  static StateEvent GetWallEvent(){
    int wallEvent = TheWall::GetEvent();
    if(wallEvent == wallCreated) ballEvent = wallCreated;
    return TheWall::GetEvent();
  }

  StateEvent GetGameEvent(){
    Serial.println("GetGameEvent");


    
    return nothing;
  }
};
