add_executable(tictactoe_cli
    main.cpp
)

target_link_libraries(tictactoe_cli PRIVATE
    tictactoe
)
