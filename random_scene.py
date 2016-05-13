import sys
import random
import os.path

if len(sys.argv) != 8:
    print "7 args:\n1: nb de sphere\n2: largeur\n3: longueur\n4: sampling\n5 et 6 cube contenant les formes (min max)\n7: nom de la scene\n"
    exit()
try:
    nb_sphere = int(sys.argv[1])
    dim = (int(sys.argv[2]), int(sys.argv[3]))
    sampling = int(sys.argv[4])
    minp = int(sys.argv[5])
    maxp = int(sys.argv[6])
except ValueError:
    print "Arg 1, 2, 3, 4: int"
    exit();

if maxp < minp:
    print "dimension cube non correcte"
    exit()
if (os.path.isfile(sys.argv[7])):
    print "file already exist"
    exit()

fichier = open(sys.argv[7], "a")
fichier.write("SCENE\n\tWINDOW\n\t\twidth: " + str(dim[0]) + ".0\n\t\theight: " + str(dim[1]) + ".0\n\n\tMULTI_SAMPLING\n\t\tpower: " + str(sampling) + "\n\n")
fichier.write("SHAPES\n")
radius = 25
for i in range (0, nb_sphere):
    if (i != 0):
        fichier.write("\n")
    x = str(random.randint(minp, maxp)) + ".0 "
    y = str(random.randint(minp, maxp)) + ".0 "
    z = str(random.randint(minp, maxp)) + ".0"
    r = str(random.randint(0, 255)) + ".0 "
    g = str(random.randint(0, 255)) + ".0 "
    b = str(random.randint(0, 255)) + ".0"
    fichier.write("\tSPHERE\n\t\ttex: 0.0\n\t\trad: " + str(radius) + ".0\n\t\trgb: " + r + g + b + "\n\t\tpos: " + x + y + z)
    if (i != nb_sphere - 1):
        fichier.write("\n")
