#include "dsets.h"



DisjointSets::DisjointSets()
{
  //dont use this constructor
}

DisjointSets::DisjointSets(int n)
{
  dset=vector<int>(n);
  for (int i=0;i<n;i++)
  {
    dset[i]=-1;
  }
}

void DisjointSets::addelements(int num)
{
  for (int i=0;i<num;i++)
  {
    dset.push_back(-1);
  }
}
//this returns the index of the root where elem resides
int DisjointSets::find(int elem)
{
  if (dset[elem]<0)return elem;

  //this whill call funciton again on parent of elem
  int findparent=find(dset[elem]);
  //flatten sthe tree by making thing elem point to root
  dset[elem]=findparent;
  return findparent;
}

void DisjointSets::setunion(int a,int b)
{
  int roota=find(a);
  int sizea=-1*dset[roota];
  int rootb=find(b);
  int sizeb=-1*dset[rootb];

  if (sizea>=sizeb)
  {
    dset[rootb]=roota;
    dset[roota]=-1*(sizea+sizeb);
  }
  else
  {
    dset[roota]=rootb;
    dset[rootb]=-1*(sizea+sizeb);
  }
}

int DisjointSets::size(int elem)
{
  int root=find(elem);//find the root
  int size=-1*dset[root];//root will be size of dataset
  return size;
}
