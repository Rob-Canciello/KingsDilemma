# KingsDilemma

Welcome to The King's Dilemma!

Official Design Doc here: https://docs.google.com/document/d/1H-vCum4QQeB4nF1hU_OXaCxobPnai5K3EtTzpQqiWWo/edit#

The King’s Dilemma!
2 players, 6+ Blinks, 5-20 Min.

The King’s Dilemma is a 2 player game where players take turns flicking their Blinks at their opponent’s “King” Blink to try to knock them off the table / out of the arena. 

<b> Setup: </b>

1. First choose a table or demarcate the boundaries of an “arena” on a surface. This is your time to assemble your battlefield! Use whatever you have in your house (books, cups, pencils, etc.) to construct your environment and create a unique playfield of barriers and obstacles.

2. Next, assemble an even number of Blinks and divide them in half between players.

3. Blinks begin the game as dim-blue. Each player clusters them together and then single clicks any Blink to have them become a King. Then, they double click that King to create their army. Based on how you assemble your cluster, different roles will be assigned, each with their own unique pattern and team color. 

4. There are two teams in King’s Dilemma - White and Black (for now). This is represented by a single unchanging face. Double click any Blink after setup to assign your team color.

5. Once teams have been assigned, players position them however they like on their side of the table. Choose who goes first and then gameplay begins.  


<b> Gameplay: </b>
Each turn, a player can take one of two actions: flick a Blink or use one of its abilities.

If a Blink connects to another Blink, unless it’s related to a role ability, separate the Blinks equally from their contact point, about  1 inch apart

If a Blink falls off the board or out of the arena bounds as the result of a flick, whether intentional or by accident, that Blink is removed from the game (unless it’s the King). Players continue flicking and repositioning their Blinks until the win condition is met. 

<b> Win Condition: </b>

The first player to lower their opponent King’s health to 0 by knocking it off the board or out of the arena wins! But be careful, if your King falls off the board at the same time as the other King, you’ll both lose!

<b> Current Roles: </b>
King - Your leader. Can be flicked at an opponent. Has 3 health. When knocked off the table, it is clicked to remove one health.
Visuals: 3 faces of a gold (crown), on slow pulsing purple. 

Knight - Can be flicked at a friendly Blink and, if successfully connected, that piece is stacked on top of the Knight to make it more stable. That piece (or the Knight) can be flicked on your following turn. A Knight cannot stack with a unit already protected by a Knight.
Visuals: Marching Red

Wizard - Can be flicked at an opponent or repositioned to anywhere on the board - but your turn ends after you reposition them. 
Visuals: Marching Blue

Jester: Can be flicked at enemy Blink and, if successfully connected, remains there to be flicked on the following turn, taking the enemy Blink with it! Removed from the game after one attempted flick. The connected enemy Blink cannot be flicked by your opponent. However, your opponent can attempt to forcibly separate the Jester by flicking one of their other pieces into them. 
Visuals: Rainbow pattern.

Queen: After being flicked, the player can hold it down around its edges during their enemy’s next turn - making it immovable.
Visuals: Shimmering white on royal purple background.

Alchemist
NOTE: MECHANIC NOT CURRENTLY IMPLEMENTED YET. USE AS REGULAR PAWN FOR NOW.

/*Upon connection with another Blink, passes a blinking “Bomb” face to the connected Blink.
Every time the affected Blink with the “Bomb” face connects to another Blink (friendly or enemy) they pass it to the other Blink and the Bomb automatically “ticks” down one. After X ticks, the unit that receives the bomb on the last tick is removed from the game. This does not work on the King.
The Bomber Blink has 1 bomb per game. 
If a Blink already has a bomb and is passed another bomb it instantly dies (explodes).
Visuals: Green with “ping-ponging” red face*/
