//printing stuff
double lineTime = 1;//delay between each line
double charTime = 2;//delay between each character
double wordTime = 200;//base delay of each word

//hall effect stuff
int sensor = 2;//halleffect data
unsigned long revolutions;
int count = 0;
int arr[10];
unsigned long timeold = 0;
int onerev;
unsigned long sum = 0;
bool revflag;
int quickdelay;
boolean spinflag = false;

//bluetooth stuff
char Incoming_value = 0;

//color stuff
uint32_t color = 0xFF0000;

//clock stuff
String hours;
String minutes;
String seconds;
String totaltime;
long prevtime;

//calcualtor
double result;
String resultout;
double number1;
char op; // calSignal will be the first char after the first number
double number2;  // stores the second number in number2
 String number2s;
  String minus = "-";
  String esign="=";
  String spacesign=" ";

//led strip stuff
#include "Adafruit_NeoPixel.h"
#define PIN 4//led data 
#define LEDS 12
#include <Adafruit_DotStar.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
int head  = 0, tail = -9; // snake function

String wordTimen;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  pinMode(sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensor), interruptFunction, FALLING);
}
void loop()
{
  if (Serial.available())
  {
    Incoming_value = Serial.read();
  }
  switch (Incoming_value)
  {
    case '1'://change color
      Serial.print("case 1 ");
      Serial.println(Incoming_value);

      color >>= 8;
      if (color == 0)
      { // Next color
        color = 0xFF0000;
      }
      while (Incoming_value == '1')
      {
        if (Serial.available() > 0)
        {
          break;
        }
        strip.fill(color, 4, 7);
        strip.show();
      }

      //Show The Color
      break;

    case '2'://preprogramed text
      cleanup();
              Serial.print("case 2 ");
        Serial.println(Incoming_value);
      while (Incoming_value == '2')
      {

        if (Serial.available() > 0)
        {
          break;
        }
        displayString("ee175 project");


      }
      break;



    case '5'://mode 5 user input
      cleanup();
      String words = "";
      words = Serial.readStringUntil('*');
      words.toLowerCase();
             Serial.print("case 5 ");
        Serial.println(words);
      while (Incoming_value == '5')
      {
        //halleffect();
        if (Serial.available() > 0)
        {
          break;
        }
        displayString(words.c_str());
      }
      break;
    default:
      Serial.print("default");
      break;

  }


  switch (Incoming_value)
  {
    case '4':
      if (Incoming_value == '4')
      {
        if (Serial.available() > 0)
        {
          break;
        }
        cleanup();
        strip.setPixelColor(0, 0, 0, 0); //RED
        strip.show(); //Show The Color
      }
      break;

      case '7':
      Serial.print("case 7 ");
      Serial.println(Incoming_value);
      spinflag = !spinflag;
      while(Incoming_value=7)
      {
       if (Serial.available() > 0)
        {
          break;
        }
      
      if (spinflag == true)
      {
        displayString("still");
      }
      else
      {
        displayString("moving");
      }
      }

      break;

    case '6'://mode 6 clock function

      Serial.print("case 6 ");
      Serial.println(Incoming_value);

      hours = Serial.readStringUntil(':');
      minutes = Serial.readStringUntil(':');
      seconds = Serial.readStringUntil('*');

      int hoursn = hours.toInt();
      int minutesn = minutes.toInt();
      int secondsn = seconds.toInt();

      Serial.print(hours);
      Serial.print(": ");
      Serial.print(minutes);
      Serial.print(": ");
      Serial.println(seconds);
      prevtime = millis();
      while (Incoming_value == '6')
      {
        //halleffect();
        if (Serial.available() > 0)
        {
          break;
        }

        if (millis() - prevtime > 980)
        {
          prevtime = millis();
          secondsn++;
        }
        if (secondsn > 59)
        {
          minutesn++;
          secondsn = 0;
        }
        if (minutesn > 59)
        {
          hoursn++;
          minutesn = 0;
        }
        if (hoursn > 23)
        {
          hoursn = 0;
        }
        String secondsout;
        String minutesout;
        String zero = "0";
        if (secondsn < 10)
        {
          secondsout = zero + secondsn;
        }
        else
        {
          secondsout = secondsn;
        }

        if (minutesn < 10)
        {
          minutesout = zero + minutesn;
        }
        else
        {
          minutesout = minutesn;
        }
        String co = ":"; //what kind of wierd ass language is this to concacate the string int total time i had to do this
        totaltime = hoursn + co + minutesout + co + secondsout;
        Serial.println(totaltime);
        displayString(totaltime.c_str());
      }
      break;

    default:
      Serial.print("default2");
      break;

  }

  switch (Incoming_value)
  {
    case '3'://calculator mode
      cleanup();
     
      number1 = Serial.parseFloat();
      op = Serial.read();
      number2s = Serial.readStringUntil("*");
      Serial.print(number1);
      Serial.print(op);
      number2 = number2s.toFloat();
      Serial.println(number2);

      if (op == '+') {
        result = number1 + number2;
      }
      else if (op == '-')  {
        result = number1 - number2;
      }
      else if (op == '*')  {
        result = number1 * number2;
      }
      else if (op == '/')  {
        result = number1 / number2;
      }
      Serial.println(String(result, 2));

      if (result - int(result) > 0)
      {
        resultout = String(result, 2);
      }
      else
      {
        resultout = String(result, 0);
      }
        Serial.print("case 3: ");
        Serial.println(resultout);
             if (result < 0)
        {
          resultout = minus + resultout;
        }
        resultout=esign+resultout;
      while (Incoming_value == '3')
      {
        if (Serial.available() > 0)
        {
          break;
        }
        displayString(resultout.c_str());
      }
      break;

    default:
      Serial.print("default3");
      break;
  }

}


