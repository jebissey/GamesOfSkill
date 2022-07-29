class TheWall : public Fsm{
private: 
  static const int initValueForBeforeWallBlinkingTime = 5000;
  static const int minValueForBeforeWallBlinkingTime = 200;
  static const int initValueForWallBlinkingTime = 3000;
  static const int minValueForWallBlinkingTime = 300;
  static const float reductionFactor = 0.95;
  static const int blinkTime = 100;
  static int beforeWallBlinkingTime;
  static int wallBlinkingTime;
  
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
    static const int eraseTime = 150;
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

  static void WaitToCreateWall(){ Serial.println("W: W->C(GS)");}
  static void CreateWallToFixWall(){ Serial.println("W: C->F(WC)");}
  static void FixWalltoBlinkWall(){ Serial.println("W: F->B(TO)");}
  static void FixWallToWait(){ Serial.println("W: F->W(GE)");}
  static void BlinkWallToEraseWall(){ Serial.println("W: B->E(TO)");}
  static void BlinkWallToWait(){ Serial.println("W: B->W(GE)");}
  static void EraseWallToWait1(){ Serial.println("W: E->W(WE)");}
  static void EraseWallToWait2(){ Serial.println("W: E->W(GE)");}

public:
  enum WallPosition{noWall, north, east, south, west};
  static int wallPosition;
  
  TheWall() : Fsm(&wait){
    wallPosition = noWall;
    
    this->add_transition(&wait,       &createWall, Events::gameStarted, WaitToCreateWall);
    this->add_transition(&createWall, &fixWall,    Events::wallCreated, CreateWallToFixWall);
    this->add_transition(&fixWall,    &blinkWall,  Events::timeoutBeforeWallBlinkingIsOver, FixWalltoBlinkWall);
    this->add_transition(&fixWall,    &wait,       Events::gameEnded, FixWallToWait);
    this->add_transition(&blinkWall,  &eraseWall,  Events::timeoutWallBlinkingIsOver, BlinkWallToEraseWall);
    this->add_transition(&blinkWall,  &wait,       Events::gameEnded, BlinkWallToWait);
    this->add_transition(&eraseWall,  &wait,       Events::wallErased, EraseWallToWait1);
    this->add_transition(&eraseWall,  &wait,       Events::gameEnded, EraseWallToWait2);

    beforeWallBlinkingTime = initValueForBeforeWallBlinkingTime;
    wallBlinkingTime = initValueForWallBlinkingTime;
  }

  static void IncreaseDifficulty(){
    beforeWallBlinkingTime *= reductionFactor;
    if(beforeWallBlinkingTime < minValueForBeforeWallBlinkingTime) beforeWallBlinkingTime = minValueForBeforeWallBlinkingTime;
    wallBlinkingTime *= reductionFactor;
    if(wallBlinkingTime < minValueForWallBlinkingTime) wallBlinkingTime = minValueForWallBlinkingTime;
  }
  static void ResetDifficulty(){
    beforeWallBlinkingTime = initValueForBeforeWallBlinkingTime;
    wallBlinkingTime = initValueForWallBlinkingTime;
  }
};
