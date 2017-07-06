/*
This is my sketch for a NEO PIXEL ring LED clock.
*/

//  Includes below:
#include <Wire.h>
#include <stdio.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h> 

RTC_DS1307 RTC;             // Create RTC object

//  Define things here and set things up.
#define LED_Loop 60
#define PIN 6    // This is defining which Arduino pin is driving the Pixel ring used pin 6 but any digital will work

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_Loop, PIN, NEO_GRB + NEO_KHZ800);

int LED[LED_Loop];
int THREE = (LED_Loop / 4);
int SIX = (THREE * 2);
int NINE = (THREE * 3);
int TWELVE = (LED_Loop-1);

int HR_Fade = 7;
int MN_Fade;

long HR_Colour;
long SE_Colour = 0x000055;

long THIS_LED;
int Led_Flag;
int argh;

//  trying this way to get colours working.
int HR_R;
int HR_G;
int HR_B;

int HR1_R = 0x55;
int HR1_G = 0;
int HR1_B = 0;

int HR2_R = 0x0D;
int HR2_G = 0;
int HR2_B = 0x0D;

int MN_R = 0;
int MN_G = 33;
int MN_B = 0;

//int SE_R = 0;
//int SE_G = 0;
//int SE_B = 0x55;

int hour_led;
int minute_led;
int second_led;
int new_minute;

