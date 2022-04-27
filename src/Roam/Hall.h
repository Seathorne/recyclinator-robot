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
  static constexpr const double HallWidthDefault = 243.84; // 243.84cm = 8ft

  Hall(HallId id, double width = HallWidthDefault);
  Hall(HallId id, const Hall *north, const Hall *south, const Hall *east, const Hall *west, double width = HallWidthDefault);

  void setConnection(Direction dir, const Hall *connection);
  
  HallId getId() const;
  void setLength(double length);
  double getLength() const;
  double getWidth() const;
  const Hall *getConnection(Direction dir) const;
  const Hall *getConnection() const;

  bool isWallConst(double y, Side side, double &distance) const;
  bool isWidthConst(double y, double &width) const;

  double xSetpointAt(double y) const;

  static constexpr int SetpointCount = 100;
  double *_xSetpoints;
  double *_wallDistances[2];

private:
  HallId _id;
  double _length, _width;
  const Hall *_connections[4] = { NULL, NULL, NULL, NULL }; // 1 connection per cardinal direction

  int yToIndex(double y) const;
};

#endif // _HALL_H
