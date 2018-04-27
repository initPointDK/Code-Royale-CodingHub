import sys
import math
import time

class Site:
    def __init__(self, row_input):
        self.site_id, self.x, self.y, self.radius = map(int, row_input.split())        
    
    def update(self, row_input):
        self.site_id, self.ignore_1, self.ignore_2, self.structure_type, self.owner, self.param_1, self.param_2 = map(int, row_input.split())
        
class Unit:
    me = None
    enemy = None
    def __init__(self, row_input):
        self.x, self.y, self.owner, self.unit_type, self.health = map(int, row_input.split())
        if self.owner == 0 and self.unit_type == -1:
            Unit.me = self
        if self.owner == 1 and self.unit_type == -1:
            Unit.enemy = self

def dist(self, other):
    return math.sqrt((other.x - self.x) ** 2 + (other.y - self.y) ** 2)
    
num_sites = int(input())
sites = [Site(input()) for i in range(num_sites)]

while True:
    gold, touched_site = map(int,input().split())
    for s in sites: s.update(input())
    num_units = int(input())
    units = [Unit(input()) for _ in range(num_units)]
    empty_sites = filter(lambda s: s.structure_type == -1,sites)
    dists = sorted(empty_sites,key= lambda s: dist(Unit.me,s))
    my_sites = list(filter(lambda s: s.owner == 0,sites))
    to_enemy_dists = sorted(my_sites,key= lambda s: dist(Unit.enemy,s))
    no_knights = len(list(filter(lambda s: s.param_2 == 0, my_sites)))
    no_archers = len(list(filter(lambda s: s.param_2 == 1, my_sites)))
    if no_knights < 2:
        if no_archers < 2:
            print("BUILD " + str(dists[0].site_id) + " BARRACKS-ARCHER")
        else:
            print("BUILD " + str(dists[0].site_id) + " BARRACKS-KNIGHT")
    else:
        print("WAIT")
    no_archer_units = len(list(filter(lambda u: u.owner == 0 and u.unit_type == 1, units)))
    st=""
    for s in to_enemy_dists:
        if no_archer_units < 2 :
            if gold >= 100 and s.param_2 == 1:
                st +=  " " + str(s.site_id)
                gold -= 100
        else:
            if gold >= 80 and s.param_2 == 0:
                st +=  " " + str(s.site_id)
                gold -= 80
    print("TRAIN" + st)
