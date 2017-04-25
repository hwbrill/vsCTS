# read-CTS
A virtual scoreboard by intercepting a [Colorado Time Systems](https://www.coloradotime.com/) scoreboard input
## [The CTS Scoreboard](https://www.google.com/patents/US4263736)
Colorado Time Systems developed the protocol to drive a scoreboard composed of multiple module displays having up to eight seven-segment readouts for each.

The modules are configured to represent either Lane, Event/Heat, Lengths/Record, Team Scores, Place and Time information.

Lane modules are configured, by displaying left to right; Lane Number, Place, Minutes x 10, Minutes x 1, Seconds x 10, Seconds x 1, Seconds x .1 and Seconds x .01

The position of the readouts correlates, left to right, to the address of an eight character array[0-7]. So, data in array[0] - Lane Number; array[1] - Place; ... array[7] - Seconds x .01

Communications to the scoreboard is done serially at 9600 baud continuously having no delimiters, new line or carriage return; the scoreboard doesn't respond back at all to the timing console.

Each module will receive two sets of eight bytes of data with the first set representing the value to be displayed and the second set representing the decimal/colon activation. For the purpose of this project the second set is not needed and is ignored.

The data for the readouts is preceded by one byte representing the address of the module.  The first set of eight bytes, representing the readout values, is determined by the LSB, Least Significant Bit, being FALSE or 0.  The second set of eight bytes, representing the decimal/colon activation, is determined by the LSB being TRUE or 1.
