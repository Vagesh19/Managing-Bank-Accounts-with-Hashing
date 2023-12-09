#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
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
    // Other data members and functions specific to Chaining
    int dbsize=0;
    void ms(std::vector<int>& arr, int left, int right);
    void merge(std::vector<int>& arr, int left, int middle, int right);
    int powermod(int a, int b, int c);
};

#endif // CHAINING_H
