#pragma once
#include "../csand.hh"

Color GetRandomColor(Color min, Color max) {
  Color NewColor;
  NewColor.r = GetRandomValue(min.r, max.r);
  NewColor.g = GetRandomValue(min.g, max.g);
  NewColor.b = GetRandomValue(min.b, max.b);
  NewColor.a = GetRandomValue(min.a, max.a);
  return NewColor;
}