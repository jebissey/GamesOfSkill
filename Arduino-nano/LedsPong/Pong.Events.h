class Events{
private:

public:
  static int gameEvent; 
  static int wallEvent;
  static int ballEvent; 
  Events(){
    gameEvent = wallEvent = ballEvent = nothing;
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
    boardShaked,
  };

  Event GetWallEvent(){
    static int externalWallEvent = nothing;
    static int lastExternalWallEvent = nothing;
    if(ballEvent == ballErased || ballEvent == ballHitTheWall) externalWallEvent = ballEvent;
    else if(gameEvent == winAnimationIsOver || gameEvent == boardShaked) externalWallEvent = gameEvent;
    if(lastExternalWallEvent != externalWallEvent){
      lastExternalWallEvent = externalWallEvent;
      return externalWallEvent;
    }
    Serial.print(wallEvent);
    return wallEvent;
  }

  Event GetBallEvent(){
    static int externalBallEvent = nothing;
    static int lastExternalBallEvent = nothing;
    if(wallEvent == wallCreated || wallEvent == wallErased) externalBallEvent == wallEvent;
    if(lastExternalBallEvent != externalBallEvent){
      lastExternalBallEvent = externalBallEvent;
      Serial.print("___");
      return externalBallEvent;
    }
    ballEvent = TheBall::GetEvent();
    Serial.print(ballEvent);
    return ballEvent;
  }

  Event GetGameEvent(){ 
    static int externalGameEvent = nothing; 
    static int lastExternalGameEvent = nothing; 
    if(ballEvent == ballErased || ballEvent == ballHitTheWall ) externalGameEvent = ballEvent;
    else if(wallEvent == wallErased) externalGameEvent = wallEvent;
    if(lastExternalGameEvent != externalGameEvent){
      lastExternalGameEvent = externalGameEvent;
      return externalGameEvent;
    }
    if(gy521.IsShaked()) gameEvent = boardShaked;
    return gameEvent; 
  }
};
