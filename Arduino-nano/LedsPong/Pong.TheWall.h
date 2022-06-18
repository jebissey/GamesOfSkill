class TheWall : public Fsm{
private:
  static const int beforeWallBlinkingTime = 5000;
  static const int wallBlinkingTime = 2000;
  
  State createWall = State(Create,  NULL,         InitBeforeWallBlinkingTimer);
  State fixWall =    State(Display, FixThenBlink, NULL);
  State blinkWall =  State(NULL,    FixThenBlink, NULL);
  State eraseWall =  State(NULL,    WallErasing,  NULL);
  State wait =       State(NULL,    NULL,       NULL);
  

  static void Display_(int mask){
    switch(wallPosition){
      case north: matriceLeds.SetRow(7, mask); break;
      case est:   matriceLeds.SetColumn(0, mask); break;
      case south: matriceLeds.SetRow(0, mask); break;
      case west:  matriceLeds.SetColumn(7, mask); break;
    }
    Serial.print("Display the wall: ");
    Serial.println(mask);
  }


  static unsigned long beforeWallBlinkingTimer;
  static void InitBeforeWallBlinkingTimer(){ time.Reset(&beforeWallBlinkingTimer); }
  
  static unsigned long wallBlinkingTimer;
  static void InitWallBlinkingTimer(){ time.Reset(&wallBlinkingTimer); Serial.println("InitWallBlinkingTimer"); }
  
  static void IsWallBlinkingTimerOver(){ if(time.IsOver(wallBlinkingTime, &wallBlinkingTimer)) wallStatus = Events::wallErasing; }
  
  static void FixThenBlink(){
    Serial.print("-");
    static int mask = 0;
    static const int blinkTime = 200;
    static unsigned long blinkTimer;
    if(time.IsOver(beforeWallBlinkingTime, &beforeWallBlinkingTimer)) wallStatus = Events::wallBlinking;
    if(wallStatus == Events::wallBlinking){
      //if(time.IsOver(wallBlinkingTime, &wallBlinkingTimer)) wallStatus = Events::timeoutWallBlinkingIsOver;
      if(time.IsOver(blinkTime, &blinkTimer)){
        Display_(mask);
        if(mask == 0) mask = B11111111;
        else mask = 0;
      }
    }
  }
  
  static void WallErasing(){
    Serial.print("=");
    static int step = 0;
    static int mask;
    static const int eraseTime = 250;
    static unsigned long eraseTimer;
    if(time.IsOver(eraseTime, &eraseTimer)){
      switch(step++){
        case 0 : mask = B11111111; break;
        case 1 : mask = B01111110; break;
        case 2 : mask = B00111100; break;
        case 3 : mask = B00011000; break;
        case 4 : mask = B00000000; break;
      }
      Display_(mask);
      if(step > 4) wallStatus = Events::wallBlinking;
    }
  }
  
  static void Create(){
    while(1==1){
      int newWallPosition = random(north, west);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
    wallStatus = Events::wallCreated;
  }
  
  static void Display(){ Display_(B11111111); }
  
public:
  static int wallStatus; 
  enum WallPosition{noWall, north, est, south, west};
  static int wallPosition;
  
  TheWall() : Fsm(&createWall){
    wallPosition = noWall;
    wallStatus = Events::wallDoesNotExist;
    
    this->add_transition(&createWall, &fixWall,    Events::wallCreated, NULL);
    this->add_transition(&fixWall,    &blinkWall,  Events::timeoutBeforeWallBlinkingIsOver, NULL);
    this->add_transition(&blinkWall,  &eraseWall,  Events::timeoutWallBlinkingIsOver, NULL);
    this->add_transition(&fixWall,    &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::wallErased, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&wait,       &createWall, Events::winAnimationIsOver, NULL);
  }

  static int GetStatus(){ return wallStatus; }
};
