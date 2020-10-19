#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Wallet 
{
    private:
        int mMoney;
    public:
        Wallet(): mMoney(0){}
        int getMoney() { return mMoney; }
        void addMoney(int money) 
        {
            for(int i = 0; i< money; ++i) 
            {
                mMoney++;
            }
        }
};

int testMultithreadedWallet()
{
    Wallet walletObject;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.push_back(thread(&Wallet::addMoney, &walletObject, 1000));
    for (int i = 0; i < threads.size(); i++)
        threads.at(i).join();

    return walletObject.getMoney();
}

int main()
{
    int val = 0;
    for (int k = 0; k < 1000; k++)
    {
        if ((val = testMultithreadedWallet()) != 5000)
        {
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
    }
    return 0;
}
