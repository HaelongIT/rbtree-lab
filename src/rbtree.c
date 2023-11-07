#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed

  node_t *nil = (node_t *)calloc(1, sizeof(node_t));

  nil->color = RBTREE_BLACK;

  p->root = p->nil = nil;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory

  node_t *node = t->root;

  if (node != t->nil)
  {
    traverse_and_delete_node(t, node);
  }

  free(t->nil);
  free(t);
}

void traverse_and_delete_node(rbtree *t, node_t *node)
{
  if (node->left != t->nil)
  {
    traverse_and_delete_node(t, node->left);
  }
  if (node->right != t->nil)
  {
    traverse_and_delete_node(t, node->right);
  }

  free(node);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;
  new_node->left = new_node->right = t->nil;

  node_t *current = t->root;
  while (current != t->nil)
  {
    if (key < current->key)
    {
      if (current->left == t->nil)
      {
        current->left = new_node;
        break;
      }
      current = current->left;
    }
    else
    {
      if (current->right == t->nil)
      {
        current->right = new_node;
        break;
      }
      current = current->right;
    }
  }
  new_node->parent = current;

  if (current == t->nil)
  {
    t->root = new_node;
  }

  rbtree_insert_fixup(t, new_node);

  return new_node;
}

void rbtree_insert_fixup(rbtree *t, node_t *node)
{
  // TODO: implement rbtree_insert_fixup
  node_t *parent = node->parent;
  node_t *grand_parent = parent->parent;
  node_t *uncle;

  int is_left = node == parent->left;
  int is_parent_is_left;

  if (node == t->root)
  {
    node->color = RBTREE_BLACK;
    return;
  }

  if (parent->color == RBTREE_BLACK)
  {
    return;
  }

  is_parent_is_left = grand_parent->left == parent;
  uncle = (is_parent_is_left) ? grand_parent->right : grand_parent->left;

  if (uncle->color == RBTREE_RED)
  {
    parent->color = RBTREE_BLACK;
    uncle->color = RBTREE_BLACK;

    grand_parent->color = RBTREE_RED;

    rbtree_insert_fixup(t, grand_parent);
    return;
  }

  if (is_parent_is_left)
  {
    if (is_left)
    {
      right_rotate(t, parent);
      exchange_color(parent, parent->right);
      return;
    }
    left_rotate(t, node);
    right_rotate(t, node);
    exchange_color(node, node->right);
    return;
  }

  if (is_left)
  {
    right_rotate(t, node);
    left_rotate(t, node);
    exchange_color(node, node->left);
    return;
  }

  right_rotate(t, parent);
  exchange_color(parent, parent->left);
}

void right_rotate(rbtree *t, node_t *node)
{
  node_t *parent = node->parent;
  node_t *grand_parent = parent->parent;
  node_t *node_right = node->right;

  if (parent == t->root)
  {
    t->root = node;
  }
  else
  {
    if (grand_parent->left == parent)
    {
      grand_parent->left = node;
    }
    else
    {
      grand_parent->right = node;
    }
  }

  node->parent = grand_parent;
  node->right = parent;
  parent->parent = node;
  parent->left = node_right;
  node_right->parent = parent;
}
void left_rotate(rbtree *t, node_t *node)
{
  node_t *parent = node->parent;
  node_t *grand_parent = parent->parent;
  node_t *node_left = node->left;

  // 부모가 루트인 경우: 현재 노드를 루트로 지정 (노드를 삭제한 경우만 해당)
  if (parent == t->root)
    t->root = node;
  else
  { // 1-1) 노드의 부모를 grand_parent로 변경
    if (grand_parent->left == parent)
      grand_parent->left = node;
    else
      grand_parent->right = node;
  }
  node->parent = grand_parent; // 1-2) 노드를 grand_parent의 자식으로 변경 (양방향 연결)
  parent->parent = node;       // 2-1) parent의 부모를 노드로 변경
  node->left = parent;         // 2-2) parent를 노드의 자식으로 변경 (양방향 연결)
  parent->right = node_left;   // 3-1) 노드의 자식의 부모를 parent로 변경
  node_left->parent = parent;  // 3-2) 노드의 자식을 부모의 자식으로 변경 (양방향 연결)
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
