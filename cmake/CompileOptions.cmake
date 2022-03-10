function(set_compile_options target_name)
    target_compile_options(${target_name} PRIVATE -Wall -Wextra -Werror -pedantic)

  set_target_properties(
    ${target_name}
    PROPERTIES
      CXX_STANDARD 20
      CXX_STANDARD_REQUIRED ON
      CXX_EXTENSIONS OFF
  )

endfunction()