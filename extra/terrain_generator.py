from random import random,randint,choice

class cell:
    """
    A class used to represent a terrain cell of a 2D terrain grid

    Attributes
    ----------
    x : int
        the row position of the cell in the grid
    y : int
        the column position of the cell in the grid
    state : str
        the terrain of the cell (default water)
    neighbours: list
        list of neighbouring cells of the grid
    
    Methods
    -------
    state_neighbours(_state) : int
        Returns the number of neighbouring cells that have `_state`
    non_diagonal() : list
        Returns the non-diagonal neighbours of the cell
    """
    def __init__(self,i=-1,j=-1):
        """
        Parameters
        ----------
        i : int, optional
            the row of the cell in the grid (default -1)
        j : int, optional
            the column of the cell in the grid (default -1)
        """
        self.x = i
        self.y = j
        self.state = ""
        self.neighbours = []
  
    def state_neighbours(self,_state):
        """ Returns the number of neighbouring cells that have `_state`
        Parameters
        ----------
        _state : str
            the cell state
        """
        num = 0
        for a in self.neighbours:
            if a.state==_state:
                num += 1
        return num
    
    def non_diagonal(self):
        """Returns the non-diagonal neighbours of the cell
        """
        non_diag = [self.neighbours[i] for i in range(len(self.neighbours)) if 
                    (self.x==self.neighbours[i].x and (self.y==self.neighbours[i].y+1 
                    or self.y==self.neighbours[i].y-1)) or 
                    (self.y==self.neighbours[i].y and (self.x==self.neighbours[i].x+1 
                    or self.x==self.neighbours[i].x-1))]
        return non_diag

class map2D:
    """
    A class used to represent a 2D map


    Attributes
    ----------
    water : str
        the symbol to represent water
    land : str
        the symbol to represent land
    river : str
        the symbol to represent a river
    mountain : str
        the symbol to represent a mountain
    map : list
        the grid of the map
    height : int
        the height of the map
    width : int
        the width of the map
    
    Methods
    -------
    set_terrain_view(iter,prob_l,tol,prob_r,r_len,prob_m,m_len) : void
        Creates the map
    print_map() : str
        Returns a graphical representation for the map
    """

    water = "~"
    land = "⯀"
    river = "-"
    mountain = "^"

    def __init__(self,h,w):
        self.map = []
        self.height = h
        self.width = w

        for i in range(h):
            row = []
            for j in range(w):
                c = cell(i,j)
                c.state = map2D.water
                row.append(c)
            self.map.append(row)
        
        for row in self.map:
            for c in row:
                for i in range(c.x-1,c.x+2):
                    for j in range(c.y-1,c.y+2):
                        if i>=0 and i<h:
                            if j>=0 and j<w:
                                    c.neighbours.append(self.map[i][j])
                c.neighbours.remove(c)

    def set_terrain(self,iter=3,prob_l=0.5,tol=4,prob_r=0.1,r_len=6,prob_m=0.05,m_len=4):
        """Creates the map
        Parameters
        ----------
        iter : int, optional
            the number of smoothing iterations to the map (default 3)
        prob_l : float, optional
            the probability to spawn land (default 0.5)
        tol : int, optional
            the number of adjacent cells minimum for a cell to have the same state (default 4)
        prob_r : float, optional
            the probability to spawn rivers (default 0.1)
        r_len : int, optional
            the maximum lenght of rivers (default 6)
        prob_m : float, optional
            the probability to spawn mountains (default 0.05)
        m_len : int, optional
            the maximum lenght of mountain ranges (default 4)
        """
        # Land generation
        for row in self.map:
            for c in row:
                if random()<prob_l:
                    c.state = map2D.land
        print(self.print_map(),"\n")
        
        # Smoothing
        n_iter = iter
        while n_iter>=0:
            for row in self.map:
                for c in row:
                    corner = ((c.x==0 or c.x==self.height-1) and
                              (c.y==0 or c.y==self.width-1))
                    if c.state==map2D.water and c.state_neighbours(map2D.water)<tol:
                        if corner and c.state_neighbours(map2D.water)<2:
                            c.state = map2D.land
                        elif not corner:
                            c.state = map2D.land
                    elif c.state==map2D.land and c.state_neighbours(map2D.land)<tol:
                        if corner and c.state_neighbours(map2D.land)<2:
                            c.state = map2D.water
                        elif not corner:
                            c.state = map2D.water
            n_iter -= 1
            print("Smoothing number",iter-n_iter,":")
            print(self.print_map(),"\n")
        
        # Mountain and river generation
        for row in self.map:
            seas = [row[i] for i in range(len(row)) if row[i].state==map2D.water]
            for c in seas: # River generation
                shores = [c.neighbours[i] for i in range(len(c.neighbours)) if 
                          c.neighbours[i].state==map2D.land]
                if shores and random()<prob_r:
                    new_river = choice(shores)
                    if new_river.state_neighbours(map2D.river)==0:
                        new_river.state = map2D.river
                        river_lenght = randint(0,r_len-1)
                        last_cell = new_river
                        end = False
                        while river_lenght>0 and not end:
                            non_diag = last_cell.non_diagonal()
                            candidates = [non_diag[i] for i in 
                                        range(len(non_diag)) if 
                                        non_diag[i].state!=map2D.water
                                        and non_diag[i].state!=map2D.river]
                            if not candidates:
                                end = True
                            else:
                                last_cell = choice(candidates)
                                last_cell.state = map2D.river
                                river_lenght -= 1
                        print("New river:")
                        print(self.print_map(),"\n")
            lands = [row[i] for i in range(len(row)) if row[i].state==map2D.land and 
                     row[i].state_neighbours(map2D.mountain)==0]
            for c in lands: # Mountain generator
                if random()<prob_m:
                    c.state = map2D.mountain
                    mountain_lenght = randint(0,m_len-1)
                    last_cell = c
                    end = False
                    while mountain_lenght>0 and not end:
                        candidates = [last_cell.neighbours[i] for i in
                                      range(len(last_cell.neighbours)) if
                                      last_cell.neighbours[i].state==map2D.land]
                        if not candidates:
                            end = True
                        else:
                            last_cell = choice(candidates)
                            last_cell.state = map2D.mountain
                            mountain_lenght -= 1
                        print("New mountain:")
                        print(self.print_map(),"\n")
        print("\nFINAL VERSION:")
        print(self.print_map(),"\n")

    def print_map(self):
        """Returns a graphical representation for the map
        """
        map_image = "   "
        for i in range(len(self.map[0])):
            map_image += str(i+1) + " "
            if i<9:
                map_image += " "
        map_image += "\n"
        for i in range(len(self.map)):
            map_image += str(i+1) + " "
            if i<9:
                map_image += " "
            for j in range(len(self.map[i])):
                map_image += str(self.map[i][j].state) + "  "
            map_image += "\n"
        return map_image

# Program
mapa = map2D(20,40)
mapa.set_terrain()