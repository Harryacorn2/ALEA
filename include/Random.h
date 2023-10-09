#ifndef Random_h
#define Random_h

class Random {
public:
    static unsigned long GetLong();
    static int GetInt(int i);
    static int GetIntInRange(int i, int j);
    
private:
    static unsigned long x;
    static unsigned long y;
    static unsigned long z;
};

#endif
