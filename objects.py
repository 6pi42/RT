class Shape:
	def __init__(self, type, pos, rgb, tex, rad):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.rad = rad

class Triple:
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
"""
class Sphere(Shape):
	def write(self, file_name):
		fichier = open(file_name, "a")
		fichier.write("\tSPHERE\n\t\ttex: "+ str(self.tex) + "\n\t\trad: " + str(self.rad[0]) +
			".0\n\t\trgb: " + str(self.rgb[0]) + str(self.rgb[1]) + str(self.rgb[2])
			+ "\n\t\tpos: " + str(self.pos[0]) + y str(self.pos[1]) +
			str(self.pos[2]))

class Plane(Shape):
	def write(self, file_name):
		fichier = open(file_name, "a")
		fichier.write("\tPLANE\n\t\ttex: "+ str(self.tex) + "\n\t\tnor: " +
		str(self.rad[0]) + str(self.rad[1]) + str(self.rad[2]) +
			".0\n\t\trgb: " + str(self.rgb[0]) + str(self.rgb[1]) + str(self.rgb[2])
			+ "\n\t\tpos: " + str(self.pos[0]) + y str(self.pos[1]) +
			str(self.pos[2]))

class Cylinder(Shape):
	def write(self, file_name):
		fichier = open(file_name, "a")
		fichier.write("\tSPHERE\n\t\ttex: "+ str(self.tex) + "\n\t\trad: " + str(self.rad) +
			".0\n\t\trgb: " + str(self.rgb[0]) + str(self.rgb[1]) + str(self.rgb[2])
			+ "\n\t\tpos: " + str(self.pos[0]) + y str(self.pos[1]) +
			str(self.pos[2]))

class Cone(Shape):
	def write(self, file_name):
		fichier = open(file_name, "a")
		fichier.write("\tSPHERE\n\t\ttex: "+ str(self.tex) + "\n\t\trad: " + str(self.rad) +
			".0\n\t\trgb: " + str(self.rgb[0]) + str(self.rgb[1]) + str(self.rgb[2])
			+ "\n\t\tpos: " + str(self.pos[0]) + y str(self.pos[1]) +
			str(self.pos[2]))
"""
