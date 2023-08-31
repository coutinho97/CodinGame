#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// define
#define DEBUG_ENABLE        1
#define LEFT                0
#define RIGHT               1

// macros
#if DEBUG_ENABLE
#define DEBUG(fmt, ...)     fprintf(stderr, fmt, ##__VA_ARGS__)
#define ola                 DEBUG("ola\n");
#else
#define DEBUG(...)
#define ola
#endif

// Define os movimentos possíveis
typedef enum {
    WAIT        = 0,
    ELEVATOR    = 1,
    BLOCK       = 2
} Move;

// Estrutura para representar uma unidade no jogo
typedef struct {
    int floor, position, clones, ad_elevators_count, direction;
    Move parent_move;
} Unit;

// Estrutura para representar todas as possiblidades do jogo
typedef struct {
    int total_floor, total_position, total_clone, total_elevator;
    bool *****arr;
} Checked;

// Estrutura para armazenar as possiblidades do jogo
typedef struct {
    int *size;
    Unit *arr;
} Moves;

// Estrutura para representar o mapa do jogo
typedef struct {
    int floors, positions, rounds, exit_floor, exit_position, clones, ad_elevators_count, elevators_count;
    bool **elevators;
} GameMap;

// function prototype
void GameMap_Init(GameMap* map);
void Elevators_Init(GameMap *map);
void Checked_Init(GameMap map);
void Moves_Init(int rounds);
void Unit_Init(Unit* unit, int floor, int position, int clones, int ad_elevators_count, int direction, Move parent_move);
void UpdateClone(int *clone_floor, int *clone_position, int *direction);
void ExecuteMove(Move move, GameMap *map);
Move GetMove(Unit now);
void BFS(Unit now, int time);
//
void SetChecked(int floor, int position, int clones, int elevators, int direction);
bool GetChecked(int floor, int position, int clones, int elevators, int direction);
void AddMoves(int time, int floor, int position, int clones, int elevators, int direction, int move);
Unit GetMoves(int time);
bool PositionInRange(int position);
bool Elevator(Unit unit);
bool Exit(Unit unit);

// var
GameMap map;
Moves moves;
Checked checked;

