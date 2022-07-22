class Events{
private:
  int externalGameEvent = nothing; 
  int lastExternalGameEvent = nothing; 
  int ballEvent = nothing; 

public:
  static int gameEvent; 
  static int wallEvent;
  Events(){
    gameEvent = nothing;
  }
  
  enum Event{
    nothing,
    
    ballErased,
    ballHitTheWall, 
    ballMovedOutsideTheBoard, 

    wallCreated,
    timeoutBeforeWallBlinkingIsOver, 
    timeoutWallBlinkingIsOver,
    wallErased,
  
    winAnimationIsOver,
    gameOverAnimationIsOver,
  };

  // Called first
  Event GetWallEvent(){
    Serial.print(gameEvent);
    if(gameEvent == ballErased || gameEvent == ballHitTheWall || gameEvent == winAnimationIsOver) return gameEvent;
    Serial.print("_");
    Serial.print(wallEvent);
    if(wallEvent == wallCreated || wallEvent == wallErased) gameEvent = wallEvent;
    return wallEvent;
  }

  // Called second
  Event GetBallEvent(){
    static int lastBallEvent = nothing;
    if(gameEvent != lastBallEvent){
      lastBallEvent = gameEvent;
      if(gameEvent == wallCreated || gameEvent == wallErased) return gameEvent;
    }
    if((ballEvent = TheBall::GetEvent()) != nothing) gameEvent = ballEvent;
    return ballEvent;
  }

  //Called third
  Event GetGameEvent(){ 
    if((ballEvent == ballErased || ballEvent == ballHitTheWall || wallEvent == wallErased) && lastExternalGameEvent != externalGameEvent){
      lastExternalGameEvent = externalGameEvent;
      externalGameEvent = ballEvent == ballErased || ballEvent == ballHitTheWall ? ballEvent : wallEvent;
      return externalGameEvent;
    }
    return gameEvent; 
  }
};
