/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
double sumer=0;
template <typename T>
T sum(stack<T>& s)
{
  if (s.size()==0)return 0;
    T temp=s.top();
    s.pop();
    sumer=temp+sum(s);
    s.push(temp);

    // Your code here
    return sumer; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
 int count1=0;
 int count2=0;
 int i=0;
bool isBalanced(queue<char> input)
{
  //std::cout<<input.front()<<std::endl;
  if (i==0)
  {
    stack<char> temp;
    i++;
  }
  if (input.empty()==true)
  {
    if (count2==count1)return true;
    else
    {
      //std::cout<<count1<<std::endl;
      //std::cout<<count2<<std::endl;
      return false;
    }

  }

  if (input.front()== '['  )count1++;
  if (input.front()== ']'  )count2++;

  input.pop();

  return isBalanced(input);

return true;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
  int counter=0;
    T temp;
    stack<T> s;
    queue<T> q2;
    T* arr=new T(q.size());
    //int inc=0;
//std::cout<<"start"<<std::endl;
    for (int n=1;!q.empty();n++)
    {//std::cout<<n<<std::endl;
    if (n%2==0)
    {
      for (int i=0;i<n;i++)
      {//std::cout<<"even"<<std::endl;
        if (q.size()>0)
        {
          arr[i]=q.front();
        //temp=q.front();
        //s.push(q.front());
        q.pop();
        //temp=s.top();
        counter++;
        }

      }
      for (int jk=counter-1;jk>=0;jk--)
      {
        //q2.push(s.top());
        //s.pop();
        q2.push(arr[jk]);
      }
      counter=0;

    }
    else
    {
      for (int i=0;i<n;i++)
      {//std::cout<<"odd"<<std::endl;
        if (q.size()>0)
        {
          //temp=q.front();
          q2.push(q.front());
          q.pop();
        }
      }
    }

  }
  for (int l=0;!q2.empty();l++)
  {
    //temp=q2.front();
    q.push(q2.front());
    q2.pop();
  }
}

}
















//keep down