int main()
{
    GameMap_Init(&map); 
    Elevators_Init(&map);

    while (1) 
    {
        int clone_floor, clone_position, dir;
        Unit player_unit;
        Move move;

        UpdateClone(&clone_floor, &clone_position, &dir);
        Unit_Init(&player_unit, clone_floor, clone_position, map.clones, map.ad_elevators_count, dir, WAIT);

        move = GetMove(player_unit);
        ExecuteMove(move, &map);
    }

    return 0;
}
//
void GameMap_Init(GameMap *map)
{
    scanf("%d%d%d%d%d%d%d%d", &map->floors, &map->positions, &map->rounds, &map->exit_floor, &map->exit_position, &map->clones, &map->ad_elevators_count, &map->elevators_count);
    //DEBUG("GameMap_Init -> floors: %d, positions: %d, rounds: %d, exit_floor: %d, exit_position: %d, clones: %d, ad_elevators_count: %d, elevators_count: %d\n", map->floors, map->positions, map->rounds, map->exit_floor, map->exit_position, map->clones, map->ad_elevators_count, map->elevators_count);

    map->elevators = (bool**)malloc(map->floors * sizeof(bool*));

    for (int floor_idx = 0; floor_idx < map->floors; floor_idx++)
    {
        map->elevators[floor_idx] = (bool*)malloc(map->positions * sizeof(bool*));
        
        for (int position_idx = 0; position_idx < map->positions; position_idx++)
        {
            map->elevators[floor_idx][position_idx] = false;
        }
    }
}
void Unit_Init(Unit *unit, int floor, int position, int clones, int ad_elevators_count, int direction, Move parent_move)
{
    unit->floor                 = floor;
    unit->position              = position;
    unit->clones                = clones;
    unit->ad_elevators_count    = ad_elevators_count;
    unit->direction             = direction;
    unit->parent_move           = parent_move;
}
void Elevators_Init(GameMap *map)
{
    for (int elevator_idx = 0; elevator_idx < map->elevators_count; elevator_idx++) 
    {
        int elevator_floor, elevator_pos;
        scanf("%d%d", &elevator_floor, &elevator_pos);
        map->elevators[elevator_floor][elevator_pos] = true;    // armazenar elevadores
    }
}
void Checked_Init(GameMap map)
{
    checked.total_floor     = map.floors;
    checked.total_position  = map.positions;
    checked.total_clone     = map.clones + 1;
    checked.total_elevator  = map.ad_elevators_count + 1;

    //DEBUG("Checked_Init -> floors %d, positions %d, clones %d, elevators %d, directions %d\n", checked.total_floor, checked.total_position, checked.total_clone, checked.total_elevator, 2);

    checked.arr = (bool*****)malloc(checked.total_floor * sizeof(bool****));

    for(int floor_idx = 0; floor_idx < checked.total_floor; floor_idx++)
    {
        checked.arr[floor_idx] = (bool****)malloc(checked.total_position * sizeof(bool***));

        for (int position_idx = 0; position_idx < checked.total_position; position_idx++)
        {
            checked.arr[floor_idx][position_idx] = (bool***)malloc(checked.total_clone * sizeof(bool**));

            for (int clone_idx = 0; clone_idx < checked.total_clone; clone_idx++)
            {
                checked.arr[floor_idx][position_idx][clone_idx] = (bool**)malloc(checked.total_elevator * sizeof(bool*));

                for (int elevator_idx = 0; elevator_idx < checked.total_elevator; elevator_idx++)
                {
                    checked.arr[floor_idx][position_idx][clone_idx][elevator_idx] = (bool*)malloc(2 * sizeof(bool));
                    checked.arr[floor_idx][position_idx][clone_idx][elevator_idx][0] = false;
                    checked.arr[floor_idx][position_idx][clone_idx][elevator_idx][1] = false;
                }
            }
        }
    }
}
void Moves_Init(int rounds)
{
    moves.arr = (Unit*)malloc(rounds * sizeof(Unit));
    moves.size = (int*)malloc(rounds * sizeof(int));
    
    //DEBUG("Moves_Init -> rounds %d \n", rounds);

    for (int round_idx = 0; round_idx < rounds; round_idx++)
    {
        moves.size[round_idx] = rounds;
    }
}
void UpdateClone(int *clone_floor, int *clone_position, int *direction)
{
    char direction_string[11];
    scanf("%d%d%s", clone_floor, clone_position, direction_string);

    if(direction_string[0] == 'R')  (*direction) = RIGHT;
    else                            (*direction) = LEFT;
}
void ExecuteMove(Move move, GameMap *map)
{
    char move_string[20];

    switch (move) 
    {
        case ELEVATOR:

            map->clones--;
            map->ad_elevators_count--;
            strcpy(move_string, "ELEVATOR\n");
        break;
        
        case BLOCK:
        
            map->clones--;
            strcpy(move_string, "BLOCK\n");
        break;

        default:

            strcpy(move_string, "WAIT\n");
        break;
    }

    map->rounds--;

    printf("%s", move_string);
}
Move GetMove(Unit now)
{
    static bool found_path = false;

    if (now.position == -1) return WAIT;

    Checked_Init(map);
    Moves_Init(map.rounds);

    SetChecked(now.floor, now.position, now.clones, now.ad_elevators_count, now.direction);
    AddMoves(0, now.floor, now.position, now.clones, now.ad_elevators_count, now.direction, now.parent_move);

    for (int time = 0; time < map.rounds; time++)
    {
        //DEBUG("moves %d - ", moves.size[time]);

        while (moves.size[time] > 0)
        {
            Unit cnt = GetMoves(time);
 
            if (Exit(cnt))
            {
                DEBUG("Reached exit at: %d", time);
                found_path = true;
                return cnt.parent_move;
            }

            BFS(cnt, time);
            moves.size[time]--;
        }

        //DEBUG("\n");
    }

    return WAIT;
}
void BFS(Unit now, int time)
{
    bool can_block, can_lift;
    int dir, next_point_actual_dir, next_point_opposite_dir;

    can_block = now.clones > 0;
    can_lift  = now.ad_elevators_count > 0 && can_block && now.floor < map.exit_floor;

    dir                     = now.direction == LEFT ? -1 : 1;
    next_point_actual_dir   = now.position + dir;
    next_point_opposite_dir = now.position - dir;

    time++;

    if (Elevator(now))
    {
        AddMoves(time, now.floor, next_point_actual_dir, now.clones, now.ad_elevators_count, now.direction, WAIT);
        SetChecked(now.floor, next_point_actual_dir, now.clones, now.ad_elevators_count, now.direction);
        return;
    }

    // Check if we can go oposite direction and if we can wait and block clones
    if (can_block && PositionInRange(next_point_opposite_dir) && \
    !GetChecked(now.floor, next_point_opposite_dir, now.clones - 1, now.ad_elevators_count, !now.direction))
    {
        AddMoves(time, now.floor, next_point_opposite_dir, now.clones - 1, now.ad_elevators_count, !now.direction, BLOCK);
        SetChecked(now.floor, next_point_opposite_dir, now.clones - 1, now.ad_elevators_count, !now.direction);
        DEBUG("%d ", next_point_opposite_dir);
    }

    // Check if we can continue with same direction
    if (PositionInRange(next_point_actual_dir) && \
    !GetChecked(now.floor, next_point_actual_dir, now.clones, now.ad_elevators_count, now.direction)) 
    {
        AddMoves(time, now.floor, next_point_actual_dir, now.clones, now.ad_elevators_count, now.direction, WAIT);
        SetChecked(now.floor, next_point_actual_dir, now.clones, now.ad_elevators_count, now.direction);
        //DEBUG("S ");
    }

    // Check if we can wait and activate elevator
    if (can_lift && PositionInRange(now.position) && \
    !GetChecked(now.floor + 1, now.position, now.clones - 1, now.ad_elevators_count - 1, now.direction)) 
    {
        AddMoves(time, now.floor + 1, now.position, now.clones - 1, now.ad_elevators_count - 1, now.direction, ELEVATOR);
        SetChecked(now.floor + 1, now.position, now.clones - 1, now.ad_elevators_count - 1, now.direction);
        //DEBUG("A ");
    }
}
//
bool CheckError(int floor, int position, int clones, int elevators, int direction)
{
    bool error = false;

    //DEBUG("floor %d, position %d, clones %d, elevators %d, direction %d\n", floor, position, clones, elevators, direction);
    if (floor > checked.total_floor - 1 || floor < 0)
    {
        DEBUG("ERROR GetC floor");
        error = true;
    }

    if (position > checked.total_position - 1 || position < 0)
    {
        DEBUG("ERROR GetC position %d", position);
        error = true;
    }

    if (clones > checked.total_clone - 1 || clones < 0)
    {
        DEBUG("ERROR GetC clones %d", clones);
        error = true;
    }

    if (elevators > checked.total_elevator - 1 || elevators < 0)
    {
        DEBUG("ERROR GetC elevators %d", elevators);
        error = true;
    }

    if (direction > 1 || direction < 0)
    {
        DEBUG("ERROR GetC direction %d", position);
        error = true;
    }

    if (error) DEBUG("\n");

    return error;
}
void SetChecked(int floor, int position, int clones, int elevators, int direction)
{
    if (CheckError(floor, position, clones, elevators, direction))
    {
        return;
    }
    else
    {
        checked.arr[floor][position][clones][elevators][direction] = true;
    }
}
bool GetChecked(int floor, int position, int clones, int elevators, int direction)
{
    if (CheckError(floor, position, clones, elevators, direction))
    {
        return true;
    } 
    else
    {
        return checked.arr[floor][position][clones][elevators][direction];
    }
}
void AddMoves(int time, int floor, int position, int clones, int elevators, int direction, int move)
{
    Unit new_unit;

    if (time > map.rounds)
    {
        DEBUG("ERROR AddMoves time: %d rounds: %d\n",time, map.rounds); return;
    }
    else
    {
        Unit_Init(&new_unit, floor, position, clones, elevators, direction, move);
        moves.arr[time] = new_unit;
    }
}
Unit GetMoves(int time)
{
    Unit ret;

    if (time > map.rounds)
    {
        DEBUG("ERRO GetMoves %d\n", time);
    }
    else
    {
        ret = moves.arr[time];
    }

    return ret;
}
bool PositionInRange(int position)
{
    return position >= 0 && position < map.positions - 1;
}
bool Elevator(Unit unit)
{
    return map.elevators[unit.floor][unit.position];
}
bool Exit(Unit unit)
{
    return unit.floor == map.exit_floor && unit.position == map.exit_position;
}

// end
