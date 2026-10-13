# 16-Bit LZW Data Compression (C++)

A lightweight C++ implementation of the **Lempel–Ziv–Welch (LZW)** lossy-less data compression algorithm optimized for a **16-bit integer dictionary** ($65,535$ max entries). 

Supports compressing both user-entered string buffers and external `.txt` files, generating a binary file containing $16$-bit output tokens alongside a diagnostic execution log.

---

## Features

* **16-Bit Fixed Dictionary:** Pre-populates the standard ASCII set ($0–255$) and dynamically expands up to $65,535$ dictionary entries.
* **Dual Input Modes:** Interactively input text via CLI or read full contents from `.txt` files into memory.
* **Binary File Output:** Writes compressed tokens directly as binary data (`uint16_t` / $2$ bytes per token) to `compressed.bin`.
* **Execution Logging:** Generates `log.txt` showing step-by-step dictionary lookups and entry assignments.
* **CLI Progress Tracking:** Real-time feedback bar during execution.

---

## How It Works

1. **Initialization:** The dictionary initializes with the $256$ standard single-byte ASCII characters.
2. **Matching:** The program reads input character by character, searching for matching substrings within the dictionary.
3. **Dictionary Expansion:** Unseen sequences are assigned incrementing integer codes starting at $256$.
4. **16-Bit Cap:** Once entry count reaches $65,535$ (`UINT16_MAX`), dictionary growth freezes, and subsequent input is encoded using the existing static entries.

---

## File Structure

```text
├── include/
│   └── lzw.h               # LZW compression core logic & dictionary handler
├── src/
│   └── lempelZivAlgo.cpp   # Interactive CLI menu and file I/O entry point
└── README.md
```

---

## Building & Running

### Requirements
* C++11 compatible compiler (`g++`, `clang++`, or MSVC)

### Compilation

Using **g++**:
```bash
g++ -std=c++11 -Iinclude src/lempelZivAlgo.cpp -o lzw_demo
```

### Execution

```bash
./lzw_demo
```

---

## Example Usage

1. Launch `./lzw_demo`.
2. Select **Option 1** to type custom text or **Option 2** to specify a file path (e.g., `sample.txt`).
3. Select **Option 4** (`Run Algo`).
4. Output files generated in the working directory:
   * `compressed.bin`: Raw binary file containing $16$-bit tokens (`uint16_t`).
   * `log.txt`: Detailed lookup trace for verification and debugging.

---

## Limitations

* **Decompression:** Currently implements the **compression** pipeline.
* **Dictionary Reset:** When the $16$-bit limit ($65,535$ entries) is reached, dictionary expansion stops without flushing or clearing old entries.
