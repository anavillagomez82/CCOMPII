#include <iostream>

class XVector
{
public:

  XVector(unsigned long s);
  XVector();
//private:
  int* v;
  unsigned long size, nelem;
};

XVector::XVector(umsigned long s)
{
  size=s;
  nelem=0;
  v= new int[size];
}
XVector::-XVector()
{
   delete[];
}
int XVector:: fi(unsigned long i){
    return 
int main()
{
    XVector v(5);

    xv.set(0,10);
    xv.set(1,20);
    xv.set(2,30);
    xv.set(3,40);
    xv.set(4,50);

    int a= xv.fi(3);
    xv.fi(3)=100;


