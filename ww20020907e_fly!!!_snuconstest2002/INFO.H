#ifndef __INFO_H
#define __INFO_H

	extern void update_pos(unsigned char rel_dir);

	extern void maze_backup();
	extern void maze_recover();
	extern void maze_wallup();

	extern void save_maze();
	extern void load_maze();

	extern void save_sampl_value();
	extern void load_sampl_value();

	extern void show_info();

	extern void show_mouse();
	extern void show_path();
		   void _show_path();
	extern void show_maze();
	extern void show_weight();

#endif