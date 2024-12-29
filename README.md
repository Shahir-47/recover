# Recover

**Recover** is a forensic recovery program written in C that extracts JPEG files from a forensic image. It simulates the process used by forensic investigators to recover deleted files from memory cards by identifying JPEG signatures and writing the recovered files to disk.

---

## 📖 Background

When photos are deleted from a memory card, they are not truly erased. Instead, they are marked as "forgotten," leaving their raw data intact until overwritten. This program scans a forensic image of a memory card (`card.raw`), identifies JPEG files by their unique signatures, and reconstructs them into separate `.jpg` files.

JPEG files are identified by their specific signature:
- The first three bytes: `0xff 0xd8 0xff`
- The fourth byte: A value ranging from `0xe0` to `0xef` (the first four bits are `1110`).

The program operates in 512-byte blocks, as memory cards often use a block size of 512 bytes due to FAT file systems. Each JPEG starts on a block-aligned boundary.

---

## 🚀 How It Works

1. **Command-Line Input**:
   - The program requires one command-line argument specifying the forensic image (e.g., `card.raw`) to process.
   - Example usage: `./recover card.raw`

2. **File Reading**:
   - The program reads the input file in 512-byte chunks (blocks).

3. **JPEG Detection**:
   - Each block is analyzed to check if it begins with a JPEG signature (`0xff 0xd8 0xff` and `0xe0`–`0xef`).
   - If a JPEG signature is found, the program creates a new `.jpg` file to store the image data.

4. **File Writing**:
   - All subsequent blocks are written to the current `.jpg` file until another JPEG signature is encountered, signaling the start of a new file.

5. **Output**:
   - Each recovered JPEG is saved in the current directory as `###.jpg` (e.g., `000.jpg`, `001.jpg`, etc.), where `###` is a three-digit number.

---

## 🛠 Implementation

The program is implemented in `C` using the following logic:
- **Validation**:
  - Ensures exactly one command-line argument is provided.
  - Checks if the forensic image can be opened for reading.
- **Memory Management**:
  - Uses a buffer of 512 bytes to process the forensic image efficiently.
  - Ensures no memory leaks by properly closing files before exiting.
- **File Creation**:
  - Dynamically generates filenames using `sprintf` (e.g., `000.jpg`, `001.jpg`).
  - Handles file writing with `fwrite`.

---

## 💻 Usage

### Compile the Code
Use the `gcc` compiler to build the program:
```bash
gcc -o recover recover.c
```

### Run the Program
Provide the forensic image file (`card.raw`) as an argument:
```bash
./recover card.raw
```

The program will recover all JPEG files from `card.raw` and save them in the current directory.

---

## 🧪 Example

**Input**: A forensic image file (`card.raw`) containing JPEG data.  
**Output**: Recovered files saved as `000.jpg`, `001.jpg`, ..., `049.jpg`.

```bash
$ ./recover card.raw
```

Recovered files:
```
000.jpg
001.jpg
002.jpg
...
049.jpg
```

---

## 🔍 Code Overview

### Key Sections of the Code

1. **Command-Line Validation**:
   - Ensures the correct usage of the program with a single argument.

2. **JPEG Detection**:
   - Identifies the start of a JPEG using the signature:
     ```c
     if (pic[0] == 0xff && pic[1] == 0xd8 && pic[2] == 0xff && (pic[3] & 0xf0) == 0xe0)
     ```

3. **File Management**:
   - Writes data to a new `.jpg` file each time a JPEG signature is detected:
     ```c
     sprintf(imagename, "%03i.jpg", jpfound);
     image = fopen(imagename, "w");
     fwrite(pic, 512, 1, image);
     ```

4. **Memory Safety**:
   - Ensures all files are properly closed:
     ```c
     fclose(image);
     fclose(memory);
     ```

---

## 🛡️ Edge Cases

1. **No Command-Line Argument**:
   - The program will display usage instructions if no arguments or more than one argument is provided:
     ```bash
     $ ./recover
     Usage: ./recover image
     ```

2. **Invalid File**:
   - The program will display an error if the input file cannot be opened:
     ```bash
     $ ./recover missing.raw
     forensic image cannot be opened
     ```

3. **End of File**:
   - Ensures all files are closed once the input file has been fully processed.

---

## 🏆 Key Features

- Detects and recovers JPEG files based on signature patterns.
- Handles contiguous and slack space data to reconstruct files.
- Outputs neatly numbered files in the current directory.

---

## 🧹 Cleanup

To remove all recovered JPEG files from the directory:
```bash
rm *.jpg
```

---

## 📜 Licensing

This project was developed as part of a CS50 assignment and adheres to its guidelines. 

---
