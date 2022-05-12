	1. Course Policies

	Part (a)

		1,4

	Part (b)

		4

	Part (c)

		2,3,4,5

	Part (d)

		2

	Part (e)

		2

2. Git Quiz

	Part (a)

		3

	Part (b)

		1

	Part (c)

		1) 

			git add hw1q2b.cpp
			git commit -m "add hw1q2b.cpp"

		2)

			git log -p -3

	Part (d)

		This will launch a text editor prompting you for a commit message. 
		After you have entered a message, save the file and close the editor to create the actual commit.

	Part (e)

		cd~
		rm -rf CSCI104
		cd
		git clone https://github.com/ShenChikai/CSCI104.git

3. More Git Questions

	Part (a)

		README.md: Unmodified

	Part (b)

		README.md: Modified, fun_problem.txt: Untracked

	Part (c)

		README.md: Staged, fun_problem.txt: Staged

	Part (d)

		README.md: Modified, fun_problem.txt: Modified

	Part (e)

		README.md: Modified, fun_problem.txt: Staged
	
		fun_problem.txt is now empty, because ' git checkout -- fun_problem.txt' resotre this file, replacing it with the latest copy from the HEAD.

	Part (f)

		first README.md: Staged and second README.md: Modified

		This is because one README is local, and the other README is remote.
