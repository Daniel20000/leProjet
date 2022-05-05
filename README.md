# Cadre du Projet
Projet de semestre BA6 de l'EPFL en Systèmes Embarqués et Robotique.

# Objectif:
Programmer un robot e-puck2 afin d'utiliser les deux moteurs, les leds, l'IMU et les capteurs de distances infrarouge.

# Application:
Le robot est capable de  contourner 6 types d'obstacles parfaitement voir plus:
- mur droit devant
- angle à droite
- angle à gauche
- mur orienté à 45 degré à droit
- mur orienté à 45 degré à gauche
- rentrer et sortir d'une impasse

Il affiche les leds 1,3,5,7 du côté où il détecte l'obstacle, puis le contourne au plus proche.

Si il détecte une pente trop forte, il s'arrête par mesure de sécurité afin de ne pas glisser, et il fait clignoter ses leds rgb.

Ce type de système pourrait être utiliser pour le déplacement d'un robot tondeuse par exemple.
