# search.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
In search.py, you will implement generic search algorithms which are called 
by Pacman agents (in searchAgents.py).
"""

import util
           

def tinyMazeSearch(problem):
  """
  Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze
  """
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s,s,w,s,w,w,s,w]

def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first [p 85].
  
  Your search algorithm needs to return a list of actions that reaches
  the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].
  
  To get started, you might want to try some of these simple commands to
  understand the search problem that is being passed in:
  
  print "Start:", problem.startingState()
  print "Is the start a goal?", problem.isGoal(problem.startingState())
  print "Start's successors:", problem.successorStates(problem.startingState())

  """

  #create a stack 
  from util import Stack
  stack = Stack()

  #get the starting vertex, push it on the stack
  startingVertex = (problem.startingState(),"",0)
  stack.push(startingVertex)

  #create a dict that stores the parents of a node
  parents = {}

  #set of visited nodes
  visited = set(startingVertex[0])

  #final path to be returned
  path = []

  while stack:
    v = stack.pop()
    #get successors of the coordinates of v
    for u in problem.successorStates(v[0]):
      
      #if the coordinate hasn't been visited then
      #visit it, push it, and set parent coordinate and direction
      if not u[0] in visited:
        visited.add(u[0])
        stack.push(u)
        parents[u[0]] = v
        
        #if we found the goal then backtrace using the parent dict
        #and prepend to the final path with the next nodes corresponding
        #directions
        if problem.isGoal(u[0]):

          curr = u
          while curr != startingVertex:
            path.insert(0,curr[1])
            curr = parents[curr[0]]

          #return the path of directions
          return path


def breadthFirstSearch(problem):
  print "IN BFS"

  #create a queue 
  from util import Queue
  queue = Queue()

  #get the starting vertex, push it on the queue
  startingVertex = (problem.startingState(),"",0)
  queue.push(startingVertex)

  #create a dict that stores the parents of a node
  parents = {}

  #set of visited nodes
  visited = set(startingVertex[0])

  #final path to be returned
  path = []

  while queue:
    v = queue.pop()
    #print v
    #get successors of the coordinates of v
    for u in problem.successorStates(v[0]):
      
      #if the coordinate hasn't been visited then
      #visit it, push it, and set parent coordinate and direction
      if not u[0] in visited:
        visited.add(u[0])
        queue.push(u)
        parents[u[0]] = v
        
        #if we found the goal then backtrace using the parent dict
        #and prepend to the final path with the next nodes corresponding
        #directions
        if problem.isGoal(u[0]):

          curr = u
          while curr != startingVertex:
            path.insert(0,curr[1])
            curr = parents[curr[0]]

          #return the path of directions
          #print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          print path
          return path

      
def uniformCostSearch(problem):

  #create a priority queue 
  from util import PriorityQueue
  pQueue = PriorityQueue()

  #get the starting vertex, push it on the priority queue
  startingVertex = (problem.startingState(),"",0)
  pQueue.push(startingVertex,startingVertex[2])

  #create a dict that stores the parents of a node
  parents = {}

  #set of visited nodes
  visited = set(startingVertex[0])

  #final path to be returned
  path = []

  #used to calculate cost
  cost = 0

  while pQueue:
    v = pQueue.pop()
    #print v

    #get successors of the coordinates of v
    for u in problem.successorStates(v[0]):
      
      #if the coordinate hasn't been visited then
      #visit it, push it, and set parent coordinate and direction
      if not u[0] in visited:
        visited.add(u[0])

        #arithmetic to set the cost equal to u + it's parents cost
        if parents.has_key(v[0]):
          par = parents[v[0]]
          cost = u[2] + par[1]
        else:
          cost = u[2]

        #push the cost upstream
        parents[u[0]] = (v,cost)
        pQueue.push(u,cost)
        
        #if we found the goal then backtrace using the parent dict
        #and prepend to the final path with the next nodes corresponding
        #directions
        if problem.isGoal(u[0]):

          curr = u
          while curr != startingVertex:
            path.insert(0,curr[1])
            par = parents[curr[0]]
            curr = par[0]

          #return the path of directions

          return path

    

def nullHeuristic(state, problem=None):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided SearchProblem.  This heuristic is trivial.
  """

  return 0


def aStarSearch(problem, heuristic=nullHeuristic):

  #create a priority queue 
  from util import PriorityQueue
  pQueue = PriorityQueue()

  #get the starting vertex, push it on the priority queue
  startingVertex = (problem.startingState(),"",0)
  pQueue.push(startingVertex,startingVertex[2])

  #create a dict that stores the parents of a node
  parents = {}

  #set of visited nodes
  visited = set(startingVertex[0])

  #final path to be returned
  path = []

  #used to calculate cost
  cost = 0

  while pQueue:
    v = pQueue.pop()

    #get successors of the coordinates of v
    for u in problem.successorStates(v[0]):
      
      #if the coordinate hasn't been visited then
      #visit it, push it, and set parent coordinate and direction
      if not u[0] in visited:
        visited.add(u[0])

        #arithmetic to set the cost equal to u + it's parents cost
        if parents.has_key(v[0]):
          par = parents[v[0]]
          cost = u[2] + par[1]
        else:
          cost = u[2]

        #push the cost upstream
        parents[u[0]] = (v,cost)

        #add the heuristic value
        f = cost + heuristic(u[0],problem)

        #push u with f value onto the priority queue
        pQueue.push(u,f)
        
        #if we found the goal then backtrace using the parent dict
        #and prepend to the final path with the next nodes corresponding
        #directions
        if problem.isGoal(u[0]):

          curr = u
          while curr != startingVertex:
            path.insert(0,curr[1])
            par = parents[curr[0]]
            curr = par[0]

          #return the path of directions
          print len(path)
          return path
  
# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
