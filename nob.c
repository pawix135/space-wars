#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_FOLDER  "build/"
#define SRC_FOLDER    "src/"

int main(int argc, char **argv){

  NOB_GO_REBUILD_URSELF(argc, argv);
  
  Nob_Cmd cmd = {0};

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;
  nob_cc(&cmd);
  nob_cc_flags(&cmd);

  nob_cmd_append(&cmd, "-g");
  nob_cmd_append(&cmd, "-O0");
  nob_cmd_append(&cmd, "-Iinclude");
  nob_cmd_append(&cmd, "-Llib");

  nob_cc_output(&cmd, BUILD_FOLDER "space-war.exe");

  nob_cc_inputs(&cmd, SRC_FOLDER "main.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "sprite_loader.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "sound_loader.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "sounds.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "assets.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "projectile.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "game_window.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "player.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "enemy.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "textures.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "background_stars.c");
  nob_cc_inputs(&cmd, SRC_FOLDER "game.c");

  nob_cmd_append(&cmd, "-lraylib");
  nob_cmd_append(&cmd, "-lopengl32");
  nob_cmd_append(&cmd, "-lgdi32");
  nob_cmd_append(&cmd, "-lwinmm");

  if (!nob_cmd_run(&cmd)) return 1;

  return 0;
}