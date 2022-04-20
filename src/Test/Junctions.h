#ifndef JUNCTIONS_H
#define JUNCTIONS_H

#include "Junction.h"

/* Static class holding Junction instances */
class Junctions
{
public:
  static Junction A, B, C, D, E, F, G, H;
  static constexpr Junction *const All[8] = { &A, &B, &C, &D, &E, &F, &G, &H };

  static void Init();
  static Junction const *const ById(JunctionId id);
};

#endif // JUNCTIONS_H
