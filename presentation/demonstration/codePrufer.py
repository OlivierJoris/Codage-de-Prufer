from sympy.combinatorics.prufer import Prufer

def codage_prufer(listeArcs):
	i = 0
	j = 0
	for arc in listeArcs:
		j = 0
		for sommet in arc:
			#On doit diminuer l'index de chaque sommet de 1 car il faut un noeud d'index 0.
			listeArcs[i][j] = listeArcs[i][j] - 1
			j+=1
		i+=1

	codage = Prufer(listeArcs).prufer_repr

	indiceCodage = 0

	#On diminue les index de 1 avant de 'calculer' la séquence de Prüfer
	#donc on doit augmenter de 1 chaque nombre de la sequence pour compenser.
	for i in range (0, len(codage)):
		codage[i] = codage[i] + 1

	return codage

def affiche_codage(SequenceCodage):

	print(SequenceCodage)
