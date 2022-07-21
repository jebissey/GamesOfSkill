class Events{
private:
  static int event; 
  int lastEvent = nothing; 

public:
  Events(){
    event = nothing;
  }
  
  enum Event{
    nothing,
    
    ballErased,
    ballHitTheWall, 
    ballMovedOutsidetheBoard, 

    wallCreated,
    timeoutBeforeWallBlinkingIsOver, 
    timeoutWallBlinkingIsOver,
    wallErased,
  
    winAnimationIsOver,
    gameOverAnimationIsOver,
  };

  static Event GetWallEvent(){
    int event_ = TheWall::GetEvent();
    if(event_ == wallCreated || event_ == wallErased) event = event_;
    return event_;
  }

  static Event GetBallEvent(){
    if(event == wallCreated){
      event = nothing; 
      return wallCreated;
    }
    if(TheBall::IsBallErased()){
      event = ballErased;
      return ballErased;
    }
    if(TheBall::IsBallHitedTheWall())         return ballHitTheWall;
    if(TheBall::IsBallMovedOutsideTheBoard()) return ballMovedOutsidetheBoard;
    return nothing;
  }

  Event GetGameEvent(){ 
    if(event != nothing && lastEvent != event){
      lastEvent = event; 
      return event;
    }
    return Pong::GetEvent(); 
  }
};
