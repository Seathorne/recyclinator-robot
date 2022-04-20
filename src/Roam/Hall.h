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

enum Side
{
  Left,
  Right,
};

class Hall
{
public:
  static constexpr const double HallWidthDefault = 244; // 244cm (8ft)

  Hall(HallId id, double width = HallWidthDefault);
  Hall(HallId id, const Hall *north, const Hall *south, const Hall *east, const Hall *west, double width = HallWidthDefault);

  void setConnection(Direction dir, const Hall *connection);
  
  HallId getId() const;
  double getWidth() const;
  const Hall *getConnection(Direction dir) const;
  const Hall *getConnection() const;
  bool isWallConst(double y, Side side) const;

private:
  HallId _id;
  double _width;
  const Hall *_connections[4] = { NULL, NULL, NULL, NULL }; // 1 connection per cardinal direction
};

#endif // _HALL_H
