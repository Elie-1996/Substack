#include <stdio.h>

typedef struct _node* Nodeptr;
typedef struct _node {
    int data;
    Nodeptr left;
    Nodeptr right;
} Node;

Nodeptr generate_node(int data)
{
    Nodeptr node = (Nodeptr) malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int exp(int x)
{
    int i, result=1;
    for(i = 0; i < x;i++)
        result *= 2;
    return result;
}

/* A counter which will initialize the values of the tree to something */
int global_counter = -1;
Nodeptr* generateNewLevel(Nodeptr* old_level_nodes, int old_level)
{
    int new_level = old_level + 1;

    /* These lines calculate 2^(old_level) and 2^(old_level+1)
    which is the exact number of nodes in each level */
    int old_level_size = exp(old_level);
    int new_level_size = exp(new_level);
    int i;

    /* Generate an array of size new_level_size, which will hold all the new nodes */
    Nodeptr* new_level_nodes = (Nodeptr*)malloc(sizeof(Nodeptr) * new_level_size);
    for (i = 0; i < new_level_size; i++)
    {
        new_level_nodes[i] = generate_node(global_counter--);
    }

    /* Apply the logic you just read about in order to connect between the pointers
        from the last level to the new level. */
    for (i = 0; i < old_level_size; i++)
    {
        int left_idx = i * 2, right_idx = i * 2 + 1;
        old_level_nodes[i]->left = new_level_nodes[left_idx];
        old_level_nodes[i]->right = new_level_nodes[right_idx];
    }

    return new_level_nodes;
}


Nodeptr generateFullTree(int levels)
{
    int i;
    int last_level_size = exp(levels);
    Nodeptr *root_nodes, *old_level_nodes;

    /* We can only generate trees with at least 1 level*/
    if (levels <= 0) return NULL;

    /* generate level 0 (The level which contains the root node)*/
    root_nodes = (Nodeptr*) malloc(sizeof(Nodeptr) * 1);
    root_nodes[0] = generate_node(global_counter--);
    if (levels == 1) return root_nodes[0];

    /* generate all other levels */
    old_level_nodes = root_nodes;
    for (i = 0; i < levels - 1; i++)
    {
        old_level_nodes = generateNewLevel(old_level_nodes, i);
    }

    return root_nodes[0];
}

void preorder(Nodeptr root)
{
    if(root == NULL) return;
    printf("%d, ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Nodeptr root)
{
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d, ", root->data);
}

void inorder(Nodeptr root)
{
    if(root == NULL) return;
    inorder(root->left);
    printf("%d, ", root->data);
    inorder(root->right);
}

int main()
{
    Nodeptr root = generateFullTree(4);

    printf("Pre-order:");
    preorder(root);
    printf("\nIn-order:");
    inorder(root);
    printf("\nPost-order:");
    postorder(root);
    return 0;
}
