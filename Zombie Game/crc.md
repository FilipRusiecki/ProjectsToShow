# jp21-mk-fr
jp21-jp21-mk-fr created by GitHub Classroom



CRC cards

------------------------------------------------------
**Class Game**
-----
Responsibilies:
-----
*Render and update based on current gameState

*Stores game, menu, and loading screen objects

Collaborators
----

-Menu

-GameOver

------------------------------------------------------






------------------------------------------------------
**Class Player**
-----
Responsibilies:
----

*Store Player Position

*Source of bullets

*Be controlled by real-life player


Collaborators
------
-GamePlay

-Bullet

-CollisionManager

------------------------------------------------------






------------------------------------------------------
**Class Zombie**
-----
Responsibilies:
-----
*Store Zombie Position

*Follow player around map

*attack player when in range


Collaborators
-----
-GamePlay

-CollisionManager

------------------------------------------------------






------------------------------------------------------
**Class CollisionManager**
-----
Responsibilies:
-----
*Get values of colliders(sf::rectangles)

*Compare values to check for overlap

*Call functions on objects when collision happens (e.g. bullet hitting)


Collaborators
-----

-Walls

-Player

-Zombie

-Bullet

------------------------------------------------------






------------------------------------------------------
**Class GamePlay**
-----
Responsibilies:
----
*stores values of all the objects that will be used in game

Collaborators
----
-Menu

-GameOver


------------------------------------------------------






------------------------------------------------------
**Class Menu**
-----
Responsibilies:
----
*Display different menu options for the player to use
such as Starting new game, Loading game, Instrucions
and Settings.

*Play background sounds.

Collaborators
----
-StartNewGame

-LoadGame

-Instructions

-Settings

------------------------------------------------------






------------------------------------------------------
**Class StartNewGame**
-----
Responsibilies:
----
*Resets all the saved values and resets the game 
as if its played for the first time.

Collaborators
----
-Menu

-GamePlay
------------------------------------------------------






------------------------------------------------------
**Class LoadGame**
-----
Responsibilies:
----
*Loads the game values from a saved file that player
saved when last playing the game.

Collaborators
----
-Menu

-GamePlay

------------------------------------------------------






------------------------------------------------------
**Class Instructions**
-----
Responsibilies:
----
*Displays all the basic instructions of how to play the
game.

*Display all the controls that are available for the
player.

Collaborators
----
-Menu

------------------------------------------------------






------------------------------------------------------
**Class Settings**
-----
Responsibilies:
----
*Allows the player to turn sound on and off

Collaborators
----
-Menu

-GamePlay

------------------------------------------------------






------------------------------------------------------
**Class GameOver**
-----
Responsibilies:
----
*Display a game over screen when the player dies.

*Allow player to restart the game.

Collaborators
----
-GamePlay

------------------------------------------------------
