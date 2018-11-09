#ifndef __BODY_H__
#define __BODY_H__

#include <vector>

struct GridPos {
  int x = 0;
  int y = 0;
};


typedef GridPos BodyPart;


class Body {
 private:

  std::vector<BodyPart> body;
  
  unsigned int head = 0;
  std::vector<BodyPart>::iterator headIt = body.begin();

  int direction = 0; // 0: move right, 1: move down, 2: move left, 3: move up

  unsigned int defaultInitialSize = 3;

  void updateHead();

 public:
  
  Body(const int& x0=0, const int& y0=0, const int& dir0=0, const unsigned int& initialSize=0);

  unsigned int size() const { return body.size(); }
  GridPos getNewHeadPos(const int direction) const;

  const BodyPart& operator[](unsigned int idx) const;
        BodyPart& operator[](unsigned int idx);

  bool move  (const int direction);
  void extend(const int direction);
};

#endif // __BODY_H__
