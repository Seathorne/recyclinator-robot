#ifndef _HALLS_H
#define _HALLS_H

#include "Hall.h"

class Halls {
public:
  static void init();
  static void setConnection(Hall *a, Hall *b, Direction dir);
  static const Hall *getById(HallId id);

private:
  static Hall _halls[(int)(HallId::H) + 1];
  static Hall *_getById(HallId id);
};

#endif // _HALLS_H
