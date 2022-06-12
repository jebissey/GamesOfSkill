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
  
  typedef Event (*checkEventsFunction)();
  static checkEventsFunction checkEvents;
  
  static void SetCheckEvents(checkEventsFunction checkEvents_){ checkEvents = checkEvents_; }
  
  Event GetEvent(){
    Event newEvent = checkEvents();
    Serial.println(newEvent);
    return newEvent;
  }

  static Event CheckEventsDuringGame(){
    if(TheWall::GetStatus() == TheWall::wallErased) return wallErased;
    return ballHitedTheWall;
  }
};
