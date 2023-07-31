#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// define
#define DEBUG_ENABLE                1
#define MAX_ITERATIONS              500

// macros
#if DEBUG_ENABLE
#define DEBUG(fmt, ...)             fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#define BIT_SET(value, position)    ((value) |= (1U << (position)))
#define BIT_CLEAR(value, position)  ((value) &= ~(1U << (position)))
#define BIT_GET(value, position)    (((value) & (1U << (position))) != 0)

// XBITS
typedef struct {
    uint8_t height;
    uint8_t byte_count;
    uint8_t **number;   // array de duas dimensões
} XBITS;

static inline void XBits_Init(XBITS **number, int height, int width)
{
    if (number == NULL)
    {
        return; DEBUG("ERROR XBits_Init NULL pointer");
    }

    (*number) = (XBITS*)malloc(sizeof(XBITS));

    (*number)->number = (uint8_t **)malloc(height * sizeof(uint8_t*));

    (*number)->byte_count = width / 8;

    for (int floor_idx = 0; floor_idx < height; floor_idx++)
    {
        (*number)->number[floor_idx] = (uint8_t*)malloc((*number)->byte_count * sizeof(uint8_t));

        for (uint8_t byte_idx = 0; byte_idx < (*number)->byte_count; byte_idx++)
        {
            (*number)->number[floor_idx][byte_idx] = 0;
        }
    }
}
static inline void SetPoint(XBITS **number, int floor, int position) 
{
    int byte_index = 0;
    int bit_index = 0;

    if (number == NULL || (*number)->number == NULL)
    {
        return; DEBUG("ERROR SetPoint NULL pointer");
    }

    byte_index = position / 8;
    bit_index = position % 8;

    BIT_SET((*number)->number[floor][byte_index], bit_index);
}
static inline void ClearPoint(XBITS **number, int floor, int position) 
{
    int byte_index = 0;
    int bit_index = 0;

    if (number == NULL || (*number)->number == NULL)
    {
        return; DEBUG("ERROR ClearPoint NULL pointer");
    }

    byte_index = position / 8;
    bit_index = position % 8;

    BIT_CLEAR((*number)->number[floor][byte_index], bit_index);
}
static inline bool GetPoint(XBITS number, int floor, int position) 
{
    int byte_index = 0;
    int bit_index = 0;

    if(number.number == NULL) DEBUG("ERROR GetPoint NULL pointer 2");

    byte_index = position / 8;
    bit_index = position % 8;

    return BIT_GET(number.number[floor][byte_index], bit_index);
}
// XBITS

// enum
typedef enum{
    BLOCK,
    ELEVATOR,
    WAIT,
} ACTION;

typedef enum{
    LEFT  = -1,
    RIGHT = 1,
    NONE  = 0,
} DIRECTION;

// struct
typedef struct point{
    int floor, position;
} POINT;

typedef struct node{
    POINT point;
    struct node *parent;
} NODE;

typedef struct queue{
    int front, rear, length;
    struct node **items;        //array de apontadores
} QUEUE;

typedef struct clone{
    POINT point;
    DIRECTION direction;
} CLONE;

// functions prototypes
ACTION BreadthFirstSearch(POINT clone_point);
//
void Queue_Init(QUEUE *queue, int length);
bool QueueEmpty(QUEUE queue);
void Enqueue(struct node *node, QUEUE *queue);
struct node *Dequeue(QUEUE *queue);
struct node *NewChildNode(POINT point, struct node *parent);
struct node *GetParentNode(struct node *child);
//
void PrintGame(POINT current);
void SetVisitedPoint(POINT point);
void SetAdElevatorPoint(POINT point);
void SetForbidenPoint(POINT point);
void SetPathPoint(POINT point);
//
bool ValidPoint(POINT point);
bool ExitPoint(POINT point);
bool ElevatorPoint(POINT point);
bool VisitedPoint(POINT point);
bool AdElevatorPoint(POINT point);
bool ForbidenPoint(POINT point);
bool PathPoint(POINT point);
bool StartPoint(POINT point);
int FloorElevators(int floor);

