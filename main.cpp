
/******************************************************************************
Summary

Given class A which contains public numeric template function f with argument
std::vector<numeric type> and this vector size is predefined.

Your task is to apply some operation (for example you can just simply multiply by some random
number) on every single element of a vector in different threads and return the changed vector.
See below the starter snippet:

#include <iostream>
class A
{
public:
   template<typename T>
   std::vector<T> f(const std::vector<T>& vec);
   
public:
   static constexpr int num_threads = 8;
   
private:
   std::vector<std::thread> processors_;
};

*******************************************************************************/

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

using namespace std;

class A
{
    public:
        // Entry point for all threads
        template<typename T>
        static void startThread(int threadNumber, const std::vector<T>& input, std::vector<T>& outVec, std::atomic<int>& index, int maxCount)
        {
            cout << "Entering thread " << threadNumber << endl;
            int ii;
            
            // Atomic increment of index and save the value to local variable. This guarantees each thread operate on
            // a different element in the input and output vectors
            while ( (ii = ++index) < maxCount)
            {
                // Since we are reading a specific memory location from the input vector that no other thread reads,
                // this is safe. Likewise, the output vector location is also unique to this thead, and is thread safe.
                outVec[ii] = input[ii] * 2;
            }
            
            cout << "Exiting thread " << threadNumber << endl;
        }
        
        template<typename T>
        std::vector<T> f(const std::vector<T>& input)
        {
            // Get size of input vector
            const int maxCount = input.size();
            
            // Create the output vector to the same size as input vector
            std::vector<T> output(maxCount);
            
            // To allow multiple threads to read different elements from the input vector
            // we use an atomic index to avoid race condition between threads trying to update it.
            // Initial value is set to -1, as each thread will increment the index before getting
            // the value from the input vector to process
            std::atomic<int> index(-1);
            
            // For this test, we create all the worker threads in this function and remove them when done
            for (int ii = 0; ii < A::numThreads; ++ii) 
            {
                // Each thread will execute function startThread, and process the input vector until index reaches the end
                threadList.push_back(std::thread(A::startThread<T>, ii, input, std::ref(output), std::ref(index), maxCount));
            }
            
            // Wait for all threads to finish
            for (int ii = 0; ii < threadList.size(); ++ii) 
            {
                threadList[ii].join();
            }
            
            threadList.clear();
            
            return output;
        }        
        
    public:
        static constexpr int numThreads = 8;
        
    private:
        std::vector<std::thread> threadList;
};

int main()
{
    cout << "Hello World" << endl;

    std::vector<int> input;
    
    // Initialize input vector
    for (int ii = 0; ii < 20; ++ii)
    {
        input.push_back(ii);
    }
    
    // Create class A object
    A myA;
    
    // Call function f() to process the input vector
    std::vector<int> output = myA.f(input);
    
    // Display output vector
    for (int ii = 0; ii < output.size(); ++ii)
    {
        cout << ii << ": " << output[ii] << endl;
    }
    
    cout << "Goodbye World" << endl;
    
    return 0;
}
