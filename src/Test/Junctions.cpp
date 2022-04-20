#include "Junctions.h"

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
