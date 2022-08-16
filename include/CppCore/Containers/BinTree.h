#pragma once

#include <CppCore/Root.h>
#include <CppCore/Containers/Pool.h>

namespace CppCore
{
   /// <summary>
   /// Fixed Size Binary Tree (TODO: Make Balanced)
   /// Use nested classes ST and MT.
   /// </summary>
   class BinTree
   {
   private:
      INLINE BinTree() { }

   public:
      /// <summary>
      /// The Node stored in the binary tree
      /// </summary>
      template<class T>
      struct Node
      {
      public:
         T     Data;
         Node* Left;
         Node* Right;
         int   Height;
      };

   public:
      /// <summary>
      /// BinaryTree for Single Thread Access
      /// </summary>
      template<class T, size_t SIZE, typename KEY = T>
      class ST
      {
      protected:
         Node<T>*                     mRoot;
         size_t                       mLength;
         Pool::Fix::ST<Node<T>, SIZE> mPool;

         /// <summary>
         /// Returns the height of a node or 0 if nullptr.
         /// </summary>
         INLINE int heightOf(Node<T>* n)
         {
            return n ? n->Height : 0;
         }

         /// <summary>
         /// Returns the balance of a node or 0 if nullptr.
         /// </summary>
         INLINE int balanceOf(Node<T>* n)
         {
            return n ? heightOf(n->Left) - heightOf(n->Right) : 0;
         }

         /// <summary>
         /// Returns the minimum node from given root.
         /// </summary>
         INLINE Node<T>* findMinNode(Node<T>* root)
         {
            // minimum is always stored on
            // the most left child
            if (root)
               while (root->Left)
                  root = root->Left;

            return root;
         }

         /// <summary>
         /// Returns the maximum node from given root.
         /// </summary>
         INLINE Node<T>* findMaxNode(Node<T>* root)
         {
            // maximum is always stored on
            // the most right child
            if (root)
               while (root->Right)
                  root = root->Right;

            return root;
         }

         /// <summary>
         /// Performs a right rotation and returns new root.
         /// </summary>
         INLINE Node<T>* rotateRight(Node<T>* y)
         {
            Node<T>* x = y->Left;
            Node<T>* T2 = x->Right;

            // Perform rotation
            x->Right = y;
            y->Left = T2;

            // Update heights
            y->Height = ::std::max<int>(heightOf(y->Left), heightOf(y->Right)) + 1;
            x->Height = ::std::max<int>(heightOf(x->Left), heightOf(x->Right)) + 1;

            // Return new root
            return x;
         }

         /// <summary>
         /// Performs a left rotation and returns new root.
         /// </summary>
         INLINE Node<T>* rotateLeft(Node<T>* x)
         {
            Node<T>* y = x->Right;
            Node<T>* T2 = y->Left;

            // Perform rotation
            y->Left = x;
            x->Right = T2;

            //  Update heights
            x->Height = ::std::max<int>(heightOf(x->Left), heightOf(x->Right)) + 1;
            y->Height = ::std::max<int>(heightOf(y->Left), heightOf(y->Right)) + 1;

            // Return new root
            return y;
         }

         /// <summary>
         /// Turns the tree into a ascending sorted linked list (only right child)
         /// </summary>
         INLINE Node<T>* createRightVine(Node<T>* node)
         {
            if (!node)
               return 0;

            Node<T>* prev = 0;
            Node<T>* root = node;

            while (true)
            {
               // rotate right until there are no more 
               // left nodes attached to current node
               if (node->Left)
               {
                  node = rotateRight(node);
                  continue;
               }

               // no more left nodes, save this as root
               // or update previous right child
               if (prev) prev->Right = node; // nth run
               else      root = node;        // 1st run

               // remember as previous
               prev = node;

               // continue with right child if there is any
               if (Node<T>* rc = node->Right)
                  node = rc;

               // done
               else
                  break;
            }

            return root;
         }

         /// <summary>
         /// Turns the tree into a descending sorted linked list (only left child) 
         /// </summary>
         INLINE Node<T>* createLeftVine(Node<T>* node)
         {
            if (!node)
               return 0;

            Node<T>* prev = 0;
            Node<T>* root = node;

            while (true)
            {
               // rotate left until there are no more 
               // right nodes attached to current node
               if (node->Right)
               {
                  node = rotateLeft(node);
                  continue;
               }

               // no more right nodes, save this as root
               // or update previous left child
               if (prev) prev->Left = node;  // nth run
               else      root = node;        // 1st run

               // remember as previous
               prev = node;

               // continue with left child if there is any
               if (Node<T>* lc = node->Left)
                  node = lc;

               // done
               else
                  break;
            }

            return root;
         }

