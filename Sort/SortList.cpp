#include <iostream>
#include <string>
#include <cstdlib>
#include <set>

using std::string;
using std::cout;
using std::endl;
using std::set;

template<class T>
class Node{
public:
  Node(T v):m_Value(v), nextPtr(nullptr){}
  void next(Node* n){ this->nextPtr = n; }
  Node* next(){ return this->nextPtr;}
  T value(){return m_Value;}

private:
  T m_Value;
  std::shared_ptr<Node> nextPtr;
};

typedef Node<string> SNode;

SNode* nMove(SNode* r, int n, bool cut=false){
  SNode* ret=r;
  int c(0);
  while(ret->next() != nullptr && c<n ){
     c++;
     ret = ret->next();
  }
  if(cut){
    ret->next(nullptr);
  }
  return ret;
}

  
SNode* merge(SNode* r, SNode* r2){
  if(r == nullptr)
    return r2;
  if(r2 == nullptr)
    return r;
  SNode* ret=nullptr;
  if (r->value() > r2->value()) {
    ret =r2;
    r2 = r2->next();
  } else {
    ret = r;
    r = r->next();
  }
  SNode* currentEle=ret;
  while (r != nullptr && r2 != nullptr) {
    
    if (r->value() > r2->value()) {
      currentEle->next(r2);
      r2 = r2->next();
    } else {
      currentEle->next(r);
      r = r->next();
    }
    
    currentEle = currentEle->next();    
  } 
  if (r == nullptr)
    currentEle->next(r2);
  else
    currentEle->next(r);
  return ret;
}


SNode* sortList(SNode* r, int l){
  if(l<=1)
    return r;
  int n = l/2;
  SNode* r2 = nMove(r,n);
  nMove(r,n-1, true);

  return merge(sortList(r, n), sortList(r2,l-n));
};

int main(int agrc, char** argv){
  SNode* root = new SNode(string("test0"));
  set<string> groundTruth;
  groundTruth.insert(root->value());
  SNode* currentNode = nullptr;
  SNode* prevNode = root;
  int len(atoi(argv[1]));
  for(auto i=1;i<=len;i++)  
  {
    string a("test");
    a.append(std::to_string(std::rand()));
    a.append(":");
    a.append(std::to_string(i));
    groundTruth.insert(a);
    currentNode =new SNode(a);
    prevNode->next(currentNode);
    prevNode = currentNode;
  }

  cout << "________origin___________" << endl;

  currentNode = root;
  while(currentNode != nullptr){
    cout << currentNode->value() << endl;
    currentNode = currentNode->next();
  }  
  
  cout << "________groundtruth___________" << endl;

  for(auto i: groundTruth)
    cout << i << endl;
  cout << "________result___________" << endl;
  currentNode = sortList(root, len+1);
  while(currentNode != nullptr){
    cout << currentNode->value() << endl;
    currentNode = currentNode->next();
  }

  return 0;

}
