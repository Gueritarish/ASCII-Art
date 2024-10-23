add_executable(ascii
               display.c
               display.h
               ppm_data.c
               ppm_data.h
               update.c
               update.h
               utils.h
               utils.c
               main.c)

target_link_libraries(ascii jpeg)
target_link_libraries(ascii png)