class Events{
public:
  enum Event { ballMovedOutside, ballHitedWall, timeoutWallBeforeBlinkIsOver, timeoutWallBlinkking, boardShaked, wallExist};
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