//-----------------------------  Set up here -----------------------------//
void setup() 
{
  // put your setup code here, to run once:
  delay(2000);          //  This is just to give you time to open the window and watch.
  Serial.begin(9600);
  Serial.println("-------------------------------");
  Serial.println("Setting up");
  
  Wire.begin();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


  if (! RTC.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("Done setting up");
  Serial.println("-------------------------------");
}

//-----------------------------  MAIN LOOP here -----------------------------//
void loop() 
{
  //  Get time
   DateTime now = RTC.now();

   //  24 hour time change colour of hour hand.
   int hr = now.hour();
   if (hr < 12)
   {
     //HR_Colour = HR_Colour1;
     HR_R = HR1_R;
     HR_G = HR1_G;
     HR_B = HR1_B;
   }
   else
   {
     //HR_Colour = HR_Colour2;
     HR_R = HR2_R;
     HR_G = HR2_G;
     HR_B = HR2_B;
   }
   
   int mins = now.minute();        //  This line is only incase any maths had to be done.
   second_led = now.second();

  //
  //  calculate leds
   hour_led = (((LED_Loop/12) * hr) + (mins / (LED_Loop/5)))%LED_Loop;
   if (hour_led == 60)
   {
     hour_led = 59;
   }

   minute_led = mins;

//  Debug code below
//
//------------------------------------------//
/*    
    Serial.print(now.year());
    Serial.print('/');
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.day());
    Serial.print(' ');
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.print(now.second());
    Serial.println();
*/
//------------------------------------------//
/*
  Serial.println("=========================");
  Serial.println(hr);
  Serial.println(mins);
  Serial.println("-------------------------");
  Serial.println(hour_led);
  Serial.println(minute_led);
  Serial.println(second_led);
*/
//------------------------------------------//

  //
  //  Show LEDs            ------------------   Main loop here -----------------

   //  Keep this at the top so it doesn't mess up any other settings when LEDs are
   //  turned on.
   strip.setPixelColor(second_led-1,SE_Colour/2);
   strip.setPixelColor(second_led-2,SE_Colour/4);
   strip.setPixelColor(second_led-3,SE_Colour/8);
   strip.setPixelColor(second_led-4,SE_Colour/16);
   strip.setPixelColor(second_led-5,0);

  //
  //  show THREE, SIX, NINE and TWELVE
  //
  
  strip.setPixelColor (THREE, 0x050505);
  strip.setPixelColor (SIX, 0x050505);
  strip.setPixelColor (NINE, 0x050505);
  strip.setPixelColor (TWELVE, 0x050505);
  
  //
  //  Now start setting LEDs below here.
  //
  


   if (second_led == 0)
   {
      strip.setPixelColor(LED_Loop-1, SE_Colour/2);
      strip.setPixelColor(LED_Loop-2,SE_Colour/4);
      strip.setPixelColor(LED_Loop-3,SE_Colour/8);
      strip.setPixelColor(LED_Loop-4,SE_Colour/16);
      strip.setPixelColor(LED_Loop-5,0);
      new_minute = 1;
   }
   if (second_led == 1)
   {
      strip.setPixelColor(second_led-1, SE_Colour/2);
      strip.setPixelColor(LED_Loop-1, SE_Colour/4);
      strip.setPixelColor(LED_Loop-2,SE_Colour/8);
      strip.setPixelColor(LED_Loop-3,SE_Colour/16);
      strip.setPixelColor(LED_Loop-4,0);
   }
   if (second_led == 2)
   {
      strip.setPixelColor(second_led-1, SE_Colour/2);
      strip.setPixelColor(second_led-2, SE_Colour/4);
      strip.setPixelColor(LED_Loop-1, SE_Colour/8);
      strip.setPixelColor(LED_Loop-2,SE_Colour/16);
      strip.setPixelColor(LED_Loop-3,0);
   }
   if (second_led == 3)
   {
      strip.setPixelColor(second_led-1, SE_Colour/2);
      strip.setPixelColor(second_led-2, SE_Colour/4);
      strip.setPixelColor(second_led-3, SE_Colour/8);
      strip.setPixelColor(LED_Loop-1,SE_Colour/16);
      strip.setPixelColor(LED_Loop-2,0);
   }
   if (second_led == 4)
   {
      strip.setPixelColor(second_led-1, SE_Colour/2);
      strip.setPixelColor(second_led-2, SE_Colour/4);
      strip.setPixelColor(second_led-3, SE_Colour/8);
      strip.setPixelColor(second_led-4,SE_Colour/16);
      strip.setPixelColor(LED_Loop-1,0);
   }

/*
  if (Led_Flag == 0)
  {
    //
    Led_Flag = 1;
    THIS_LED = strip.getPixelColor(second_led);
    //  This is where I am at.
    Serial.print(second_led);
    Serial.print(" ");
    Serial.println(THIS_LED);
  }
*/  



  /*----------------  Draw SECOND HAND on clock ----------------*/
   strip.setPixelColor(second_led,SE_Colour);
//   strip.setPixelColor(second_led,SE_Colour+THIS_LED);
//   strip.setPixelColor(second_led-1,THIS_LED);
   if (new_minute == 1)
   {
     //new_minute = 0;
//     strip.setPixelColor(minute_led-1,MN_Colour/50);
   }
  /*----------------  Draw MINUTE HAND on clock ----------------*/
   //strip.setPixelColor(minute_led,MN_Colour);
   //  MN_Fade for fading.
   strip.setPixelColor(minute_led,MN_R,MN_G,MN_B);
   strip.setPixelColor(minute_led+1, MN_R,     (MN_G * (second_led*10/6)/100)      , MN_B);
   strip.setPixelColor(minute_led-1, MN_R,     (MN_G * (100-(second_led*10/6))/100)      , MN_B);
  /*----------------  Draw HOUR HAND on clock ----------------*/
   strip.setPixelColor(hour_led,HR_R,HR_G,HR_B);
   //strip.setPixelColor((hour_led-1)%LED_Loop,HR_R/HR_Fade,HR_G,HR_B/HR_Fade);
   //strip.setPixelColor((hour_led+1)%LED_Loop,HR_R/HR_Fade,HR_G,HR_B/HR_Fade);
/*
   strip.setPixelColor(hour_led,HR_Colour);
   strip.setPixelColor((hour_led-1)%LED_Loop,HR_Colour);
   strip.setPixelColor((hour_led+1)%LED_Loop,HR_Colour);
*/   

   if (second_led > minute_led)
   {
     new_minute = 0;
   }

/*
  if (second_led != argh)
  {
     Led_Flag = 0;
     argh = second_led;
  }
*/  
  


  
  


  //
  //  show alarms
  //
  
  strip.show();
  delay(400);
  //                    ------------------   End of Main loop here -----------------
}

//==================================================================
//==================================================================
//
//    end of code
//
//==================================================================

