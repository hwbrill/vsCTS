# read-CTS
A virtual scoreboard by intercepting a Colorado Timing System scoreboard input
## The CTS Scoreboard
Colorado Timing Systems developed the protocol to drive a scoreboard composed of module displays having up to eight seven-segment readouts.
The modules are configured to represent Lane, Event/Heat, Lengths/Record, Team Scores, Place and Time information.
Lane modules are configured, by displaying left to right; Lane Number, Place, Minutes x 10, Minutes x 1, Seconds x 10, Seconds x 1, Seconds x .1 and Seconds x .01
The position of the readout correlates, left to right, to the address of an eight character array[0-7]. So, data in array[0] - Lane Number; array[1] - Place; ... array[7] - Seconds x .01
