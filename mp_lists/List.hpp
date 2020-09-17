/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() :length_(0) {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    //int length_=0;

}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(this->head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(this->tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>      ///////////mebe
void List<T>::_destroy()
{
  ListNode * curr=head_;
  if (curr==NULL)return;
  ListNode * nextup=NULL;
  while (curr->next != NULL)
  {
      nextup=curr->next;
      delete curr;
      curr=nextup;
  }
  delete curr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  newNode -> next = head_;
  newNode -> prev = NULL;
//std::cout<<ndata<<std::endl;

  //std::cout<<"here"<<std::endl;

  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_=newNode;
  //std::cout<<"here"<<std::endl;


  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata)
{
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_ != NULL) {
    tail_->next=newNode;
  }
  tail_=newNode;

  if (head_ == NULL) {
    head_ = newNode;
  }


  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{

  /// @todo Graded in MP3.1
  ListNode * curr = start;
  int subr=0;
  for (int i = 0; i < splitPoint && curr != NULL; i++)
  {
    curr = curr->next;
    subr++;
  }

  if (curr != NULL) {
      if (curr->prev!=NULL)(curr->prev)->next = NULL;
      curr->prev = NULL;
  }
  //length_=length_-subr;
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate()
{
  ListNode* ptrFront;
  ListNode* ptrMid;
  ListNode* ptrLast;
  ListNode* ptrOld=NULL;
  ListNode* curr=this->head_;
  for (int i=2;i<(this->size()-(this->size()%3));i=i+3)
  {
    ptrFront=curr;
    curr=curr->next;
    ptrMid=curr;
    curr=curr->next;
    ptrLast=curr;
    curr=curr->next;   ///curr is rady for next return

    ptrMid->prev=ptrFront->prev;

    ptrFront->next=curr;
    if (ptrOld !=NULL)ptrOld->next=ptrMid;
    ptrOld=ptrFront;

//std::cout<<tail_->data<<std::endl;
    ptrFront->prev=ptrLast;

    ptrLast->next=ptrFront;

    if(curr !=NULL)curr->prev=ptrFront;
    if (ptrFront==head_)head_=ptrMid;
    if (ptrLast==tail_)
    {
      tail_=ptrFront;   //////if at ends
      //std::cout<<tail_->data<<std::endl;
    }

  }


}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint)
{
  if (startPoint==endPoint)return;
  bool boo=true;
  int counter=0;
  ListNode * curr=startPoint;
  ListNode * last=(endPoint->prev)->next;
  ListNode * first=(startPoint->next)->prev;
  ListNode * dummySpec;

  while (curr!=endPoint)
  {
    curr=curr->next;
    counter++;
  }
  //std::cout<<counter+1/2<<std::endl;

for (int i=0;i<(counter)/2;i++) ////wont work
{

//std::cout<<last->data<<std::endl;
//std::cout<<first->data<<std::endl;

  ListNode * before=first->prev;   //null
  ListNode * after=last->next;      //null
  ListNode * dummy1=first->next;
  first->next=last->next;

  ListNode * dummy2=first->prev;
  first->prev=last->prev;


  dummy1->prev=last;
  (last->prev)->next=first;

  last->next=dummy1;
  last->prev=dummy2;

  if(before!=NULL)before->next=last;
  else head_=last;
  if(after!=NULL)after->prev=first;
  else tail_=first;

//if(i==2)std::cout<<"made it here"<<std::endl;
if (i<((counter+1)/2)-1)
{
  dummy1=first->prev;
  first=last->next;
  last=dummy1;
}


//  std::cout<<last->data<<std::endl;
//  std::cout<<first->data<<std::endl;
//if(i==2)std::cout<<"made it here"<<std::endl;
}
if (counter%2==1)   /////////switch last two on evens(counter is one short)
{
  dummySpec=first->prev;
  (first->prev)->next=last;
  first->next=last->next;
  first->prev=last;
  last->prev=dummySpec;
  last->next=first;
}





//std::cout<<"made it here"<<std::endl;
//  reverse(startPoint->next,endPoint->prev);
//startPoint=last;
//endPoint=first;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  ListNode * beg=head_;
  ListNode * end=head_;
  for (int i=0;i<this->size() ;i=i+n)
  {
    beg=head_;
    end=head_;
    for (int b=0;b<i && beg->next !=NULL ;b++)
    {
      beg=beg->next;
    }
    end=beg;
    for (int a=0;a<n-1 && end->next !=NULL ;a++)
    {
      end=end->next;

    }
    //std::cout<<beg->data<<std::endl;
    //std::cout<<end->data<<std::endl;


    reverse(beg,end);


  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second)
{
  ListNode * curr;
  ListNode * curr2;
  ListNode * newOne;
  ListNode * start;
  start=first;
  curr=first;
  curr2=second;
  while (curr!=NULL)
  {//std::cout<<"out"<<std::endl;

    while (curr2!=NULL)
    {//std::cout<<"outinner"<<std::endl;

      if (curr2->data<curr->data && curr->prev==NULL)  //at beging
      {//std::cout<<"out1"<<std::endl;

        newOne=curr2->next;
        curr2->prev=NULL;
        curr2->next=curr;
        curr->prev=curr2;
        start=curr2;
        curr2=newOne;

      }
      else if (curr2->data<curr->data )   ///at middle
      {//std::cout<<"out2"<<std::endl;

        newOne=curr2->next;
        curr2->next=curr;
        curr2->prev=curr->prev;
        (curr->prev)->next=curr2;
        curr->prev=curr2;
        curr2=newOne;
      }
      else if (curr->next==NULL)    ///at end
      {//std::cout<<"out3"<<std::endl;

        newOne=curr2->next;
        curr->next=curr2;
        curr2->next=NULL;
        curr2->prev=curr;
        curr2=newOne;
        if(newOne ==NULL)break;
      }
      else curr=curr->next;
    }
    break;
  }
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength)
{
  if (chainLength<=1)return start;
  ListNode * new1;
  ListNode * new2;
  ListNode * left;
  ListNode * right;
  new1=start;// std::cout<<new1->data<<std::endl;
  new2=split(start,chainLength/2);//std::cout<<new2->data<<std::endl;

  left=mergesort(new1,chainLength/2);
  right=mergesort(new2,chainLength-chainLength/2);
  return merge(left,right);
}
