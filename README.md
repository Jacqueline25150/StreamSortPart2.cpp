# StreamSort++ Part 2

## Build and Run Instructions
Compile the program with a standard C++11 (or newer) compiler and run the executable:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o streamsort
./streamsort
```
*(On Windows PowerShell or Command Prompt, run `streamsort.exe` after compiling.)*

---

## Test Results
All required test cases were executed against the sample dataset (`Galaxy Run` - 95 min, `City Lights` - 42 min, `Galaxy Run` - 67 min) as well as empty and single-record vectors:

| Test Case | Expected Result | Actual Result | Status |
| :--- | :--- | :--- | :--- |
| **Empty vector (Search & Total)** | `Title not found.` and `Total runtime: 0 minutes` | Printed `Title not found.` and `Total runtime: 0 minutes` | **Passed** |
| **Single record (`City Lights`, 42 min)** | Search finds index `0`; total runtime is `42 minutes` | Returned index `0` (`City Lights (42 minutes)`) and `Total runtime: 42 minutes` | **Passed** |
| **Search for `Galaxy Run`** | Index `0` internally; displays 95-minute record | Displayed `Found at index 0: Galaxy Run (95 minutes)` | **Passed** |
| **Search for `City Lights`** | Index `1` internally; displays 42-minute record | Displayed `Found at index 1: City Lights (42 minutes)` | **Passed** |
| **Search for `city lights`** | `-1` internally; reports title not found | Displayed `Title not found.` | **Passed** |
| **Calculate total runtime (3 records)** | `204 minutes` | Displayed `Total runtime: 204 minutes` | **Passed** |

---

## Recursion Call-Stack Trace (`totalRuntimeRecursive`)
Tracing `totalRuntimeRecursive(catalog, 0)` on the three sample records (`[0]: 95`, `[1]: 42`, `[2]: 67`, where `catalog.size() == 3`):

1. **Call 1:** `totalRuntimeRecursive(catalog, 0)`
   * `index` (`0`) is not `>= 3`.
   * Pauses and calls `totalRuntimeRecursive(catalog, 1)` to add to `95`.
2. **Call 2:** `totalRuntimeRecursive(catalog, 1)`
   * `index` (`1`) is not `>= 3`.
   * Pauses and calls `totalRuntimeRecursive(catalog, 2)` to add to `42`.
3. **Call 3:** `totalRuntimeRecursive(catalog, 2)`
   * `index` (`2`) is not `>= 3`.
   * Pauses and calls `totalRuntimeRecursive(catalog, 3)` to add to `67`.
4. **Call 4 (Base Case):** `totalRuntimeRecursive(catalog, 3)`
   * `index` (`3`) satisfies `index >= catalog.size()`.
   * Base case returns **`0`**.

### Stack Unwinding Return Values
* **Call 4 (`index = 3`)** returns **`0`** to Call 3.
* **Call 3 (`index = 2`)** computes `67 + 0` and returns **`67`** to Call 2.
* **Call 2 (`index = 1`)** computes `42 + 67` and returns **`109`** to Call 1.
* **Call 1 (`index = 0`)** computes `95 + 109` and returns **`204`** to `handleTotalRuntime()`.

### Progress and Bounds-Check Explanation
Each recursive call increments `index` by 1 (`index + 1`), shrinking the remaining unprocessed portion of the vector until `index` reaches `catalog.size()` and triggers the base case. Checking `index >= catalog.size()` *before* accessing `catalog[index]` prevents out-of-bounds memory reads when `index` reaches the end of the vector or when the vector is completely empty (`size() == 0`).
