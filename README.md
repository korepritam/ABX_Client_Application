
### Dependencies

- **C++17** support in your compiler (e.g., GCC, Clang, MSVC)
- **Eclipse** IDE is used. The exe is in ***${Project}/Debug/.***
- **Manual Compilation Tools**: `g++` C++ compiler or `Eclipse IDE`

### Setup and Building the Project

Follow these steps to manually compile and run the project:

#### 1. Clone the Repository

Clone this repository to your local machine using `git`:

```bash
git clone https://github.com/korepritam/ABX_Client_Application.git
cd ABX_Client_Application/Deubg
make clean
make -k all
./ABX_Client_Application 1>out 2>err&
```

#### Key Points:
1. **Configuration File**: 
   - Describes the **ABX Client Application configuration file** and the various fields that can be customized.
   - A sample configuration file (`Debug/ABX_Client_Config.cfg`) is included.
    Sample Configuration File details:
```bash
      SERVER_IP=127.0.0.1  //server IP where ABX server running
      SERVER_PORT=3000  //server port where ABX server running
      JSON_FILENAME=packet.json //JSON output of packets
```

2. **Output File**:
   - Explains what the program will output, specifically the **JSON output file** (`packet.json`).
   - Exe normal output present in `out` and `err` file.
