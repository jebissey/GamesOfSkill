class TheBall{
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
 
  static void Erase(){
    ledsSquare.SetLight(Off);
  }
};
