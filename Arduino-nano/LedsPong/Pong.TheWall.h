class TheWall : public Fsm{
private:
  State createWall = State(Create,  NULL,                          InitBeforeWallBlinkingTimer);
  State fixWall =    State(Display, IsBeforeWallBlinkingTimerOver, InitWallBlinkingTimer);
  State blinkWall =  State(NULL,    IsWallBlinkingTimerOver, NULL);
  State eraseWall =  State(NULL,    Erase, NULL);
  State wait =       State(NULL,    NULL,  NULL);
   
  enum WallPosition{noWall, north, est, sud, west};
  static int wallPosition;
  
  static int wallStatus;

  static void Display_(int mask){
    switch(wallPosition){
      case north: matriceLeds.SetRow(7, mask); break;
      case est:   matriceLeds.SetColumn(0, mask); break;
      case sud:   matriceLeds.SetRow(0, mask); break;
      case west:  matriceLeds.SetColumn(7, mask); break;
    }
    Serial.print("Display the wall: ");
    Serial.println(mask);
  }


  static const int beforeWallBlinkingTime = 5000;
  static unsigned long beforeWallBlinkingTimer;
  static void InitBeforeWallBlinkingTimer(){ time.Reset(&beforeWallBlinkingTimer); }
  static void IsBeforeWallBlinkingTimerOver(){
    if(time.IsOver(beforeWallBlinkingTime, &beforeWallBlinkingTimer)) wallStatus = wallBlinking;
  }

  
  static const int wallBlinkingTime = 2000;
  static unsigned long wallBlinkingTimer;
  static void InitWallBlinkingTimer(){ time.Reset(&beforeWallBlinkingTimer); }
  static void IsWallBlinkingTimerOver(){ 
    if(time.IsOver(wallBlinkingTime, &wallBlinkingTimer)) wallStatus = wallErasing;
    else Blink();
  }

  
  static void Blink(){
    static int mask = 0;
    static const int blinkTime = 200;
    static unsigned long blinkTimer;
    if(time.IsOver(blinkTime, &blinkTimer)){
      Display_(mask);
      if(mask == 0) mask = B11111111;
      else mask = 0;
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
    Serial.print("Create the wall: ");
    Serial.println(wallPosition);
  }
  
  static void Display(){ Display_(B11111111); }
  static void Erase(){ Display_(0); }
  static void SetWallStatusToWallCreated(){ wallStatus = wallCreated; 
    Serial.print("wallStaus: ");
    Serial.println(wallStatus);
  }
  
public:
  enum WallStatus{wallDoesNotExist, wallCreated, wallBlinking, wallErasing, wallErased};
  
  TheWall() : Fsm(&createWall){
    wallPosition = noWall;
    wallStatus = wallDoesNotExist;
    
    this->add_transition(&createWall, &fixWall,    Events::wallCreated, &SetWallStatusToWallCreated);
    this->add_transition(&fixWall,    &blinkWall,  Events::tiemoutBeforeWallBlinkingIsOver, NULL);
    this->add_transition(&fixWall,    &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&blinkWall,  &eraseWall,  Events::tiemoutWallBlinkingIsOver, NULL);
    this->add_transition(&blinkWall,  &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::wallErased, NULL);
    this->add_transition(&eraseWall,  &wait,       Events::ballHitedTheWall, NULL);
    this->add_transition(&wait,       &createWall, Events::winAnimationIsOver, NULL);
  }

  static int GetStatus(){ return wallStatus; }
};
