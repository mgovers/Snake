#ifndef __BODY_PART_H__
#define __BODY_PART_H__

class BodyPart {
 public:
  unsigned int x = 0;
  unsigned int y = 0;

  BodyPart(const unsigned int x_, const unsigned int y_):
    x(x_), y(y_) 
    {}
};

#endif // __BODY_PART_H__

