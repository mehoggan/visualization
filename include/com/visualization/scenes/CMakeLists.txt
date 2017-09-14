SET(BASE_HEADERS
  indexed_rainbow_rectangle.h
  indexed_rainbow_sphere.h
  indexed_rainbow_textured_rectangle.h
  multi_textured_rectangle.h
  projected_textured_rectangle.h
  rainbow_triangle.h
  simple_triangle.h
)

install(FILES
  ${BASE_HEADERS}
  DESTINATION include/com/visualization/scenes/
)
