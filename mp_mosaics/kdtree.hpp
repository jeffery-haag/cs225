/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (first[curDim]<second[curDim])return true;

    if (first[curDim]==second[curDim])
    {
      if (first<second)return true;
    }

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{


    int distPot=0;
    int distCurr=0;
    for (int i=0;i<Dim;i++)
    {
      distPot=distPot+pow((potential[i]-target[i]),2);
      distCurr=distCurr+pow((currentBest[i]-target[i]),2);
    }
      //std::cout<<distPot<<std::endl;
        //std::cout<<distCurr<<std::endl;

    if (distPot<distCurr)return true;
    if (distPot==distCurr)
    {
      if (potential<currentBest)return true;
    }


     return false;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    list=newPoints;
    size=0;
    if (!list.empty())
    {
      size++;
      root=recBuild(0,0,list.size()-1);
    }
    best=Point<Dim>();
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::recBuild(int dim, int beg,int end)
{

  int med=(beg+end)/2;
  quickSelect(dim,beg,end, med);

  KDTreeNode* newb=new KDTreeNode(list[med]);
  size++;
  if (beg==end)return newb;
    //std::cout<<"here"<<std::endl;

  if (beg<med)newb->left=recBuild((dim+1)%Dim,beg,med-1);
  if (end>med)newb->right=recBuild((dim+1)%Dim,med+1,end);
  return newb;
}

template <int Dim>
void KDTree<Dim>::quickSelect(int dim, int left,int right,int k)
{
  while (left!=right)
  {
    int pivotInd=partition(dim,left,right,k);
    if (pivotInd==k)return;
    else if (k<pivotInd)right=pivotInd-1;
    else left=pivotInd+1;
  }
}

template <int Dim>
int KDTree<Dim>::partition(int dim, int left,int right,int k)
{
  Point<Dim> pivot=list[k];
  Point<Dim> temp=list[right];
  list[right]=pivot;
  list[k]=temp;
  int j=left;

  for (int i=left;i<right;i++)
  {
    if (smallerDimVal(list[i],pivot,dim) || list[i]==pivot)
    {
      temp=list[j];
      list[j]=list[i];
      list[i]=temp;
      j++;
    }
  }
  //putting the "med" back
  temp=list[j];
  list[j]=list[right];

  list[right]=temp;
  return j;
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other)
{
  KDtree(other->list);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs)
{
  //list=other->list;
  //size=other->size;
  delete this;
  KDTree newb=new KDTree(list);

  return *newb;
}

template <int Dim>
KDTree<Dim>::~KDTree()
{
  if (this->size==0)return;
  else delHelper(this->root);
  //delete root;
  return;
}
template <int Dim>
void KDTree<Dim>::delHelper(KDTreeNode* curr)
{
  if (curr==NULL)return;
  if (curr->left==NULL && curr->right==NULL)
  {
    delete curr;
    return;
  }
  if (curr->left!=NULL)delHelper(curr->left);
  if (curr->right!=NULL)delHelper(curr->right);
  delete curr;
  return;
}

template <int Dim>
int KDTree<Dim>::distance(Point<Dim> a, Point<Dim> b) const
{
  int sum=0;
  for (int i=0;i<Dim;i++)
  {
    sum=sum+(a[i]-b[i])*(a[i]-b[i]);
  }
  return (sum);
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (list.size()==0) return Point<Dim>();
    if (list.size()==1)return list[0];

    int med =  (list.size()-1)/2;

    return list[nnHelp(query, med, 0, list.size()-1, 0)];
}
template <int Dim>
int KDTree<Dim>::nnHelp(const Point<Dim>& query, int curr,
                            int left, int right, int dim) const
{
  if (left >= right)return curr;
  int med = 0;

  while (dim >= Dim) {
    dim -= Dim;
  }

  int dist = list[curr][dim] -query[dim];
  dist = dist*dist;
  int other = curr;
  int best = curr;

  int asdffake=0;
  for (int i=0;i<3;i++)
  {
    asdffake=asdffake+i;
  }

  if (smallerDimVal(query,list[curr],dim))
  {
    med = (curr-1-left)/2;
    best = nnHelp(query, med+left, left, curr-1, dim+1);
    if (shouldReplace(query, list[best], list[curr])) best = curr;

    int rad = distance(list[best], query);
    if (rad >= dist)
    {
      med = (right-curr-1)/2;
      other = nnHelp(query, med+curr+1, curr+1, right, dim+1);
      if (shouldReplace(query, list[best], list[other])) best = other;
    }
  }
  else
  {
    med = (right-curr-1)/2;
    best = nnHelp(query, med+curr+1, curr+1, right, dim+1);
    if (shouldReplace(query, list[best], list[curr])) best = curr;

    int rad = distance(list[best], query);
    if (rad >= dist)
    {
      med = (curr-1-left)/2;
      other = nnHelp(query, med+left, left, curr-1, dim+1);
      if (shouldReplace(query, list[best], list[other])) best = other;
    }
  }
  return best;
}
