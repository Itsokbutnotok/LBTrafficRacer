//  made by Itsokbutnotok   ?   I don't know what to write here
//  v.2 released 5/9/2020
//input pins for the joystick are on lines 117/118
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
int ButtonPin = 9;
int x=114,xr=129,xr2=173,randlane1,randlane2,yr,yr2,pont,randomspeed1=3,randomspeed2=3,xp,yp=32;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// random car white pixels, 30x21px
const unsigned char randcarw [] PROGMEM = {
	0x00, 0x00, 0x40, 0x00, 0x1f, 0x00, 0x27, 0xc0, 0x3f, 0xff, 0xff, 0xe0, 0x40, 0x10, 0x40, 0x10, 
	0x87, 0xff, 0xf8, 0x08, 0x8a, 0x00, 0x17, 0x08, 0x9a, 0x00, 0x11, 0x04, 0x92, 0x00, 0x08, 0x84, 
	0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 
	0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x11, 0x04, 0x8a, 0x00, 0x16, 0x08, 
	0x87, 0xff, 0xf8, 0x08, 0x40, 0x10, 0x40, 0x10, 0x3f, 0xff, 0xff, 0xe0, 0x1f, 0x00, 0x27, 0xc0, 
	0x00, 0x00, 0x40, 0x00
};
// car black pixels, 30x21px
const unsigned char carb [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xef, 0xbf, 0xe0, 
	0x78, 0x00, 0x07, 0xf0, 0x75, 0xff, 0xe8, 0xf0, 0x65, 0xff, 0xee, 0xf8, 0x6d, 0xff, 0xf7, 0x78, 
	0x6d, 0xff, 0xf7, 0x78, 0x6d, 0xff, 0xf7, 0x78, 0x6d, 0xff, 0xf7, 0x78, 0x6d, 0xff, 0xf7, 0x78, 
	0x6d, 0xff, 0xf7, 0x78, 0x6d, 0xff, 0xf7, 0x78, 0x6d, 0xff, 0xee, 0xf8, 0x75, 0xff, 0xe9, 0xf0, 
	0x78, 0x00, 0x07, 0xf0, 0x3f, 0xef, 0xbf, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00
};

// player's car white pixels, 30x21px
const unsigned char car [] PROGMEM = {
	0x00, 0x00, 0x40, 0x00, 0x1f, 0x00, 0x27, 0xc0, 0x3f, 0xff, 0xff, 0xe0, 0x41, 0x04, 0x10, 0x10, 
	0x87, 0xff, 0xf8, 0x08, 0x8a, 0x00, 0x16, 0x08, 0x9a, 0x00, 0x11, 0x04, 0xf3, 0xff, 0xf0, 0xfc, 
	0xf3, 0xff, 0xf8, 0xfc, 0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 0x92, 0x00, 0x08, 0x84, 
	0xf3, 0xff, 0xf8, 0xfc, 0xf3, 0xff, 0xf0, 0xfc, 0x92, 0x00, 0x11, 0x04, 0x8a, 0x00, 0x16, 0x08, 
	0x8f, 0xff, 0xf8, 0x08, 0x41, 0x04, 0x10, 0x10, 0x3f, 0xff, 0xff, 0xe0, 0x1f, 0x00, 0x27, 0xc0, 
	0x00, 0x00, 0x40, 0x00
};
//drawing the lines
int csik(int x)
{   
    display.drawFastHLine(x,20,14,1);
    display.drawFastHLine(x,21,14,1);
    display.drawFastHLine(x,43,14,1);
    display.drawFastHLine(x,44,14,1);
    return 0;
}
void setup() {
    Serial.begin(9600);
    pinMode(ButtonPin,INPUT);
    digitalWrite(ButtonPin,HIGH);
    if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.clearDisplay();
    display.setCursor(5,5);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Low Budget");
    display.setCursor(22,25);
    display.println("Traffic");
    display.setCursor(35,45);
    display.println("Racer");
    display.setCursor(100,53);
    display.setTextSize(1);
    display.println("v2");
    display.display();
    delay(1500);
}

