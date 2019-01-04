#include <iostream>
#include <vector>
#include <string.h>
#include <benchmark/benchmark.h>

using namespace std;


struct node {
  int e[100];
  int a;
  float b;
  double c;
  char d;
};

template <typename T>
void printVect(vector<T> v) {

  for(auto &i:v) {
    i.printData();
  }
}


class testCopy {
  public:
    testCopy() {}
    testCopy(const node* dat) {
      memcpy(&n1, dat,sizeof(node));
      cout << "Inside regular constructor" << endl;  
    }
    testCopy(const testCopy& dat){
      memcpy(&n1, &dat.n1,sizeof(node));
      cout << "Inside copy constructor" << endl;
    }

    ~testCopy() {cout << "Inside testCopy Destructor" << endl; }
     void printData() { cout << "Values printed " << n1.a << " " << n1.b << " "<<n1.c<< " " << n1.d << endl; }

  private:
    node n1;
};


class testMove {
  public:
    testMove():n1(nullptr)  {}
    testMove(const node* dat) : n1{new node} { 
       memcpy(n1, dat,sizeof(node));
      cout << "Inside regular constructor" << endl;  
    }

    testMove(const testMove& dat){
      node *temp = new node;
      memcpy(temp, dat.n1, sizeof(node));
      n1=temp;
      cout << "Inside copy constructor" << endl;
    }

    testMove(testMove&& dat) noexcept : n1{dat.n1} {
      dat.n1 = nullptr;
      cout << "Inside move constructor" << endl;
    }

    testMove& operator=(testMove&& dat) noexcept {
      if(this != &dat) {
        if(n1) {
          delete n1;
        }
        n1 = dat.n1;
        dat.n1 = nullptr;
        cout << "Inside move assignment" << endl;
      }
      return *this;
    }

    ~testMove() { delete n1; n1=nullptr; cout << "Inside testMove Destructor" << endl;}
     void printData() { cout << "Values printed " << n1->a << " " << n1->b << " "<<n1->c<< " " << n1->d << endl; }

  private:
    node *n1=nullptr;
};

void vectorWorkCopy(int size) {
  vector<testCopy> v1;
  node *n1 = new node;

  for(auto i=1; i<=size; i++) {
    n1->a = i;
    n1->b = i;
    n1->c = i;
    n1->d = i;
    testCopy d1(n1);
    //d1.printData();
    //cout << "Will push back to vector.. d1 = " << &d1 << endl;
    v1.push_back(std::move(d1));
    //cout<< "Vector size " << v1.size() << " vector capacity" << v1.capacity()  << " Vect " << &(v1[i])<< endl;
    //v1[i-1].printData();
  }
  //printVect(v1);
  delete n1;
}

void vectorWorkMove(int size) {
  vector<testMove> v2;
  node *n1 = new node;

  for(auto i=1; i<=size; i++) {
    n1->a = i;
    n1->b = i;
    n1->c = i;
    n1->d = i;
    testMove d1(n1);
    //d1.printData();
    //cout << "Will push back to vector.. d1 = " << &d1 << endl;
    v2.push_back(std::move(d1));
    //cout<< "Vector size " << v2.size() << " vector capacity" << v2.capacity()  << " Vect " << &(v2[i])<< endl;
    //v2[i-1].printData();
  }
  //printVect(v2);
  delete n1;
}

static void BM_VecCopy(benchmark::State& state) {
  int ret;

  for(auto _:state) {
    vectorWorkCopy((int)state.range(0));
  }

}

static void BM_VecMove(benchmark::State& state) {
  int ret;

  for(auto _:state) {
    vectorWorkMove((int)state.range(0));
  }

}


#if 0
BENCHMARK(BM_VecCopy)->Range(1,4096);
BENCHMARK(BM_VecMove)->Range(1,4096);
//BENCHMARK(BM_VecCopy)->Arg(40000);
//BENCHMARK(BM_VecMove)->Arg(40000);
BENCHMARK_MAIN();

#else

int main() {
  vectorWorkCopy(32);
  cout << endl << endl << endl << "Doing Move Work " << endl << endl << endl;
  vectorWorkMove(32);
}
#endif
