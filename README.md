# Console Text Editor

This program is a console-based text editor implemented in C. It allows users to create, modify, and save text files with a range of functionalities. The program includes support for various keyboard shortcuts and extended keys for navigation, editing, and file management.

---

## Features

### Basic Functionalities
- **File Management:**
  - Automatically checks for the existence of a file (`doc.txt`). If not found, a new file is created.
  - Reads the content of an existing file and displays it for editing.
- **Text Editing:**
  - Insert new characters.
  - Delete characters using `Backspace` or the `Delete` key.
  - Save changes to the file using `Ctrl+S`.

### Navigation
- **Cursor Movement:**
  - `Right Arrow`: Move the cursor one character to the right.
  - `Left Arrow`: Move the cursor one character to the left.
  - `Up Arrow`: Move the cursor up one line.
  - `Down Arrow`: Move the cursor down one line.
  - `Home`: Move the cursor to the start of the text.
  - `End`: Move the cursor to the end of the text.

### Display
- Displays the text with proper formatting in a multi-line layout.
- Handles line wrapping and spaces for better readability.

### Error Handling
- Prevents cursor movement beyond text boundaries.
- Displays messages for invalid actions (e.g., deleting when there are no characters).
- Warns when the maximum allowed number of characters is reached.

---

## How to Use

1. **Run the Program:**
   Compile and run the program in a console environment.

2. **Enter Text:**
   - Type your text directly into the console.
   - Use `Backspace` to delete characters.
   - Use the navigation keys for cursor movement.

3. **Save Changes:**
   Press `Ctrl+S` to save the current text to `doc.txt`.

4. **Exit the Program:**
   Press `Esc` to exit the program. The final message will be displayed before closing.

---

## Keyboard Shortcuts
| Key          | Action                                   |
|--------------|-----------------------------------------|
| `Right Arrow`| Move cursor right                       |
| `Left Arrow` | Move cursor left                        |
| `Up Arrow`   | Move cursor up                          |
| `Down Arrow` | Move cursor down                        |
| `Home`       | Move cursor to the start of the text    |
| `End`        | Move cursor to the end of the text      |
| `Delete`     | Delete the character after the cursor   |
| `Backspace`  | Delete the character before the cursor  |
| `Ctrl+S`     | Save the current text to `doc.txt`      |
| `Esc`        | Exit the program                        |

---

## How It Works

1. **Initialization:**
   - The program checks if `doc.txt` exists. If not, it creates a new file.
   - Allocates memory for storing the text input.

2. **User Input:**
   - Handles regular key presses for inserting characters.
   - Detects special keys for navigation and editing using `getch()` and extended key codes.

3. **Rendering Text:**
   - Formats and displays the text within a specified line width.
   - Highlights the current cursor position.

4. **Saving and Exiting:**
   - Saves the content to `doc.txt` upon `Ctrl+S`.
   - Exits gracefully upon pressing `Esc`.

---

## Function Descriptions

### `calculateExtraSpaces`
Calculates the extra spaces introduced by `Enter` keys in the text. Ensures proper line alignment and formatting in the console display.

### `print_finaltxt`
Displays the text with proper formatting, highlighting the lines and background colors as needed.

### `handleEXETENDEDkeys`
Handles navigation and editing functionality for extended keys (e.g., arrow keys, `Home`, `End`, `Delete`).

---

## Prerequisites
- **Operating System:** Windows (uses `windows.h` for console management).
- **Compiler:** A C compiler like GCC (e.g., MinGW on Windows).

---

## Compilation and Execution
1. Compile the program using:
   ```bash
   gcc -o console_editor console_editor.c
   ```
2. Run the executable:
   ```bash
   ./console_editor
   ```

---

## Future Enhancements
- Support for additional file formats.
- Enhanced navigation options (e.g., word-based movements).
- Improved UI with customizable colors and fonts.
- Compatibility with non-Windows platforms.

---

## Author
This program was developed as a demonstration of C programming skills, showcasing advanced console operations, file handling, and memory management.

Feel free to contribute or share feedback!

