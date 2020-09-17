/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::getHeight(Node*& subtree) {
  if (subtree->left == NULL && subtree->right == NULL)
   {
    subtree->height = 0;
  }
  else if (subtree->left  == NULL)
  {
    subtree->height = subtree->right->height + 1;
  }
  else if (subtree->right == NULL)
  {
    subtree->height = subtree->left->height  + 1;
  } 
  else
  {
    subtree->height = max(subtree->right->height, subtree->left->height) + 1;
  }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if (t==NULL ||t->right==NULL)return;


    Node* newBoss=t->right;
    Node* oldBoss=t;
    Node* kid=newBoss->left;

    t=newBoss;
    newBoss->left=oldBoss;
    oldBoss->right=kid;


    getHeight(newBoss);
    getHeight(oldBoss);

}



template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    if (t == NULL || t->left == NULL)return;


    Node* newBoss=t->left;
    Node* oldBoss=t;
    Node* kid=newBoss->right;

    t=newBoss;
    newBoss->right=oldBoss;
    oldBoss->left=kid;

    getHeight(oldBoss);
    getHeight(newBoss);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
int AVLTree<K, V>::balance(Node*& subtree)
{
  if (subtree==NULL)return 0;


  int rightHeight = heightOrNeg1(subtree->right);
  int leftHeight  = heightOrNeg1(subtree->left);
  return rightHeight - leftHeight;
}
template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if (subtree == NULL)return;


  getHeight(subtree);

  int checker=balance(subtree);
  if (abs(checker) <= 1) return;

  //getHeight(subtree);
  if (checker>0)//right heavy
  {
    if (balance(subtree->right)<0)//right subtree is left heavy
    {
      rotateRightLeft(subtree);
    }
    else rotateLeft(subtree);

  }
  else if (checker<0)//left heavy
  {
    if (balance(subtree->left)>0)rotateLeftRight(subtree);
    else rotateRight(subtree);
  }
//  getHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if (subtree == NULL) {
    subtree = new Node(key, value);
  } else if (subtree->key == key) {
    subtree->value = value;
  } else if (key < subtree->key) {
    insert(subtree->left, key, value);
    rebalance(subtree);
  } else {
    insert(subtree->right, key, value);
    rebalance(subtree);
  }

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
       remove(subtree->left,key);
       rebalance(subtree);
    } else if (key > subtree->key) {
      remove(subtree->right, key);
      rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
          delete subtree;
          subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
          Node*& IOP = rightMostNode(subtree->left);
          swap(IOP, subtree);
          delete IOP;
          IOP = NULL;
          //rebalance(subtree);////////////
        } else {
          Node* subtreeNewChild = leftMostNode(subtree->right);
          delete subtree;
          subtree = subtreeNewChild;
        }
        rebalance(subtree);
    }
  }

  template <class K, class V>
  typename AVLTree<K, V>::Node*& AVLTree<K, V>::rightMostNode(Node*& subtree)
    {
        if (subtree==NULL)return subtree;

        while (subtree->right!=NULL)subtree=subtree->right;
        return subtree;
    }

    template <class K, class V>
    typename AVLTree<K, V>::Node*& AVLTree<K, V>::leftMostNode(Node*& subtree)
      {
      if (subtree==NULL)return subtree;

      while (subtree->left!=NULL)subtree=subtree->left;
      return subtree;
    }
