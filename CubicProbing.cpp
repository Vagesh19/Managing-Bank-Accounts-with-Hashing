#include "CubicProbing.h"

void CubicProbing::createAccount(std::string id, int count)
{
    if (bankStorage1d.size() == 0)
    {
        for (int i = 0; i < 130043; i++)
        {
            Account *temp = new Account();
            temp->id = "";
            temp->balance = -2;
            bankStorage1d.push_back(*temp);
        }
    }
    int ha = hash(id);
    if (bankStorage1d[ha].balance < 0)
    {
        bankStorage1d[ha].balance = count;
        bankStorage1d[ha].id = id;
    }
    else
    {
        int i = ha;
        int m = 1;
        while (bankStorage1d[i].balance >= 0)
        {
            int probe = powermod(m, 3, 130043);
            i = ((i) % 130043 + probe) % 130043;
            m++;
        }
        bankStorage1d[i].balance = count;
        bankStorage1d[i].id = id;
    }
    dbsz++;
}
int CubicProbing::powermod(int a, int b, int c)
{
    if (a == 0)
    {
        return 0;
    }
    if (b == 0)
    {
        return 1;
    }
    long long int y;
    if (b % 2 == 0)
    {
        y = powermod(a, b / 2, c);
        y = (y * y) % c;
    }
    else
    {
        y = a % c;
        y = (y * powermod(a, b - 1, c) % c) % c;
    }
    return (int)((y + c) % c);
}
std::vector<int> CubicProbing::getTopK(int k)
{
    std::vector<int> all;
    if (bankStorage1d.size() == 0)
    {
        return all;
    }
    for (int i = 0; i < 130043; i++)
    {
        if (bankStorage1d[i].balance >= 0)
        {
            all.push_back(bankStorage1d[i].balance);
        }
    }
    ms(all, 0, all.size() - 1);
    if (all.size() > k)
    {
        for (int i = all.size() - 1; i >= k; i--)
        {
            all.pop_back();
        }
    }
    return all;
}
void CubicProbing::merge(std::vector<int> &arr, int l, int m, int r)
{
    int len1 = m - l + 1;
    int len2 = r - m;
    std::vector<int> L(len1), R(len2);
    for (int i = 0; i < len1; ++i)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < len2; ++j)
    {
        R[j] = arr[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < len1 && j < len2)
    {
        if (L[i] >= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < len1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < len2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void CubicProbing::ms(std::vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (r + l) / 2;
        ms(arr, l, m);
        ms(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int CubicProbing::getBalance(std::string id)
{
    int ha = hash(id);
    int i = ha;
    if (bankStorage1d.size() == 0)
    {
        return -1;
    }
    if (bankStorage1d[i].id == id)
    {
        return bankStorage1d[i].balance;
    }
    else
    {
        i = (i + 1) % 130043;
        int m = 2;
        while (ha != i && bankStorage1d[i].id != id && bankStorage1d[i].balance != -2)
        {
            int probe = powermod(m, 3, 130043);
            i = ((i) % 130043 + probe) % 130043;
            m++;
        }
        if (ha == i || bankStorage1d[i].balance == -2)
        {
            return -1;
        }
        else
        {
            return bankStorage1d[i].balance;
        }
    }
}

void CubicProbing::addTransaction(std::string id, int count)
{
    int ha = hash(id);
    int i = ha;
    if (bankStorage1d.size() == 0)
    {
        createAccount(id, count);
    }
    else
    {
        if (bankStorage1d[i].id == id)
        {
            bankStorage1d[i].balance += count;
        }
        else
        {
            i = (i + 1) % 130043;
            int m = 2;
            while (ha != i && bankStorage1d[i].id != id && bankStorage1d[i].balance != -2)
            {
                int probe = powermod(m, 3, 130043);
                i = ((i) % 130043 + probe) % 130043;
                m++;
            }
            if (ha == i || bankStorage1d[i].balance == -2)
            {
                createAccount(id, count);
            }
            else
            {
                bankStorage1d[i].balance += count;
            }
        }
    }
}

bool CubicProbing::doesExist(std::string id)
{
    int ha = hash(id);
    int i = ha;
    if (bankStorage1d.size() == 0)
    {
        return false;
    }
    if (bankStorage1d[i].id == id)
    {
        return true;
    }
    else
    {
        i = (i + 1) % 130043;
        int m = 2;
        while (ha != i && bankStorage1d[i].id != id && bankStorage1d[i].balance != -2)
        {
            int probe = powermod(m, 3, 130043);
            i = ((i) % 130043 + probe) % 130043;
            m++;
        }
        if (ha == i || bankStorage1d[i].balance == -2)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool CubicProbing::deleteAccount(std::string id)
{
    int ha = hash(id);
    int i = ha;
    if (bankStorage1d.size() == 0)
    {
        return false;
    }
    else
    {
        if (bankStorage1d[i].id == id)
        {
            bankStorage1d[i].balance = -1;
            bankStorage1d[i].id = "";
            dbsz--;
            return true;
        }
        else
        {
            i = (i + 1) % 130043;
            int m = 2;
            while (ha != i && bankStorage1d[i].id != id && bankStorage1d[i].balance != -2)
            {
                int probe = powermod(m, 3, 130043);
                i = ((i) % 130043 + probe) % 130043;
                m++;
            }
            if (ha == i || bankStorage1d[i].balance == -2)
            {
                return false;
            }
            else
            {
                bankStorage1d[i].balance = -1;
                bankStorage1d[i].id = "";
                dbsz--;
                return true;
            }
        }
    }
}
int CubicProbing::databaseSize()
{
    return dbsz;
}

int CubicProbing::hash(std::string id)
{
    int sum=0;
    int p=130043;
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
