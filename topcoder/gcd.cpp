#include<cstring>
#include<cstdio>
#include<stdlib.h>
#include<string>
using std::string;

class ExerciseMachine {
public:
  int getPercentages(string time);
};

int Gcd1(int a, int b)
{
    if(b == 0)
        return a;
    return Gcd(b, a % b);
}

int Gcd2(int a, int b)
{
    while(b != 0)
    {
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

/**
    对于a' = b, b' = a % b 而言，我们求得 x, y使得 a'x + b'y = Gcd(a', b')
    b' = a % b = a - a / b * b
    a'x + b'y = Gcd(a', b')  ===>
    bx + (a - a / b * b)y = Gcd(a', b') = Gcd(a, b)  ===>
    ay +b(x - a / b*y) = Gcd(a, b)

  */
int exGcd(int a, int b, int &x, int &y) {
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int r = exGcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;

    return r;
}

int gcd(int a, int b) {
  if (a<0) a=-a;
  if (b<0) b= -b;
  int t=a;
  if (a<b) {
    a=b;
    b=t;
  } 
  while(b != 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}
int ExerciseMachine::getPercentages(string time) {
  int time_s = 0;
  char t[9];
  strncpy(t, time.c_str(), sizeof(t));
  time_s += atoi(t+6);
  t[5] = '\0';
  time_s += atoi(t+3)*60;
  t[2] = '\0';
  time_s += atoi(t)*3600;
  return gcd(time_s, 100)-1;
}

