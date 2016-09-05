
class Robot {
public:
  Robot();
  long getDistanceInInches();
  void reverse();
  void forward();
  void setSpeed(int wheel, int speed);
  void stop(int wheel);
  void turnLeft(long seconds);
  void turnRight(long seconds);
private:
  void move(int wheel, bool reverse);
  const int pingPin = 5;
  // connect motor controller pins to Arduino digital pins
  // motor one
  const int enA = 10;
  const int in1 = 9;
  const int in2 = 8;
  // motor two
  const int enB = 5;
  const int in3 = 7;
  const int in4 = 6;
  long microsecondsToCentimeters(long microseconds);
  long microsecondsToInches(long microseconds);
};

Robot::Robot(void) {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  forward();
}

long
Robot::getDistanceInInches() {

  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);

  return inches;
}

void Robot::forward() {
  move(0, false);
  move(1, false);
}

void Robot::reverse() {
  move(0, true);
  move(1, true);
}

void Robot::move(int wheel, bool reverse)
{
  if (wheel == 0) {
    if (reverse == true) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
  } else {
    if (reverse == true) {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    } else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }   
  }
}

void Robot::turnLeft(long seconds)
{
  unsigned long time = millis() + (seconds * 1000);
  while (millis() < time) {
    move(0, true);
    move(1, false);
  }
}


void Robot::turnRight(long seconds)
{
  unsigned long time = millis() + (seconds * 1000);
  while (millis() < time) {
    move(0, false);
    move(1, true); 
  }
}

void Robot::setSpeed(int wheel, int speed)
{
  if (speed > 255) {
    speed = 255;
  }
  if (speed < 0) {
    speed = 0;
  }
  if (wheel == 0) {
    analogWrite(enA, speed);
  } else {
    analogWrite(enB, speed);
  }
}

void Robot::stop(int wheel)
{
  if (wheel == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW); 
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

long Robot::microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long Robot::microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

Robot *robot;

void setup()
{
  Serial.begin(9600);
  robot = new Robot();
}

void wanderAndAvoid()
{

  long inches;


  inches = robot->getDistanceInInches();
  if (inches < 8) {
    robot->stop(0);
    robot->stop(1);
    delay(2000);
    robot->reverse();
    delay(1000);
    robot->stop(0);
    robot->stop(1);
    int randomnumber;
    randomnumber = rand() % 10;
    if (randomnumber < 5) {
      robot->turnLeft(1 + randomnumber / 3);
    } else {
      robot->turnRight(1 + randomnumber / 3);
    }
  } 
  robot->forward();
}

void loop()
{
  wanderAndAvoid();
  delay(200);
}
