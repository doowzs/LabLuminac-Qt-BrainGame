# LabLuminac-Qt-BrainGame
Trying to make a simple "remaster" of a brain training game on 3DS with Qt5.

## Progress
[![experimental](http://badges.github.io/stability-badges/dist/experimental.svg)](http://github.com/badges/stability-badges)

10%. Only the basic game implemention is done.
Maybe I will develop further after finishing problem solving homework.

## Original game
[Brain Age: Concentration Training](https://en.wikipedia.org/wiki/Brain_Age:_Concentration_Training), a game by Ryuta Kawashima from Tohoku University, first released on 3DS in 2012. One of my favorite training games.

## What to do
- Create a simple GUI app for "devilish calculation" in the game.
- Make it fun with different modes just like the original game.
- Make difficulty changable for different levels of players.
- Trying to learn Internet Socket and build a server app to save player data.

## Rule of Game
The default level of game is 2, the default length is 1 minute.
- An easy calculation problem is shown, i.e. 1+1=?.
- The problem is hidden, and the second one is shown.
- The second one is hidden, and the third one is shown, the player has to answer the first question.
- The third question is hidden, the fourth is shown, the player has to answer the second question.
- The game continues in this manner until time out.