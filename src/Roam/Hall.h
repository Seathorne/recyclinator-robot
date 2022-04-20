#ifndef _HALL_H
#define _HALL_H

#include "Arduino.h" // For NULL, rand()

enum HallId
{
  A, AB, B,     C, CD, D,
  AE,   BF,     CG,   DH,
  E, EF, F, FG, G, GH, H,
};

enum Direction
{
  North,
  South,
  East,
  West,
};

class Hall
{
public:
  Hall(HallId id);
  Hall(HallId id, const Hall *north, const Hall *south, const Hall *east, const Hall *west);

  void setConnection(Direction dir, const Hall *connection);

  HallId getId() const;
  const Hall *getConnection(Direction dir) const;
  const Hall *getConnection() const;

private:
  HallId _id;
  const Hall *_connections[4] = { NULL, NULL, NULL, NULL }; // 1 connection per cardinal direction
};

#endif // _HALL_H
