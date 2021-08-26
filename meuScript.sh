#!/bin/bash

#vai para a basta do código do Geant4
#cd ~/Documents/Simulação/Publication_Lucas/interactionDensity-build
cd interactionDensity-build/
source ~/Programas/Geant4/geant4.10.05.p01-install/bin/geant4.sh
cmake -DGeant4_DIR=~/Programas/Geant4/geant4.10.05.p01-install/lib/Geant4-10.5.1 ~/Documents/Simulação/Thgem_Fe55_X-ray/interactionDensity

echo "Compiling program"

make -j4

echo "Running main.exe"

#argument 1 = gas composition:
#	4 = ArCO2 (70/30)
#	5 = XeCO2
#argument 2 = run mode (e.g. *(argv[2])=='1' execute vis.mac)
#	1 = execute vis.mac
#	!1 = without visualization
./main 4 2

echo "End of Geant4 execution"


