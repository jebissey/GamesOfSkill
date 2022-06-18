class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;
  static int ballStatus;
  
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
    
  static void Display(){ ledsSquare.SetLight(On); }
  static void Erase(){ ledsSquare.SetLight(Off); }

  
  enum BallStatus{ballHitTheWall, ballOutsideTheBoard, ballInTheBoard};
  static int GetBallStatus(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row == 0 || ballCoordonate.col == 0
    || ballCoordonate.row + ballSize.row >= ledsSquare.matriceSize
    || ballCoordonate.col + ballSize.col >= ledsSquare.matriceSize) return ballOutsideTheBoard;

    if(ballCoordonate.row == 1 && TheWall::wallPosition == TheWall::north 
    || ballCoordonate.col == 1 && TheWall::wallPosition == TheWall::west 
    || ballCoordonate.row + ballSize.row == ledsSquare.matriceSize - 1 && TheWall::wallPosition == TheWall::south 
    || ballCoordonate.col + ballSize.col == ledsSquare.matriceSize - 1 && TheWall::wallPosition == TheWall::est ) return ballInTheBoard;
    
    return ballInTheBoard;
  }
  
public:

  TheBall() : Fsm(&wait){
    this->add_transition(&moveBall, &eraseBall, Events::ballMovedOutsidetheBoard, NULL);
    this->add_transition(&moveBall, &wait,      Events::ballHitedTheWall, NULL);
    this->add_transition(&eraseBall,&wait,      Events::ballErased, NULL);
    this->add_transition(&wait,     &moveBall,  Events::wallCreated, &Display);
  }

  static bool IsBallMovedOutsideTheBoard(){ return (GetBallStatus() == ballOutsideTheBoard); }
  static bool IsBallHitedTheWall(){         return (GetBallStatus() == ballHitTheWall); }
  static bool IsBallErased(){               return (ledsSquare.GetLight() == Off); }
};
