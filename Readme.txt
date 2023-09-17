The assignment contains 3 C files and 1 header file: Please open the text file as whole screen to see it better.

	a2.h :
		This header file contains a struct where PID, FD, Filename, Inode, and pointer
		to the next node is stored. 

		Header file includes all the documentation for the function description.
	
	-------------------------------------------------------------------------------------------------------------------
	
	link-list.c :
		
		/*Creates a new node for the link list and returns the new node 'new_node'*/
		FDtable* new_FD_node() : 

		This function allocates memory using calloc, creates a node for the linked list.
		It stores 0 for int fields and empty string for the string and NULL for the next pointer.

		/*Inserts the new_node 'new_node' created by the given arguments inserts at 
		the tail of the linked list*/

		FDtable* insert(FDtable *head, int pid, int fd, char filename[MAX_STR_LEN], int inode):

		This function creates the node by using the previous function and updates the node according to
		the function arguments. After that, function inserts the node at the tail of the linked list finding
		the tail by linked list traversal.

		/*Creates a whole linked list according to the information from /proc directory*/
		FDtable *find_pid();

		This function has the pointer to the head, initially NULL. 
		Bu using get_uid, I store my username uid into a variable.
		Then I open the /proc directory to get the information from /proc/[pid]/status and /proc/[pid]/fd
		proc/pid/status is read to get the pids that have the same uid as the current user.
		proc/pid/fd is read to get the information about the fd.
		To get the filename redlink is used.
		To get the inode number I used the stat structure and access the inode number.
		
		https://www.man7.org/linux/man-pages/man3/readdir.3.html
		https://www.man7.org/linux/man-pages/man0/sys_stat.h.0p.html
		https://man7.org/linux/man-pages/man0/pwd.h.0p.html
		https://man7.org/linux/man-pages/man5/proc.5.htmls
		https://www.man7.org/linux/man-pages/man2/readlink.2.html
		
		This function gets the all information and for the node that should be inserted to linked list
		and adds it to the the link list and returns the head of the linked list

		/*Deletes the FDtable linked list*/
		FDtable* delete_list(FDtable *head);

		This function goes through the linked list and for each node that is visited, the memory is
		freed by free function.

	---------------------------------------------------------------------------------------------------------------------

	print_s.c : 
		
		/*Prints the FD table that has more number of FDs than given input*/
		void print_threshold(FDtable *head, int input);
		Traverses through the linked list and prints the PIDs that have more
		number of FDs

		/*Print the FD table as composite i.e. prints PID, FD, Filename, Inode*/
		void print_composite(FDtable *head, int pid, int num);
		Traverses through the linked list and prints all the fields into a table format

		/*Prints the FD table according to the process PID number. 
		It prints PID, FD, Filenodes, Inodes according to given pid*/
		void print_per_process(FDtable *head, int pid, int num);
		Traverses through the linked list and prints PID and FD the fields into a table format

		/*Prints the FD table as system wide i.e. PID, FD, Filename*/
		void print_systemWide(FDtable *head, int pid, int num);
		Traverses through the linked list and prints PID,FD, Filename the fields into a table format

		/*Prints the FD table that includes only PID, Inode*/
		void print_Vnodes(FDtable *head , int pid, int num);
		Traverses through the linked list and prints Inode field into a table format

		/*Saves the FD table in composite formst into a .txt file i.e. text file*/
		void text_file(FDtable *head, int pid, int num);
		Traverses through the linked list and saves all the field information as a table into a text file

		/*Saves the FD table in composite format into a .bin file i.e. binary file*/
		void bin_file(FDtable *head, int pid, int num);
		Traverses through the linked list and saves all the field information as a table into a binary file
	--------------------------------------------------------------------------------------------------------------------

	a2.c : 
		This C file has the main. It goes through the command line arguments and update the flags accordingly.
		For the flags updated, it calles the corresponding print function to give the FD table(s).
	---------------------------------------------------------------------------------------------------------------------

	How to compile : 
		
		By assignment directions, I created a Makefile. 
		If 'make is uptodate' please do make clean first and after that you can use make to compile the program.
		The executable should be ./showFDtables

		./showFDtables :
				It will print the composite table

		./showFDtables --per-process:
				It will print the table with PID and FD (additionally I kept the row index)

		./showFDtables --systemWide:
				It will print the table with PID, FD, Filename (additionally I kept the row index)

		./showFDtables --Vnodes:
				It will print the table with Inode (additionally I kept the row index)

		./showFDtables --composite:
				It will print the composite table 
		
		./showFDtables --threshold=N:
				It will print the composite table (all the time) after the composite table it will
				print the PID that have more number of file descriptors than N. (N should be given in order to have an output)
		
		./showFDtables [currently owned PID]:
				It will print the composite table for that specific PID

		./showFDtables --output_TXT:
				It will save composite to the compositeTable.txt

		./showFDtables --output_binary:
				It will save composite to the compositeTable.bin

		
		./showFDtables --per-process --systemWide: 
				It will print per-process table then systemWide table

		./showFDtables --per-process --systemWide --Vnodes:
			 	It will print per-process table then systemWide table then Inode table

		./showFDtables --per-process --systemWide --Vnodes --composite:
				It will print per-process table then systemWide table then Inode table then composite

		./showFDtables --per-process --systemWide --Vnodes --composite --threshold=N:
				It will print per-process table then systemWide table then Inode table then composite then threshold info

		./showFDtables [currently owned PID] --per-process --systemWide --Vnodes --composite --threshold=N:
				It will print all flag information related to given PID and threshold information related to the all PIDs 
				like in the Professor's video. The table order is same as the order of flags.
		
		Similar cases for the following:

		./showFDtables --per-process [currently owned PID] --systemWide --Vnodes --composite --threshold=N:

		./showFDtables  --per-process --systemWide [currently owned PID] --Vnodes --composite --threshold=N:

		./showFDtables --per-process --systemWide --Vnodes [currently owned PID] --composite --threshold=N:

		./showFDtables --per-process --systemWide --Vnodes --composite [currently owned PID] --threshold=N:

		./showFDtables --per-process --systemWide --Vnodes --composite --threshold=N [currently owned PID]:

	
	For Bonus part :
			If the text file compositeTable.txt is already created, you can use make clean_txt to clean it and then using ./showFDtables --output_TXT should give the text
			file that has the composite table

			If the binary file compositeTable.bin is already created, you can use make clean_bin to clean it and then using ./showFDtables --output_binary should give the binary
			file that has the composite table

			In order to make sense the output and since bonus part was not included in the video please use them separately and do not combine them. (It is working but I feel like it's unnecessary)
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Important Notes:

	The order of printing always going to be --per-process --systemWide --Vnodes --composite --threshold=N, therefore please use it in this order to make sense the output.

	Using threshold only will give composite table and threshold information. Using composite and threshold also gives one composite table and the threshold information.
	If the specific pid is given then composite table is for that specific pid but the threshold information related to all pid's that user owns.

	The report for the bonus part provided as a pdf file because it's easier to read.
	
	Make file has additional clean commands such as clean_txt and clean_bin it should be used if the compositeTable.bin or compositeTable.txt is created. This is something that I created for
	myself to test my functions if they created properly. It can be used if the files are created otherwise terminal would give error because such file does not exists. 

	Please make sure using currently running PID when it passed as positional argument as command line argument.

	Positional argument only works for one PID not multiple PIDs.
	
	I have two versions of Makefile one is with Makefile type that Mac gave me the other one is Plain text which how I created on bv machines. I wasn't sure which one compile and makes the makefile while 
	testing therefore I included both, please use the one that works. 

	I'm sure my output works how Professor showed on his video. Please follow that in general, I tried my best to cover all the cases :). 



		