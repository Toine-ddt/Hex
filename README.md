# Hex
Hex Game - S6 Project

Pour faire fonctionner ce projet, il faut installer la librairie gsl : https://www.gnu.org/software/gsl/

Ce projet a été fait dans le cadre du semestre 6 de la première année d'informatique.

Pour compiler notre code, il faut lancer la commande :

make install

make server

./install/server -m [M] -t [T] ./install/player1.so ./install/player2.so

avec [M] et [T] des paramètres optionnels qui indiquent respectivement la taille et la forme du plateau. Il faut entrer une forme parmi c et h, car nous n'avons pas réussi à faire de graphes triangulaires. ./install/player1.so et ./install/player2.so sont deux paramètres obligatoires et sont des exemples. Nous avons aussi fait une autre stratégie qui s'appelle avec  ./install/Djiplayer.so ou  ./install/Djiplayer2.so.

Pour nettoyer, il faut lancer la commande : make clean
