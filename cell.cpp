
#include<iostream>
using namespace std;

typedef enum{available,route,backtracked,wall} Status;

typedef enum{unknown,east,south,west,north,no_way} ESWN;

inline ESWN next_eswn(ESWN eswn )
{
    return ESWN(eswn +1);
}
typedef int Rank;
struct Cell
{
    int x,y;
    Status status;
    ESWN incoming, outgoing; 
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];

inline Cell*neighbor(Cell *cell)
{
    switch (cell->outgoing)
    {
        case east:return cell+LABY_MAX;
        case south:return cell +1;
        case west:return cell-LABY_MAX;
        case north: return cell-1;
        default: exit(-1);
    }
}

inline Cell*advance(Cell*cell)
{
    Cell*next;
    switch(cell->outgoing)
    {
        case east: 
            next=cell+LABY_MAX;
            next->incoming=west;
            break;
        case south:
            next=cell+1;
            next->incoming=north;
            break;
        case west:
            next=cell-LABY_MAX;
            next->incoming=east;
            break;
        case north:
            next=cell-1;
            next->incoming =south;
            break;
        default:    
            exit(-1);
    }
    return next;
}

bool labyrinth(Cell laby[LABY_MAX][LABY_MAX],Cell*s,Cell*t)
{
    if((available!=s->status)||(available!=t->status))
        return false;
    stack<cell*> path;
    s->incoming=unknown;
    s->status=route;
    path.push(s);

    do
    {
        Cell*c= path.top();
        if(c==t)
            return true;
        while(no_way>(c->outgoing=next_eswn(c->outgoing)))
            if(available==neighbor(c)->status)
                break;
        if(no_way<=c->outgoing)
        {
            c->status=backtracked;
            c=path.pop();
        }else
        {
            path.push(c=advance (c));
            c->outgoing=unknown;
            c->status=route;
        }
        
    }while(!path.empty());
    return false;
}

int main()
{
    return 0;
}