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
    gameStarting,
    gameEnding,
  };

  Event GetWallEvent(){
    if(Pong::IsGameStarting()) return gameStarting;
    if(Pong::IsGameEnding())   return gameEnding;
    return wallEvent;
  }

  Event GetBallEvent(){
    if(Pong::IsGameStarting(true)) return gameStarting;
    if(Pong::IsGameEnding(true))   return gameEnding;
    return (ballEvent = TheBall::GetEvent());
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
