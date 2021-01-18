## Introduction
Ce document précise l'utilité des fichiers fournis en entrée pour un chargement en masse d'informations.
Il existe deux (02) fichiers d'entrée
# infra
Ce fichier permet de charger des informations de toute une infrastructure physique (noeuds et liens physiques inclus).
- Nomenclature générale --> NODES=<informations_noeud 1>[...<informations_noeud n>]LINKS=<informations_lien 1>[...<informations_lien n>]
- Nomenclature <informations_noeud x> --> <node_id>:<disk_capacity>,<ram>,<cpu>,<cost>,;
	++ Représentation d'un noeud 0, d'une capacité mémoire de 1000GB, d'une ram de 5GB, d'un processeur d'une fréquence de 10GHz et d'un coût de 3 --> 0:1000,5,10,3,;
	++ Suivre la même nomenclature pour autant de noeuds qu'il faut et ajouter les entrées les unes à la suite des autres
	++ Exemple d'une représentation de 2 noeuds --> 0:1000,5,10,3,;1:1500,4,10,2,;
- Nomenclature <informations_lien x> --> (<src_node_id>,<dest_node_id>):<bandwidth>,<delay>,<cost>,;
	++ Représentation d'un lien entre les noeuds 0 et 1, d'une bande passante de 50Mbps, d'un délai de 10ms et d'un coût de 3 --> (0,1):50,10,3,;
	++ Suivre la même nomenclature pour autant de liens physiques qu'il faut et ajouter les entrées les unes à la suite des autres
	++ Exemple d'une représentation de 2 liens physiques --> (0,1):50,10,3,;(0,2):20,5,1,;
- Exemple Entrée Fichier infra --> NODES=0:1000,5,10,3,;1:1500,4,10,2,;2:1000,5,10,3,;LINKS=(0,1):50,10,3,;(0,2):20,5,1,;


# requests
Ce fichier permet de charger des informations liées aux requêtes de chaînes de services (des VNC formées de VNF et de liens virtuels) à traiter.
- Nomenclature générale --> VNF=<informations_vnf 1>[...<informations_vnf n>]VLINKS=<informations_lien 1>[...<informations_lien n>]
- Nomenclature <informations_vnf x> --> <vnf_id>:<description>,<cpu>,<ram>,<disk_capacity>,;
	++ Représentation d'une vnf 0 décrite par 'VNF0', et ayant un cpu de 3Ghz, d'une ram de 5GB et d'une capacité de stockage de 500GB --> 0:VNF0,3,5,500,;
	++ Suivre la même nomenclature pour autant de vnf qu'il faut et ajouter les entrées les unes à la suite des autres
	++ Exemple d'une représentation de 2 vnf --> 0:VNF0,3,5,500,;1:VNF1,5,4,175,;
- Nomenclature <informations_lien x> --> (<src_vnf_id>,<dest_vnf_id>):<bandwidth>,<latency>,;
	++ Représentation d'un lien entre les vnf 0 et 1, d'une bande passante de 15Mbps et d'une latence de 3ms --> (0,1):15,3,;
	++ Suivre la même nomenclature pour autant de liens virtuels qu'il faut et ajouter les entrées les unes à la suite des autres
	++ Exemple d'une représentation de 2 liens virtuels --> (0,1):15,3,;(0,2):30,5,;
- Exemple Entrée Ligne Fichier requests --> VNF=0:VNF0,3,5,500,;1:VNF1,5,4,175,;2:VNF2,3,5,200,;VLINKS=(0,1):15,3,;(0,2):30,5,;
- Rajouter autant de lignes que nécessaire pour la prise en compte de plusieurs requêtes
