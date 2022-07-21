class Events{
private:
  static int event;  

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

  static Event GetWallEvent(){
    int event_ = TheWall::GetEvent();
    if(event_ == wallCreated || event_ == wallErased) event = event_;
    else event = nothing;
    return event_;
  }

  Event GetGameEvent(){ 
    if(event != nothing){
      int event_ = event;
      event = nothing; 
      return event_;
    }
    return Pong::GetEvent(); 
  }
};
