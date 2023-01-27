Voici le fichier dans lequel nous allons répertorier les différentes manipulations réalisées sur la jetson nano :
-  Il a fallu connecter la carte à internet dans un premier temps, nous avons utilisé un cable éthernet (car pas de wifi) puis récemment par wifi 
- ensuite, nous avons suivi le tuto proposé par Nvidia,
- il a donc fallu installer une image docker fonctionnelle (nous avons eu beaucoup de difficulté à en trouver une),
- une fois l'image trouvée nous avons fait fonctionner Jupyter et réussi à obtenir des images de la caméra,
- Cependant, la librairie Torch n'était pas bien installée,
- on a donc abandonné docker pour passer directement par un environnement virtuel de python (venv)
- on a installé à la main les librairies dont on avait besoin (Tensorflow,...)
- enfin, on a formaté la carte SD car elle n'était pas reconnue par la Nvidia afin que nos données soit stockés dessus 