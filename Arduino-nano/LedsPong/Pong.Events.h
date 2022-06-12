class Events{
public:
  enum Event{
    ballErased,
    ballHitedTheWall, 
    ballMovedOutsidetheBoard, 
    gameOverAnimationIsOver,
    tiemoutBeforeWallBlinkingIsOver, 
    tiemoutWallBlinkingIsOver, 
    wallCreated,
    wallErased,
    winAnimationIsOver,
  };
    
  Event GetBallEvent(){
    Serial.println("GetBallEvent");

    int theWallStatus = TheWall::GetStatus();
    if( theWallStatus == TheWall::wallErased) return wallErased;
    if( theWallStatus == TheWall::wallCreated) return wallCreated;
    return ballHitedTheWall;
  }

  Event GetWallEvent(){
    Serial.println("GeGetWallEvent");

    int theWallStatus = TheWall::GetStatus();
    if( theWallStatus == TheWall::wallErased) return wallErased;
    if( theWallStatus == TheWall::wallCreated) return wallCreated;
    return ballHitedTheWall;
  }

  Event GetGameEvent(){
    Serial.println("GetGameEvent");

    int theWallStatus = TheWall::GetStatus();
    if( theWallStatus == TheWall::wallErased) return wallErased;
    if( theWallStatus == TheWall::wallCreated) return wallCreated;
    return ballHitedTheWall;
  }
};
