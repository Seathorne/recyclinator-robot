#include "Junction.h"

bool Junction::connectsTo(Junction const& dest, Direction &dir) {
  for (int i = 0; i < 4; i++) {
    dir = (Direction)i;
    Junction const* j = next(dir);
    if (j && (j->_id == dest._id)) {
      return true;
    }
  }
  return false;
}

JunctionId Junction::id() const {
  return _id;
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
