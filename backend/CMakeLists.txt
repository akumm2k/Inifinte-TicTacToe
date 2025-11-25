# Create a header-only library called "tictactoe"
add_library(tictactoe INTERFACE)

# Tell consumers where to find backend/include
target_include_directories(tictactoe INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
