#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <string>
#include <algorithm>
#include <random>

class BankAccount{
    std::string accountNumber;
    float balance;
public:
    BankAccount(){
    }

    BankAccount(std::string accountNumber, float balance = 0)
    :accountNumber(accountNumber),balance(balance)
    {
    }

    std::string getAccountNumber()
    {
	    return this->accountNumber;
    }
};

//INTERFACE - gränssnitt "standard"
class IAccountStorage {
public:    
    virtual void addAccount(BankAccount account) = 0;
	virtual BankAccount *findAccount(std::string accountNumber) = 0;        
};

// BINARY SEARCH  

class BinarySearchStorage : public IAccountStorage {

    std::vector<BankAccount> accounts;

public:

    void printAccounts() {
        for (BankAccount x : accounts) { std::cout << x.getAccountNumber() << std::endl; }
    }

    void addAccount(BankAccount newAccount) {
        accounts.push_back(newAccount);
    }

    void shuffleAccounts() {

        std::random_device r;
        std::mt19937 g(r());

        std::shuffle(accounts.begin(), accounts.end(), g);
    }

    

    BankAccount* findAccount(std::string query) {

        BankAccount* searchResult = nullptr;

        int start = 0;
        int end = accounts.size() - 1;
        // int mid = 0;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;

            // Account found
            if (accounts[mid].getAccountNumber() == query)
            {
                return &accounts[mid];
            }
            // Account is on right side
            if (accounts[mid].getAccountNumber() < query)
            {
                start = mid + 1;
            }
            // Account is on left side
            else
            {
                end = mid - 1;
            }
        }

        return searchResult;
    }
};

class Bank
{
private:
	IAccountStorage * accountStorage;
public:
	Bank(IAccountStorage *storage):accountStorage(storage){

    }
	bool addAccount(std::string accountNumber){
        //validate
        //if something (accountNumber) return false
        accountStorage->addAccount(accountNumber);
        return true;
    }
	BankAccount *getAccount(std::string accountNumber){
        return accountStorage->findAccount(accountNumber);
    }
};

class MapAccountStorage: public IAccountStorage{
    std::map<std::string,BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts[account.getAccountNumber()] = account;
    }
    BankAccount *findAccount(std::string accountNumber){
        return &(accounts[accountNumber]);
    }

};

class DistributedVectorAccountStorage : public IAccountStorage{
    
    std::vector<BankAccount> accountsStartingWith0;
    std::vector<BankAccount> accountsStartingWith1;
    std::vector<BankAccount> accountsStartingWith2;
    std::vector<BankAccount> accountsStartingWith3;
    std::vector<BankAccount> accountsStartingWith4;
    std::vector<BankAccount> accountsStartingWith5;
    std::vector<BankAccount> accountsStartingWith6;
    std::vector<BankAccount> accountsStartingWith7;
    std::vector<BankAccount> accountsStartingWith8;
    std::vector<BankAccount> accountsStartingWith9;
    std::vector<BankAccount> empty;

    std::vector<BankAccount> &getRef(char firstChar){

        switch(firstChar){
            case '0':
                return accountsStartingWith0;
            case '1':
                return  accountsStartingWith1;
            case '2':
                return accountsStartingWith2;
            case '3':
                return accountsStartingWith3;
            case '4':
                return accountsStartingWith4;
            case '5':
                return  accountsStartingWith5;
            case '6':
                return accountsStartingWith6;
            case '7':
                return accountsStartingWith7;
            case '8':
                return accountsStartingWith8;
            case '9':
                return  accountsStartingWith9;
        }
        return empty;
    }


public:

    void addAccount(BankAccount account) override{
        std::vector<BankAccount> &ref = getRef(account.getAccountNumber()[0]);
        ref.push_back(account);
    }
    BankAccount *findAccount(std::string accountNumber){
        std::vector<BankAccount> &ref = getRef(accountNumber[0]);
        BankAccount *ret = nullptr;
        for(BankAccount &account : ref){
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return ret;
    }
};

class VectorAccountStorage: public IAccountStorage{
        std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts.push_back(account);
    }

    BankAccount *findAccount(std::string accountNumber){
        BankAccount *ret = nullptr;
        for(BankAccount &account : accounts){
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return ret;
    }
    

};

void addPadding(std::string &accountNumber) {

    int paddingAmount = 10 - accountNumber.size();

    for (int i = 0; i < paddingAmount; i++)
    {
        accountNumber.insert(0, "0");
    }
}

int main(int, char**){
    //VectorAccountStorage storage;
    //DistributedVectorAccountStorage storage;
    //MapAccountStorage storage;

    // BinarySearchStorage
    BinarySearchStorage binaryStorage;

    Bank bank(&binaryStorage);
    
    const int AntalAccounts =  10;


    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 

    std::cout << "INITIALIZE: " << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();

    for(int i = 0;i < AntalAccounts; i++){
        std::string accountNumber =  std::to_string(i);
        addPadding(accountNumber);

        if(i == 0){
            sFirst = accountNumber;
        }
        if(i == AntalAccounts-1){
            sLast = accountNumber;
        }
        bank.addAccount(accountNumber);
        
    }

    binaryStorage.shuffleAccounts();
    //binaryStorage.sortAccounts();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    BankAccount *p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;
}
