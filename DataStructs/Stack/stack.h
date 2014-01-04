# define S_FULL -1
# define S_EMPTY -1
# define stack_full(sd) (sd->sp == sd->end)
# define stack_empty(sd) (sd->sp == sd->beg)

typedef struct {
	char *beg;
	char *end;
	char *sp;
	int dyn;
	int nmax;
	int size;
} STACK;

STACK *open_stack (int size, int nmax);
int push (STACK *sd, char *item);
int pop (STACK *sd, char *item);
int peek (STACK *sd, char *item);
void close_stack (STACK *sd);
