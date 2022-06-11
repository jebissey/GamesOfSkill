class TheWall{
public:
  static void Create(){
    enum WallPosition{noWall, north, est, sud, west};
    static int wallPosition = noWall;

    while(1==1){
      int newWallPosition = random(north, west);
      if(wallPosition != newWallPosition){
        wallPosition = newWallPosition;
        break;
      }
    }
    switch(wallPosition){
      case north:
        matriceLeds.SetRow(7, B11111111);
        break;
      case est:
        matriceLeds.SetColumn(0, B11111111);
        break;
      case sud:
        matriceLeds.SetRow(0, B11111111);
        break;
      case west:
        matriceLeds.SetColumn(7, B11111111);
        break;
    }
  }


      


  
  static void Blink(){
    
  }



  static void Erase(){
    
  }


};
