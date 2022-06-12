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
  static void SetCheckEvents(checkEventsFunction checkEvents_){
      checkEvents = checkEvents_;
  }
  
  Event GetEvent(){
    return checkEvents();
  }


  static Event CheckEventsDuringGame(){
    return ballHitedTheWall;
  }

};
