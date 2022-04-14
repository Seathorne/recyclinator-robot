#ifndef JUNCTION_H
#define JUNCTION_H

#include <stddef.h>

enum Direction {
  North,
  South,
  East,
  West,
};

enum JunctionId {
  A, B, C, D, E, F, G, H,
};

class Junction
{
public:
  bool connectsTo(Junction const& dest, Direction &dir);
  Junction const* next(Direction dir) const;
  Junction const* prev(Direction dir) const;

  static Direction Opposite(Direction dir);
  static void Link(Junction &prev, Junction &next, Direction dir, bool twoway = true);

private:
  JunctionId _id;
  Junction const* _nexts[4] = { NULL, NULL, NULL, NULL };
  Junction const* _prevs[4] = { NULL, NULL, NULL, NULL };
};

/* Static class holding Junction instances */

class Junctions
{
public:
  static Junction A, B, C, D, E, F, G, H;
  static constexpr Junction *const All[8] = { &A, &B, &C, &D, &E, &F, &G, &H };

  static void Init();
  static Junction const *const ById(JunctionId id);
};

#endif // JUNCTION_H