         /// <summary>
         /// Helper Function used on Insert
         /// </summary>
         INLINE Node<T>* rebalanceInsert(Node<T>* node, T key)
         {
            const int balance = balanceOf(node);

            // Left Left
            if (balance > 1 && key < node->Left->Data)
               return rotateRight(node);

            // Right Right
            if (balance < -1 && key > node->Right->Data)
               return rotateLeft(node);

            // Left Right
            if (balance > 1 && key > node->Left->Data)
            {
               node->Left = rotateLeft(node->Left);
               return rotateRight(node);
            }

            // Right Left
            if (balance < -1 && key < node->Right->Data)
            {
               node->Right = rotateRight(node->Right);
               return rotateLeft(node);
            }

            // Unmodified
            return node;
         }

         /// <summary>
         /// Helper Function used on Removal
         /// </summary>
         INLINE Node<T>* rebalanceDelete(Node<T>* node)
         {
            const int balance = balanceOf(node);

            // Left Left
            if (balance > 1 && balanceOf(node->Left) >= 0)
               return rotateRight(node);

            // Left Right
            if (balance > 1 && balanceOf(node->Left) < 0)
            {
               node->Left = rotateLeft(node->Left);
               return rotateRight(node);
            }

            // Right Right
            if (balance < -1 && balanceOf(node->Right) <= 0)
               return rotateLeft(node);

            // Right Left
            if (balance < -1 && balanceOf(node->Right) > 0)
            {
               node->Right = rotateRight(node->Right);
               return rotateLeft(node);
            }

            // Unmodified
            return node;
         }

         /// <summary>
         /// 
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         INLINE Node<T>* findNode(const T& key, Node<T>* root)
         {
            while (root)
            {
               // continue looking left
               if (COMPARER::greater(root->Data, key))
                  root = root->Left;

               // continue looking right
               else if (COMPARER::less(root->Data, key))
                  root = root->Right;

               // found at idx
               else
                  return root;
            }
            return 0;
         }

         /// <summary>
         /// Recursive Depth Finder
         /// </summary>
         size_t findDepth(Node<T>* node)
         {
            if (node)
            {
               // depth of subtrees
               const size_t lDepth = findDepth(node->Left);
               const size_t rDepth = findDepth(node->Right);

               // use larger one
               if (lDepth > rDepth)
                  return(lDepth + 1);

               else
                  return(rDepth + 1);
            }
            else
               return 0;
         }

         /// <summary>
         /// Recursive Delete
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         Node<T>* deleteNode(Node<T>* root, const T& key)
         {
            // STEP 1: PERFORM STANDARD BST DELETE

            if (root == 0)
               return root;

            // If the key to be deleted is smaller than the
            // root's key, then it lies in left subtree
            if (COMPARER::greater(root->Data, key))
               root->Left = deleteNode(root->Left, key);

            // If the key to be deleted is greater than the
            // root's key, then it lies in right subtree
            else if (COMPARER::less(root->Data, key))
               root->Right = deleteNode(root->Right, key);

            // if key is same as root's key, then This is
            // the node to be deleted
            else
            {
               // node with only one child or no child
               if ((root->Left == 0) || (root->Right == 0))
               {
                  Node<T>* temp = root->Left ?
                     root->Left :
                     root->Right;

                  // No child case
                  if (temp == 0)
                  {
                     temp = root;
                     root = 0;
                  }
                  // One child case
                  else
                  {
                     // Copy the contents of
                     // the non-empty child
                     *root = *temp; 
                  }

                  mLength--;
                  mPool.pushBack(temp);
               }
               else
               {
                  // node with two children: Get the inorder
                  // successor (smallest in the right subtree)
                  Node<T>* temp = findMinNode(root->Right);

                  // Copy the inorder successor's data to this node
                  root->Data = temp->Data;

                  // Delete the inorder successor
                  root->Right = deleteNode(root->Right, temp->Data);
               }
            }

            // If the tree had only one node then return
            if (root == 0)
               return root;

            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            root->Height = 1 + ::std::max<int>(
               heightOf(root->Left),
               heightOf(root->Right));

            // STEP 3: REBALANCE
            return rebalanceDelete(root);
         }
         
         /// <summary>
         /// Recursive Insert
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         Node<T>* insertNode(Node<T>* node, const T& key)
         {
            // create node
            if (node == NULL)
            {
               // TODO: handling if none available? peek before call?
               Node<T>* newNode = NULL;
               if (mPool.popBack(newNode))
               {
                  newNode->Data = key;
                  newNode->Left = 0;
                  newNode->Right = 0;
                  newNode->Height = 1;
                  mLength++;
               }
               return newNode;
            }

            // go left
            if (COMPARER::greater(node->Data, key))
               node->Left = insertNode(node->Left, key);

            // go right
            else if (COMPARER::less(node->Data, key))
               node->Right = insertNode(node->Right, key);

            // duplicated keys are not allowed
            else 
               return node;

            // update height
            node->Height = 1 + ::std::max<int>(
               heightOf(node->Left),
               heightOf(node->Right));

            // rebalance
            return rebalanceInsert(node, key);
         }
      
      public:
         /// <summary>
         /// Constructor
         /// </summary>
         INLINE ST() : mRoot(0), mLength(0)
         {
         }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t size() const { return SIZE; }

