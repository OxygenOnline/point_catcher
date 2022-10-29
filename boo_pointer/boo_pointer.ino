#include <LiquidCrystal.h>
// character icons
#include "Icons.h"
#include "Coords.cpp"

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int column = 20, row = 4;
// const int column = 16, row = 2;

// joystick
const int SW_PIN = A2;
const int X_PIN = A0;
const int Y_PIN = A1;

// ------------------------------------------------------------------------------------------- //

// position of playable character, item
Coordinates player = Coordinates();
Coordinates item = Coordinates();

int points = 0;

// for delaying in loop()
unsigned long t0 = 0;
unsigned long start, finish;
unsigned long duration = 0;
bool endless;

// ------------------------------------------------------------------------------------------- //

void setup()
{
  lcd.begin(column, row);
  lcd.createChar(0, player_icon);
  lcd.createChar(1, item_icon);

  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);

  randomSeed(analogRead(5));

  welcome_message();

  while (true)
  {
    int timer_x = decode(X_PIN);
    int timer_y = decode(Y_PIN);
    bool button = pushed();
    if (button || timer_x != 0 || timer_y != 0)
    {
      if (!button)
      {
        set_timer();
        endless = false;
      }
      else
      {
        endless = true;
      }

      lcd.clear();
      lcd.home();
      lcd.print("Starting");
      for (int i = 0; i < 3; i++)
      {
        delay(300);
        lcd.print(".");
      }
      delay(500);

      // player + item draw
      draw(true, player, 0);
      while (item == player)
      {
        item = Coordinates(random(column), random(row));
      }
      draw(false, item, 1);
      break;
    }
  }

  start = millis();
}

// ------------------------------------------------------------------------------------------- //

void loop()
{

  if (pushed() || (!endless && millis() - start >= duration))
  {
    finish = millis();
    quit_menu();
    exit(0);
  }

  // joystick reading interval
  if (t0 + 150 < millis())
  {

    const int x_move = decode(X_PIN);
    const int y_move = decode(Y_PIN);

    // joystick not in default position
    if (x_move != 0 || y_move != 0)
    {
      player = Coordinates(player.x() + x_move, player.y() + y_move);
      draw(true, player, 0);

      // player on same field as item
      if (player == item)
      {
        points++;
        item = Coordinates(random(column), random(row));
      }
      draw(false, item, 1);

      t0 = millis();
    }
  }
}

// ------------------------------------------------------------------------------------------- //

void welcome_message()
{
  String welcome1 = "Press > endless mode";
  String welcome2 = "Toggle > timer";
  lcd.setCursor(0, 0);
  lcd.print(welcome1);
  lcd.setCursor(0, 1);
  lcd.print(welcome2);
  // scrolling for smaller displays
  unsigned long delay_time = millis();
  int welcome_length = welcome1.length();
  if (welcome2.length() > welcome_length)
  {
    welcome_length = welcome2.length();
  }
  if (column < welcome_length)
  {
    while (delay_time + 1500 > millis()) {
      if (pushed()) {
        return;
      }
    }
    int scroll = welcome_length - column;
    for (int i = 0; i < scroll; i++)
    {
      lcd.scrollDisplayLeft();
      delay_time = millis();
      while (delay_time + 300 > millis()) {
        if (pushed()) {
          return;
        }
      }
    }
    delay_time = millis();
    while (delay_time + 1500 > millis()) {
      if (pushed()) {
        return;
      }
    }
    for (int i = 0; i < scroll; i++)
    {
      lcd.scrollDisplayRight();
      delay_time = millis();
      while (delay_time + 300 > millis()) {
        if (pushed()) {
          return;
        }
      }
    }
  }
}

void set_timer()
{
  lcd.clear();
  lcd.home();
  lcd.print("Setting time:");
  lcd.setCursor(0, 1);
  lcd.print("Move UP or DOWN");
  duration = 120000;
  delay(1000);
  while (true)
  {
    int diff = decode(Y_PIN);
    if (diff != 0)
    {
      lcd.clear();
      lcd.home();
      duration += (-1) * diff * 30 * 1000;
      if (duration < 30000)
      {
        duration = 30000;
      }
      if (duration > 300000)
      {
        duration = 300000;
      }
      lcd.print("Time: ");
      lcd.print(duration / 1000);
      lcd.print(" s");
      lcd.setCursor(0, 1);
      lcd.print("Press to start.");
      delay(300);
    }

    if (pushed())
    {
      break;
    }
  }
}

void draw(bool clear, Coordinates coords, byte symbol)
{
  if (clear)
  {
    lcd.clear();
  }
  lcd.setCursor(coords.x(), coords.y());
  lcd.write(symbol);
}

void quit_menu()
{
  lcd.clear();
  lcd.home();
  lcd.print("Quitting game");
  for (int i = 0; i < 3; i++)
  {
    delay(300);
    lcd.print(".");
  }
  delay(500);
  lcd.clear();
  lcd.home();
  lcd.print("Score: ");
  lcd.print(points);
  lcd.print("p");
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print((finish - start) / 1000);
  lcd.print("s");
  delay(1000);
}

int decode(int pin)
{
  int position = analogRead(pin);
  const int sensitivity = 100;
  const int min = sensitivity, max = 1024 - sensitivity;
  if (position < min)
  {
    return -1;
  }
  else if (position > max)
  {
    return 1;
  }
  return 0;
}

bool pushed()
{
  return !digitalRead(SW_PIN);
}

// ------------------------------------------------------------------------------------------- //
