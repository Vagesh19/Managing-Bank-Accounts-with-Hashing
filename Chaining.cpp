#include "Chaining.h"
using namespace std;
void Chaining::createAccount(std::string id, int count) {
    int ha = hash(id);
    if(bankStorage2d.size()==0){
        for(int i=0;i<50021;i++){
            vector<Account> *temp= new vector<Account>;
            bankStorage2d.push_back(*temp);
        }
    }
    int i=0;
    Account *acc = new Account();
    acc->balance = count;
    acc->id= id;
    bankStorage2d[ha].push_back(*acc);
    dbsize++;
}
std::vector<int> Chaining::getTopK(int k) {
    vector<int> all;
    for(int i=0;i<bankStorage2d.size();i++){
        for(int j=0; j<bankStorage2d[i].size();j++){
            all.push_back(bankStorage2d[i][j].balance);
        }
    }
    ms(all,0,all.size()-1);
    if(all.size()>k){
        for(int i=all.size()-1; i>=k; i--){
            all.pop_back();
        }
    }
    return all;
}
void Chaining::merge(std::vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    std::vector<int> L(len1), R(len2);
    for (int i = 0; i < len1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < len2; ++j) {
        R[j] = arr[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < len1 && j < len2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < len2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void Chaining::ms(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = (l+r)/ 2;
        ms(arr, l, m);
        ms(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
int Chaining::getBalance(std::string id) {
    int ha = hash(id);
    int i=0;
    bool found=false;
    for(;i<bankStorage2d[ha].size();i++){
        if(bankStorage2d[ha][i].id==id){
            found=true;
            break;
        }
    } 
    if(found){
        return bankStorage2d[ha][i].balance;
    }
    else{
        return -1;
    } 
}

void Chaining::addTransaction(std::string id, int count) {
    int ha = hash(id);
    int i=0;
    bool found=false;
    if(bankStorage2d.size()==0){
        createAccount(id,count);
    }
    else{
        for(;i<bankStorage2d[ha].size();i++){
            if(bankStorage2d[ha][i].id==id){
                found=true;
                break;
            }
        }
        if(found){
            bankStorage2d[ha][i].balance+=count;  
        }
        else{
            createAccount(id,count);
        }
    }
}

bool Chaining::doesExist(std::string id) {
    int ha = hash(id);
    int i=0;
    bool found=false;
    if(bankStorage2d.size()==0){
        return false;
    }
    for(;i<bankStorage2d[ha].size();i++){
        if(bankStorage2d[ha][i].id==id){
            found=true;
            break;
        }
    }
    return found;
}

bool Chaining::deleteAccount(std::string id) {
    if(!doesExist(id)){
        return false;
    }
    else{
        int ha= hash(id);
        int i=0;
        for(;i<bankStorage2d[ha].size();i++){
            if(bankStorage2d[ha][i].id==id){
                break;
            }
        }
        bankStorage2d[ha].erase(bankStorage2d[ha].begin()+i);
        dbsize--;
        return true;
    }
}

int Chaining::databaseSize() {
    return dbsize;
}
int Chaining::powermod(int a, int b,int c){
    if (a==0){
        return 0;
    }
    if (b==0){
        return 1;
    }
    long long int y;
    if (b%2==0) {
        y=powermod(a, b / 2, c);
        y=(y*y) % c;
    }
    else {
        y=a%c;
        y=(y*powermod(a,b-1,c)%c)%c;
    }
    return (int)((y+c)%c);
}
int Chaining::hash(std::string id) {
    int sum=0;
    int p=50021;
    int i=1;
    for (char c: id){
        if(i<=4){
            sum=((sum)%p+powermod((int)c,i+3,p))%p;
            i++;
        }
        else if(c!='_'){
            sum=((sum)%p+powermod((int)c,i,p))%p;
            i++;
        }
        if(i==11){
            i=5;
        }
    }
    return sum;
}