// number of floors, width of the area, maximum number of rounds, floor on which the exit is found, position of the exit on its floor
// number of generated clones, number of additional elevators that you can build, number of elevators
int nb_floors, width, nb_rounds, exit_floor, exit_pos, nb_total_clones, nb_additional_elevators, nb_elevators;
int map_size;

CLONE clone;
XBITS *visited, *elevators, *ad_elevators;
uint8_t *floor_elevator_count;

int main()
{
    scanf("%d%d%d%d%d%d%d%d", &nb_floors, &width, &nb_rounds, &exit_floor, &exit_pos, &nb_total_clones, &nb_additional_elevators, &nb_elevators);

    map_size = (nb_floors * width);
    floor_elevator_count = (uint8_t*)malloc(map_size * sizeof(uint8_t));
    memset(floor_elevator_count, 0, map_size);

    XBits_Init(&visited,      nb_floors, width);
    XBits_Init(&elevators,    nb_floors, width);
    XBits_Init(&ad_elevators, nb_floors, width);

    for (int i = 0; i < nb_elevators; i++) 
    {
        // floor on which this elevator is found, position of the elevator on its floor
        int elevator_floor, elevator_pos;
        scanf("%d%d", &elevator_floor, &elevator_pos);

        SetPoint(&elevators, elevator_floor, elevator_pos);
        floor_elevator_count[elevator_floor]++;
    }

    // game loop
    while (1) 
    {
        ACTION action = WAIT;
        char direction[11];

        // floor of the leading clone, position of the leading clone on its floor, direction of the leading clone: LEFT or RIGHT
        scanf("%d%d%s", &clone.point.floor, &clone.point.position, direction);

        if      (direction[0] == 'L')       clone.direction = LEFT;
        else if (direction[0] == 'R')       clone.direction = RIGHT;
        else                                clone.direction = NONE;    


        for (int round_idx = 0; round_idx < nb_rounds; round_idx++) 
        {
            // moves[i] = new Moves();
        }

        for (int time = 0; time < nb_rounds; time++)
        {
            DEBUG("Time = %d\n", time);

        }

        //action = BreadthFirstSearch(clone.point);


        if      (action == ELEVATOR) printf("ELEVATOR\n");
        else if (action == BLOCK)    printf("BLOCK\n");
        else                         printf("WAIT\n");

        //PrintGame(clone.point);
    }

    return 0;
}

// functions
ACTION BreadthFirstSearch(POINT clone_point)
{
    ACTION action = WAIT;

    QUEUE search_queue;
    struct node *start_node = NULL;

    Queue_Init(&search_queue, map_size);

    start_node = NewChildNode(clone_point, NULL);
    Enqueue(start_node, &search_queue);
    SetVisitedPoint(clone_point);
    
    PrintGame(clone_point);

    while(!QueueEmpty(search_queue))
    {
        struct node *current_node   = NULL;
        POINT current_point         = {0, 0};
        POINT point_up              = {0, 0};
        POINT point_left            = {0, 0};
        POINT point_right           = {0, 0};

        current_node                = Dequeue(&search_queue);
        current_point               = current_node->point;
        point_up.floor              = current_point.floor + 1;
        point_up.position           = current_point.position;
        point_left.floor            = current_point.floor;
        point_left.position         = current_point.position - 1;
        point_right.floor           = current_point.floor;
        point_right.position        = current_point.position + 1;

        //DEBUG("OLA");

        // saída
        if (ExitPoint(current_point))
        {
            DEBUG("Exit point found at (%d, %d)\n", current_point.floor, current_point.position);
        }

        // cima
        if (ValidPoint(point_up) && !VisitedPoint(point_up) && ElevatorPoint(current_point))
        {
            struct node *new_child = NewChildNode(point_up, current_node);
            Enqueue(new_child, &search_queue);
            SetVisitedPoint(point_up);
        }

        // esquerda
        if (ValidPoint(point_left) && !VisitedPoint(point_left))
        {
            struct node *new_child = NewChildNode(point_left, current_node);
            Enqueue(new_child, &search_queue);
            SetVisitedPoint(point_left);
        }

        // direita
        if (ValidPoint(point_right) && !VisitedPoint(point_right))
        {
            struct node *new_child = NewChildNode(point_right, current_node);
            Enqueue(new_child, &search_queue);
            SetVisitedPoint(point_right);
        }

        //PrintGame(current_point); //ver a procura a evoluir gasta muitos recursos
    }

    PrintGame(clone_point);

    return action;
}
//
void Queue_Init(QUEUE *queue, int length)
{
    if (queue == NULL)
    {
        DEBUG("ERROR Queue_Init NULL pointer");
        return;
    }

    queue->items = (struct node **)malloc(length *  sizeof(struct node *));
    queue->length = length;
    queue->front = 0;
    queue->rear = 0;
}
bool QueueEmpty(QUEUE queue)
{
    return queue.rear < queue.front;
}
void Enqueue(struct node *node, QUEUE *queue)
{
    if(node == NULL || queue == NULL || queue->items == NULL)
    {
        DEBUG("ERROR Enqueue NULL pointer");
        return;
    }

    queue->items[++queue->rear] = node;
}
struct node *Dequeue(QUEUE *queue)
{ 
    if (queue == NULL || queue->items == NULL)
    {
        DEBUG("ERROR Dequeue NULL pointer\n");
    }

