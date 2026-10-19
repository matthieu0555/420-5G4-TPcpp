# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`

# Question 1 

Une fonctionnalit dans le code que on n'a ps beaucoup vue dans le cours serait les fonctions lambda, par exemple sort. Un lambda est tout simplement une fonction anonyme donc sans sans nom. Elle peut etre déclaré n'importe ou. Un bon exemple dans mon code serait lorsque j'utiliser la fonction sort(), pour trier les livres soit par titre ou par auteur.

sort(livres.begin(), livres.end(), [](Book *a, Book *b)
{
    return a->getTitle() < b->getTitle();
});

Dans l'exemple de code en haut:

sort() parcourt le vecteur pour trier les livres.

[] indique le début de la lambda (aucune variable nécessaire pour le 3e argument).

(Book *a, Book *b) représente les deux livres à comparer.

return a->getTitle() < b->getTitle() retourne true si le titre du livre A doit être placer avant celui du livre b. Elle permet alors un tri alphabtique

Exemple de sortie de mon programme :

Choix 1: Titre
Choix 2: Auteur
1

=== TOUS LES LIVRES TRIÉ PAR TITRE ===

Livre 1 :
Andromaque
-------------------------

Livre 2 :
Atala
-------------------------

Livre 3 :
Bel-Ami
-------------------------

Livre 4 :
Britannicus
-------------------------

Livre 5 :
Candide
-------------------------

(code continue, mais de facon trié)


# Question 2

En ce moment les données persistent grace a l'utilisation de txt et des vecteurs. Il est vrai que sa marche et que sa fait la job, mais pour améliorer la technologie j'utiliserait une vrai base de donnée tel que MongoDB ou MySQL. Il est vachement meilleur d'utiliser une base de donnée externe, car déja elle permettra de gérer plus efficacement les données, grace au divers fonctionnalités + béné fices des bases de données. Par exemple l'indexation, meilleur performances, type de données, relations entre les tables, ects. Pour l'intégrer avec le c++, j'aurai utiliser des librarie public qui permettront de communiquer avec sois mongoDB ou mySql. De plus l'utilisation d'une base de donnée, déja pour tester localement permettrait de tester plus efficacement la gestion de données, les bug potentiel, surotut lorsque dans le futur la biblibliotheque utilisera une grande quantité de livre. 