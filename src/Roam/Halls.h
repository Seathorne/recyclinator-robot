#ifndef _HALLS_H
#define _HALLS_H

#include "Hall.h"

class Halls {
public:
  static Hall JunctA, HallAB, JunctB,         JunctC, HallCD, JunctD,
              HallAE,         HallBF,         HallCG,         HallDH,
              JunctE, HallEF, JunctF, HallFG, JunctG, HallGH, JunctH;

  static void init();
  static void setConnection(Hall *a, Hall *b, Direction dir);
  static const Hall *getById(HallId id);
  
  static Direction opposite(Direction dir);
  static int degreesBetween(Direction a, Direction b);

private:
  static Hall *_halls[(int)(HallId::H) + 1];
};

#endif // _HALLS_H
