class Events{
public:
  enum Event { ballHitedWall, timeoutWallBeforeBlinkingIsOver, timeoutWallBlinkkingIsOver, boardShaked, ballMovedOutsidetheBoard, 
              tiemoutBeforeWallBlinkingIsOver, tiemoutWallBlinkingIsOver, WallErasing, 
              wallErased,
              wallExist, ballMovedOutside, winnedPoint, gameOver};
  typedef Event (*checkEventsFunction)();
  
  static checkEventsFunction checkEvents;
  static void SetCheckEvents(checkEventsFunction checkEvents_){
      checkEvents = checkEvents_;
  }
  
  Event GetEvent(){
    return checkEvents();
  }


  static Event CheckEventsDuringGame(){
    return ballMovedOutside;
  }

};