int a[] = {127, 136, 136, 136, 127};
int b[] = {255, 145, 145, 145, 110};
int c[] = {126, 129, 129, 129, 66};
int d[] = {255, 129, 129, 129, 126};
int e[] = {255, 145, 145, 145, 129};
int f[] = {255, 144, 144, 144, 128};
int g[] = {126, 129, 137, 137, 78};
int h[] = {255, 16, 16, 16, 255};
int i[] = {129, 129, 255, 129, 129};
int j[] = {6, 129, 129, 129, 254};
int k[] = {255, 16, 40, 68, 131};
int l[] = {255, 1, 1, 1, 1};
int m[] = {255, 64, 32, 64, 255};
int n[] = {255, 64, 32, 16, 255};
int o[] = {126, 129, 129, 129, 126};
int p[] = {255, 144, 144, 144, 96};
int q[] = {126, 129, 133, 131, 127};
int r[] = {255, 144, 152, 148, 99};
int s[] = {66, 161, 145, 138, 68};
int t[] = {128, 128, 255, 128, 128};
int u[] = {254, 1, 1, 1, 254};
int v[] = {248, 6, 1, 6, 248};
int w[] = {254, 1, 6, 1, 254};
int x[] = {129, 66, 60, 66, 129};
int y[] = {128, 64, 63, 64, 128};
int z[] = {135, 137, 145, 161, 193};

int n0[] = {126, 129, 129, 129, 126};
int n1[] = {129, 129, 255, 1, 1};
int n2[] = {71, 137, 145, 161, 65};
int n3[] = {66, 145, 145, 145, 110};
int n4[] = {8, 24, 40, 72, 255};
int n5[] = {241, 145, 145, 145, 142};
int n6[] = {126, 137, 137, 137, 70};
int n7[] = {128, 143, 144, 160, 192};
int n8[] = {110, 145, 145, 145, 110};
int n9[] = {96, 144, 144, 144, 127};

int add[] = {16, 16, 124, 16, 16};
int sub[] = {16, 16, 16, 16, 16};
int mult[] = {68, 40, 16, 40, 68};
int divide[] = {16, 16, 84, 16, 16};
int equalsign[] = {40, 40, 40, 40, 40};
int period[] = {0, 0, 1, 0, 0};
int colon[] = {0, 20, 0};
int eos[] = {0, 1, 0, 0, 0};
int excl[] = {0, 29, 0, 0, 0};
int ques[] = {8, 19, 20, 8, 0};
int space[] = {0, 0, 0, 0, 0};

