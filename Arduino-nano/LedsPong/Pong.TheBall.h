class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;

  
public:
  static void Move(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(boardTilts);
      int ballRowIncrement = round(map(boardTilts[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(boardTilts[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }
  
  State moveBall =   State(NULL, TheBall::Move, NULL);
  State eraseBall =  State(TheBall::Erase, NULL, NULL);

  TheBall() : Fsm(&moveBall){
    this->add_transition(&moveBall,  &eraseBall, Events::ballMovedOutsidetheBoard, NULL);
  }
  

 
  static void Erase(){
    ledsSquare.SetLight(Off);
  }
};
