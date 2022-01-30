# What do we want this to be
* Small text editor that can be opened from the terminal, without having to clear the entire screen.  Not sure if this is totally possibly yet.

# Next Steps
* [] Display buffer on screen
* [] Take keyboard input to type to buffer
* [] modal commands
	* Probably want an insert and normal mode like vim
	* in insert mode keyboard mode is sent to the buffer 
	* Normal  mode command requirements
		* switch to command buffer (I can probably use the same buffer for this) 
		* w - write buffer to file
		* q	- quit
* [] Display buffer to curses dislay
	* This is going to take some time to set up, but I think it should be possible to set 
