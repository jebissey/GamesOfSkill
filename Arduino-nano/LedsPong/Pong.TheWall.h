class TheWall : public Fsm{
private: 
  static int   beforeWallBlinkingTime;
  static int   wallBlinkingTime;
  static const int   initValueForBeforeWallBlinkingTime = 5000;
  static const int   initValueForWallBlinkingTime = 3000;
  static const float reductionFactor = 0.9;
  static const int   blinkTime = 200;
  
  State createWall = State(Create, Display, NULL);
  State fixWall =    State(InitBeforeWallBlinkingTimer, FixThenBlink, NULL);
  State blinkWall =  State(InitWallBlinkingTimer, FixThenBlink, NULL);
  State eraseWall =  State(InitStep, WallErasing, NULL);
  State wait =       State(NULL, NULL, NULL);

  static void Display_(int mask){
    switch(wallPosition){
      case north: ledsSquare.setRow(0, 7, mask); break;
      case east:  ledsSquare.setColumn(0, 0, mask); break;
      case south: ledsSquare.setRow(0, 0, mask); break;
      case west:  ledsSquare.setColumn(0, 7, mask); break;
    }
  }

  static unsigned long beforeWallBlinkingTimer;
  static void InitBeforeWallBlinkingTimer(){ time.Reset(&beforeWallBlinkingTimer); }
  
  static unsigned long wallBlinkingTimer;
  static void InitWallBlinkingTimer(){ time.Reset(&wallBlinkingTimer); }

  static void Create(){
    ledsSquare.ClearDisplay();
    while(1==1){
      int newWallPosition = random(north, west + 1);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
    Events::wallEvent = Events::wallCreated;
  }
  
  static void Display(){ Display_(B11111111); }
    
  static void FixThenBlink(){
    static int mask = 0;
    static unsigned long blinkTimer;
    if(Events::wallEvent == Events::wallCreated && time.IsOver(beforeWallBlinkingTime, &beforeWallBlinkingTimer)){
      Events::wallEvent = Events::timeoutBeforeWallBlinkingIsOver;
      return; // mandatory for fsm
    }
    if(Events::wallEvent == Events::timeoutBeforeWallBlinkingIsOver){
      if(time.IsOver(wallBlinkingTime, &wallBlinkingTimer)) Events::wallEvent = Events::timeoutWallBlinkingIsOver;
      if(time.IsOver(blinkTime, &blinkTimer)){
        Display_(mask);
        if(mask == 0) mask = B11111111;
        else mask = 0;
      }
    }
  }

  static int step;
  static void InitStep(){ step = 0; }
  static void WallErasing(){
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
        default : 
          Events::wallEvent = Events::wallErased; 
          step = 0; 
          break;
      }
      Display_(mask);
    }
  }

  static void WaitToCreateWall(){ Serial.println("Wall: WaitToCreateWall");}
  static void CreateWallToFixWall(){ Serial.println("Wall: CreateWallToFixWall");}
  static void FixWalltoBlinkWall(){ Serial.println("Wall: FixWalltoBlinkWall");}
  static void FixWallToWait(){ Serial.println("Wall: FixWallToWait");}
  static void BlinkWallToEraseWall(){ Serial.println("Wall: BlinkWallToEraseWall");}
  static void BlinkWallToWait(){ Serial.println("Wall: BlinkWallToWait");}
  static void EraseWallToWait1(){ Serial.println("Wall: EraseWallToWait1");}
  static void EraseWallToWait2(){ Serial.println("Wall: EraseWallToWait2");}

public:
  enum WallPosition{noWall, north, east, south, west};
  static int wallPosition;
  
  TheWall() : Fsm(&wait){
    wallPosition = noWall;
    
    this->add_transition(&wait,       &createWall, Events::gameStarting, WaitToCreateWall);
    this->add_transition(&createWall, &fixWall,    Events::wallCreated, CreateWallToFixWall);
    this->add_transition(&fixWall,    &blinkWall,  Events::timeoutBeforeWallBlinkingIsOver, FixWalltoBlinkWall);
    this->add_transition(&fixWall,    &wait,       Events::gameEnding, FixWallToWait);
    this->add_transition(&blinkWall,  &eraseWall,  Events::timeoutWallBlinkingIsOver, BlinkWallToEraseWall);
    this->add_transition(&blinkWall,  &wait,       Events::gameEnding, BlinkWallToWait);
    this->add_transition(&eraseWall,  &wait,       Events::wallErased, EraseWallToWait1);
    this->add_transition(&eraseWall,  &wait,       Events::gameEnding, EraseWallToWait2);

    beforeWallBlinkingTime = initValueForBeforeWallBlinkingTime;
    wallBlinkingTime = initValueForWallBlinkingTime;
  }

  static void IncreaseDifficulty(){
    beforeWallBlinkingTime *= reductionFactor;
    wallBlinkingTime       *= reductionFactor;
  }
};
