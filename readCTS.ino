// Constants

// Forward declarations
char dis[25][10];

// Global variables
char c = 0;

byte data = 0;
byte add = 0;
byte sub = 0;
byte seg = 0;

bool uP = false;
bool lN = false;

void setup() {
	// VIA RS-232 Port 1 To Read CTS
	Serial1.begin(9600, SERIAL_DATA_BITS_8 | SERIAL_STOP_BITS_1 | SERIAL_PARITY_EVEN);
	// VIA USB
	Serial.begin();
}

void loop() {

}

// Read scoreboard input from CTS console on Serial 1
// LN PL MM mm SS ss tt hh
// 00 01 02 03 04 05 06 07

void serialEvent1() {

	c = Serial1.read();
	// Determine if Module Address
	if (c > 127) {
		// Determine if Lane is Enabled and Running
		if (c > 190) {
			uP = true;
		}
		else {
			uP = false;
		}
		// Determine if Lane Address, only thru Lane 10
		if (c > 169 && c < 190) {
			lN = true;
		}
		else {
			lN = false;
		}
		// Determine type Data = 0(even) or Format = 1(odd)
		sub = c & 0x01;
		// Address index
		add = ((c >> 1) & 0x1f) ^ 0x1f;
	}

	// Extract Data for each Segment Data, not Format
	if (c < 128 && sub == 0) {
		// Determine which segment the data's for
		seg = (c & 0xf0) >> 4;
		// Extract the data for the segment
		data = (((c << 4) & 0xf0)) >> 4;
		// Determine if Data is to be Displayed, this is done before the XOR
		if (add >= 0 && data == 0x00) {
			data = 0x20; // Space
		}
		else {
			data = data ^ 0x0f + 48; // Numeric Char after XOR
		}
		dis[add][seg] = data;
	}

	// Blank out Lane info After Start or Split Display
	if (uP) {
		// Show lane number but blank out everything else
		for (int i = 1; i < 10; i++) {
			dis[add][i] = 0x20; // Space
		}
	}

	if (lN) {
		// Show Splits or Finish Time and Place
		dis[add][8] = 0x3A; // Colon
		dis[add][9] = 0x2E; // Period
		// Determine if Lane is OFF from Console
		if (dis[add][0] == 0x20) {
			// Totally Blank Lane if OFF from Console
			for (int i = 1; i < 10; i++) {
				dis[add][i] = 0x20; // Space
			}
		}
	}
}
