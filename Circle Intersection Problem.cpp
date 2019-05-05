#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

template <typename T>
void exchange(T &f, T& s){ T t = f; f = s; s = t;}

struct point{
  double x,y;
  point(){
    x=0;y=0;
  }
  point(double x1,double y1,double r,char t){
    if(t=='l'){x=x1-r;}
    if(t=='r'){x=x1+r;}
    if(t=='c'){x=x1;}
    y=y1;
  }
  bool operator==(const point &other){ return x == other.x && y == other.y;}
};

struct circle{
  double r;
  circle(){
    point lt,rt,c;
  }
  circle(double x1,double y1,double r1){
    point lt(x1,y1,r1,'l');
    point rt(x1,y1,r1,'r');
    point c(x1,y1,r1,'c');
    r=r1;
  }
  // bool operator<(const circle & rhs) const{
  //   bool res;
  //   if(top.y < rhs.top.y)
  //     res = orientation(top, bottom, rhs.top) == 2;
  //   else
  //     res = orientation(rhs.top, rhs.bottom, top) == 1;
  //   cout <<top.x<<','<<top.y<<"   "<<rhs.top.x<<','<<rhs.top.y<<": "<<res<<endl;
  //   return res;
  // }
};

struct ptseg{
  point pt; size_t segIndex;
  ptseg(point pp, size_t i){pt = pp; segIndex = i;}
};

bool intersect(circle cir1, circle cir2){
  int distSq = (cir1.c.x - cir2.c.x) * (cir1.c.x - cir2.c.x) + (cir1.c.y - cir2.c.y) * (cir1.c.y - cir2.c.y);
  int radSumSq = (cir1.r + cir2.r) * (cir1.r + cir2.r);
  if (distSq >= radSumSq)
    return false;
  else
    return true;
}

int main(){
  vector<circle> circles;

  while(cin >> ){
    double x,y,r;
    cin >> x >> y >> r;
    cout << "Yes";
    circle cir(x,y,r);
    circles.push_back(cir);
  }

  vector<ptseg>ptls; // Endpoints with link back to segments
  for(size_t i=0; i<circles.size(); i++){
    ptls.push_back(ptseg(circles[i].lt, i));
    ptls.push_back(ptseg(circles[i].rt, i));
  }

  sort(ptls.begin(),ptls.end(),  // sort top to bottom
       [](ptseg &p, ptseg &q)
       {return p.pt.x < q.pt.x;});

  set<circle> S;
  bool found = false;
  for(auto p : ptls){
    if(p.pt == circles[p.segIndex].lt){
      S.insert(circles[p.segIndex]).lt;
      auto l = S.find(circles[p.segIndex])
      if(next(l) != S.end() && intersect(*l, *next(l))){
        found = true; break;
      }
      if(l != S.begin() && intersect(*l, *prev(l))){
        found = true; break;
      }
    }
    else{  // bottom endpoint
      auto l = S.find(circles[p.segIndex]);
      if(next(l) != S.end() && prev(l) != S.end()&& intersect(*prev(l), *next(l))){
        found = true; break;
      }
      S.erase(l);
    }
  }
  cout <<"intersection: "<<found<<endl;
}
