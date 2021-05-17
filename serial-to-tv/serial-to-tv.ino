#include <TVout.h>
#include <fontALL.h>

TVout TV;

long c = 0;
bool h = 1;
int margin = 1;

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
  TV.delay(1000);
  TV.println("n2048");
  TV.delay(1000);
  TV.clear_screen();
  randomSeed(analogRead(0));

  Serial.setTimeout(10);


}

void loop() {
  if (Serial.available()) {

    int p = Serial.parseInt();
    if (lastPos != p && p != 0) {
      tvDraw(float(p));
      lastPos = p;
    }

  }
  decorate();
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

  //    TV.draw_circle(TV.hres()/2,TV.vres()/2,TV.vres()/3,WHITE);
  //  TV.draw_rect(20,20,80,56,WHITE);
  //  TV.draw_rect(10,10,100,76,WHITE,INVERT);
  //  TV.draw_line(10,10,110,86,INVERT);
}


void tvDraw(float pos) {

  float maxPos = 1600;

  float a = map(pos, 0., maxPos, 0., maxPos * TWO_PI) / maxPos;
  float w = map(pos, 0., maxPos, 0., maxPos * TV.hres()) / maxPos;

  float x = (cos(a) * TV.vres()  + TV.hres()) / 2;
  float y = (sin(a) * TV.vres()  + TV.vres()) / 2;

  //  Serial.print("pos: ");
  //  Serial.println(pos);
  //  Serial.print("a: ");
  //  Serial.println(a / maxPos);
  //  Serial.print("[x,y] = [");
  //  Serial.print(x);
  //  Serial.print(",");
  //  Serial.print(y);
  //  Serial.println("]");

  if (pos != 0) {
    TV.clear_screen();
  }
  TV.println(x);
  TV.println(y);

  TV.draw_rect(0, TV.vres() / 3 + margin, w, TV.vres() / 3 - 2 * margin, WHITE, INVERT);
  //  TV.draw_line(TV.hres() / 2, TV.vres() / 2, x, y, INVERT);

}

void decorate() {
  int x1 = random(0, TV.hres());
  int x2 = random(0, TV.hres());
  TV.draw_rect(x1, margin , margin, TV.vres() / 3 - 2 * margin, WHITE, INVERT);
  TV.draw_rect(x2, TV.vres() * 2 / 3 + margin , margin, TV.vres() / 3 - 2 * margin, WHITE, INVERT);
}
