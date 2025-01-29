#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// Function to disable canonical mode and enable non-blocking key reading
void set_raw_mode(struct termios *old) {
    struct termios new_settings;
    tcgetattr(STDIN_FILENO, old);  // Get current terminal settings
    new_settings = *old;

    new_settings.c_lflag &= ~(ICANON | ECHO);  // Disable line buffering and echo
    new_settings.c_cc[VMIN] = 1;  // Minimum 1 character input
    new_settings.c_cc[VTIME] = 0; // No timeout

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);  // Apply new settings
}

// Function to restore original terminal settings
void restore_mode(struct termios *old) {
    tcsetattr(STDIN_FILENO, TCSANOW, old);
}

int main() {
    struct termios old_settings;
    set_raw_mode(&old_settings);  // Enable raw mode

    printf("Press keys to see their key codes. Press 'q' to exit.\n");

    int ch;
    while ((ch = getchar()) != 'q') {  // Capture keypresses
        if (ch == 27) {  // Escape key or an arrow key sequence
            if (getchar() == 91) {  // '[' character (second byte of escape sequence)
                switch (getchar()) {  // Read third character to identify the key
                    case 'A': printf("Arrow Key Pressed: UP\n"); break;
                    case 'B': printf("Arrow Key Pressed: DOWN\n"); break;
                    case 'C': printf("Arrow Key Pressed: RIGHT\n"); break;
                    case 'D': printf("Arrow Key Pressed: LEFT\n"); break;
                    default: printf("Unknown escape sequence.\n"); break;
                }
            }
        } else {
            printf("Key Pressed: ASCII: %d | Hex: 0x%X | Char: %c\n",
                   ch, ch, (ch >= 32 && ch <= 126) ? ch : ' ');
        }
    }

    restore_mode(&old_settings);  // Restore original settings
    printf("\nExiting...\n");
    return 0;
}
