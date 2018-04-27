import sys
import math
class Site:
    def __init__(self, row_input):self.site_id, self.x, self.y, self.radius = map(int, row_input.split())        
    def update(self, row_input):
        self.site_id, self.gold, self.max_mine_size, self.structure_type, self.owner, self.param_1, self.param_2 = map(int, row_input.split())
class Unit:
    me = None
    enemy = None
    def __init__(self, row_input):
        self.x, self.y, self.owner, self.unit_type, self.health = map(int, row_input.split())
        Unit.me = self if self.owner == 0 and self.unit_type == -1 else Unit.me
        Unit.enemy = self if self.owner == 1 and self.unit_type == -1 else Unit.enemy
def dist(self, other): return math.sqrt((other.x - self.x) ** 2 + (other.y - self.y) ** 2)
def wait():
    print("WAIT")

trying_build_mine=0
def build(site, struct, creep):
    s = str(site.site_id)
    if struct == 0:
        s+= " MINE"
        trying_build_mine+=1
    elif struct == 1:
        s+=" TOWER" 
        trying_build_mine=0
    else: 
        trying_build_mine=0
        s+=" BARRACKS-"
        if creep == 0:
            s+="KNIGHT"
        elif creep == 1:
            s+="ARCHER"
        else:
            s+="GIANT"
    print("BUILD "+s)
def move(p):
    s=str(p.x) + " " + str(p.y)
    print("MOVE "+s)
sites = [Site(input()) for i in range(int(input()))]
while 1:
    gold, touched_site = map(int,input().split())
    for s in sites: s.update(input())
    units = [Unit(input()) for _ in range(int(input()))]
    empty_sites = filter(lambda s: s.structure_type == -1,sites)
    dists = sorted(empty_sites,key= lambda s: dist(Unit.me,s))
    my_sites = list(filter(lambda s: s.owner == 0,sites))
    no_knights = len(list(filter(lambda s: s.param_2 == 0, my_sites)))
    no_archers = len(list(filter(lambda s: s.param_2 == 1, my_sites)))
    mines_not_max = list(filter(lambda s: s.structure_type == 0 and s.param_1 != s.max_mine_size, my_sites))
    mines_not_max_sorted = sorted(mines_not_max, key=lambda s:dist(Unit.me,s))
    no_mines_max = len(list(filter(lambda s: s.structure_type == 0 and s.param_1 == s.max_mine_size, my_sites)))
    
    towers = list(filter(lambda s: s.structure_type == 1, my_sites))
    no_towers = len(towers)
    if no_towers < 1 :
        if no_archers < 1:
            if no_knights <1:
                if no_mines_max <1:
                    if trying_build_mine>5:
                        build(dists[0],1,0)
                    else:
                        if len(mines_not_max_sorted):
                            build(mines_not_max_sorted[0], 0,0)
                        else:
                            build(dists[0], 0,0)
                else:
                    build(dists[0], 2,0)
            else:
                build(dists[0], 2, 1)
        else:
            build(dists[0], 1, 0)  
    else:
        if no_mines_max <2:
            if trying_build_mine >5:
                build(dists[0],1,0)
            else:
                try:
                    build(mines_not_max_sorted[0], 0,0)
                except:
                    build(dists[0], 0,0)
    no_archer_units = len(list(filter(lambda u: u.owner == 0 and u.unit_type == 1, units)))
    no_knight_units = len(list(filter(lambda u: u.owner == 0 and u.unit_type == 0, units)))
    to_enemy_dists = sorted(my_sites,key= lambda s: dist(Unit.enemy,s))
    st=""
    for s in to_enemy_dists:
        if no_knight_units >=4 and no_archer_units < 2 :
            if gold >= 100 and s.param_2 == 1:
                st +=  " " + str(s.site_id)
                gold -= 100
        else:
            if gold >= 80 and s.param_2 == 0:
                st +=  " " + str(s.site_id)
                gold -= 80
    print("TRAIN" + st)
