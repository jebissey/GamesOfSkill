class Events{
private:
  static int gameEvent; 
  int lastGameEvent = nothing; 

public:
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
    if(gameEvent == ballErased || gameEvent == ballHitTheWall) return gameEvent;
    int wallEvent = TheWall::GetEvent();
    if(wallEvent == wallCreated || wallEvent == wallErased) gameEvent = wallEvent;
    return wallEvent;
  }

  // Called second
  Event GetBallEvent(){
    static int ballEvent = nothing; 
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
    if((gameEvent == ballErased || gameEvent == ballHitTheWall || gameEvent == wallErased) && lastGameEvent != gameEvent){
      lastGameEvent = gameEvent;
      return gameEvent;
    }
    return Pong::GetEvent(); 
  }
};
