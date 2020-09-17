
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1; ///1 indexed;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    if (currentIdx%2==1)return (currentIdx-1)/2;

    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    if (leftChild(currentIdx)<_elems.size())return true;
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    size_t left=leftChild(currentIdx);
    size_t right=rightChild(currentIdx);
    if (right>=_elems.size())return left;
    if (!(higherPriority(_elems[left],_elems[right])))return right;
    return left;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!(hasAChild(currentIdx)))return;
    int biggest=maxPriorityChild(currentIdx);
    if (higherPriority(_elems[biggest],_elems[currentIdx]))
    {
      std::swap(_elems[biggest],_elems[currentIdx]);
      heapifyDown(biggest);
    }
    return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    T spacer;//=numeric_limits<T>::min();////////////
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
  T spacer;//=numeric_limits<T>::min();////////////
  _elems.push_back(T());

  _elems.insert(_elems.end(),elems.begin(),elems.end());

  for (size_t i=_elems.size()-1;i>0;i--)//////////
  {
    heapifyDown(i);
  }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (empty())return T();
    T highest=_elems[1];
    _elems[1]=_elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(1);
    return highest;

}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{

      if (empty())return T();
      return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems[idx]=elem;
    heapifyUp(idx);
    heapifyDown(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    if (_elems.size()<2)return true;
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
