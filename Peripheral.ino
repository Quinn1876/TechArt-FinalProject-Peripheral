#include "Arduino.h"
#include "Servo.h"
#include "MirrorServo.hpp"

#define NUM_PATTERNS 3

using namespace TechArt;

// HARDWARE UNO
MirrorServo servos[10] = {
    MirrorServo(2, 90),
    MirrorServo(3, 90),
    MirrorServo(4, 90),
    MirrorServo(7, 90),
    MirrorServo(8, 90),
    MirrorServo(13, 90),
    MirrorServo(A2, 90),
    MirrorServo(A3, 90),
    MirrorServo(A0, 90),
    MirrorServo(A1, 90),
};

Lazer lazers[5] = {
  Lazer(5),
  Lazer(6),
  Lazer(9),
  Lazer(10),
  Lazer(11),
};

int angles[NUM_PATTERNS][10] = {
  {
    0,0,0,0,0,
    0,0,-19,23,0
  },
  {
    -19,0,0,0,5,
    -14,0,-7,0,37
  },
  {
    0,-15,40,0,-20,
    -10,0,-25,0,0,
  }
};

int lazerLevels[NUM_PATTERNS][5] = {
  {
    0,1,0,0,0
  },
  {
    0,0,0,1,1
  },
  {
    1,1,0,0,1
  }
};
// Show
Pattern patterns[NUM_PATTERNS] = {
  Pattern(1000, angles[0], lazerLevels[0]),
  Pattern(1000, angles[1], lazerLevels[1]),
};

void zero() {
  for (auto & servo : servos) {
    servo.setAngle(0);
  }
}

void setup() {
    for (auto& servo : servos) {
        servo.initialize();
    }
    for(auto& lazer : lazers) {
      lazer.initialize();
    }
    Serial.begin(9600);
}

void loop() {
  static int lights[5] = {
    1,1,0,0,1
  };
  static int angles[10] = {
    0,-15,40,0,-20,
    -10,0,-25,0,0,
  };
  static Pattern pattern(1000, angles, lights);
  pattern.applyPatternLazers(lazers);
  pattern.applyPatternServos(servos);  
  pattern.applyPatternDelay();

  // patterns[1].applyPatternLazers(lazers);
  // patterns[1].applyPatternServos(servos);  
  // patterns[1].applyPatternDelay();
  // zero();
  // pattern.applyPatternDelay();
}

