# PointerPolling
Quick tool to look at mouse/stylus tracking info during drawing (also demonstrating subclassing of QGraphicsView to do this sort of stuff):
  * During drawing, times and positions of mouse actions are recorded in the table to the right.
  * Navigating the table moves crosshairs on the graphics view to show position.
  * Notes can be entered (say, noting where the vertices are).
  * Table data can be saved to CSV for further analysis.

Notes: 

1. From my initial pokes at this, the most reliable indicator of vertices seems to be slowdown of the pointer---try holding down the "down" key when scrolling through the events, and you'll see more events near the vertices.
2. You'll see multiple mouse events with identical timestamps during quick motion; it might be worth looking into whether it's possible to get more accurate timing, but I'm not sure it's necessary for this project, even if it is possible.
