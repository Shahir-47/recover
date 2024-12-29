# Runoff

**Runoff** is a ranked-choice voting program implemented in C. This program simulates an instant-runoff election, where voters rank candidates in order of preference, and votes are redistributed in multiple rounds until one candidate achieves a majority. The program provides a practical demonstration of how ranked-choice voting works, ensuring the winner has the broadest support among voters.

---

## 📖 Background

In a ranked-choice voting system, voters rank candidates in order of preference. The election is conducted in rounds:
1. Each voter’s top choice is counted.
2. If a candidate has a majority of the votes (more than 50%), they are declared the winner.
3. If no candidate has a majority, the candidate with the fewest votes is eliminated, and their votes are redistributed to the next-ranked candidates on their ballots.
4. The process repeats until a candidate has a majority or there is a tie.

### Why Ranked-Choice Voting?

Ranked-choice voting solves issues with the plurality voting system, such as:
- Preventing "vote splitting" among similar candidates.
- Ensuring the winner reflects the preferences of the majority.

---

## 🚀 How It Works

### Key Features:
1. **Ranked Voting**: Voters rank candidates in order of preference.
2. **Instant Runoff**: Eliminates the candidate with the fewest votes in each round and redistributes their votes.
3. **Tie Handling**: Handles ties for the last-place candidate by eliminating all tied candidates unless it results in no remaining candidates.

### Election Process:
- Voters rank candidates (e.g., 1 for the most preferred, 2 for the second, etc.).
- Votes are counted, and rounds are conducted:
  - If a candidate has a majority, they win.
  - If not, the last-place candidate is eliminated, and their votes are redistributed.

---

## 🛠 Installation

This program uses the **CS50 library**. Follow the steps below to install the library and compile the program.

### Install the CS50 Library:

#### Ubuntu:
```bash
$ curl -s https://packagecloud.io/install/repositories/cs50/repo/script.deb.sh | sudo bash
$ sudo apt install libcs50
```

#### Fedora:
```bash
$ curl -s https://packagecloud.io/install/repositories/cs50/repo/script.rpm.sh | sudo bash
$ sudo dnf install libcs50
```

#### From Source (Linux and macOS):
1. Download the latest release from [CS50 Library Releases](https://github.com/cs50/libcs50/releases).
2. Extract the downloaded file:
   ```bash
   tar -xvf libcs50-*.tar.gz
   cd libcs50-*
   sudo make install
   ```

---

## 💻 Usage

### Compile the Program:
To compile `runoff.c` using the CS50 library:
```bash
gcc -o runoff runoff.c -lcs50
```

### Run the Program:
Provide the candidates’ names as command-line arguments:
```bash
./runoff Alice Bob Charlie
```

### Example Input and Output:
1. **Input**:
   ```bash
   ./runoff Alice Bob Charlie
   Number of voters: 5
   Rank 1: Alice
   Rank 2: Bob
   Rank 3: Charlie
   
   Rank 1: Alice
   Rank 2: Charlie
   Rank 3: Bob
   
   Rank 1: Bob
   Rank 2: Charlie
   Rank 3: Alice
   
   Rank 1: Bob
   Rank 2: Alice
   Rank 3: Charlie
   
   Rank 1: Charlie
   Rank 2: Alice
   Rank 3: Bob
   ```

2. **Output**:
   ```bash
   Alice
   ```

---

## 🧪 Example Scenarios

### Scenario 1: Basic Majority
- **Voter Preferences**:
  - Voter 1: Alice > Bob > Charlie
  - Voter 2: Bob > Alice > Charlie
  - Voter 3: Bob > Alice > Charlie
  - Voter 4: Alice > Bob > Charlie
  - Voter 5: Charlie > Alice > Bob
- **Rounds**:
  - Round 1: Alice (2), Bob (2), Charlie (1). Charlie is eliminated.
  - Round 2: Bob receives Charlie's vote and wins with 3 votes.
- **Winner**: Bob.

### Scenario 2: Tie
- **Voter Preferences**:
  - Voter 1: Alice > Bob > Charlie
  - Voter 2: Bob > Charlie > Alice
  - Voter 3: Charlie > Alice > Bob
- **Result**: All candidates have equal votes. Declared a tie.

---

## 🔍 Code Overview

### Key Functions:
1. **`vote`**:
   - Records a voter’s preference.
   - Returns `true` if the vote is valid, `false` otherwise.

2. **`tabulate`**:
   - Counts votes for non-eliminated candidates based on voter preferences.

3. **`print_winner`**:
   - Prints the winner if a candidate has a majority.

4. **`find_min`**:
   - Finds the minimum number of votes for non-eliminated candidates.

5. **`is_tie`**:
   - Determines if all non-eliminated candidates have the same vote count.

6. **`eliminate`**:
   - Eliminates the candidate(s) with the fewest votes.

---

## 🛡️ Edge Cases

1. **Tie for Last Place**:
   - Eliminates all tied candidates unless it leaves no candidates.
   
2. **Invalid Votes**:
   - Rejects votes for non-existent candidates.

3. **All Candidates Tie**:
   - Declares a tie between remaining candidates.

4. **Single Candidate**:
   - Declares the single candidate as the winner without further processing.

---

## 📜 Licensing

This project was developed as part of a CS50 assignment and adheres to its guidelines.