void loop() {
    display.clearDisplay();
//setting the speed and the lane if they are in the same lane
    if(yr==yr2)
    {   //if car2 is spawns in the same lane as car 1
        if(xr+31<xr2)  //for avoiding displaying them at each other
            randomspeed2=randomspeed1;
        if((xr<xr2)&&(xr+31>xr2)){
            if(randlane2==0)
            randlane1 = random(1, 3);
            if(randlane2==2)
            randlane1 = random(1, 2);
            if(randlane2==1)
            {
                int r=random(0,2);
                if(r==0)
                    randlane2=0;
                else
                    randlane2=2;
            }
        }
        //if car1 spawns in the same lane as car 2
        if(xr2<=xr)  
            randlane1 = random(0, 3);
    }
//lane position reset
    if(x==2)
         x=114;
//car1 reset
    if(xr<-30)
    {
        xr=140;
        randlane1 = random(0, 3);
        randomspeed1 = random(1,5);
    }
//car2 reset
    if(xr2<-31)
    {
        xr2=173;
        randlane2 = random(0, 3);
        randomspeed2 = random(1,5);
    }
//control
    int Ysv = analogRead(A6); //y analog value
    int Xsv = analogRead(A7); //x analog value
    int ytp = Ysv * (6/1023.0); //y joystick position or throttle
    int xtp = Xsv * (6/1023.0); //x joystick postion or steering
//player's car vertical limit
    if((yp>=3)&&(yp<=60))  //moving bettween the limits
        yp=yp+3-ytp;
    if(yp<=3){              //upper limit
        if(ytp<3)
            yp=yp+3-ytp;
    }
    if(yp>=60){             //bottom limit
        if(ytp>4)
            yp=yp+4-ytp;
    }
//player's car horisontal limit
    //right side limit
    if(xtp>3){       //if there is throttle
            if(xp<110){    //if it doesn't reached the right limit
            xp=xp-3+xtp;
        }
        else           //if it doesn reached the right limit
            xp=110;
    }
    //left side limit
    if(xtp==3)               //if there is throttle
    {
        if(xp>-11)       
        xp=xp-3; //if it doesn't reached the left limit
        else
        xp=-12;        //if it doesn reached the right limit
    }
    if(xtp<3)
    {
        if(xp>-11)       
        xp=xp-4; //if it doesn't reached the left limit
        else
        xp=-12;        //if it doesn reached the right limit
        
    }

//lines
    csik(x);
    int x1=x-28,x2=x-56,x3=x-84,x4=x-112,x11=x+28,x22=x+56,x33=x+84,x44=x+112;
    csik(x1);
    csik(x2);
    csik(x3);
    csik(x4); 
    csik(x11);
    csik(x22);
    csik(x33);
    csik(x44);
//lane choosing
    yr=22*randlane1;        //car1 lane choosing
    yr2=22*randlane2;       //car2 lane choosing

//displaying car1
    display.drawBitmap(xr,yr, randcarw, 30, 21, 1);
//displayin car2
    display.drawBitmap(xr2,yr2, randcarw, 30, 21, 1);
//displaying player's car
    display.drawBitmap(xp,yp-10, carb, 30, 21, 0);//black, it needs this to hide the lines "on the asphalt under the car"
    display.drawBitmap(xp,yp-10, car, 30, 21, 1);//white
//displaying points
    pont=pont+1;
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println(pont);
    display.display();      // this draws the entire thing
    xr=xr-randomspeed1;     //car1 speed
    xr2=xr2-randomspeed2;   //car2 speed
    x=x-4;                  //lane speed
    
    //collision detection
    if ((((yr>yp-28)&&(yr<yp+7))&&(((xp<xr)&&(xp+31>xr))||(((xp+2>xr)&&(xp<xr+31)))))||(((yr2>yp-28)&&(yr2<yp+7))&&(((xp+2<xr2)&&(xp+31>xr2))||((xp>xr2)&&(xp<xr2+31)))))
    {   delay(500);
    //reset
        yp=32;      //player'svertical reset
        xp=1;       //player's car horisontal reset
        xr=129;     //car1 spawnpoint
        xr2=173;    //car2 spawnpoin
        randlane1 = random(0, 3);  //car1 lane reset
        randlane2 = random(0, 3); //car2 lane reset
    //game over screen
        display.clearDisplay();
        display.setCursor(10,20);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.println("GAME OVER");
        display.setCursor(30,40);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.println("Points:");
        display.setCursor(72,40);
        display.println(pont);
        display.display();
        delay(1500);
        pont=0; //pont reset
    }
    delay(1);
}
