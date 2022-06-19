class Events{
public:
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
    
  static StateEvent GetBallEvent(){
    Serial.println("GetBallEvent");

    if(TheBall::IsBallMovedOutsideTheBoard()) return ballMovedOutsidetheBoard;
    if(TheBall::IsBallHitedTheWall())         return ballHitedTheWall;
    if(TheBall::IsBallErased())               return ballErased;
    return nothing;
  }

  static StateEvent GetWallEvent(){
    Serial.print(".");
    return TheWall::GetEvent();
  }

  StateEvent GetGameEvent(){
    Serial.println("GetGameEvent");


    
    return nothing;
  }
};
