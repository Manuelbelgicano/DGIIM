from random import shuffle,randrange

# --------------------------------------------
# Clases universales

class state:
    walled = 0
    path = 1

class cell:
    def __init__(self,x,y,wn=state.walled,we=state.walled,ws=state.walled,ww=state.walled):
        self.x = x
        self.y = y
        self.walls = {'N':wn,'E':we,'S':ws,'W':ww}
        self.visited = False
    
    def unwall(self,dir):
        self.walls[dir] = state.path
    
    def is_walled(self,dir):
        walled = False
        if self.walls[dir]==state.walled:
            walled = True
        return walled

class maze:
    def __init__(self,row,col,f):
        self.r = row
        self.c = col
        self._map = f(row,col)
    
    def str_maze(self):
        output = "_"
        for i in range(self.c):
            output += "__"
        output += "\n"

        for i in range(self.r):
            if self._map[i][0].is_walled('W'):
                output += "|"
            else:
                output += " "
            for j in range(self.c):
                if self._map[i][j].is_walled('S'):
                    output += "_"
                else:
                    output += " "
                if self._map[i][j].is_walled('E'):
                    output += "|"
                else:
                    output += " "
            output += "\n"
        return output


# --------------------------------------------
# Algoritmo de Prim

def add_frontier(x,y,_map,frontier):
    if x>=0 and x<len(_map) and y>=0 and y<len(_map[0]) and not _map[x][y].visited:
        frontier.append(_map[x][y])

def neighbours(x,y,_map):
    n = []
    if x-1>=0 and _map[x-1][y].visited:
        n.append([x-1,y])
    if x+1<len(_map) and _map[x+1][y].visited:
        n.append([x+1,y])
    if y-1>=0 and _map[x][y-1].visited:
        n.append([x,y-1])
    if y+1<len(_map[x]) and _map[x][y+1].visited:
        n.append([x,y+1])
    return n

def opposite(dir):
    if dir=='N':
        return 'S'
    if dir=='S':
        return 'N'
    if dir=='W':
        return 'E'
    if dir=='E':
        return 'W'

# from 1-->2
def get_dir(x1,y1,x2,y2):
    if x1<x2:
        return 'S'
    elif x1>x2:
        return 'N'
    elif y1<y2:
        return 'E'
    else:
        return 'W'

def visit(c,frontier,_map):
    c.visited = True
    add_frontier(c.x+1,c.y,_map,frontier)
    add_frontier(c.x-1,c.y,_map,frontier)
    add_frontier(c.x,c.y-1,_map,frontier)
    add_frontier(c.x,c.y+1,_map,frontier)

def prim_gen(r,c):
    _map = [[cell(i,j) for j in range(c)] for i in range(r)]
    
    current = _map[randrange(0,r)][0]
    current.unwall('W')
    frontier = []
    visit(current,frontier,_map)

    while frontier:
        current = frontier[0]
        frontier = frontier[1:]
        if not current.visited:
            neig = neighbours(current.x,current.y,_map)
            nx,ny = neig[randrange(0,len(neig))]
            d = get_dir(current.x,current.y,nx,ny)
            current.unwall(d)
            _map[nx][ny].unwall(opposite(d))
            visit(current,frontier,_map)
    
    current = _map[randrange(0,r)][c-1]
    current.unwall('E')

    return _map

# --------------------------------------------
# Algoritmo de Kruskal

def movx(dir):
    mov = 0
    if dir=='N':
        mov = -1
    elif dir=='S':
        mov = 1
    return mov

def movy(dir):
    mov = 0
    if dir=='W':
        mov = -1
    elif dir=='E':
        mov = 1
    return mov

def edges(r,c):
    edges = []
    for i in range(r):
        for j in range(c):
            if i>0:
                edges.append([i,j,'N'])
            if j>0:
                edges.append([i,j,'W'])
    shuffle(edges)
    return edges

def kruskal_gen(r,c):
    _map = [[cell(i,j) for j in range(c)] for i in range(r)]
    sets = [[] for i in range(r*c)]
    k = 0
    for i in range(r):
        for j in range(c):
            sets[k].append(_map[i][j])
            k += 1
            


    print(sets)
    candidates = edges(r,c)

    while candidates:
        x,y,d = candidates[0]
        candidates = candidates[1:]
        nx = x + movx(d)
        ny = y + movy(d)

    return _map

lab1 = maze(10,10,prim_gen)
print("ALGORITMO PRIM:")
print(lab1.str_maze())
lab2 = maze(10,10,kruskal_gen)
print("ALGORITMO KRUSKAL:")
print(lab2.str_maze())