from sympy.combinatorics.prufer import Prufer

def decodage_prufer(sequencePrufer):

	i = 0
	for number in sequencePrufer:
		#On doit diminuer de 1 chaque nombre dans la suite de Prüfer car il faut un noeud de label 0
		sequencePrufer[i] = sequencePrufer[i] - 1
		i+=1

	list = Prufer(sequencePrufer).tree_repr

	i = 0
	j = 0
	for arc in list:
		j = 0
		for sommet in arc:
			#On doit augmenter l'index de chaque sommet de chaque arc car on a diminué de 1 avant le calcul.
			list[i][j] = list[i][j] + 1
			j+=1
		i+=1

	return list
