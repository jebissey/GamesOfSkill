class Events{
public:
  enum Event{
    nothing,
    
    ballErased,
    ballHitedTheWall, 
    ballMovedOutsidetheBoard, 
    
    wallDoesNotExist,
    wallCreated,
    timeoutBeforeWallBlinkingIsOver, 
    wallBlinking,
    timeoutWallBlinkingIsOver, 
    wallErasing,
    wallErased,
    
    winAnimationIsOver,
    gameOverAnimationIsOver,
  };
    
  static Event GetBallEvent(){
    Serial.println("GetBallEvent");

    if(TheBall::IsBallMovedOutsideTheBoard()) return ballMovedOutsidetheBoard;
    if(TheBall::IsBallHitedTheWall())         return ballHitedTheWall;
    if(TheBall::IsBallErased())               return ballErased;
    return nothing;
  }

  static Event GetWallEvent(){
    Serial.print(".");
    return TheWall::GetStatus();
  }

  Event GetGameEvent(){
    Serial.println("GetGameEvent");


    
    return nothing;
  }
};
