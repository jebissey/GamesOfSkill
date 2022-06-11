class TheWall : public Fsm{
private:
  enum WallPosition{noWall, north, est, sud, west};
  static int wallPosition;

  static void Display_(int mask){
    switch(wallPosition){
      case north:
        matriceLeds.SetRow(7, mask);
        break;
      case est:
        matriceLeds.SetColumn(0, mask);
        break;
      case sud:
        matriceLeds.SetRow(0, mask);
        break;
      case west:
        matriceLeds.SetColumn(7, mask);
        break;
    }
  }
  
  static void Blink(){
    
  }

  static void Erase(){
    Display_(0);
  }
  
public:
  static void Create(){
    while(1==1){
      int newWallPosition = random(north, west);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
  }
  
  static void Display(){
    Display_(B11111111);
  }

  
  State fixWall =   State(Display, NULL,  NULL);
  State blinkWall = State(NULL,    Blink, NULL);
  State eraseWall = State(NULL,    Erase, NULL);
  State gameOver =  State(NULL,    NULL,  NULL);
  
  TheWall() : Fsm(&fixWall){
    wallPosition = noWall;
    
    this->add_transition(&fixWall,  &blinkWall, Events::tiemoutBeforeWallBlinkingIsOver, NULL);
    this->add_transition(&blinkWall, &eraseWall, Events::tiemoutWallBlinkingIsOver, NULL);
    this->add_transition(&eraseWall, &gameOver,  Events::wallErased, NULL);
  }
};
