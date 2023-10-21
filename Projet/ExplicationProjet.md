# TP-INF1015

Voici le projet de jeu d'échecs créé par Nicolas Mayr et Charles-Olivier Caron.

Nous avons utilisé Qt pour afficher notre projet afin qu'il soit jouable par un utilisateur. Ainsi, nous avons séparé la vue et le modèle dans notre code. La partie de la vue se trouve dans les fichiers TestQt, MainMenu et SelectionScreen. Notre logique se retrouve dans EchiquierLogique. Notre fichier Piece contient une classe Position qui attribue une position à la pièce dans l'EchiquierLogique. De plus, il y a une classe Piece de base qui a pour classes dérivées Rook, Knight, Bishop, Pawn, King et Queen, représentant toutes les pièces possibles. Ces pièces ont également une couleur, soit blanche ou noire. Notre fichier ChessSquare attribue une coordonnée x et y à nos QPushButton.

La manière dont notre jeu fonctionne est la suivante : lorsque nous cliquons sur une pièce dans l'interface utilisateur, un vecteur de cette pièce stocke toutes les positions possibles où elle peut se déplacer, qui sont ensuite mises en surbrillance en vert. Il est possible de recliquer sur la pièce pour changer la pièce que nous voulons déplacer. Ensuite, si nous déplaçons une pièce et qu'elle met en échec le roi adverse, un pop-up indiquera qu'il y a échec. Enfin, si une équipe réussit à capturer le roi adverse, un pop-up indiquera quelle équipe gagne et ramènera le joueur à la fenêtre du menu.
