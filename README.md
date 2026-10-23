# 16-Bit LZW Compression & Decompression Engine (C++)

A lightweight C++ implementation of the Lempel-Ziv-Welch (LZW) data compression and decompression algorithm. This utility uses a **16-bit integer dictionary limit** ($65,535$ max entries) and processes raw binary streams composed of fixed 16-bit unsigned integers (`uint16_t`).

---

## Key Features

- **Full Compression & Decompression:** Complete round-trip LZW encoder and decoder.
- **Interactive CLI Menu:** Input custom text or load `.txt` files directly into memory.
- **16-Bit Overflow Guard:** Aborts compression early if the dictionary exceeds $65,535$ entries, avoiding dictionary index corruption.
- **Special Case Handling:** Handles the classic LZW decoder edge case ($CS = CS + CS[0]$ for unknown codes).
- **Binary I/O:** Serializes compressed output directly as fixed-width 16-bit binary (`compressed.bin`).
- **Detailed Diagnostics:** Produces comprehensive log files (`log.txt` for encoding, `decLog.txt` for decoding) tracking dictionary updates step-by-step.
- **Real-Time Terminal Progress:** Console progress indicator for monitoring execution.

---

## File Structure

- `lempelZivAlgo.cpp`: Interactive CLI entry point.
- `lzw.h`: 16-bit LZW encoder implementation.
- `lzwDec.h`: 16-bit LZW decoder implementation.

---

## Build and Usage

### Compilation
Build with any compiler supporting **C++11 or higher**:

```bash
g++ -std=c++11 lempelZivAlgo.cpp -o lzw_engine
