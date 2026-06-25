# Bell
A basic shell
The shell has been renamed to 'Bell' as it is a shell, and my name is Bill.

The lexer is a standard lexer, adapted from the book "Crafting Interpreters"
I then built a Recursive Descent Parser to parse the tokens made in the lexer.
Finally, I used an executor, which I dubbed 'Executioner' because it sounds cooler.

To build, run (clan)g++ main.cpp




I felt the need to put this asterisk at the bottom here. I tried to implement logical operators (||, |, &&) but failed repeatedly.
I got an AI to help me get on the right tracks but it was way beyond my current level with memory management.
With realistically hours before development ends, I cannot possibly implement these features myself, and so I will not.
I wanted to be entirely stransparent about my use of AI and so I am adding this paragraph.
If anyone ever reads my code, the parser already breaks the code into different pipelines.

Tomorrow i will make the shell a bit prettier, aswell as ignoring a SIGINT signal. Then it is done in its current form. Hoorah!
