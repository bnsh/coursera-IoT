#include <EEPROM.h>

int state = 0;
int address = 0;
int value = 0;

void setup() {
  Serial.begin(9600);
  EEPROM.begin();
}

void read_address(int address) {
  int value = EEPROM.read(address);
  char buffer[32]; snprintf(buffer, 32, "R: %d => %d", address, value);
  Serial.println(buffer);
}

void write_address(int address, int value) {
  EEPROM.write(address, value);
  char buffer[32]; snprintf(buffer, 32, "W: %d, %d", address, value);
  Serial.println(buffer);
}

void loop() {
  int ch = Serial.read();
  if (ch != -1) {
    if (state == 0) { // We just read a new line or we just started.
      address = 0;
      value = 0;
      if (ch == 'r') state = 101;
      else if (ch == 'w') state = 201;
      else {
        if (!((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n'))) state = -1;
      }
    }
    else if (101 <= state && state <= 103) {
      const char *read_str = "read";
      if (ch != read_str[state-100]) state = -1;
      else state += 1;
    }
    else if (state == 104) { // Finished the "read" look for a sequence of whitespace.
        if (((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n'))) state = 104; // Swallow whitespace
        else if ('0' <= ch && ch <= '9') { address = (ch - '0'); state = 300; }
    }
    else if (201 <= state && state <= 204) {
      const char *write_str = "write";
      if (ch != write_str[state-200]) state = -1;
      else state += 1;
    }
    else if (state == 205) { // Finished the "write" look for a sequence of whitespace.
        if (((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n'))) state = 205; // Swallow whitespace
        else if ('0' <= ch && ch <= '9') { address = (ch - '0'); state = 400; }
    }

    else if (state == 300) { // read address
      if ('0' <= ch && ch <= '9') address = address * 10 + (ch - '0');
      else if ((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n')) {
        read_address(address);
        state = 0;
      }
      else state = -1;
    }

    else if (state == 400) { // write address
      if ('0' <= ch && ch <= '9') address = address * 10 + (ch - '0');
      else if ((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n')) state = 500;
      else state = -1;      
    }
    else if (state == 500) { // write value
      if ('0' <= ch && ch <= '9') value = value * 10 + (ch - '0');
      else if ((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n')) {
        write_address(address, value);
        state = 0;
      }
      else state = -1;
    }
    else {
      Serial.println("Unknown state! Returning to state 0.");
      state = 0;
    }

    if (state == -1) {
      Serial.println("Unknown character ignored. Returning to state 0.");
      state = 0;
    }
  }
}
