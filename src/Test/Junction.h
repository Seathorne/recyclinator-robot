#ifndef JUNCTION_H
#define JUNCTION_H

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
  bool connectsTo(Junction const &dest, Direction &dir);
  
  JunctionId id() const;
  Junction const* next(Direction dir) const;
  Junction const* prev(Direction dir) const;

  static Direction Opposite(Direction dir);
  static void Link(Junction &prev, Junction &next, Direction dir, bool twoway = true);

private:
  JunctionId _id;
  Junction const* _nexts[4];
  Junction const* _prevs[4];
};

#endif // JUNCTION_H
