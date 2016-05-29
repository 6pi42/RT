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
		"\n\t\trgb: " + str(float(self.rgb[0])) + " " + str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) +  " " +str(float(self.pos[1])) +  " " +
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
		+ str(float(self.rad[0])) +  " " +str(float(self.rad[1])) +  " " +str(float(self.rad[2])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) +  " " +str(float(self.pos[1])) +
		 " " +str(float(self.pos[2])) + "\n")

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
		str(float(self.norm[0])) +  " " +str(float(self.norm[1])) +  " " +str(float(self.norm[2])) +
		"\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) +  " " +str(float(self.pos[1])) +
		 " " +str(float(self.pos[2])) + "\n")

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
		"\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +
		 " " +str(float(self.rgb[2])) + "\n\t\tpos: " + str(float(self.pos[0])) +
		 " " +str(float(self.pos[1])) +  " " +str(float(self.pos[2])) + "\n\t\taxis: " +
		 " " +str(float(self.axis[0])) +  " " +str(float(self.axis[1])) +
		 " " +str(float(self.axis[2])) + "\n")


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
		"\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
		+ "\n\t\tpos: " + str(float(self.pos[0])) +  " " +str(float(self.pos[1])) +
		 " " +str(float(self.pos[2])) + "\n\t\taxis: " + str(float(self.axis[0])) +  " " +str(float(self.axis[1])) +
		 " " +str(float(self.axis[2])) + "\n")

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
			fichier.write("\tCUBE\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
			+ "\n\t\tpt1: " + str(float(self.pt1[0])) +  " " +str(float(self.pt1[1])) +
			 " " +str(float(self.pt1[2])) + "\n\t\tpt2: " + str(float(self.pt2[0])) +  " " +str(float(self.pt2[1])) +
			 " " +str(float(self.pt2[2])) + "\n")

class Triangle():
	def __init__(self, pt1, pt2, pt3, rgb):
		self.pt1 = pt1
		self.pt2 = pt2
		self.pt3 = pt3
		self.rgb = rgb
		try:
			for i in range (0,2):
				float(self.pt1[i])
				float(self.pt2[i])
				float(self.pt3[i])
				float(self.rgb[i])
		except ValueError:
			print "error in the trangle specification"
			exit()
		def write(self, fichier):
			fichier.write("\tCUBE\n\t\trgb: " + str(float(self.rgb[0])) +  " " +str(float(self.rgb[1])) +  " " +str(float(self.rgb[2]))
			+ "\n\t\tpt1: " + str(float(self.pt1[0])) +  " " +str(float(self.pt1[1])) +
			 " " +str(float(self.pt1[2])) + "\n\t\tpt2: " + str(float(self.pt2[0])) +  " " +str(float(self.pt2[1])) +
			 " " +str(float(self.pt2[2])) + "\n\t\tpt3: " + str(float(self.pt3[0])) +  " " +str(float(self.pt3[1])) +
			 " " +str(float(self.pt3[2])) + "\n")

class Cercle():
	def __init__(self, pos, dire, rgb, rad):
		self.pos = pos
		self.dir = dire
		self.rgb = rgb
		self.rad = rad
		try:
			for i in range (0,2):
				float(self.pos[i])
				float(self.rgb[i])
				float(self.dir[i])
			float(self.rad)
		except ValueError:
			print "Error in the Cercle specification"
			exit()
		def write(self, fichier):
			fichier.write("\tCERCLE\n\t\trgb: " + str(float(self.rgb[0])) + " " + str(float(self.rgb[1])) + " " + str(float(self.rgb[2]))
			+ "\n\t\tpos: " + str(float(self.pos[0])) + " " + str(float(self.pos[1])) + " " + str(float(self.pos[2])) + "\n\t\tdir: " +
			str(float(self.dir[0])) + " " + str(float(self.dir[1])) + " " + str(float(self.dir[2])) + "\n\t\trad: " + str(float(self.rad)) + "\n")

class Spotlight():
	def __init__(self, pos):
		self.pos = pos
		try:
			for i in range (0, 2):
				float(self.pos[i])
		except ValueError:
			print "Error in the Spotlight specification"
			exit()
	def write(self, fichier):
		fichier.write("\tSPOTLIGHT\n\t\tpos: " + str(float(self.pos[0])) + " " + str(float(self.pos[1]))
		+ " " + str(float(self.pos[2])) + "\n")
