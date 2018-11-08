/*
Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como
argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el
"grupo" y para "otros". Además del nombre de los archivos encontrados, deberá devolver sus números de inodo
y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
		$> ./buscar <pathname>
donde <pathname> especifica la ruta del directorio a partir del cual queremos que empiece a analizar la
estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida
el directorio actual.
*/
