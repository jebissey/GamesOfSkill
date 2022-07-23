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
    static int externalWallEvent;
    static int lastExternalWallEvent;
    if(ballEvent == ballErased || ballEvent == ballHitTheWall) externalWallEvent = ballEvent;
    else if(gameEvent == winAnimationIsOver || gameEvent == boardShaked) externalWallEvent = gameEvent;
    if(lastExternalWallEvent != externalWallEvent){
      lastExternalWallEvent = externalWallEvent;
      return externalWallEvent;
    }
    return wallEvent;
  }

  Event GetBallEvent(){
    static int externalBallEvent;
    static int lastExternalBallEvent;
    if(wallEvent == wallCreated || wallEvent == wallErased) externalBallEvent = wallEvent;
    if(lastExternalBallEvent != externalBallEvent){
      lastExternalBallEvent = externalBallEvent;
      return externalBallEvent;
    }
    ballEvent = TheBall::GetEvent();
    return ballEvent;
  }

  Event GetGameEvent(){ 
    static int externalGameEvent; 
    static int lastExternalGameEvent; 
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
