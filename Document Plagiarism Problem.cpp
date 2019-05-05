#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int main(){
    vector <string> phrase;
    map <string,vector <int>> index;
    string str;
    for(int id=0;cin>>str && str!="*";id++){
            if(!any_of(str.begin(), str.end(), ::ispunct)){
                transform(str.begin(), str.end(), str.begin(), ::tolower);
                index[str].push_back(id);
            }
            else{
                if(!all_of(str.begin(), str.end(), ::ispunct)){
                        for (int i = 0, len = str.size(); i < len; i++){
                             if (ispunct(str[i])){
                                 str.erase(i--, 1);
                                 len = str.size();
                              }
                         }
                        transform(str.begin(), str.end(), str.begin(), ::tolower);
                        index[str].push_back(id);
                }
                else{
                       id--;
                }
            }
     }

while(cin.peek()!='\n'){
      cin >> str;
      phrase.push_back(str);
}

for(auto cNp:index){
    cout << cNp.first;
    for(size_t i=0;i<cNp.second.size();i++){
        cout << " "<< cNp.second[i] ;
    }
    cout << endl;
}
cout <<"* ";
int dif;

if(index.count(phrase[0])>0){
    for(size_t i=0;i<index[phrase[0]].size();i++){
            int p=0;
        dif=index[phrase[0]][i];
          for(size_t j=1;j<phrase.size();j++){
              if(index.count(phrase[j])>0){
                    for(size_t k=0;k<index[phrase[j]].size();k++){
                        if(dif==index[phrase[j]][k]-int(j)){
                          p=p+1;
                          break;
                        }
                        else {}
                    }
                    if(p==0) break;
              }
              else break;
          }
          if(p==int(phrase.size())-1) cout << index[phrase[0]][i] << " ";
    }
}
}
