# 1. Minimum version and Project setup
cmake_minimum_required(VERSION 3.10)
project(MyInterpreter VERSION 1.0)

# 2. Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. CREATE the target first (The "Chicken")
add_executable(
    zedc 
    src/main.cpp
    src/vm.cpp
    src/natives.cpp
)

# 4. CONFIGURE the target (The "Egg")
# Now that 'zedc' exists, we can tell it where the headers are
target_include_directories(zedc PRIVATE include)