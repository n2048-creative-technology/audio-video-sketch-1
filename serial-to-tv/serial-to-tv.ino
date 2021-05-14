#include <TVout.h>
#include <fontALL.h>

TVout TV;

long c = 0;
bool h = 1;

int lastPos = 0;

void setup() {


  Serial.begin(115200);
  while (! Serial);
  Serial.println("n2048");

  TV.begin(NTSC);
  //  TV.begin(NTSC, 120, 96);
  TV.select_font(font4x6);

  //  TV.select_font(font6x8);
  TV.clear_screen();
  TV.delay(1500);
  TV.println("n2048");
  TV.delay(1000);
  randomSeed(analogRead(0));

  Serial.setTimeout(10);


}

void loop() {
  if (Serial.available()) {

    int p = Serial.parseInt();
    if (p != 0) {
      lastPos = p;
    }
  }
  tvDraw();

  //  TV.println(c);



  //  for (int i = 0; i < c; i++) {
  //    int x1 = random(0, TV.hres());
  //    int y1 = random(0, TV.vres());
  //    int x2 = random(0, TV.hres());
  //    int y2 = random(0, TV.vres());
  //
  //
  //    //    TV.draw_line(x1, y1, x2, y2, WHITE);
  //    TV.draw_rect(x1, y1, x2, y2, WHITE);

  //    if (h) {
  //      TV.draw_line(x1, y1, x2, y1, WHITE);
  //    }
  //    else {
  //      TV.draw_line(x1, y1, x1, y2, WHITE);
  //    }
  //  }
  //
  //  if (rand() > 0.9) {
  //    TV.clear_screen();
  //  }
  c++;

  //  if (c > 32) {
  //    c = 0;
  //    h = !h;
  //  }

  //  TV.draw_circle(TV.hres()/2,TV.vres()/2,TV.vres()/3,WHITE);
  //  TV.draw_rect(20,20,80,56,WHITE);
  //  TV.draw_rect(10,10,100,76,WHITE,INVERT);
  //  TV.draw_line(10,10,110,86,INVERT);
}


void tvDraw() {
  TV.println(lastPos);

  int maxPos = 1600;

  int x = map(lastPos, 0, maxPos, 0, TV.hres());

  int x1 = constrain(x  - random(0, TV.hres()) / 20, 0, TV.hres());
  int y1 = random(0, TV.vres() / 2);
  int x2 = constrain(x + random(0 , TV.hres()) / 20, 0, TV.hres());
  int y2 = random(TV.vres() / 2, TV.vres());

  TV.draw_rect(x1, y1, x2, y2, WHITE);
}
