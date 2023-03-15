set(lox_lib_src 
    main.cpp  
    debug.cpp
    interpreter.cpp
    lexer.cpp
    tokens.cpp
    types.cpp
    )

add_library(liblox ${lox_lib_src})