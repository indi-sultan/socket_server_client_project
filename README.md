# 🔌 Socket Programming Project (C++)

### 📘 Overview
This repository is a **modular C++ socket programming project** built with:

- **CMake** (with CMakePresets)
- **Boost.Asio** for networking
- **GoogleTest** for unit testing
- **vcpkg** for dependency management

The project is structured for long-term scalability with clean separation of:

- **Client**
- **Server**
- **Common (shared utilities)**

---

### ⚙️ Building the Project

Use the provided CMake preset:

```bash
cmake --preset vcpkg
cmake --build build
```

The executable will be creted under
```
build/bin/
```
---

### ▶ Running the Executables

After building successfully:
```
cd build/bin
./server      # start the server
./client      # start the client
```
(Currently these are simple test executables — i will add socket logic later.)

---

### 🛠️ Upcoming Features (Roadmap)

* Implement TCP/UDP server-client logic using Boost.Asio.
* Add checksum verification.
* Implement file transfer and authentication.
* Integrate GoogleTest for automated testing.

---

### 👨‍💻 Author
**Shivam Kumar**  
C/C++ | Systems Programming | Linux & Embedded Enthusiast