void displayLine(int line) {
  cleanup();
  int currentline;
  currentline = line;
  if (currentline >= 128) {
    strip.setPixelColor((3), color);
    //strip.show();
    currentline -= 128;
  }
  if (currentline >= 64) {
    strip.setPixelColor((4), color);
    //strip.show();
    currentline -= 64;
  }
  if (currentline >= 32) {
    strip.setPixelColor((5), color);
    //strip.show();
    currentline -= 32;
  }
  if (currentline >= 16) {
    strip.setPixelColor((6), color);
    //strip.show();
    currentline -= 16;
  }

  if (currentline >= 8) {
    strip.setPixelColor((7), color);
    //strip.show();
    currentline -= 8;
  }

  if (currentline >= 4) {
    strip.setPixelColor((8), color);
    //strip.show();
    currentline -= 4;
  }

  if (currentline >= 2) {
    strip.setPixelColor((9), color);
    //strip.show();
    currentline -= 2;
  }


  if (currentline >= 1) {
    strip.setPixelColor((10), color);
    //strip.show();
    currentline -= 1;
  }
  strip.show();
}


void displayChar(char c2) {
  cleanup();
  if (c2 == 'a') {
    for (int i = 0; i < 5; i++) {
      displayLine(a[i]);
      delay(lineTime);
    }
  }

  if (c2 == 'b') {
    for (int i = 0; i < 5; i++) {
      displayLine(b[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'c') {
    for (int i = 0; i < 5; i++) {
      displayLine(c[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'd') {
    for (int i = 0; i < 5; i++) {
      displayLine(d[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'e') {
    for (int i = 0; i < 5; i++) {
      displayLine(e[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'f') {
    for (int i = 0; i < 5; i++) {
      displayLine(f[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'g') {
    for (int i = 0; i < 5; i++) {
      displayLine(g[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'h') {
    for (int i = 0; i < 5; i++) {
      displayLine(h[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'i') {
    for (int it = 0; it < 5; it++) {
      displayLine(i[it]);
      delay(lineTime);
    }
  }
  if (c2 == 'j') {
    for (int i = 0; i < 5; i++) {
      displayLine(j[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'k') {
    for (int i = 0; i < 5; i++) {
      displayLine(k[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'l') {
    for (int i = 0; i < 5; i++) {
      displayLine(l[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'm') {
    for (int i = 0; i < 5; i++) {
      displayLine(m[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'n') {
    for (int i = 0; i < 5; i++) {
      displayLine(n[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'o') {
    for (int i = 0; i < 5; i++) {
      displayLine(o[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'p') {
    for (int i = 0; i < 5; i++) {
      displayLine(p[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'q') {
    for (int i = 0; i < 5; i++) {
      displayLine(q[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'r') {
    for (int i = 0; i < 5; i++) {
      displayLine(r[i]);
      delay(lineTime);
    }
  }
  if (c2 == 's') {
    for (int i = 0; i < 5; i++) {
      displayLine(s[i]);
      delay(lineTime);
    }
  }
  if (c2 == 't') {
    for (int i = 0; i < 5; i++) {
      displayLine(t[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'u') {
    for (int i = 0; i < 5; i++) {
      displayLine(u[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'v') {
    for (int i = 0; i < 5; i++) {
      displayLine(v[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'w') {
    for (int i = 0; i < 5; i++) {
      displayLine(w[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'x') {
    for (int i = 0; i < 5; i++) {
      displayLine(x[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'y') {
    for (int i = 0; i < 5; i++) {
      displayLine(y[i]);
      delay(lineTime);
    }
  }
  if (c2 == 'z') {
    for (int i = 0; i < 5; i++) {
      displayLine(z[i]);
      delay(lineTime);
    }
  }
  if (c2 == '!') {
    for (int i = 0; i < 5; i++) {
      displayLine(excl[i]);
      delay(lineTime);
    }
  }
  if (c2 == '?') {
    for (int i = 0; i < 5; i++) {
      displayLine(ques[i]);
      delay(lineTime);
    }
  }
  if (c2 == '.') {
    for (int i = 0; i < 5; i++) {
      displayLine(eos[i]);
      delay(lineTime);
    }
  }
  if (c2 == '0') {
    for (int i = 0; i < 5; i++) {
      displayLine(n0[i]);
      delay(lineTime);
    }
  }
  if (c2 == '1') {
    for (int i = 0; i < 5; i++) {
      displayLine(n1[i]);
      delay(lineTime);
    }
  }
  if (c2 == '2') {

    for (int i = 0; i < 5; i++) {
      displayLine(n2[i]);
      delay(lineTime);
    }
  }
  if (c2 == '3') {
    for (int i = 0; i < 5; i++) {
      displayLine(n3[i]);
      delay(lineTime);
    }
  }
  if (c2 == '4') {
    for (int i = 0; i < 5; i++) {
      displayLine(n4[i]);
      delay(lineTime);
    }
  }
  if (c2 == '5') {
    for (int i = 0; i < 5; i++) {
      displayLine(n5[i]);
      delay(lineTime);

    }
  }
  if (c2 == '6') {
    for (int i = 0; i < 5; i++) {
      displayLine(n6[i]);
      delay(lineTime);

    }
  }
  if (c2 == '7') {
    for (int i = 0; i < 5; i++) {
      displayLine(n7[i]);
      delay(lineTime);

    }
  }
  if (c2 == '8') {
    for (int i = 0; i < 5; i++) {
      displayLine(n8[i]);
      delay(lineTime);

    }
  }
  if (c2 == '9') {
    for (int i = 0; i < 5; i++) {
      displayLine(n9[i]);
      delay(lineTime);

    }
  }
  if (c2 == ':') {
    for (int i = 0; i < 3; i++) {
      displayLine(colon[i]);
      delay(lineTime);
    }
  }

 if (c2 == ' ') {
    for (int i = 0; i < 5; i++) {
      displayLine(space[i]);
      delay(lineTime);
    }
  }


  if (c2 == '-') {
    for (int i = 0; i < 5; i++) {
      displayLine(sub[i]);
      delay(lineTime);
    }
  }


  if (c2 == '=') {
    for (int i = 0; i < 5; i++) {
      displayLine(equalsign[i]);
      delay(lineTime);
    }
  }

  delay(charTime);
}


void displayString(char* s) {
  prevtime = millis();
  while (revflag)
  {
    if (spinflag == true)
    {
      for (int i = 0; i <= strlen(s); i++)
      {
        displayChar(s[i]);
      }
      revflag = false;
    }
    else
    {
      if (millis() - prevtime > quickdelay)
      {
        for (int i = 0; i <= strlen(s); i++)
        {
          displayChar(s[i]);
        }
        revflag = false;
        // Serial.println(revflag);
        quickdelay += 10;
        if (quickdelay > 240)
        {
          quickdelay = 0;
        }
        prevtime = millis();
      }
    }
  }
}

 
  /*quickdelay += 10;
  if (quickdelay > 120)
  {
    quickdelay = 0;
  }
  
}*/


void cleanup() {//clear leds of color
  strip.clear();
  strip.show();
}


/*void ColorChange()
{
  if (millis() - prevtime > 200)
  {
    if ((color >>= 4) == 0)
    { //  Next color (R->G->B)
      color = 0x370000;
      prevtime = millis();
      Serial.println("ColorChange");
    }
  }
}

  void halleffect()
  {
  if (revolutions > 2) {
    onerev = (millis() - timeold) / revolutions;//result in ms
    timeold = millis();
    revolutions = 0;
    if (count < 9)
    {
      arr[count] = onerev;
      count++;
    }
    else
    {
      for (int y = 0; y < 10; y++)
      {
        sum += arr[y];
      }
      arr[9] = onerev;
      for (int x = 0; x < 9; x++)//rolling avg replacing values
      {
        arr[x] = arr[x + 1];
      }
      wordTime = sum / 10;
    }

    String outMsg = String("time for one loop :") + wordTime;
    Serial.println(outMsg);

  }
  }

void snake() {
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(100);                        //

  if (head++ >= LEDS) {        // Increment head index
    head = 0;                       //  Yes, reset head index to start
    if ((color >>= 4) == 0)         //  Next color (R->G->B)
      color = 0x370000;             //   Yes, reset to red
  }

  if (tail++ >= LEDS) tail = 0; // Increment, reset tail index
}
*/
void interruptFunction()
{
  revolutions++;
  revflag = true;
  Serial.print(revflag);
  Serial.println(" rev");
}