    return queue->items[++queue->front];
}
struct node *NewChildNode(POINT point, struct node* parent)
{
    struct node * new_child_node = NULL;

    new_child_node = (struct node *)malloc(sizeof(struct node));

    new_child_node->point.floor = point.floor;
    new_child_node->point.position = point.position;
    new_child_node->parent = parent;

    return new_child_node;
}
struct node *GetParentNode(struct node* child)
{
    if (child == NULL)
    {
        DEBUG("ERROR GetParentNode NULL pointer");
    }

    return child->parent;
}
//
void PrintGame(POINT current)
{
    POINT map_point;

    for(int floor_idx = nb_floors - 1; floor_idx >= 0; floor_idx--)
    {
        DEBUG( "Floor %2d ", floor_idx);
        for(int pos_idx = 0; pos_idx < width; pos_idx++)
        {
            map_point.floor = floor_idx;
            map_point.position = pos_idx;

            if (current.floor == map_point.floor && current.position == map_point.position)
            {
                DEBUG("C");
            }
            else if (ExitPoint(map_point))
            {
                DEBUG( "S");
            }
            else if (ElevatorPoint(map_point))
            {
                DEBUG("E");
            }
            else if (AdElevatorPoint(map_point))
            {
                DEBUG("A");
            }
            else if (VisitedPoint(map_point))
            {
                DEBUG("_");
            }
            else
            {
                DEBUG(".");
            }
        }
        DEBUG("\n");
    }
    DEBUG("\n");
}
void SetVisitedPoint(POINT point)
{
    SetPoint(&visited, point.floor, point.position);
}
void SetAdElevatorPoint(POINT point)
{
    SetPoint(&ad_elevators, point.floor,point.position);
}
//
bool ValidPoint(POINT point)
{
    return (point.floor >= 0 && point.floor < nb_floors && point.position >= 0 && point.position < width); 
}
bool ExitPoint(POINT point)
{
    return (point.floor == exit_floor && point.position == exit_pos);
}
bool ElevatorPoint(POINT point)
{
    return GetPoint((*elevators), point.floor, point.position);
}
bool VisitedPoint(POINT point)
{
    return GetPoint((*visited), point.floor, point.position);
}
bool AdElevatorPoint(POINT point)
{
    bool res = GetPoint((*ad_elevators), point.floor, point.position);
    
    ClearPoint(&ad_elevators, point.floor, point.position);

    return res;
}
int FloorElevators(int floor)
{
    return floor_elevator_count[floor];
}

// end
