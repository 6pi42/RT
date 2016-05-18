class Sphere():
	def __init__(self, type, pos, rgb, tex, rad):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.rad = rad
		try:
			for i in range (0, 2):
				float(self.pos[i])
				float(self.rgb[i])
			float(self.rad)
		except ValueError:
			print "Error in the ellipsoid specification"
			exit()

	def write(self, file_name):
		file_name.write("\tSPHERE\n\t\ttex: "+ str(float(self.tex)) + "\n\t\trad: " + str(float(self.rad[0]))+
		"\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) + str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) + str(float(self.pos[1])) +
		str(float(self.pos[2])) + "\n")

class Ellipsoid():
	def __init__(self, type, pos, rgb, tex, rad):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.rad = rad
		try:
			for i in range (0, 2):
				float(self.pos[i])
				float(self.rgb[i])
				float(self.rad[i])
		except ValueError:
			print "Error in the ellipsoid specification"
			exit()
	def write(self, file_name):
		file_name.write("\tELLIPSOID\n\t\ttex: "+ str(float(self.tex)) + "\n\t\trad: "
		+ str(float(self.rad[0])) + str(float(self.rad[1])) + str(float(self.rad[2])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) + str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) + str(float(self.pos[1])) +
		str(float(self.pos[2])) + "\n")

class Plane():
	def __init__(self, type, pos, rgb, tex, norm):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.norm = norm
		try:
			for i in range (0, 2):
				float(self.pos[i])
				float(self.rgb[i])
				float(self.norm[i])
		except ValueError:
			print "Error in the Plane specification"
			exit()
	def write(self, fichier):
		fichier.write("\tPLANE\n\t\ttex: "+ str(float(self.tex)) + "\n\t\tnor: " +
		str(float(self.norm[0])) + str(float(self.norm[1])) + str(float(self.norm[2])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) + str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) + str(float(self.pos[1])) +
		str(float(self.pos[2])) + "\n")

class Cylinder():
	def __init__(self, type, pos, rgb, tex, axis, rad):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.axis = axis
		self.rad = rad
		try:
			for i in range (0, 2):
				float(self.pos[i])
				float(self.rgb[i])
				float(self.axis[i])
			float(self.rad)
		except ValueError:
			print "Error in the Plane specification"
			exit()
	def write(self, fichier):
		fichier.write("\tCYLINDER\n\t\ttex: "+ str(float(self.tex)) + "\n\t\trad: " + str(float(self.rad[0])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) +
		str(float(self.rgb[2])) + "\n\t\tpos: " + str(float(self.pos[0])) +
		str(float(self.pos[1])) + str(float(self.pos[2])) + "\n\t\taxis: " +
		str(float(self.axis[0])) + str(float(self.axis[1])) +
		str(float(self.axis[2])) + "\n")


class Cone():
	def __init__(self, type, pos, rgb, tex, axis, k):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.axis = axis
		self.k = k
		try:
			for i in range (0, 2):
				float(self.pos[i])
				float(self.rgb[i])
				float(self.axis[i])
			float(self.k)
		except ValueError:
			print "Error in the Plane specification"
			exit()
	def write(self, fichier):
		fichier.write("\tCONE\n\t\ttex: "+ str(float(self.tex)) + "\n\t\tagl: " + str(float(self.rad[0])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) + str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) + str(float(self.pos[1])) +
		str(float(self.pos[2])) + "\n\t\taxis: " + str(float(self.axis[0])) + str(float(self.axis[1])) +
		str(float(self.axis[2])) + "\n")

class Cube():
	def __init__(self, pt1, pt2, rgb):
		self.pt1 = pt1
		self.pt2 = pt2
		self.rgb = rgb
		try:
			for i in range (0,2):
				float(self.pt1[i])
				float(self.pt2[i])
				float(self.rgb[i])
		except ValueError:
			print "error in the cube specification"
			exit()
		def write(self, fichier):
			fichier.write("\tCUBE\n\t\trgb: " + str(float(self.rgb[0])) + str(float(self.rgb[1])) + str(float(self.rgb[2]))
			+ "\n\t\tpt1: " + str(float(self.pt1[0])) + str(float(self.pt1[1])) +
			str(float(self.pt1[2])) + "\n\t\tpt2: " + str(float(self.pt2[0])) + str(float(self.pt2[1])) +
			str(float(self.pt2[2])) + "\n")
