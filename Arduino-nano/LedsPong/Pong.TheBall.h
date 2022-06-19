class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;
  static int ballStatus;
  
  State moveBall =  State(Display,   Move,      NULL);
  State eraseBall = State(NULL,      Erasing,   NULL);
  State wait =      State(WaitEntry, WaitState, WaitExit);


  enum BallExit{inside, north, est, south, west};
  static GetBalStatus_(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row < 0) return west;
    if(ballCoordonate.col < 0) return south;
    if(ballCoordonate.row + ballSize.row - 1 >= ledsSquare.matriceSize) return est;
    if(ballCoordonate.col + ballSize.col - 1 >= ledsSquare.matriceSize) return north;
    return inside;
  }

  static void Display(int mask){
    switch(GetBalStatus_()){
      case north: matriceLeds.SetColumn(ledsSquare.matriceSize - 1, mask); break;
      case south: matriceLeds.SetColumn(0, mask); break;
      case est:   matriceLeds.SetRow(ledsSquare.matriceSize - 1, mask); break;
      case west:  matriceLeds.SetRow(0, mask); break;
    }
  }

  
  static void WaitEntry(){ Serial.println("WaitEntry(ball)"); }
  static void WaitState(){ Serial.print("#"); }
  static void WaitExit(){ Serial.println("WaitExit(ball)"); }

  static void Move(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(boardTilts);
      int ballRowIncrement = round(map(boardTilts[1], -90, +90, -10, +10) / 3.0);
      int ballColIncrement = round(map(boardTilts[2], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }
    
  static void Display(){ ledsSquare.SetLight(On); Serial.println("display ball");}

  static void Erasing(){
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
    || ballCoordonate.row + ballSize.row == ledsSquare.matriceSize - 1 && TheWall::wallPosition == TheWall::south 
    || ballCoordonate.col + ballSize.col == ledsSquare.matriceSize - 1 && TheWall::wallPosition == TheWall::est ) return ballHitTheWall;
    
    if(GetBalStatus_() != inside) return ballOutsideTheBoard;  
    return ballInTheBoard;
  }
  
public:
  TheBall() : Fsm(&moveBall/*wait*/){
    this->add_transition(&wait,     &moveBall,  Events::wallCreated,              NULL);
    this->add_transition(&moveBall, &eraseBall, Events::ballMovedOutsidetheBoard, NULL);
    this->add_transition(&moveBall, &wait,      Events::ballHitedTheWall,         NULL);
    this->add_transition(&eraseBall,&wait,      Events::ballErased,               NULL);
  }

  static bool IsBallMovedOutsideTheBoard(){ return (GetBallStatus() == ballOutsideTheBoard); }
  static bool IsBallHitedTheWall(){         return (GetBallStatus() == ballHitTheWall); }
  static bool IsBallErased(){               return (ledsSquare.GetLight() == Off); }
};
