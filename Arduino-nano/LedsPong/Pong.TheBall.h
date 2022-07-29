class TheBall : public Fsm{
private:
  static const int timeBetweenBallMove = 100;
  static int ballStatus;
  
  State moveBall =  State(Display, Move, NULL);
  State eraseBall = State(NULL, EraseBall, NULL);
  State wait =      State(CenterBall, NULL, NULL);

  static void Display(){ ledsSquare.SetLightOn(); }
  
  static void Move(){
    if(time.IsOver(timeBetweenBallMove, &timerForMoveTheBall)){
      gy521.Read(boardTilts);
      int ballRowIncrement = round(map(boardTilts[1], +90, -90, -10, +10) / 3.0);
      int ballColIncrement = round(map(boardTilts[0], -90, +90, +10, -10) / 3.0);
      ledsSquare.MoveRelative(RowCol(ballRowIncrement, ballColIncrement));
    }
  }    

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
        default : ledsSquare.SetLightOff();
      }
      DisplayOuting(mask);
    }
  }
  static void DisplayOuting(int mask){
    switch(GetBallPosition()){
      case north: ledsSquare.setColumn(0, ledsSquare.matrixSize - 1, mask); break;
      case south: ledsSquare.setColumn(0, 0, mask); break;
      case east:  ledsSquare.setRow(0, ledsSquare.matrixSize - 1, mask); break;
      case west:  ledsSquare.setRow(0, 0, mask); break;
    }
  }
  
  static void CenterBall(){
    static const RowCol ballCoordonateAtStartUp = RowCol(3, 3);
    ledsSquare.MoveAbsolute(ballCoordonateAtStartUp);
  }
// End of state functions

  enum BallPosition{inside, north, east, south, west};
  static enum BallPosition GetBallPosition(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row < 0) return west;
    if(ballCoordonate.col < 0) return south;
    if(ballCoordonate.row + ballSize.row - 1 >= ledsSquare.matrixSize) return east;
    if(ballCoordonate.col + ballSize.col - 1 >= ledsSquare.matrixSize) return north;
    return inside;
  }
  
  enum BallStatus{ballHitTheWall, ballOutsideTheBoard, ballInTheBoard};
  static enum BallStatus GetBallStatus(){
    RowCol ballCoordonate = ledsSquare.GetCoordonate();
    if(ballCoordonate.row == 1 && TheWall::wallPosition == TheWall::south
    || ballCoordonate.col == 1 && TheWall::wallPosition == TheWall::east
    || ballCoordonate.row + ballSize.row == ledsSquare.matrixSize - 1 && TheWall::wallPosition == TheWall::north 
    || ballCoordonate.col + ballSize.col == ledsSquare.matrixSize - 1 && TheWall::wallPosition == TheWall::west ) return ballHitTheWall; 
    return GetBallPosition() == inside ? ballInTheBoard : ballOutsideTheBoard;
  }

  static void WaitToMoveBall(){ Serial.println("Ball: WaitToMoveBall");}
  static void MoveBallToEraseBall(){ Serial.println("Ball: MoveBallToEraseBall");}
  static void EraseBallToWait(){ Serial.println("Ball: EraseBallToWait");}
  static void MoveBallToWait1(){ Serial.println("Ball: MoveBallToWait1");}
  static void MoveBallToWait2(){ Serial.println("Ball: MoveBallToWait2");}
  
public:
  TheBall() : Fsm(&wait){
    this->add_transition(&wait,      &moveBall,  Events::gameStarted, WaitToMoveBall);
    this->add_transition(&moveBall,  &eraseBall, Events::ballMovedOutsideTheBoard, MoveBallToEraseBall);
    this->add_transition(&eraseBall, &wait,      Events::ballErased, EraseBallToWait);
    this->add_transition(&moveBall,  &wait,      Events::ballHitTheWall, MoveBallToWait1);
    this->add_transition(&moveBall,  &wait,      Events::gameEnded, MoveBallToWait2);
  }

  static int GetEvent(){ 
    if(ledsSquare.IsLightOff())           return Events::ballErased;
    int ballStatus = GetBallStatus();
    if(ballStatus == ballHitTheWall)      return Events::ballHitTheWall;
    if(ballStatus == ballOutsideTheBoard) return Events::ballMovedOutsideTheBoard;
    return Events::nothing; 
  }
};
