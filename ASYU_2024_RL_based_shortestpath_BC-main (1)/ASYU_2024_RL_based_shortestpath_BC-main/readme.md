# ASYU_2024_RL_based_shortestpath_BC

Using reinforcement learning to find the shortest paths.

## Requirements

- numpy
- networkx



Training: 
shortest_path.py
Sizden gelen file, buna dokunmaidm diye biliyorum. File icinden degistimeniz lazim farkli graphlari icin, birkac tane comment biraktim hangi txt filelari okutmak gerektigini)

deep_rl_shortest.py + run_sim.py
bu ikisi deep rl icin filelar. Ilki train ediyor, ikincisi simulation run edip resultlari cikartiyor. Maalesef buda otomatik degil, yani txt fillari ve isimleri manual degistirmek gerek. 


Plotting: (bunlar otomatik, tek yapmak gereken sey directorylerden emin olup run etmek, asigda ornekleri var) 

Exec_t_figure.py {link factor} {network name}

ex run: 
$ python3 Exec_t_figure.py d_bw NSF

Perc_RS_figure.py {link factor} {network name}

ex run: 
$ python3 Exec_t_figure.py bw US


baska yardimci filelar: 

metric_eval, verilen iki result.txt filelari karsilastiriyor.ister mean ister median. Biz Mediani daha cok kullandik, outlierlar cok etkilemesin diye. 
