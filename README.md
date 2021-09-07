<h1 align="center">THGEM Simulation Fe55 X-ray</h1>
<p align="center">This project simulates X-ray with Fe 55 characteristic gamma decay energy shooted to a one foil of THGEM detector inside a gas setup.</p>


* Gmsh and Elmer
run in the same folder starting with thgem.geo file
* Geant4:
interactionDensity/ and interactionDensity-build/. For more easily execution was created the meuScript.sh: changes to build folder add Geant4 software source, compile and run with/out visualization
* Garfield++
Garfield_simulation/ separated into two folders in order to transfer more easily to titanio cluster and run separately avalanches from: 
-primary X-ray electrons produced
-fluorescence electrons produced