         /// <summary>
         /// Complexity: O(1)
         /// </summary>
         INLINE size_t length() const { return mLength; }

         /// <summary>
         /// 
         /// </summary>
         INLINE void clear(Node<T>** stack)
         {
            mLength = 0;
            
            if (Node<T>* node = mRoot)
            {
               size_t stidx = 0;      // index on stack
               stack[++stidx] = node; // push root node

               // remove nodes
               do
               {
                  // pop next node
                  node = stack[stidx--];

                  // push left child
                  if (Node<T>* lc = node->Left)
                     stack[++stidx] = lc;

                  // push right child
                  if (Node<T>* rc = node->Right)
                     stack[++stidx] = rc;

                  // push node to free ones
                  mPool.pushBack(node);
               } 
               while (stidx);

               // reset root
               mRoot = 0;
            }
         }

         //////////////////////////////////////////////////////////////////////
         
         /// <summary>
         /// 
         /// </summary>
         INLINE bool findMin(T& min)
         {
            if (Node<T>* node = findMinNode(mRoot))
            {
               min = node->Data;
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// 
         /// </summary>
         INLINE bool findMax(T& max)
         {
            if (Node<T>* node = findMaxNode(mRoot))
            {
               max = node->Data;
               return true;
            }
            else
               return false;
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         INLINE bool find(const KEY& key, T& item)
         {
            if (Node<T>* node = findNode<COMPARER>(key, mRoot))
            {
               item = node->Data;
               return true;
            }
            else
               return false;
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE void insert(const T& item)
         {
            mRoot = insertNode<COMPARER>(mRoot, item);
         }

         /// <summary>
         /// Complexity: O(log(n))
         /// </summary>
         template<typename COMPARER = Comparer<T, KEY>>
         INLINE void remove(const KEY& key)
         {
            mRoot = deleteNode<COMPARER>(mRoot, key);
         }

         //////////////////////////////////////////////////////////////////////

         /// <summary>
         /// Returns true if the tree is a valid binary search tree.
         /// TODO: Check if balanced.
         /// </summary>
         template<typename COMPARER = Comparer<T, T>>
         INLINE bool validate(Node<T>** stack)
         {
            Node<T>* root = mRoot;
            size_t len = 0;

            if (root)
            {
               size_t stidx = 0;      // index on stack
               stack[++stidx] = root; // push root node
               len++;

               do
               {
                  // pop next index/node
                  root = stack[stidx--];

                  // height of this node must be correct
                  if (root->Height != findDepth(root))
                     return false;

                  // test left child
                  if (Node<T>* lc = root->Left)
                  {
                     // left child must be smaller
                     if (COMPARER::less(lc->Data, root->Data))
                     {
                        stack[++stidx] = lc;
                        len++;
                     }
                     // else not valid
                     else
                        return false;
                  }

                  // test right child
                  if (Node<T>* rc = root->Right)
                  {
                     // right child must be bigger
                     if (COMPARER::greater(rc->Data, root->Data))
                     {
                        stack[++stidx] = rc;
                        len++;
                     }
                     // else not valid
                     else
                        return false;
                  }
               }
               while (stidx);
            }

            // length must match
            return (len == mLength);
         }
      };

      /// <summary>
      /// BinaryTree for Multi Thread Access
      /// </summary>
      template<class T, size_t SIZE, typename KEY = T>
      class MT : ST<T, SIZE, KEY>
      {
      protected:
         CPPCORE_MUTEX_TYPE mLock;

      public:
         INLINE MT() : ST<T, SIZE, KEY>() { CPPCORE_MUTEX_INIT(mLock); }
         INLINE ~MT() { CPPCORE_MUTEX_DELETE(mLock); }
         INLINE size_t size() { return SIZE; }

         template<typename COMPARER = Comparer<T, KEY>>
         INLINE bool find(const KEY& key, T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            bool ret = ST<T, SIZE, KEY>::template find<COMPARER>(key, item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
         template<typename COMPARER = Comparer<T, T>>
         INLINE void insert(const T& item)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE, KEY>::template insert<COMPARER>(item);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return;
         }
         template<typename COMPARER = Comparer<T, KEY>>
         INLINE void remove(const KEY& key)
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE, KEY>::template remove<COMPARER>(key);
            CPPCORE_MUTEX_UNLOCK(mLock);
            return;
         }
         INLINE void clear()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            ST<T, SIZE, KEY>::clear();
            CPPCORE_MUTEX_UNLOCK(mLock);
         }
         /// <summary>
         /// BEWARE: You must consider the returned value already outdated/invalid.
         /// This is for e.g. monitoring usage only.
         /// </summary>
         INLINE size_t length()
         {
            CPPCORE_MUTEX_LOCK(mLock);
            size_t ret = ST<T, SIZE, KEY>::length();
            CPPCORE_MUTEX_UNLOCK(mLock);
            return ret;
         }
      };
   };
}
