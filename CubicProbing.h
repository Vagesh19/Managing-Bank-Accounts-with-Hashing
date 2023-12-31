#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Quadratic Probing
    int dbsz=0;
    void ms(std::vector<int>& arr, int l, int r);
    void merge(std::vector<int>& arr, int l, int m, int r);
    int powermod(int a, int b, int c);
};

#endif // CUBICPROBING_H
