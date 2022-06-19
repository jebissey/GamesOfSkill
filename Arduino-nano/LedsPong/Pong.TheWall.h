class TheWall : public Fsm{
private:
  static const int beforeWallBlinkingTime = 5000;
  static const int wallBlinkingTime = 3000;
  static const int blinkTime = 200;
  
  State createWall = State(Create,                      Display,      NULL);
  State fixWall =    State(InitBeforeWallBlinkingTimer, FixThenBlink, NULL);
  State blinkWall =  State(InitWallBlinkingTimer,       FixThenBlink, NULL);
  State eraseWall =  State(NULL,                        WallErasing,  NULL);
  State wait =       State(WaitEntry,                   NULL,         WaitExit);

  static void Display_(int mask){
    switch(wallPosition){
      case north: matriceLeds.SetRow(7, mask); break;
      case est:   matriceLeds.SetColumn(0, mask); break;
      case south: matriceLeds.SetRow(0, mask); break;
      case west:  matriceLeds.SetColumn(7, mask); break;
    }
  }

  static unsigned long beforeWallBlinkingTimer;
  static void InitBeforeWallBlinkingTimer(){ time.Reset(&beforeWallBlinkingTimer); }
  
  static unsigned long wallBlinkingTimer;
  static void InitWallBlinkingTimer(){ time.Reset(&wallBlinkingTimer); }

  static void WaitEntry(){ Serial.println("WaitEntry"); }
  static void WaitExit(){ Serial.println("WaitExit"); }


  static void Create(){
    while(1==1){
      int newWallPosition = random(north, west);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
    wallEvent = Events::wallCreated;
  }
  
  static void Display(){ Display_(B11111111); }
    
  static void FixThenBlink(){
    static int mask = 0;
    static unsigned long blinkTimer;
    if(wallEvent == Events::wallCreated && time.IsOver(beforeWallBlinkingTime, &beforeWallBlinkingTimer)){
      wallEvent = Events::timeoutBeforeWallBlinkingIsOver;
      return; // mandatory for fsm
    }
    if(wallEvent == Events::timeoutBeforeWallBlinkingIsOver){
      if(time.IsOver(wallBlinkingTime, &wallBlinkingTimer)) wallEvent = Events::timeoutWallBlinkingIsOver;
      if(time.IsOver(blinkTime, &blinkTimer)){
        Display_(mask);
        if(mask == 0) mask = B11111111;
        else mask = 0;
      }
    }
  }
  
  static void WallErasing(){
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
      if(step > 4) wallEvent = Events::wallErased;
    }
  }

public:
  static int wallEvent; 
  enum WallPosition{noWall, north, est, south, west};
  static int wallPosition;
  
  TheWall() : Fsm(&createWall){
    wallPosition = noWall;
    
    this->add_transition(&createWall, &fixWall,    Events::wallCreated, NULL);
    this->add_transition(&fixWall,    &blinkWall,  Events::timeoutBeforeWallBlinkingIsOver, NULL);
    this->add_transition(&blinkWall,  &eraseWall,  Events::timeoutWallBlinkingIsOver, NULL);
    this->add_transition(&fixWall,    &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::wallErased, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&wait,       &createWall, Events::winAnimationIsOver, NULL);
  }

  static int GetEvent(){ return wallEvent; }
};
