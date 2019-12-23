-Android studio + SDK à installer
-NDK à copier sur le disque C en local
-Variables d'environnement Windows à changer (indiquer le path du NDK sur le disque C)
-Sur android studio dans File -> Project Structure -> Projet : mettre la version android gradle plugin version en 3.5.2
-Sur android studio dans File -> Project Structure -> Projet : mettre la version gradle version en 5.4.1
-Dans SDK location -> Android NDK location : indiquer le chemin vers la version NDK copiée sur le disque
-Dans Tools -> AVD manager -> Create Virtual device créer un émulateur avec les propriétés appropriées (version android 8.0 ou 9.0)

Au lancement il devrait y avoir un texte "is::engine demo" puis un écran noir (c'est normal j'avais supprimé la plupart des scènes pour garder l'essentiel du moteur android)

Pour avoir le projet complet de base : https://www.developpez.net/forums/d2021636/applications/developpement-2d-3d-jeux/api-graphiques/sfml/moteur-jeux-sfml-android/#post11247850

NDK download : https://developer.android.com/ndk/downloads  (prendre version 20)
SDK download : https://developer.android.com/studio