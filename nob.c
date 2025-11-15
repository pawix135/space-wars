#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#if defined(_WIN32)
    #define OUT "space-wars.exe"
#else
  #define OUT "space-wars"
#endif

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"

int main(int argc, char **argv) {

  NOB_GO_REBUILD_URSELF(argc, argv);

  Nob_Cmd cmd = {0};

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER))
    return 1;

#if !defined(_WIN32)
  nob_cmd_append(&cmd, "clang"); 
  nob_cmd_append(&cmd, "-Wall", "-Wextra", "-g", "-O3");
  nob_cmd_append(&cmd, "-Iinclude");
  nob_cmd_append(&cmd, "-L./lib"); 
  nob_cmd_append(&cmd, "-lraylib", "-framework", "CoreVideo", "-framework", "IOKit", "-framework", "Cocoa", "-framework", "GLUT", "-framework", "OpenGL");
#endif

#if defined(_WIN32)
  nob_cc(&cmd);
  nob_cc_flags(&cmd);
  nob_cmd_append(&cmd, "game_icon.res");
#endif

  nob_cc_output(&cmd, BUILD_FOLDER OUT);

  nob_cc_inputs(&cmd, SRC_FOLDER "sprite_loader.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "sound_loader.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "extern_resources.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "projectile.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "game_window.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "game_config.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "menu.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "player.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "enemy.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "enemy_manager.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "wave_manager.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "assets.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "sounds.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "textures.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "button.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "background_stars.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "game.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "main.c");
  
#if defined(_WIN32)
  nob_cmd_append(&cmd, "-Iinclude");
  nob_cmd_append(&cmd, "-Llib");
  // nob_cmd_append(&cmd, "-g");
  nob_cmd_append(&cmd, "-O3");
  // nob_cmd_append(&cmd, "-O1");
  // nob_cmd_append(&cmd, "-Wl,--subsystem,windows");
  nob_cmd_append(&cmd, "-Llib");
  nob_cmd_append(&cmd, "-lraylib");
  nob_cmd_append(&cmd, "-lopengl32");
  nob_cmd_append(&cmd, "-lgdi32");
  nob_cmd_append(&cmd, "-lwinmm");
  nob_cmd_append(&cmd, "-lm");
#endif

  if (!nob_cmd_run(&cmd))
    return 1;

  return 0;

}