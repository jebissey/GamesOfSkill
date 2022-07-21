class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;
  static int ballStatus;
  
  State moveBall =  State(Display,   Move,      NULL);
  State eraseBall = State(EraseBallEntry,      EraseBall,   EraseBallExit);
  State wait =      State(WaitEntry, WaitState, WaitExit);


  enum BallExit{inside, north, est, south, west};
  
  static GetBalStatus_(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row < 0) return west;
    if(ballCoordonate.col < 0) return south;
    if(ballCoordonate.row + ballSize.row - 1 >= ledsSquare.matrixSize) return est;
    if(ballCoordonate.col + ballSize.col - 1 >= ledsSquare.matrixSize) return north;
    return inside;
  }

  static void Display(int mask){
    switch(GetBalStatus_()){
      case north: ledsSquare.setColumn(0, ledsSquare.matrixSize - 1, mask); break;
      case south: ledsSquare.setColumn(0, 0, mask); break;
      case est:   ledsSquare.setRow(0, ledsSquare.matrixSize - 1, mask); break;
      case west:  ledsSquare.setRow(0, 0, mask); break;
    }
  }

  static void WaitEntry(){ Serial.println("WaitEntry (ball)"); }
  static void WaitState(){ Serial.print("#"); }
  static void WaitExit(){ Serial.println("WaitExit (ball)"); }

  static void Move(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(boardTilts);
      int ballRowIncrement = round(map(boardTilts[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(boardTilts[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }
    
  static void Display(){ ledsSquare.SetLight(On); Serial.println("display ball");}

  static void EraseBallEntry(){ Serial.println("EraseBallEntry");}
  static void EraseBallExit() { Serial.println("EraseBallExit");}
  static void EraseBall(){
    static int step = 0;
    static int mask;
    static const int eraseTime = 100;
    static unsigned long eraseTimer;
    if(time.IsOver(eraseTime, &eraseTimer)){
      switch(step++){
        case 0 : mask = B10000001; break;
        case 1 : mask = B01000010; break;
        case 2 : mask = B00100100; break;
        case 3 : mask = B00011000; break;
        case 4 : mask = B00000000; break;
        case 5 : mask = B00011000; break;
        case 6 : mask = B00100100; break;
        case 7 : mask = B01000010; break;
        case 8 : mask = B10000001; break;
        case 9 : mask = B00000000; break;
        default : ledsSquare.SetLight(Off);
      }
      Display(mask);
    }
  }
  
  enum BallStatus{ballHitTheWall, ballOutsideTheBoard, ballInTheBoard};
  static int GetBallStatus(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row == 1 && TheWall::wallPosition == TheWall::north 
    || ballCoordonate.col == 1 && TheWall::wallPosition == TheWall::west 
    || ballCoordonate.row + ballSize.row == ledsSquare.matrixSize - 1 && TheWall::wallPosition == TheWall::south 
    || ballCoordonate.col + ballSize.col == ledsSquare.matrixSize - 1 && TheWall::wallPosition == TheWall::east ) return ballHitTheWall;
    
    if(GetBalStatus_() != inside) return ballOutsideTheBoard;  
    return ballInTheBoard;
  }
  
public:
  TheBall() : Fsm(&wait){
    this->add_transition(&wait,     &moveBall,  Events::wallCreated,              NULL);
    this->add_transition(&moveBall, &eraseBall, Events::ballMovedOutsideTheBoard, NULL);
    this->add_transition(&moveBall, &wait,      Events::ballHitTheWall,           NULL);
    this->add_transition(&moveBall, &wait,      Events::wallErased,               NULL);
    this->add_transition(&eraseBall,&wait,      Events::ballErased,               NULL);
  }

  static int GetEvent(){ 
    int ballStatus = GetBallStatus();
    if(ballStatus == ballOutsideTheBoard) return Events::ballMovedOutsideTheBoard;
    if(ballStatus == ballHitTheWall)      return Events::ballHitTheWall;
    if(ledsSquare.GetLight() == Off)      return Events::ballErased;
    return Events::nothing; 
  }
};
