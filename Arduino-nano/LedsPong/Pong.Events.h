class Events{
public:
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
    gameStarted,
    gameEnded,
    maxScoreReached,
  };
  
private:
  static int ballEvent; 
  static int externalGameEvent; 
  static int lastExternalGameEvent; 

  static bool IsExternalEventEndedTheGame(){ 
    if(ballEvent == ballErased || ballEvent == ballHitTheWall) {
      externalGameEvent = ballEvent;
      if(lastExternalGameEvent != externalGameEvent){
        lastExternalGameEvent = externalGameEvent;
        return true;
      }
    }
    else if(wallEvent == wallErased){
      externalGameEvent = wallEvent;
      if(lastExternalGameEvent != externalGameEvent){
        lastExternalGameEvent = externalGameEvent;
        return true;
      }
    }
    return false;
  }

public:
  static int gameEvent; 
  static int wallEvent;
  Events(){
    gameEvent = wallEvent = ballEvent = nothing;
  }
  
  Event GetWallEvent(){
    if(Pong::IsGameStarting()) return gameStarted;
    if(Pong::IsGameEnding())   return gameEnded;
    return wallEvent;
  }

  Event GetBallEvent(){
    if(Pong::IsGameStarting(true)) return gameStarted;
    if(Pong::IsGameEnding(true))   return gameEnded;
    return (ballEvent = TheBall::GetEvent());
  }

  Event GetGameEvent(){ 
    if(IsExternalEventEndedTheGame()) return externalGameEvent;
    if((gameEvent == nothing || gameEvent == gameOverAnimationIsOver) && gy521.IsShaked()) gameEvent = boardShaked;
    return gameEvent; 
  }

  static void ResetEvents(){
    externalGameEvent = lastExternalGameEvent =
    ballEvent = gameEvent = wallEvent = nothing;
  }
};
