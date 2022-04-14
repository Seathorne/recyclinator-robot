#include "Junction.h"

bool Junction::connectsTo(Junction const& dest, Direction &dir) {
  for (int i = 0; i < 4; i++) {
    dir = (Direction)i;
    Junction const* j = next(dir);
    if (j != NULL && j->_id == dest._id) {
      return true;
    }
  }
  return false;
}

Junction const* Junction::next(Direction dir) const {
  return _nexts[dir];
}

Junction const* Junction::prev(Direction dir) const {
  return _prevs[dir];
}

Direction Junction::Opposite(Direction dir) {
  switch (dir) {
    case North: return South;
    case South: return North;
    case East: return West;
    case West: return East;
  }
}

void Junction::Link(Junction &prev, Junction &next, Direction dir, bool twoway) {
  prev._nexts[dir] = &next;
  next._prevs[dir] = &prev;

  if (twoway) {
    Direction opp = Opposite(dir);
    prev._prevs[opp] = &next;
    next._nexts[opp] = &prev;
  }
}

/* Definitions for static class Junctions */

Junction Junctions::A;
Junction Junctions::B;
Junction Junctions::C;
Junction Junctions::D;
Junction Junctions::E;
Junction Junctions::F;
Junction Junctions::G;
Junction Junctions::H;

void Junctions::Init() {
  Junction::Link(A, B, East, true);
  // Junction::Link(B, C, East, true); // Not allowed in either direction
  Junction::Link(C, D, East, true);
      
  Junction::Link(A, E, South, true);
  Junction::Link(B, F, South, true);
  Junction::Link(C, G, South, true);
  Junction::Link(D, H, South, true);

  Junction::Link(E, F, East, true);
  Junction::Link(F, G, East, true);
  Junction::Link(G, H, East, true);
}

Junction const *const Junctions::ById(JunctionId id) {
  return All[id];
}
