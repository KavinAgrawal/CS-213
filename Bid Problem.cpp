#include <iostream>
#include <algorithm>
using namespace std;

struct Bidder{
    int hb,sb;
};

float exp1(int* a,int n,Bidder* b,int k){
    int s=0;
    if(k==n){
        for(int i=0;i<n;i++){
            s=max(a[i],s);
        }
    }
    else{
            a[k]=b[k].hb;
            s+=exp1(a,n,b,k+1);
            a[k]=b[k].sb;
            s+=exp1(a,n,b,k+1);

    }
    return s;
}


int main()
{

   int n;
   cin >> n;
   Bidder b[n];
   for(int i=0;i<n;i++){
       cin >> b[i].hb >> b[i].sb;
   }

   int a[n];
   float s=exp1(a,n,b,0);
   cout << s/pow(2,n) << endl;


   sort(b,b+n,
        [](const Bidder& first, const Bidder& second) ->bool {return max(first.hb,first.sb)>max(second.hb,second.sb);});
        float r=1,exp2=0;int t=0;
   for(int i=0;i<2*n;i++){
        t=max(min(b[i].hb,b[i].sb),t);
        r=r/2;
        exp2=exp2+r*max(b[i].hb,b[i].sb);
        if(t>=max(b[i+1].hb,b[i+1].sb)||i+1==n){
            exp2=exp2+t*r;
            break;
        }
   }
   cout << exp2 << endl;
   return 0;
}
