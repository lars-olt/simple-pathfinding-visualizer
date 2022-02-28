# simple-pathfinding-visualizer
This is a small project I built to visualize the Dijkstra and A* pathfinding algorithms. It is written in C++ and uses SDL2 to get user input and allow for pixel manipulation.

Controls are:
- First two mouse clicks define start and end nodes
- Subsequent mouse click/click-drags add "barrier" nodes to grid
- ("D" key) runs dijkstra's algorithm
- ("A" key) runs A* algorithm
- ("R" key) clears the grid


Examples of running A* (left) and djikstra (right) algorithms:
<p float="left">
  <img src="https://user-images.githubusercontent.com/67205657/155917343-e5f989c9-0d7f-4034-9737-ac5b9a0ca31d.gif" width=200 height=200>
  <img src="https://user-images.githubusercontent.com/67205657/155918178-94300134-9055-4ce7-a457-a04b721faeec.gif" width=200 height=200>
</p>

