set(Q_OJBECT_HEADERS
  application.h
  gl_widget.h
  main_window.h
  CACHE INTERNAL ""
)

set(BASE_HEADERS
  camera.h
  enums.h
  geometry.h
  gl_helpers.h
  glsl_shader_program.h
  logging.h
  log_helpers.h
  scene.h
)

install(FILES
  ${Q_OJBECT_HEADERS}
  ${BASE_HEADERS}
  DESTINATION include/com/visualization
)

add_subdirectory(geometries)
add_subdirectory(scenes)
