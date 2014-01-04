/* ******************* *
 * Global Declarations *
 * ******************* */
struct node {
	struct node *left;
	struct node *right;
	char data[1];
};

/* ******************* *
 * Global type defines *
 * ******************* */
typedef struct {
	struct node *root;
	int (*compare) (char *, char *);
	int size;
	int new_added;
	char leaf_added;
	char *pos;
	char *array;
	char *new_data;
} TREE;

/* ******************* *
 * Global hash defines *
 * ******************* */
# define Root (td->root)
# define Left (node->left)
# define Right (node->right)
# define Compare (td->compare)
# define Size (td->size)
# define Pos (td->pos)
# define Leaf_added (td->leaf_added)
# define Array (td->array)
# define New_data (td->new_data)
# define nleaves(td) how_many(Root)
# define Data (node->data)
# define New_added (td->new_added)
# define T_SUCCESS 1
# define T_FAILURE 0
# define nleaves(td) how_many(Root)

/* ************************** *
 * Global function Prototypes *
 * ************************** */
int add_leaf (TREE *, char *);
void free_tree (struct node *);
struct node *array_to_tree (char *, int, int, int *);
void place_leaf (char *, void *);
int find_total (TREE *);
void add_to_total (char *, void *);
void traverse (struct node *, void(*)(), void *);
int navigate (TREE *, void(*)(), void *);
int how_many (register struct node *);
TREE *open_tree (int, int(*)());
char find_leaf (TREE *, char *);
char remove_leaf (TREE *, char *);
void copy_leaf_to_array (char *old, void *x);
int tree_to_array (TREE *td);
