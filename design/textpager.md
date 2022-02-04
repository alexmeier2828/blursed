# How to handle line based buffer system in CharBuffer
* I'm trying to set up a system where text is loaded in line by line.  

## concerns
* having a seperate `textpager` module seems like it could become redundant.
	* would it make more sense to just have `CharBuffer` handle the memory management for the 2d array?.  That seems like it could get complicated 

## Reasons why I want a seperate module for the line buffer (better name actually)
* I could keep the curses curser logic separate.
	* CharBuffer will handle all of the logic to figure out where to display the cursor 
