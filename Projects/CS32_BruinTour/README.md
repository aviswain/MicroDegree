# BruinTour
Automated tour guide system that loads and indexes a bunch of Open Street Map geospatial data (which contain latitude and longitude data for thousands of streets) along with a list of 
points of interest and then uses this data to generate a relatively optimized set of instructions for the tour. 

### Example usage
Below is small example of a generated tour route using the `stops.txt` and `mapdata.txt` files on this repo.

**stops.txt**
```
Ackerman Union|This is Ackerman where you buy stuff.
John Wooden Center|This is where you go to get swole.
Diddy Riese|They sell yummy cheap cookies here.
Ackerman Union|We're back at Ackerman, and this is the end of your tour.
```
**mapdata.txt**
```
too large to fit here but you can find in the "input_files" folder.

:)
```
**program output**
```
Routing...

Starting tour...
Welcome to Ackerman Union!
This is Ackerman where you buy stuff.
Proceed 0.028 miles north on a path
Take a left turn on Bruin Walk
Proceed 0.098 miles west on Bruin Walk
Take a right turn on a path
Proceed 0.074 miles north on a path
Welcome to John Wooden Center!
This is where you go to get swole.
Proceed 0.074 miles south on a path
Take a left turn on Bruin Walk
Proceed 0.043 miles east on Bruin Walk
Take a right turn on Westwood Plaza
Proceed 0.514 miles south on Westwood Plaza
Take a right turn on Le Conte Avenue
Proceed 0.097 miles west on Le Conte Avenue
Take a left turn on Broxton Avenue
Proceed 0.053 miles south on Broxton Avenue
Take a left turn on a path
Proceed 0.015 miles northeast on a path
Welcome to Diddy Riese!
They sell yummy cheap cookies here.
Proceed 0.015 miles southwest on a path
Take a right turn on Broxton Avenue
Proceed 0.053 miles north on Broxton Avenue
Take a right turn on Le Conte Avenue
Proceed 0.097 miles east on Le Conte Avenue
Take a left turn on Westwood Plaza
Proceed 0.514 miles northeast on Westwood Plaza
Take a right turn on Bruin Walk
Proceed 0.055 miles east on Bruin Walk
Take a right turn on a path
Proceed 0.028 miles south on a path
Welcome to Ackerman Union!
We're back at Ackerman, and this is the end of your tour.
Your tour has finished!
Total tour distance: 1.758 miles
```


### Generating an optimized path
For finding the best route between tour stops, I used the A* algorithm. In short, it works by applying a heuristic function to Dijkstra's Algorithm that lets the actor know if they are moving closer towards their goal or not. If you are interesting in implementing it yourself, here are some of the resources I found extremely helpful!
- [A* (A Star) Search and Heuristics Intuition in 2 minutes](https://youtu.be/71CEj4gKDnE?si=dfaIGbBFZQcVVW8F)
- [Introduction to the A* Algorithm](https://www.redblobgames.com/pathfinding/a-star/introduction.html)
- [Implementation of A*](https://www.redblobgames.com/pathfinding/a-star/implementation.html#algorithm)

### Watch it run
Here is a video of me running it on UCLA's g32 server. No memory leaks! And its fast!
- [BruinTour Demo](https://youtu.be/4yM35dsAk-s)


This was my final project for CS 32, which is UCLA's data structures course taught in C++. The code in the enclosed folder "provided" was code that was given by the professors. I implemented the other files in "my_work". The report.txt is a file that were required to submit along with our project. "spec.pdf" has the details of this assignment.


