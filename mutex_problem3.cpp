#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

class MyData
{
    int i;
    string s;
public:
    void doTask(int ii, string ss)
    {
        i = ii;
        s = ss;
        cout << " i = " << i << " s = " << s << endl;
    };
};

class DataWrapper
{
    private:
        MyData data;
        mutex m;
    public:
        template<typename Function>
            void processData(Function userFunc) 
            {
                lock_guard<mutex> lock(m);
                userFunc(data);
            }
};

void goodFunction(MyData& protectedData)
{
    protectedData.doTask(1, "my string");
}

MyData* unprotected;

void badFunction(MyData& protectedData)
{
    unprotected = &protectedData; 
}

DataWrapper w;

void foo()
{
    w.processData(goodFunction);

    unprotected->doTask(99, "hacked string");
}

int main()
{
    thread t(foo);
    t.join();
    return 0;
}
