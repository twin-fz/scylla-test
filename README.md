# scylla-test
C++ Code Test

The implementation approach:

As dictated by the starter snippet, the input vector is passed in as a const to function f, it cannot be modified. So an output vector must be created locally
and returned (at the cost of copying a whole vector, which is inefficient).

Since multiple threads will take turn process the elements in the input vector, there must be a way to synchronize them to avoid multiple threads working on the same
element. For this, I use the an atomic integer as an index, which can be incremented atomically by each thread. Because each element of the input and output vectors
are accessed only by a one of the threads, they are thread safe, and will not interfere with each other.

Notes:
- Though I had read about conditional variables before, but because I haven't used them at all, I chose not use them in this code.
- I don't know C++17, as my knowledge is mostly C++98 and C++03, and on real-time systems, we weren't allowed to use all their features either, e.g. STL.
- I started learning a little bit of C++11 at icetana

How to build and run the code:
1. Copy the code in main.cpp
2. Paste to https://www.onlinegdb.com/online_c++_compiler
3. Click Run button
