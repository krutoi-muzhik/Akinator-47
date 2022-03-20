Akinator 47 is a simple console game based on a binary tree.

Your aim in the game is to imagine an object, human or whatever else and just answer the Akinator's questions. And his aim is to guess, what have u imagined.
If tour object is contained in the base (base.txt) he'll undoubtedly guess and win. But if you guessed something special and win the game, Akinator will remember it and save your answers in his base.

Base saving and reading is based on full bracket notation. Here is a simple example:
  ?alive (
	  ?meowing (
		  cat
		  ) {
		  ?human (
			  ?black-haired (
				  Maxik
				  ) {
				  Dimasik
				  }
			  ) {
			  dog
		  	}
  		}
	  ) {
	  ?plastic (
		  bottle
		  ) {
		  table
		  }
	  }

If you want to see the whole tree you can use graphviz dump (GVDump function in tree.c) Here is a visualization of a simple base above:
![illustration](https://github.com/krutoi-muzhik/Akinator-47/blob/main/graph/graph.png)

You can find a simple realisation of tree in my another repository [Tree](https://github.com/krutoi-muzhik/Tree)

