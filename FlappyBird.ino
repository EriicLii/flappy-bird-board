#include <U8glib.h>
U8GLIB_PCD8544 u8g(13, 11, 9, 8, 10);

int width = 84;
int height = 48;

unsigned long obsTimeToMove;
unsigned long birdTimeToMove;
int obsAniSpeed = 40;
int birdAniSpeed = 80;

int button = 7;
boolean buttonPressed;

boolean started;
boolean gameOver;

int points;

//Obstacle settings
int obsSpeed = 1;
int obsNum = 2;

int spawnDamperTop = 20;
int spawnDamperBot = 6;

int obsWidth = 6;
int gapHeight = 14;

int obsX[2];
int obsY[2];
boolean obsPassed[2];

//Bird settings
int upAccel = 3;
int downAccel = 1;
int birdMaxUpSpeed = -3;
int birdMaxDownSpeed = 4;
int birdSpeed;

int birdSize = 4;
int birdX = 10;
int birdY = height/2;


void generateObs(){
  for(int i=0; i<obsNum; i++){
    obsX[i] = width+(width/2+obsWidth/2)*i;
    obsY[i] = random(spawnDamperTop, height-spawnDamperBot);
    obsPassed[i] = false;
  }
}

void moveObs(){
  if (millis() > obsTimeToMove) {
    for(int i=0; i<obsNum; i++){
      obsX[i] -= obsSpeed;
      if (obsX[i]+obsWidth <= 0){
        obsX[i] = width;
        obsY[i] = random(spawnDamperTop, height-spawnDamperBot);
        obsPassed[i] = false;
      }
    }
    obsTimeToMove = millis() + obsAniSpeed;
  }
}

void drawObs(){
  for(int i=0; i<obsNum; i++){
    if(obsX[i] < width){
      u8g.drawBox(obsX[i], obsY[i], obsWidth, width-obsY[i]);
      u8g.drawBox(obsX[i], 0, obsWidth, obsY[i]-gapHeight);
    }
  }
}

boolean buttonPress(){
  int state = digitalRead(button);
  if(!buttonPressed && state==HIGH){
    buttonPressed = true;
    return true;
  }
  else if(buttonPressed && state==LOW){
    buttonPressed = false;
    return false;
  }
  else {
    return false;
  }
}

void jump(){
    if(birdSpeed > 0){
      birdSpeed = 0;
    }
    if(birdSpeed - upAccel < birdMaxUpSpeed){
      birdSpeed = birdMaxUpSpeed;
    }
    else{
      birdSpeed -= upAccel;
    }
    birdY += birdSpeed;
}

void moveBird(){
  if (millis() > birdTimeToMove) {
    if(birdY + birdSize >= height){
      birdY = height - birdSize;
      birdSpeed = 0;
    }
    else {
      if(birdSpeed<birdMaxDownSpeed){
        birdSpeed += downAccel;
      }
      birdY += birdSpeed;
    }
    birdTimeToMove = millis() + birdAniSpeed;    
  }
}

void drawBird(){
  u8g.drawBox(birdX, birdY, birdSize, birdSize);
}

void drawPointsDisplay(){
  char charBuff[5];
  String score = "";
  score += points;
  score.toCharArray(charBuff, 5);

  int shift = score.length()*7/2;
  
  u8g.setFont(u8g_font_freedoomr10r);
  u8g.drawStr(width/2-shift, 14, charBuff);
}

void drawStartScreen(){
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(14, 14, "Flappy Bird");
  u8g.setFont(u8g_font_micro);
  u8g.drawStr( 18, 34, "Press Button");
  u8g.drawStr( 25, 41, "to Start");
}

void drawGameOverScreen(){
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(14, 20, "Game Over");
  u8g.setFont(u8g_font_micro);
  u8g.drawStr( 19, 34, "Press Button");
  u8g.drawStr( 23, 41, "to Restart");
}

void checkCollision(){
  if(birdY+birdSize >= height){
    gameOver = true;
  }
  else {
    for(int i=0; i<obsNum; i++){
      if(birdX+birdSize > obsX[i] && birdX < obsX[i]+obsWidth){
        if(birdY < obsY[i]-gapHeight || birdY+birdSize > obsY[i]){
          gameOver = true;
        }
        else if(birdX > obsX[i] && !obsPassed[i]){
          points ++;
          obsPassed[i] = true;
        }
      }
    }
  }
}

void setup() {
  u8g.setRot180();
  pinMode(button, INPUT);

  buttonPressed = false;
  started = false;
  
  birdSpeed = 0;
  points = 0;
 
  generateObs();
}

void loop() {
  if(started && !gameOver){
    u8g.firstPage();
    do {
  
      if(buttonPress()){
        jump();
      }
      else {
        moveBird();
      }
      moveObs();
      drawObs();
      drawBird();
      drawPointsDisplay();
      checkCollision();
    } 
    while ( u8g.nextPage() );
  }
  
  else if(!started && buttonPress()){
    started = true;
    gameOver = false;
  }

  else if(gameOver && buttonPress()){
    birdSpeed = 0;
    points = 0;
    birdY = height/2;
    generateObs();
    gameOver = false;
  }

  else if(gameOver){
    u8g.firstPage();
    do {
      drawGameOverScreen();
    } 
    while ( u8g.nextPage() );
  }
  
  else {
    u8g.firstPage();
    do {
      drawStartScreen();
    } 
    while ( u8g.nextPage() );
  }
}
