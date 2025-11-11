#ifndef BSTCHECKER_H
#define BSTCHECKER_H

#include "BSTNode.h"
#include <unordered_set>
#include <limits>
#include <vector>

using namespace std;

class BSTChecker
{
public:
  static BSTNode *CheckBSTValidity(BSTNode *rootNode)
  {
    if (rootNode == nullptr)
    {
      return nullptr;
    }

    struct NodeState {
        BSTNode* node;
        long long minKey;
        long long maxKey;
    };

    vector<NodeState> nodeStack;
    unordered_set<BSTNode *> visitedPointers;

    nodeStack.push_back({rootNode, numeric_limits<long long>::min(),
                         numeric_limits<long long>::max()});

    while (!nodeStack.empty() )
    {
      NodeState currentState = nodeStack.back();
      nodeStack.pop_back();

      BSTNode* currentNode = currentState.node;

      if (currentNode == nullptr)
      {
        continue;
      }

      if (visitedPointers.find(currentNode) != visitedPointers.end())
      {
        return currentNode;
      }
      visitedPointers.insert(currentNode);

      if (currentNode->key <= currentState.minKey || 
          currentNode->key >= currentState.maxKey)
      {
        return currentNode;
      }

      nodeStack.push_back({
          currentNode->right, 
          currentNode->key, 
          currentState.maxKey
      });
      
      nodeStack.push_back({
          currentNode->left, 
          currentState.minKey, 
          currentNode->key
      });
    }

    return nullptr;
  }
};

#endif