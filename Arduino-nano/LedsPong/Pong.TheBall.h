class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;
  
  State moveBall =  State(NULL,  Move, NULL);
  State eraseBall = State(Erase, NULL, NULL);
  State wait =      State(NULL,  NULL, NULL);

  static void Move(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(boardTilts);
      int ballRowIncrement = round(map(boardTilts[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(boardTilts[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }
    
  static void Erase(){ ledsSquare.SetLight(Off); }
  
public:
  TheBall() : Fsm(&moveBall){
    this->add_transition(&moveBall, &eraseBall, Events::ballMovedOutsidetheBoard, NULL);
    this->add_transition(&moveBall, &wait,      Events::ballHitedTheWall, NULL);
    this->add_transition(&eraseBall,&wait,      Events::ballErased, NULL);
    this->add_transition(&wait,     &moveBall,  Events::wallCreated, NULL);
  }
};
