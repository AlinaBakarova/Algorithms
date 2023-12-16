#include <iostream>

static const int32_t kMod = 1000000000;

struct Node {
  int32_t key;
  unsigned int height;
  Node* left;
  Node* right;
  Node(int32_t node);
};

Node::Node(int32_t node) {
  key = node;
  height = static_cast<unsigned int>(1);
  left = nullptr;
  right = left;
}

int BalanceFactor(Node* node) {
  return ((*node).right != nullptr ? (*node).right->height : 0) -
         ((*node).left != nullptr ? (*node).left->height : 0);
}

void FixHeight(Node* node) {
  unsigned int hl = 0;
  unsigned int hr = 0;
  if (node->left != nullptr) {
    hl = node->left->height;
  }
  if (node->right != nullptr) {
    hr = node->right->height;
  }
  node->height = (hl > hr ? hl : hr) + 1;
}

Node* RotateRight(Node* node) {
  Node* tmp = (*node).left;
  (*node).left = (*tmp).right;
  (*tmp).right = node;
  FixHeight(node);
  FixHeight(tmp);
  return tmp;
}

Node* RotateLeft(Node* node) {
  Node* tmp = (*node).right;
  (*node).right = (*tmp).left;
  (*tmp).left = node;
  FixHeight(node);
  FixHeight(tmp);
  return tmp;
}

Node* Balance(Node* node) {
  FixHeight(node);
  Node* ans;
  if ((BalanceFactor(node) == 2) && (BalanceFactor((*node).right) < 0)) {
    (*node).right = RotateRight((*node).right);
    ans = RotateLeft(node);
  } else if (BalanceFactor(node) == 2) {
    ans = RotateLeft(node);
  } else if ((BalanceFactor(node) == -2) && (BalanceFactor((*node).left) > 0)) {
    (*node).left = RotateLeft((*node).left);
    ans = RotateRight(node);
  } else if (BalanceFactor(node) == -2) {
    ans = RotateRight(node);
  } else {
    ans = node;
  }
  return ans;
}

Node* Insert(Node* node, int32_t var_k) {
  if (node == nullptr) {
    return new Node(var_k);
  }
  if (var_k < (*node).key) {
    (*node).left = Insert((*node).left, var_k);
  } else if (var_k > (*node).key) {
    (*node).right = Insert((*node).right, var_k);
  }
  return Balance(node);
}

int Next(Node* node, int32_t var_k) {
  if (node == nullptr) {
    return -1;
  }
  if ((*node).key == var_k) {
    return (*node).key;
  }
  if ((*node).key < var_k) {
    return Next((*node).right, var_k);
  }
  if ((*node).left != nullptr) {
    int ans = Next((*node).left, var_k);
    if (ans != -1) {
      return ans;
    }
    return (*node).key;
  }
  return (*node).key;
}

void Clear(Node* root) {
  if (root == nullptr) {
    return;
  }
  if ((*root).left != nullptr) {
    Clear((*root).left);
  }
  if ((*root).right != nullptr) {
    Clear((*root).right);
  }
  delete root;
}

int main() {
  int32_t num;
  int32_t prev_ans = 0;
  Node* avl = nullptr;
  std::cin >> num;
  char prev_task = '+';
  for (int32_t i = 0; i < num; i++) {
    char task;
    int32_t numb;
    std::cin >> task >> numb;
    if ((task == '+') && (prev_task == '?')) {
      avl = Insert(avl, (numb + prev_ans) % kMod);
      prev_task = task;
    } else if ((task == '+') && (prev_task != '?')) {
      avl = Insert(avl, numb);
      prev_task = task;
    } else {
      prev_ans = Next(avl, numb);
      prev_task = task;
      std::cout << prev_ans << std::endl;
    }
  }
  Clear(avl);
}
