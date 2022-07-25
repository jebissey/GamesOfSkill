class Animation{
private:
  static bool GameAnimation(byte masks[], int sizeOfMasks, int animationTime = 100){
    int maxStep = sizeOfMasks - LedsSquare::matrixSize;
    static unsigned long animationTimer;
    if(time.IsOver(animationTime, &animationTimer)){
      if(step++ > maxStep) step = 0;
      else{
        for(int i = 0; i < LedsSquare::matrixSize; i++){
          ledsSquare.setRow(0, i, masks[step + i]);
        }
      }
    }
    return step == 0;
  }
  
public:
  static void StartAnimation(){
    byte shakeMe[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B01001100,
      B10010010,
      B10010010,
      B10010010,
      B01100100,

      B00000000,
      
      B11111110,
      B00001000,
      B00001000,
      B11110000,
      
      B00000000,
      
      B01110000,
      B10001000,
      B10001000,
      B11110000,
      B10000000,
      
      B00000000,
      
      B11111110,
      B00010000,
      B00110000,
      B01001000,
      B10000000,
      
      B00000000,
      
      B01110000,
      B10101000,
      B10101000,
      B10010000,
     
      B00000000,
      B00000000,
      B00000000,
      
      B11111000,
      B00001000,
      B11111000,
      B00001000,
      B11110000,
      
      B00000000,
      
      B01110000,
      B10101000,
      B10101000,
      B10010000,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    GameAnimation(shakeMe, sizeof(shakeMe)); 
  }
  
  static void WinAnimation(){
    byte win[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B00111110,
      B11000000,
      B01100000,
      B11000000,
      B00111110,
      
      B00000000,

      B00010000,
      B01111010,
      B10000000,
      B01000000,
      
      B00000000,
      
      B11111000,
      B00001000,
      B11110000,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    if(GameAnimation(win, sizeof(win), winDelay)) Events::gameEvent = Events::winAnimationIsOver; 
  }
  
  static void GameOverAnimation(){
    byte gameOver[] = {
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      
      B01111110,
      B10000001,
      B10010001,
      B10010001,
      B01100000,
      
      B00000000,
      
      B11111110,
      B00010001,
      B00010001,
      B00010001,
      B11111110,
      
      B00000000,
      
      B11111111,
      B00000010,
      B00000100,
      B00001000,
      B00000100,
      B00000010,
      B11111111,
      
      B00000000,
      
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
      
      B00000000,
      B00000000,
      B00000000,
      
      B01111110,
      B10000001,
      B10000001,
      B10000001,
      B01111110,
      
      B00000000,
      
      B00111111,
      B01000000,
      B10000000,
      B01000000,
      B00111111,
      
      B00000000,
      
      B11111111,
      B10010001,
      B10010001,
      B10010001,
      B10000001,
      
      B00000000,
      
      B11111111,
      B00010001,
      B00110001,
      B01010001,
      B10001110,
      
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
    };
    if(GameAnimation(gameOver, sizeof(gameOver), 75)) Events::gameEvent = Events::gameOverAnimationIsOver; 
  }
};
